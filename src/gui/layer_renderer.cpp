#include "gui/layer_renderer.hpp"

#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QPoint>
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <limits>
#include <mutex>
#include <unordered_map>

namespace {

constexpr double kDrawCallOverheadMs = 0.012;
constexpr size_t kMaxPreviewDrawVertices = 500'000;
constexpr size_t kMaxDrawSamples = 20;
constexpr float kStreamViewResetDistance = 25.0f;

// Analytic ray-traced sphere impostors. Each point is a screen-aligned point
// sprite sized to the sphere's perspective silhouette; the fragment shader casts
// an eye-space ray, intersects the analytic sphere, and writes the exact depth
// and surface normal. This keeps the one-vertex-per-point fast path while giving
// geometrically correct spheres of the requested world-space radius.
const char* kPointVertexShader = R"(
    #version 330 core
    in vec3 local_position;
    in float intensity;
    in float classification;
    in vec3 file_color;
    in float has_file_rgb;
    uniform float point_radius_m;   // world-space sphere radius (metres)
    uniform float viewport_height;  // framebuffer height in pixels
    uniform float fov_rad;          // vertical field of view (radians)
    uniform mat4 u_view;
    uniform mat4 u_proj;
    uniform vec3 point_offset;
    uniform int color_mode;
    uniform vec3 fixed_color;
    uniform float point_alpha;
    uniform int classification_mask[8];
    out vec4 vtx_color;
    out vec3 eye_center;            // sphere centre in eye space
    out float eye_radius;

    vec3 classification_color(int class_id) {
        if (class_id == 2) return vec3(160.0, 120.0, 80.0) / 255.0;
        if (class_id == 3) return vec3(100.0, 180.0, 100.0) / 255.0;
        if (class_id == 4) return vec3(60.0, 140.0, 60.0) / 255.0;
        if (class_id == 5) return vec3(30.0, 100.0, 30.0) / 255.0;
        if (class_id == 6) return vec3(200.0, 80.0, 80.0) / 255.0;
        if (class_id == 7) return vec3(120.0, 120.0, 120.0) / 255.0;
        if (class_id == 8) return vec3(255.0, 200.0, 0.0) / 255.0;
        if (class_id == 9) return vec3(60.0, 120.0, 220.0) / 255.0;
        if (class_id == 17) return vec3(180.0, 180.0, 180.0) / 255.0;
        return vec3(200.0, 200.0, 200.0) / 255.0;
    }

    void main() {
        int class_id = int(classification + 0.5);
        if (class_id >= 0 && class_id < 256) {
            int idx = class_id / 32;
            int bit = class_id % 32;
            if (((classification_mask[idx] >> bit) & 1) == 0) {
                gl_Position = vec4(9999.0, 9999.0, 9999.0, 1.0);
                return;
            }
        }

        vec3 position = local_position + point_offset;
        vec4 eye = u_view * vec4(position, 1.0);
        eye_center = eye.xyz;
        eye_radius = point_radius_m;

        vec3 rgb = fixed_color;
        if (color_mode == 0) {
            if (has_file_rgb > 0.5) {
                rgb = file_color;
            } else {
                rgb = vec3(intensity);
            }
        } else if (color_mode == 1) {
            rgb = classification_color(int(classification + 0.5));
        }
        vtx_color = vec4(rgb, point_alpha);

        gl_Position = u_proj * eye;
        // Sprite diameter in pixels = 2 * R * focal_length / depth.
        float depth = max(-eye.z, 1e-4);
        float proj_scale = viewport_height / (2.0 * tan(fov_rad * 0.5));
        gl_PointSize = clamp(2.0 * point_radius_m * proj_scale / depth, 1.0, 4096.0);
    }
)";

const char* kPointFragmentShader = R"(
    #version 330 core
    in vec4 vtx_color;
    in vec3 eye_center;
    in float eye_radius;
    uniform mat4 u_proj;
    out vec4 fragColor;
    void main() {
        // Reconstruct the eye-space ray through this fragment. The sprite spans
        // the sphere's silhouette: UV in [-1,1] maps to a lateral offset of
        // R metres on the tangent plane at the sphere's depth.
        vec2 uv = gl_PointCoord * 2.0 - 1.0;
        uv.y = -uv.y;
        vec3 ray_dir = normalize(vec3(eye_center.xy + uv * eye_radius, eye_center.z));

        // Ray from the eye (origin) vs analytic sphere: |t*dir - center|^2 = r^2.
        float b = dot(ray_dir, eye_center);
        float c = dot(eye_center, eye_center) - eye_radius * eye_radius;
        float disc = b * b - c;
        if (disc < 0.0) discard;
        float t = b - sqrt(disc);
        vec3 hit = ray_dir * t;              // eye-space surface point
        vec3 normal = normalize(hit - eye_center);

        // Exact, projection-correct depth so spheres interlock without z-fighting.
        vec4 clip = u_proj * vec4(hit, 1.0);
        gl_FragDepth = 0.5 * (clip.z / clip.w) + 0.5;

        // Eye-space lighting stays consistent as the camera orbits.
        vec3 light_dir = normalize(vec3(0.3, 0.5, 0.8));
        float lighting = 0.4 + 0.6 * max(dot(normal, light_dir), 0.0);
        fragColor = vec4(vtx_color.rgb * lighting, 1.0);
    }
)";

const char* kMeshVertexShader = R"(
    #version 330 core
    in vec3 position;
    in vec3 color;
    uniform mat4 proj_matrix;
    out vec3 vtx_color;
    out vec3 vtx_world_pos;
    void main() {
        vtx_color = color;
        vtx_world_pos = position;
        gl_Position = proj_matrix * vec4(position, 1.0);
    }
)";

const char* kMeshFragmentShader = R"(
    #version 330 core
    in vec3 vtx_color;
    in vec3 vtx_world_pos;
    out vec4 fragColor;
    void main() {
        vec3 dx = dFdx(vtx_world_pos);
        vec3 dy = dFdy(vtx_world_pos);
        vec3 n = normalize(cross(dx, dy));
        if (!gl_FrontFacing) {
            n = -n;
        }
        vec3 light_dir = normalize(vec3(0.65, 0.35, 0.67));
        float diffuse = clamp(dot(n, light_dir), 0.0, 1.0);
        float lighting = mix(0.45, 1.1, diffuse);
        fragColor = vec4(vtx_color * lighting, 0.92);
    }
)";

const char* kTexturedMeshVertexShader = R"(
    #version 330 core
    in vec3 position;
    in vec2 texcoord;
    uniform mat4 proj_matrix;
    out vec2 vtx_texcoord;
    out vec3 vtx_world_pos;
    void main() {
        vtx_texcoord = texcoord;
        vtx_world_pos = position;
        gl_Position = proj_matrix * vec4(position, 1.0);
    }
)";

const char* kTexturedMeshFragmentShader = R"(
    #version 330 core
    in vec2 vtx_texcoord;
    in vec3 vtx_world_pos;
    uniform sampler2D dem_texture;
    out vec4 fragColor;
    void main() {
        vec3 color = texture(dem_texture, vtx_texcoord).rgb;
        vec3 dx = dFdx(vtx_world_pos);
        vec3 dy = dFdy(vtx_world_pos);
        vec3 n = normalize(cross(dx, dy));
        if (!gl_FrontFacing) {
            n = -n;
        }
        vec3 light_dir = normalize(vec3(0.65, 0.35, 0.67));
        float diffuse = clamp(dot(n, light_dir), 0.0, 1.0);
        float lighting = mix(0.45, 1.1, diffuse);
        fragColor = vec4(color * lighting, 0.95);
    }
)";

const char* kCrosshairLineVertexShader = R"(
    #version 330 core
    in vec3 position;
    uniform mat4 proj_matrix;
    void main() {
        gl_Position = proj_matrix * vec4(position, 1.0);
    }
)";

const char* kCrosshairLineFragmentShader = R"(
    #version 330 core
    uniform vec3 line_color;
    out vec4 fragColor;
    void main() {
        fragColor = vec4(line_color, 1.0);
    }
)";

bool bind_shader(QOpenGLShaderProgram* shader) {
  if (!shader->bind()) {
    std::cout << "Shader bind error: " << shader->log().toStdString() << std::endl;
    return false;
  }
  return true;
}

}  // namespace

std::unique_ptr<LayerRenderer> LayerRenderer::create(std::shared_ptr<Layer> layer,
                                                     const Coordinate3D<double>& offset) {
  if (auto las_layer = std::dynamic_pointer_cast<LASLayer>(layer)) {
    return std::make_unique<OctreeLASLayerRenderer>(las_layer, offset);
  }
  if (auto dem_layer = std::dynamic_pointer_cast<DemLayer>(layer)) {
    return std::make_unique<MeshLayerRenderer>(
        [dem_layer]() -> const AsyncRasterData* { return &dem_layer->raster(); }, offset);
  }
  if (auto slope_layer = std::dynamic_pointer_cast<SlopeLayer>(layer)) {
    return std::make_unique<MeshLayerRenderer>(
        [slope_layer]() -> const AsyncRasterData* { return &slope_layer->raster(); }, offset);
  }
  if (auto textured_layer = std::dynamic_pointer_cast<TexturedDemLayer>(layer)) {
    return std::make_unique<MeshLayerRenderer>(
        [textured_layer]() -> const AsyncRasterData* { return &textured_layer->raster(); }, offset,
        true);
  }
  if (auto contour_layer = std::dynamic_pointer_cast<ContourLayer>(layer)) {
    return std::make_unique<ContourLayerRenderer>(contour_layer, offset);
  }
  return nullptr;
}

OctreeLASLayerRenderer::OctreeLASLayerRenderer(std::shared_ptr<LASLayer> layer,
                                               const Coordinate3D<double>& /*offset*/)
    : m_layer(layer) {}

void OctreeLASLayerRenderer::ensure_shader() {
  if (m_shader) {
    return;
  }
  m_shader = std::make_unique<QOpenGLShaderProgram>();
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, kPointVertexShader) ||
      !m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, kPointFragmentShader)) {
    std::cout << "Point shader error: " << m_shader->log().toStdString() << std::endl;
    m_shader.reset();
    return;
  }
  m_shader->bindAttributeLocation("local_position", 0);
  m_shader->bindAttributeLocation("intensity", 1);
  m_shader->bindAttributeLocation("classification", 2);
  m_shader->bindAttributeLocation("file_color", 3);
  m_shader->bindAttributeLocation("has_file_rgb", 4);
  if (!m_shader->link()) {
    std::cout << "Point shader link error: " << m_shader->log().toStdString() << std::endl;
    m_shader.reset();
    return;
  }
  m_view_matrix_loc = m_shader->uniformLocation("u_view");
  m_proj_matrix_loc = m_shader->uniformLocation("u_proj");
  m_point_radius_loc = m_shader->uniformLocation("point_radius_m");
  m_viewport_height_loc = m_shader->uniformLocation("viewport_height");
  m_fov_rad_loc = m_shader->uniformLocation("fov_rad");
  m_color_mode_loc = m_shader->uniformLocation("color_mode");
  m_fixed_color_loc = m_shader->uniformLocation("fixed_color");
  m_point_alpha_loc = m_shader->uniformLocation("point_alpha");
  m_point_offset_loc = m_shader->uniformLocation("point_offset");
  m_classification_mask_loc = m_shader->uniformLocation("classification_mask");
}

void OctreeLASLayerRenderer::ensure_crosshair_shader() {
  if (m_crosshair_shader) {
    return;
  }
  m_crosshair_shader = std::make_unique<QOpenGLShaderProgram>();
  if (!m_crosshair_shader->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                                   kCrosshairLineVertexShader) ||
      !m_crosshair_shader->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                                   kCrosshairLineFragmentShader)) {
    std::cout << "Crosshair shader error: " << m_crosshair_shader->log().toStdString() << std::endl;
    m_crosshair_shader.reset();
    return;
  }
  m_crosshair_shader->bindAttributeLocation("position", 0);
  if (!m_crosshair_shader->link()) {
    std::cout << "Crosshair shader link error: " << m_crosshair_shader->log().toStdString()
              << std::endl;
    m_crosshair_shader.reset();
    return;
  }
  m_crosshair_proj_loc = m_crosshair_shader->uniformLocation("proj_matrix");
  m_crosshair_color_loc = m_crosshair_shader->uniformLocation("line_color");
}

void OctreeLASLayerRenderer::reset_stream_cache() {
  m_node_stream.clear();
  m_stream_backlog = false;
}

void OctreeLASLayerRenderer::refresh_after_style_change() {
  m_node_stream.clear();
  m_stream_backlog = true;
  m_lod_query_vertices = 0;
  m_draw_samples.clear();
}

size_t OctreeLASLayerRenderer::visible_nodes_fingerprint(
    const std::vector<PointOctree::VisibleNode>& visible_nodes) const {
  size_t fingerprint = visible_nodes.size();
  for (const auto& visible : visible_nodes) {
    fingerprint ^= std::hash<const void*>{}(visible.node) + 0x9e3779b9 + (fingerprint << 6) +
                   (fingerprint >> 2);
  }
  return fingerprint;
}

bool OctreeLASLayerRenderer::stream_camera_changed(const Camera& camera) const {
  if ((camera.position() - m_stream_camera_pos).lengthSquared() >
      kStreamViewResetDistance * kStreamViewResetDistance) {
    return true;
  }
  if ((camera.direction() - m_stream_camera_dir).lengthSquared() > 0.01f) {
    return true;
  }
  return false;
}

bool OctreeLASLayerRenderer::visible_set_changed(
    const std::vector<PointOctree::VisibleNode>& visible_nodes) const {
  return visible_nodes_fingerprint(visible_nodes) != m_visible_fingerprint;
}

void OctreeLASLayerRenderer::sort_visible_by_lod(
    std::vector<PointOctree::VisibleNode>& visible_nodes) {
  if (visible_nodes.size() <= 1) {
    return;
  }
  const bool needs_sort =
      std::adjacent_find(visible_nodes.begin(), visible_nodes.end(),
                         [](const PointOctree::VisibleNode& a, const PointOctree::VisibleNode& b) {
                           return a.lod_distance > b.lod_distance;
                         }) != visible_nodes.end();
  if (!needs_sort) {
    return;
  }
  std::stable_sort(visible_nodes.begin(), visible_nodes.end(),
                   [](const PointOctree::VisibleNode& a, const PointOctree::VisibleNode& b) {
                     if (a.lod_distance != b.lod_distance) {
                       return a.lod_distance < b.lod_distance;
                     }
                     return a.node < b.node;
                   });
}

void OctreeLASLayerRenderer::collect_visible_octree_nodes(
    const LasRenderSnapshot& snap, const Camera& camera, double vis_quality,
    const Coordinate3D<double>& file_origin,
    std::vector<PointOctree::VisibleNode>& visible_nodes) const {
  const Frustum frustum = Frustum::from_matrix(camera.proj_matrix());
  const Coordinate3D<double> camera_local(camera.position().x(), camera.position().y(),
                                          camera.position().z());
  snap.octree.collect_visible(frustum, camera.projection_scale(), vis_quality,
                              camera.world_offset(), file_origin, camera_local, visible_nodes);
  sort_visible_by_lod(visible_nodes);
}

size_t OctreeLASLayerRenderer::estimate_draw_vertices(
    const std::vector<PointOctree::VisibleNode>& visible_nodes, double quality,
    bool incremental) const {
  size_t total = 0;
  for (const auto& visible : visible_nodes) {
    if (!visible.node || visible.node->point_count() == 0) {
      continue;
    }
    const size_t point_count = visible.node->point_count();
    const size_t chunk_size =
        PointOctree::node_draw_chunk_size(point_count, visible.lod_distance, quality);
    if (incremental) {
      const auto it = m_node_stream.find(visible.node);
      const size_t streamed =
          it != m_node_stream.end() ? std::min(it->second.streamed_count, point_count) : 0;
      if (streamed >= point_count) {
        continue;
      }
      total += std::min(chunk_size, point_count - streamed);
    } else {
      total += std::min(chunk_size, point_count);
    }
  }
  return total;
}

double OctreeLASLayerRenderer::select_draw_quality(
    const std::vector<PointOctree::VisibleNode>& visible_nodes, bool incremental,
    bool lod_base_from_incremental, double target_draw_ms) const {
  const double base = lod_base_from_incremental ? m_inc_lod_quality : m_lod_quality;
  constexpr int num_samples = 4;
  const double qualities[num_samples] = {base / 20.0, base / 4.0, base, base * 4.0};
  double frame_time_est[num_samples] = {0};
  for (int i = 0; i < num_samples; ++i) {
    const size_t vertices = estimate_draw_vertices(visible_nodes, qualities[i], incremental);
    frame_time_est[i] = static_cast<double>(vertices) * m_ms_per_vertex +
                        (vertices > 0 ? kDrawCallOverheadMs : 0.0);
  }

  double quality = base;
  if (target_draw_ms <= frame_time_est[0]) {
    quality = qualities[0];
  } else if (target_draw_ms >= frame_time_est[num_samples - 1]) {
    quality = qualities[num_samples - 1];
  } else {
    int i = 0;
    while (i < num_samples - 2 && frame_time_est[i + 1] < target_draw_ms) {
      ++i;
    }
    const double denom = frame_time_est[i + 1] - frame_time_est[i];
    const double interp = denom > 0.0 ? (target_draw_ms - frame_time_est[i]) / denom : 0.0;
    quality = (1.0 - interp) * qualities[i] + interp * qualities[i + 1];
  }
  return std::clamp(quality, 0.05, 64.0);
}

void OctreeLASLayerRenderer::record_lod_sample(size_t vertices, double ms) {
  if (vertices == 0 || ms <= 0.0) {
    return;
  }
  m_draw_samples.push_back({vertices, ms});
  while (m_draw_samples.size() > kMaxDrawSamples) {
    m_draw_samples.pop_front();
  }

  double weighted_vertices = 0.0;
  double weighted_ms = 0.0;
  double weight_sum = 0.0;
  const size_t count = m_draw_samples.size();
  for (size_t i = 0; i < count; ++i) {
    const double weight = std::exp(-0.2 * static_cast<double>(count - 1 - i));
    weighted_vertices += weight * static_cast<double>(m_draw_samples[i].vertices);
    weighted_ms += weight * m_draw_samples[i].ms;
    weight_sum += weight;
  }
  if (weighted_vertices > 0.0 && weight_sum > 0.0) {
    m_ms_per_vertex = weighted_ms / weighted_vertices;
  }
}

void OctreeLASLayerRenderer::ensure_gpu_timer(QOpenGLExtraFunctions* gl) {
  if (m_gpu_timer_query != 0 || !gl) {
    return;
  }
  gl->glGenQueries(1, &m_gpu_timer_query);
}

void OctreeLASLayerRenderer::consume_gpu_timer_sample(QOpenGLExtraFunctions* gl) {
  if (!gl || m_gpu_timer_query == 0 || m_lod_query_vertices == 0) {
    return;
  }

  GLuint available = 0;
  gl->glGetQueryObjectuiv(m_gpu_timer_query, GL_QUERY_RESULT_AVAILABLE, &available);
  if (!available) {
    return;
  }

  GLuint elapsed_ns = 0;
  gl->glGetQueryObjectuiv(m_gpu_timer_query, GL_QUERY_RESULT, &elapsed_ns);
  const double gpu_ms = static_cast<double>(elapsed_ns) / 1'000'000.0;
  m_last_point_gpu_ms = gpu_ms;
  record_lod_sample(m_lod_query_vertices, gpu_ms);
}

void OctreeLASLayerRenderer::begin_gpu_timer(QOpenGLExtraFunctions* gl) {
  if (!gl || m_gpu_timer_query == 0) {
    return;
  }
  gl->glBeginQuery(GL_TIME_ELAPSED, m_gpu_timer_query);
}

void OctreeLASLayerRenderer::end_gpu_timer(QOpenGLExtraFunctions* gl, size_t vertices_drawn) {
  if (!gl || m_gpu_timer_query == 0) {
    return;
  }
  gl->glEndQuery(GL_TIME_ELAPSED);
  m_lod_query_vertices = vertices_drawn;
}

size_t OctreeLASLayerRenderer::draw_octree_nodes(
    QOpenGLFunctions* f, const std::vector<OctreePoint>& point_storage,
    const std::vector<PointOctree::VisibleNode>& visible_nodes,
    const Coordinate3D<double>& file_origin, const Coordinate3D<double>& scene_offset,
    double quality, bool incremental) {
  m_stream_backlog = false;

  if (!m_shader) {
    return 0;
  }
  m_point_gl.ensure_initialized(f);
  m_point_gl.bind(f);

  const QVector3D point_offset(static_cast<float>(file_origin.x() - scene_offset.x()),
                               static_cast<float>(file_origin.y() - scene_offset.y()),
                               static_cast<float>(file_origin.z() - scene_offset.z()));
  m_shader->setUniformValue(m_point_offset_loc, point_offset);

  // Upload entire point cloud to GPU once; subsequent frames draw sub-ranges.
  if (!m_points_uploaded && !point_storage.empty()) {
    m_point_gl.upload_points(f, point_storage.data(), point_storage.size());
    m_points_uploaded = true;
  }

  if (!incremental) {
    for (const auto& visible : visible_nodes) {
      if (!visible.node) continue;
      NodeStreamState& state = m_node_stream[visible.node];
      state.point_count = visible.node->point_count();
      state.streamed_count = 0;
      state.locked_chunk_size = 0;
    }
  }

  m_firsts.clear();
  m_counts.clear();

  for (const auto& visible : visible_nodes) {
    if (!visible.node || visible.node->point_count() == 0) continue;
    const PointOctreeNode* node = visible.node;
    const size_t point_count = node->point_count();

    NodeStreamState& state = m_node_stream[node];
    if (state.point_count != point_count) {
      state.point_count = point_count;
      state.streamed_count = 0;
    }

    const size_t chunk_size =
        PointOctree::node_draw_chunk_size(point_count, visible.lod_distance, quality);
    if (state.locked_chunk_size == 0) state.locked_chunk_size = chunk_size;

    size_t to_draw = 0;
    if (incremental) {
      if (state.streamed_count >= point_count) continue;
      to_draw = std::min(state.locked_chunk_size, point_count - state.streamed_count);
    } else {
      to_draw = std::min(state.locked_chunk_size, point_count);
    }
    if (to_draw == 0) continue;

    m_firsts.push_back(static_cast<GLint>(node->begin_index + state.streamed_count));
    m_counts.push_back(static_cast<GLsizei>(to_draw));

    if (incremental) state.streamed_count += to_draw;
    if (state.streamed_count < point_count) m_stream_backlog = true;
  }

  return m_point_gl.draw_leaves(f, m_firsts.data(), m_counts.data(), m_firsts.size());
}

size_t OctreeLASLayerRenderer::draw_preview_points(QOpenGLFunctions* f,
                                                   const std::vector<OctreePoint>& preview,
                                                   const Coordinate3D<double>& file_origin,
                                                   const Coordinate3D<double>& scene_offset) {
  if (preview.empty() || !m_shader) {
    return 0;
  }

  m_point_gl.ensure_initialized(f);
  m_point_gl.bind(f);

  const size_t count = std::min(preview.size(), kMaxPreviewDrawVertices);
  const QVector3D point_offset(static_cast<float>(file_origin.x() - scene_offset.x()),
                               static_cast<float>(file_origin.y() - scene_offset.y()),
                               static_cast<float>(file_origin.z() - scene_offset.z()));
  m_shader->setUniformValue(m_point_offset_loc, point_offset);

  const size_t total_vertices = m_point_gl.draw_points(f, preview.data(), count);
  m_stream_backlog = preview.size() > count;
  return total_vertices;
}

std::optional<PointPickResult> OctreeLASLayerRenderer::pick_point(const Camera& camera,
                                                                  const QPoint& pixel) const {
  auto layer = m_layer.lock();
  if (!layer || !m_visible) {
    return std::nullopt;
  }

  std::vector<PointOctree::VisibleNode> visible_nodes;
  const Coordinate3D<double>& scene_offset = camera.world_offset();
  const Coordinate3D<double>& file_origin = layer->las_data().coordinate_origin();
  const std::vector<OctreePoint>* point_storage = nullptr;

  const auto snap = layer->las_data().snapshot();
  if (!snap || snap->octree.total_points() == 0) {
    return std::nullopt;
  }
  point_storage = &snap->octree.points();

  collect_visible_octree_nodes(*snap, camera, std::max(m_lod_quality, 1.0), file_origin,
                               visible_nodes);

  if (visible_nodes.empty()) {
    return std::nullopt;
  }

  const QMatrix4x4 proj = camera.proj_matrix();
  const float pick_x = static_cast<float>(pixel.x());
  const float pick_y = static_cast<float>(pixel.y());
  const float pick_radius = std::max(
      8.0f, static_cast<float>(layer->point_radius_m() * camera.projection_scale() * 0.35));
  const float pick_radius_sq = pick_radius * pick_radius;

  struct NodeScreenDistance {
    const PointOctreeNode* node = nullptr;
    float screen_dist_sq = 0.0f;
  };

  std::vector<NodeScreenDistance> node_candidates;
  node_candidates.reserve(visible_nodes.size());
  for (const auto& visible : visible_nodes) {
    if (!visible.node || visible.node->point_count() == 0) {
      continue;
    }
    const Extent3D& bounds = visible.node->bounds;
    const double cx = 0.5 * (bounds.minx + bounds.maxx) + file_origin.x() - scene_offset.x();
    const double cy = 0.5 * (bounds.miny + bounds.maxy) + file_origin.y() - scene_offset.y();
    const double cz = 0.5 * (bounds.minz + bounds.maxz) + file_origin.z() - scene_offset.z();
    const QVector4D clip = proj * QVector4D(static_cast<float>(cx), static_cast<float>(cy),
                                            static_cast<float>(cz), 1.0f);
    if (clip.w() <= 0.0f) {
      continue;
    }
    const float inv_w = 1.0f / clip.w();
    const float screen_x = (clip.x() * inv_w * 0.5f + 0.5f) * camera.screen_width();
    const float screen_y = (1.0f - (clip.y() * inv_w * 0.5f + 0.5f)) * camera.screen_height();
    const float dx = screen_x - pick_x;
    const float dy = screen_y - pick_y;
    node_candidates.push_back({visible.node, dx * dx + dy * dy});
  }

  std::sort(node_candidates.begin(), node_candidates.end(),
            [](const NodeScreenDistance& a, const NodeScreenDistance& b) {
              return a.screen_dist_sq < b.screen_dist_sq;
            });

  const size_t max_nodes = std::min(node_candidates.size(), size_t{256});

  // Two-tier selection that matches what the user sees:
  //  1. "Cover" hits: the cursor lies within a point's rendered sphere disc.
  //     Among these, pick the front-most (nearest eye depth) — i.e. the sphere
  //     drawn on top — which is the occlusion-correct, intuitive choice.
  //  2. Fallback: if no sphere covers the cursor (tiny/distant points), pick the
  //     nearest one within the pixel tolerance so points stay clickable.
  const float point_radius_px =
      static_cast<float>(layer->point_radius_m() * camera.projection_scale());

  float best_cover_eye_w = std::numeric_limits<float>::infinity();
  std::optional<PointPickResult> best_cover;
  float best_fallback_dist_sq = pick_radius_sq;
  std::optional<PointPickResult> best_fallback;

  auto make_result = [&](const OctreePoint& point, float wx, float wy, float wz) {
    PointPickResult result;
    result.point = point;
    result.world_x = wx;
    result.world_y = wy;
    result.world_z = wz;
    result.layer_name = layer->name();
    return result;
  };

  for (size_t n = 0; n < max_nodes; ++n) {
    const PointOctreeNode* node = node_candidates[n].node;
    if (!node) {
      continue;
    }
    for (size_t pi = node->begin_index; pi < node->end_index; ++pi) {
      const OctreePoint& point = (*point_storage)[pi];
      if (!layer->classification_enabled()[point.classification]) {
        continue;
      }
      const float wx =
          static_cast<float>(static_cast<double>(point.x) + file_origin.x() - scene_offset.x());
      const float wy =
          static_cast<float>(static_cast<double>(point.y) + file_origin.y() - scene_offset.y());
      const float wz =
          static_cast<float>(static_cast<double>(point.z) + file_origin.z() - scene_offset.z());
      const QVector4D clip = proj * QVector4D(wx, wy, wz, 1.0f);
      if (clip.w() <= 0.0f) {
        continue;
      }
      const float inv_w = 1.0f / clip.w();
      const float ndc_x = clip.x() * inv_w;
      const float ndc_y = clip.y() * inv_w;
      if (ndc_x < -1.05f || ndc_x > 1.05f || ndc_y < -1.05f || ndc_y > 1.05f) {
        continue;
      }
      const float screen_x = (ndc_x * 0.5f + 0.5f) * camera.screen_width();
      const float screen_y = (1.0f - (ndc_y * 0.5f + 0.5f)) * camera.screen_height();
      const float dx = screen_x - pick_x;
      const float dy = screen_y - pick_y;
      const float screen_dist_sq = dx * dx + dy * dy;

      // clip.w() is the eye-space depth (distance along the view axis); smaller
      // is closer to the camera. The point's on-screen radius matches the
      // rendered sphere: r_px = R * projection_scale / depth.
      const float eye_w = clip.w();
      const float proj_radius_px = point_radius_px * inv_w;
      const float proj_radius_sq = proj_radius_px * proj_radius_px;

      if (screen_dist_sq <= proj_radius_sq) {
        if (eye_w < best_cover_eye_w) {
          best_cover_eye_w = eye_w;
          best_cover = make_result(point, wx, wy, wz);
        }
      }
      if (!best_cover && screen_dist_sq <= best_fallback_dist_sq) {
        best_fallback_dist_sq = screen_dist_sq;
        best_fallback = make_result(point, wx, wy, wz);
      }
    }
  }

  return best_cover ? best_cover : best_fallback;
}

void OctreeLASLayerRenderer::set_highlight(const std::optional<PointPickResult>& pick) {
  auto layer = m_layer.lock();
  if (!pick || !layer || pick->layer_name != layer->name()) {
    m_highlight.reset();
    return;
  }
  m_highlight = pick;
}

void OctreeLASLayerRenderer::render_selection_highlight(const Camera& camera,
                                                        const RenderContext& ctx) {
  (void)ctx;
  auto layer = m_layer.lock();
  if (!m_highlight || !layer || !m_visible) {
    return;
  }

  ensure_crosshair_shader();
  if (!m_crosshair_shader) {
    return;
  }

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  if (!f) {
    return;
  }

  const float cx = static_cast<float>(m_highlight->world_x);
  const float cy = static_cast<float>(m_highlight->world_y);
  const float cz = static_cast<float>(m_highlight->world_z);

  // Screen-facing crosshair with a gap at the centre so the selected point stays
  // visible inside the marker. Sized in world units relative to the view distance.
  const float view_distance = std::max(static_cast<float>(camera.direction().length()), 0.1f);
  const float arm = std::max(0.25f, view_distance * 0.022f);
  const float gap = arm * 0.32f;
  const QVector3D view_dir = camera.direction().normalized();
  QVector3D right = QVector3D::crossProduct(camera.up(), view_dir);
  if (right.lengthSquared() < 1e-8f) {
    right = camera.view_right();
  } else {
    right.normalize();
  }
  const QVector3D up = QVector3D::crossProduct(view_dir, right).normalized();

  auto seg = [&](const QVector3D& dir, float inner, float outer, std::array<float, 6>& out) {
    out = {cx + dir.x() * inner, cy + dir.y() * inner, cz + dir.z() * inner,
           cx + dir.x() * outer, cy + dir.y() * outer, cz + dir.z() * outer};
  };
  std::array<float, 6> s0, s1, s2, s3;
  seg(right, gap, arm, s0);
  seg(-right, gap, arm, s1);
  seg(up, gap, arm, s2);
  seg(-up, gap, arm, s3);
  const float line_vertices[24] = {
      s0[0], s0[1], s0[2], s0[3], s0[4], s0[5], s1[0], s1[1], s1[2], s1[3], s1[4], s1[5],
      s2[0], s2[1], s2[2], s2[3], s2[4], s2[5], s3[0], s3[1], s3[2], s3[3], s3[4], s3[5],
  };

  if (!m_highlight_vao.isCreated()) {
    m_highlight_vao.create();
  }
  if (!m_highlight_vbo.isCreated()) {
    m_highlight_vbo.create();
  }

  QOpenGLVertexArrayObject::Binder vao_binder(&m_highlight_vao);
  m_highlight_vbo.bind();
  m_highlight_vbo.allocate(line_vertices, static_cast<int>(sizeof(line_vertices)));

  const GLboolean depth_test_enabled = f->glIsEnabled(GL_DEPTH_TEST);
  f->glDisable(GL_DEPTH_TEST);

  if (bind_shader(m_crosshair_shader.get())) {
    m_crosshair_shader->enableAttributeArray(0);
    m_crosshair_shader->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
    m_crosshair_shader->setUniformValue(m_crosshair_proj_loc, camera.proj_matrix());
    m_crosshair_shader->setUniformValue(m_crosshair_color_loc, QVector3D(1.0f, 0.92f, 0.15f));
    f->glDrawArrays(GL_LINES, 0, 8);
    m_crosshair_shader->release();
  }

  if (depth_test_enabled) {
    f->glEnable(GL_DEPTH_TEST);
  }

  m_highlight_vbo.release();
}

void OctreeLASLayerRenderer::render(const Camera& camera, const RenderContext& ctx) {
  if (!m_visible) {
    return;
  }
  auto layer = m_layer.lock();
  if (!layer) {
    return;
  }

  m_last_point_draw_ms = 0.0;
  m_last_point_gpu_ms = 0.0;
  m_last_point_vertices_drawn = 0;

  const bool incremental = ctx.incremental_points;

  std::vector<PointOctree::VisibleNode> visible_nodes;
  size_t loaded_octree_points = 0;
  bool load_complete = false;
  bool use_preview = false;
  const Coordinate3D<double>& scene_offset = camera.world_offset();
  const Coordinate3D<double>& file_origin = layer->las_data().coordinate_origin();

  const auto snap = layer->las_data().snapshot();
  if (!snap) {
    if (!layer->las_data().load_complete()) {
      emit repaint_required();
    }
    return;
  }

  loaded_octree_points = snap->octree.total_points();
  load_complete = layer->las_data().load_complete();

  if (loaded_octree_points == 0 && snap->preview_points.empty()) {
    if (!load_complete) {
      emit repaint_required();
    }
    return;
  }

  use_preview = !load_complete && loaded_octree_points == 0 && !snap->preview_points.empty();
  if (!use_preview) {
    collect_visible_octree_nodes(*snap, camera, std::max(m_lod_quality, 0.25), file_origin,
                                 visible_nodes);
  }

  const bool camera_moved = stream_camera_changed(camera);
  const bool visible_changed = load_complete && !use_preview && visible_set_changed(visible_nodes);
  const bool reset_stream = camera_moved || visible_changed;

  if (camera_moved || visible_changed) {
    m_stream_camera_pos = camera.position();
    m_stream_camera_dir = camera.direction();
  }
  if (visible_changed) {
    m_visible_fingerprint = visible_nodes_fingerprint(visible_nodes);
  }

  if (m_data_update_required) {
    if (load_complete) {
      reset_stream_cache();
    }
    m_data_update_required = false;
  }

  if (reset_stream) {
    reset_stream_cache();
  }

  ensure_shader();
  if (!m_shader) {
    std::cerr << "LAS render: point shader failed to compile or link\n";
    return;
  }

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  if (!f) {
    return;
  }
  QOpenGLExtraFunctions* gl = QOpenGLContext::currentContext()->extraFunctions();
  ensure_gpu_timer(gl);
  consume_gpu_timer_sample(gl);

  const double target_draw_ms = layer->point_stream_budget_ms();
  const bool stream_mode_changed = incremental != m_prev_incremental_stream;
  m_prev_incremental_stream = incremental;

  double draw_quality = 1.0;
  if (!use_preview) {
    // After incremental<->restart transitions, seed LOD from the incremental pass quality.
    draw_quality =
        select_draw_quality(visible_nodes, incremental, stream_mode_changed, target_draw_ms);
  }

  const auto draw_start = std::chrono::steady_clock::now();

  if (!bind_shader(m_shader.get())) {
    return;
  }
  f->glEnable(GL_PROGRAM_POINT_SIZE);
  m_shader->setUniformValue(m_view_matrix_loc, camera.view_matrix());
  m_shader->setUniformValue(m_proj_matrix_loc, camera.projection_matrix());
  m_shader->setUniformValue(m_point_radius_loc, layer->point_radius_m());
  m_shader->setUniformValue(m_viewport_height_loc, static_cast<float>(camera.framebuffer_height()));
  m_shader->setUniformValue(m_fov_rad_loc, static_cast<float>(camera.fov_rad()));
  m_shader->setUniformValue(m_color_mode_loc, static_cast<int>(layer->point_color_mode()));
  const std::array<uint8_t, 3>& fixed = layer->fixed_point_color();
  m_shader->setUniformValue(m_fixed_color_loc,
                            QVector3D(fixed[0] / 255.f, fixed[1] / 255.f, fixed[2] / 255.f));
  m_shader->setUniformValue(m_point_alpha_loc, 1.0f);

  std::array<GLint, 8> mask = {};
  const auto& enabled = layer->classification_enabled();
  for (int i = 0; i < 256; ++i) {
    if (enabled[i]) {
      mask[i / 32] |= static_cast<GLint>(1u << (i % 32));
    }
  }
  m_shader->setUniformValueArray(m_classification_mask_loc, mask.data(), 8);

  f->glEnable(GL_DEPTH_TEST);
  f->glDepthFunc(ctx.incremental_points ? GL_LEQUAL : GL_LESS);
  f->glDepthMask(GL_TRUE);
  f->glDisable(GL_BLEND);

  begin_gpu_timer(gl);
  size_t vertices_drawn = 0;
  if (use_preview) {
    vertices_drawn = draw_preview_points(f, snap->preview_points, file_origin, scene_offset);
  } else {
    vertices_drawn = draw_octree_nodes(f, snap->octree.points(), visible_nodes, file_origin,
                                       scene_offset, draw_quality, incremental);
  }
  end_gpu_timer(gl, vertices_drawn);

  m_shader->release();

  const double draw_ms =
      std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - draw_start)
          .count();
  m_last_point_draw_ms = draw_ms;
  m_last_point_vertices_drawn = vertices_drawn;

  if (vertices_drawn == 0) {
    if (!load_complete) {
      emit repaint_required();
    } else if (m_stream_backlog) {
      emit repaint_required();
    }
    return;
  }

  if (incremental) {
    m_inc_lod_quality = draw_quality;
    if (m_stream_backlog && !stream_mode_changed) {
      m_lod_quality = draw_quality;
    }
  } else {
    m_lod_quality = draw_quality;
    m_inc_lod_quality = draw_quality;
  }

  if (!load_complete) {
    emit repaint_required();
  } else if (m_stream_backlog) {
    emit repaint_required();
  }
}

MeshLayerRenderer::MeshLayerRenderer(std::function<const AsyncRasterData*()> data_accessor,
                                     const Coordinate3D<double>& /*offset*/, bool gpu_texture)
    : m_data_accessor(std::move(data_accessor)), m_gpu_texture(gpu_texture) {}

namespace {

struct MeshVertex {
  float position[3];
  float color[3];
};

struct TexturedMeshVertex {
  float position[3];
  float texcoord[2];
};

std::vector<uint8_t> build_texture_rgb(const Geo<MultiBand<FlexGrid>>& texture) {
  const size_t width = texture.width();
  const size_t height = texture.height();
  const size_t rgb_bands = std::min<size_t>(texture.size(), 3);
  std::vector<uint8_t> rgb(width * height * 3);
  for (size_t y = 0; y < height; ++y) {
    const size_t dest_y = height - 1 - y;
    for (size_t x = 0; x < width; ++x) {
      const size_t i = (dest_y * width + x) * 3;
      const double r = flex_grid_value(texture[0], x, y);
      const double g = rgb_bands > 1 ? flex_grid_value(texture[1], x, y) : r;
      const double b = rgb_bands > 2 ? flex_grid_value(texture[2], x, y) : r;
      rgb[i] = static_cast<uint8_t>(std::clamp(r, 0.0, 255.0));
      rgb[i + 1] = static_cast<uint8_t>(std::clamp(g, 0.0, 255.0));
      rgb[i + 2] = static_cast<uint8_t>(std::clamp(b, 0.0, 255.0));
    }
  }
  return rgb;
}

}  // namespace

void MeshLayerRenderer::upload_texture(const Geo<MultiBand<FlexGrid>>& texture) {
  const size_t width = texture.width();
  const size_t height = texture.height();
  if (width == 0 || height == 0) {
    return;
  }

  const std::vector<uint8_t> rgb = build_texture_rgb(texture);
  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  GLint unpack_alignment = 4;
  f->glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpack_alignment);
  f->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  m_texture = std::make_unique<QOpenGLTexture>(QOpenGLTexture::Target2D);
  m_texture->setSize(static_cast<int>(width), static_cast<int>(height));
  m_texture->setFormat(QOpenGLTexture::RGB8_UNorm);
  m_texture->allocateStorage(QOpenGLTexture::RGB, QOpenGLTexture::UInt8);
  m_texture->setData(QOpenGLTexture::RGB, QOpenGLTexture::UInt8, rgb.data());
  f->glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment);
  m_texture->setMinificationFilter(QOpenGLTexture::Linear);
  m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
  m_texture_uploaded = true;
}

void MeshLayerRenderer::upload_mesh(const DemMeshData& mesh, const Coordinate3D<double>& offset) {
  if (mesh.vertices.empty() || mesh.indices.empty()) {
    return;
  }
  const size_t vertex_count = mesh.vertices.size() / 3;
  const bool use_texture = m_gpu_texture && mesh.has_texture;
  if (!use_texture && mesh.colors.empty()) {
    return;
  }
  if (!use_texture && mesh.colors.size() != mesh.vertices.size()) {
    std::cerr << "Mesh color/vertex size mismatch" << std::endl;
    return;
  }
  if (use_texture && mesh.texcoords.size() != vertex_count * 2) {
    std::cerr << "Mesh texcoord/vertex size mismatch" << std::endl;
    return;
  }
  for (unsigned int index : mesh.indices) {
    if (index >= vertex_count) {
      std::cerr << "Mesh index out of range: " << index << " >= " << vertex_count << std::endl;
      return;
    }
  }

  if (!m_shader) {
    m_shader = std::make_unique<QOpenGLShaderProgram>();
    if (use_texture) {
      m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, kTexturedMeshVertexShader);
      m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, kTexturedMeshFragmentShader);
      m_shader->bindAttributeLocation("position", 0);
      m_shader->bindAttributeLocation("texcoord", 1);
    } else {
      m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, kMeshVertexShader);
      m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, kMeshFragmentShader);
      m_shader->bindAttributeLocation("position", 0);
      m_shader->bindAttributeLocation("color", 1);
    }
    if (!m_shader->link()) {
      std::cout << "Mesh shader link error: " << m_shader->log().toStdString() << std::endl;
      m_shader.reset();
      return;
    }
  }
  m_proj_matrix_loc = m_shader->uniformLocation("proj_matrix");
  if (use_texture) {
    m_texture_sampler_loc = m_shader->uniformLocation("dem_texture");
  }

  if (m_vao.isCreated()) {
    m_vao.destroy();
  }
  if (m_vbo.isCreated()) {
    m_vbo.destroy();
  }
  if (m_ibo.isCreated()) {
    m_ibo.destroy();
  }

  m_vao.create();
  {
    QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);

    m_vbo.create();
    m_vbo.bind();

    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ibo.create();
    m_ibo.bind();
    m_ibo.allocate(mesh.indices.data(),
                   static_cast<int>(mesh.indices.size() * sizeof(unsigned int)));

    if (!bind_shader(m_shader.get())) {
      return;
    }

    if (use_texture) {
      std::vector<TexturedMeshVertex> interleaved;
      interleaved.reserve(vertex_count);
      for (size_t i = 0; i < mesh.vertices.size(); i += 3) {
        TexturedMeshVertex vertex;
        vertex.position[0] = static_cast<float>(mesh.vertices[i] - offset.x());
        vertex.position[1] = static_cast<float>(mesh.vertices[i + 1] - offset.y());
        vertex.position[2] = static_cast<float>(mesh.vertices[i + 2] - offset.z());
        const size_t tex_index = (i / 3) * 2;
        vertex.texcoord[0] = mesh.texcoords[tex_index];
        vertex.texcoord[1] = mesh.texcoords[tex_index + 1];
        for (float component : vertex.position) {
          if (!std::isfinite(component)) {
            return;
          }
        }
        interleaved.push_back(vertex);
      }
      m_vbo.allocate(interleaved.data(),
                     static_cast<int>(interleaved.size() * sizeof(TexturedMeshVertex)));
      const int stride = static_cast<int>(sizeof(TexturedMeshVertex));
      m_shader->enableAttributeArray(0);
      m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(TexturedMeshVertex, position), 3, stride);
      m_shader->enableAttributeArray(1);
      m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(TexturedMeshVertex, texcoord), 2, stride);
    } else {
      std::vector<MeshVertex> interleaved;
      interleaved.reserve(vertex_count);
      for (size_t i = 0; i < mesh.vertices.size(); i += 3) {
        MeshVertex vertex;
        vertex.position[0] = static_cast<float>(mesh.vertices[i] - offset.x());
        vertex.position[1] = static_cast<float>(mesh.vertices[i + 1] - offset.y());
        vertex.position[2] = static_cast<float>(mesh.vertices[i + 2] - offset.z());
        vertex.color[0] = mesh.colors[i];
        vertex.color[1] = mesh.colors[i + 1];
        vertex.color[2] = mesh.colors[i + 2];
        for (float component : vertex.position) {
          if (!std::isfinite(component)) {
            return;
          }
        }
        interleaved.push_back(vertex);
      }
      m_vbo.allocate(interleaved.data(), static_cast<int>(interleaved.size() * sizeof(MeshVertex)));
      const int stride = static_cast<int>(sizeof(MeshVertex));
      m_shader->enableAttributeArray(0);
      m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(MeshVertex, position), 3, stride);
      m_shader->enableAttributeArray(1);
      m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(MeshVertex, color), 3, stride);
    }
    m_shader->release();
  }

  m_index_count = mesh.indices.size();
  m_mesh_uploaded = true;
}

void MeshLayerRenderer::render(const Camera& camera, const RenderContext& ctx) {
  if (ctx.incremental_points) {
    return;
  }
  if (!m_visible) {
    return;
  }
  const AsyncRasterData* data = m_data_accessor();
  if (!data) {
    return;
  }

  if (!data->ready()) {
    emit repaint_required();
    return;
  }

  if (m_data_update_required) {
    m_mesh_uploaded = false;
    m_texture_uploaded = false;
    m_texture.reset();
    m_shader.reset();
    m_data_update_required = false;
  }

  if (!m_mesh_uploaded || (m_gpu_texture && !m_texture_uploaded)) {
    DemMeshData mesh_copy;
    const Geo<MultiBand<FlexGrid>>* texture_grid = nullptr;
    {
      std::unique_lock<std::mutex> lock(data->mutex(), std::try_to_lock);
      if (!lock.owns_lock() || !data->ready()) {
        emit repaint_required();
        return;
      }
      mesh_copy = data->mesh();
      if (m_gpu_texture && mesh_copy.has_texture) {
        texture_grid = &data->texture_grid();
      }
    }
    if (!m_mesh_uploaded) {
      upload_mesh(mesh_copy, camera.world_offset());
    }
    if (m_gpu_texture && !m_texture_uploaded && texture_grid != nullptr) {
      upload_texture(*texture_grid);
    }
    m_data_update_required = false;
  }
  if (!m_shader || !m_mesh_uploaded || m_index_count == 0) {
    return;
  }
  if (m_gpu_texture && !m_texture_uploaded) {
    return;
  }

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  if (!f) {
    return;
  }
  f->glEnable(GL_DEPTH_TEST);
  if (!bind_shader(m_shader.get())) {
    return;
  }
  m_shader->setUniformValue(m_proj_matrix_loc, camera.proj_matrix());
  if (m_gpu_texture && m_texture) {
    m_texture->bind(0);
    m_shader->setUniformValue(m_texture_sampler_loc, 0);
  }

  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  if (!m_vao.isCreated() || !m_vbo.isCreated() || !m_ibo.isCreated()) {
    if (m_gpu_texture && m_texture) {
      m_texture->release();
    }
    m_shader->release();
    return;
  }
  m_vbo.bind();
  m_ibo.bind();
  if (m_gpu_texture) {
    const int stride = static_cast<int>(sizeof(TexturedMeshVertex));
    m_shader->enableAttributeArray(0);
    m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(TexturedMeshVertex, position), 3, stride);
    m_shader->enableAttributeArray(1);
    m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(TexturedMeshVertex, texcoord), 2, stride);
  } else {
    const int stride = static_cast<int>(sizeof(MeshVertex));
    m_shader->enableAttributeArray(0);
    m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(MeshVertex, position), 3, stride);
    m_shader->enableAttributeArray(1);
    m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(MeshVertex, color), 3, stride);
  }
  f->glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_index_count), GL_UNSIGNED_INT, nullptr);
  if (m_gpu_texture && m_texture) {
    m_texture->release();
  }
  m_shader->release();
}

ContourLayerRenderer::ContourLayerRenderer(std::shared_ptr<ContourLayer> layer,
                                           const Coordinate3D<double>& /*offset*/)
    : m_layer(layer) {}

namespace {

void append_contour_ribbon(const Contour& contour, double half_width,
                           std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices) {
  const auto& points = contour.points();
  if (points.size() < 2) {
    return;
  }

  const float z = static_cast<float>(contour.height() + 0.5);
  const std::array<float, 3> color{0.6f, 0.35f, 0.1f};

  auto add_vertex = [&](double x, double y) {
    MeshVertex vertex;
    vertex.position[0] = static_cast<float>(x);
    vertex.position[1] = static_cast<float>(y);
    vertex.position[2] = z;
    vertex.color[0] = color[0];
    vertex.color[1] = color[1];
    vertex.color[2] = color[2];
    vertices.push_back(vertex);
    return static_cast<unsigned int>(vertices.size() - 1);
  };

  for (size_t i = 0; i + 1 < points.size(); ++i) {
    const double x0 = points[i].x();
    const double y0 = points[i].y();
    const double x1 = points[i + 1].x();
    const double y1 = points[i + 1].y();
    const double dx = x1 - x0;
    const double dy = y1 - y0;
    const double len = std::hypot(dx, dy);
    if (len < 1e-6) {
      continue;
    }
    const double nx = -dy / len * half_width;
    const double ny = dx / len * half_width;

    const unsigned int v0 = add_vertex(x0 - nx, y0 - ny);
    const unsigned int v1 = add_vertex(x0 + nx, y0 + ny);
    const unsigned int v2 = add_vertex(x1 + nx, y1 + ny);
    const unsigned int v3 = add_vertex(x1 - nx, y1 - ny);
    indices.push_back(v0);
    indices.push_back(v1);
    indices.push_back(v2);
    indices.push_back(v0);
    indices.push_back(v2);
    indices.push_back(v3);
  }
}

}  // namespace

void ContourLayerRenderer::upload_contours(const std::vector<Contour>& contours,
                                           const Coordinate3D<double>& offset) {
  std::vector<MeshVertex> vertices;
  std::vector<unsigned int> indices;
  vertices.reserve(contours.size() * 8);
  indices.reserve(contours.size() * 12);

  // World-space half-width in meters; appears wider on screen as you zoom in.
  constexpr double kHalfWidthMeters = 1.5;
  for (const auto& contour : contours) {
    append_contour_ribbon(contour, kHalfWidthMeters, vertices, indices);
  }
  if (vertices.empty() || indices.empty()) {
    return;
  }

  for (MeshVertex& vertex : vertices) {
    vertex.position[0] -= static_cast<float>(offset.x());
    vertex.position[1] -= static_cast<float>(offset.y());
    vertex.position[2] -= static_cast<float>(offset.z());
  }

  m_shader = std::make_unique<QOpenGLShaderProgram>();
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, kMeshVertexShader) ||
      !m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, kMeshFragmentShader)) {
    m_shader.reset();
    return;
  }
  m_shader->bindAttributeLocation("position", 0);
  m_shader->bindAttributeLocation("color", 1);
  if (!m_shader->link()) {
    m_shader.reset();
    return;
  }
  m_proj_matrix_loc = m_shader->uniformLocation("proj_matrix");

  if (m_vao.isCreated()) {
    m_vao.destroy();
  }
  if (m_vbo.isCreated()) {
    m_vbo.destroy();
  }
  if (m_ibo.isCreated()) {
    m_ibo.destroy();
  }

  m_vao.create();
  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  m_vbo.create();
  m_vbo.bind();
  m_vbo.allocate(vertices.data(), static_cast<int>(vertices.size() * sizeof(MeshVertex)));

  m_ibo.create();
  m_ibo.bind();
  m_ibo.allocate(indices.data(), static_cast<int>(indices.size() * sizeof(unsigned int)));

  if (!bind_shader(m_shader.get())) {
    return;
  }
  const int stride = static_cast<int>(sizeof(MeshVertex));
  m_shader->enableAttributeArray(0);
  m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(MeshVertex, position), 3, stride);
  m_shader->enableAttributeArray(1);
  m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(MeshVertex, color), 3, stride);
  m_shader->release();

  m_index_count = indices.size();
  m_uploaded = true;
  m_vbo.release();
}

void ContourLayerRenderer::render(const Camera& camera, const RenderContext& ctx) {
  if (ctx.incremental_points) {
    return;
  }
  if (!m_visible) {
    return;
  }
  auto layer = m_layer.lock();
  if (!layer) {
    return;
  }

  if (!m_uploaded) {
    std::vector<Contour> contours;
    {
      if (!layer->ready()) {
        emit repaint_required();
        return;
      }
      contours = layer->copy_contours();
    }
    if (contours.empty()) {
      emit repaint_required();
      return;
    }
    upload_contours(contours, camera.world_offset());
  }
  if (!m_shader || !m_uploaded || m_index_count == 0) {
    return;
  }

  QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  if (!f) {
    return;
  }
  f->glEnable(GL_DEPTH_TEST);
  if (!bind_shader(m_shader.get())) {
    return;
  }
  m_shader->setUniformValue(m_proj_matrix_loc, camera.proj_matrix());
  QOpenGLVertexArrayObject::Binder vao_binder(&m_vao);
  m_vbo.bind();
  m_ibo.bind();
  const int stride = static_cast<int>(sizeof(MeshVertex));
  m_shader->enableAttributeArray(0);
  m_shader->setAttributeBuffer(0, GL_FLOAT, offsetof(MeshVertex, position), 3, stride);
  m_shader->enableAttributeArray(1);
  m_shader->setAttributeBuffer(1, GL_FLOAT, offsetof(MeshVertex, color), 3, stride);
  f->glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_index_count), GL_UNSIGNED_INT, nullptr);
  m_shader->release();
}
