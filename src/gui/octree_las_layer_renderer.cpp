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

#include "gui/frustum.hpp"
#include "gui/gl_check.hpp"
#include "gui/layer_renderer.hpp"
#include "gui/shaders.hpp"

namespace {

class ScopedGpuTimer {
 public:
  ScopedGpuTimer(QOpenGLExtraFunctions* gl, GLuint query) : m_gl(gl), m_query(query) {
    if (m_gl && m_query != 0) {
      CHECK_GL(m_gl->glBeginQuery(GL_TIME_ELAPSED, m_query));
    }
  }
  ~ScopedGpuTimer() {
    if (m_gl && m_query != 0) {
      CHECK_GL(m_gl->glEndQuery(GL_TIME_ELAPSED));
    }
  }
  explicit operator bool() const { return m_gl != nullptr && m_query != 0; }

 private:
  QOpenGLExtraFunctions* m_gl;
  GLuint m_query;
};

constexpr double DRAW_CALL_OVERHEAD_MS = 0.012;
constexpr size_t MAX_PREVIEW_DRAW_VERTICES = 500'000;
constexpr float STREAM_VIEW_RESET_DISTANCE = 25.0f;

}  // namespace

OctreeLASLayerRenderer::OctreeLASLayerRenderer(std::shared_ptr<LASLayer> layer,
                                               const Coordinate3D<double>& /*offset*/)
    : m_layer(layer) {}

OctreeLASLayerRenderer::~OctreeLASLayerRenderer() {
  if (m_gpu_timer_query != 0) {
    // Try to clean up the GPU query if a context is available.
    // If the context has already been destroyed, the resource will
    // be reclaimed by the driver on context teardown.
    if (auto* ctx = QOpenGLContext::currentContext()) {
      auto* gl = ctx->extraFunctions();
      if (gl) {
        gl->glDeleteQueries(1, &m_gpu_timer_query);
      }
    }
    m_gpu_timer_query = 0;
  }
}

void OctreeLASLayerRenderer::ensure_shader() {
  if (m_shader) {
    return;
  }
  m_shader = std::make_unique<QOpenGLShaderProgram>();
  const QString vertex_src = get_point_vertex_shader();
  const QString fragment_src = get_point_fragment_shader();
  if (vertex_src.isEmpty() || fragment_src.isEmpty()) {
    std::cout << "Failed to load point shaders from resources" << std::endl;
    m_shader.reset();
    return;
  }
  if (!m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_src) ||
      !m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_src)) {
    std::cout << "Point shader error: " << m_shader->log().toStdString() << std::endl;
    m_shader.reset();
    return;
  }
  m_shader->bindAttributeLocation("local_position", 0);
  m_shader->bindAttributeLocation("classification", 1);
  m_shader->bindAttributeLocation("file_color", 2);
  m_shader->bindAttributeLocation("has_file_rgb", 3);
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
  m_shader_layer_slot_loc = m_shader->uniformLocation("u_layer_slot");
  m_light_direction_eye_loc = m_shader->uniformLocation("u_light_direction_eye");
  m_ambient_light_loc = m_shader->uniformLocation("u_ambient_light");
  m_diffuse_light_loc = m_shader->uniformLocation("u_diffuse_light");
}

void OctreeLASLayerRenderer::reset_stream_cache() {
  m_node_stream.clear();
  m_stream_backlog = false;
}

void OctreeLASLayerRenderer::refresh_after_style_change() {
  m_node_stream.clear();
  m_stream_backlog = true;
  m_lod_query_vertices = 0;
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
      STREAM_VIEW_RESET_DISTANCE * STREAM_VIEW_RESET_DISTANCE) {
    return true;
  }
  if ((camera.direction().normalized() - m_stream_camera_dir).lengthSquared() > 0.01f) {
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
  const Coordinate3D<double>& scene_offset = camera.world_offset();
  const QVector3D point_offset(static_cast<float>(file_origin.x() - scene_offset.x()),
                               static_cast<float>(file_origin.y() - scene_offset.y()),
                               static_cast<float>(file_origin.z() - scene_offset.z()));
  QMatrix4x4 clip = camera.proj_matrix();
  clip.translate(point_offset);
  const Frustum frustum = Frustum::from_matrix(clip);
  const Coordinate3D<double> camera_local(camera.position().x() - point_offset.x(),
                                          camera.position().y() - point_offset.y(),
                                          camera.position().z() - point_offset.z());
  snap.octree.collect_visible(frustum, vis_quality, camera_local, visible_nodes);
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
  const size_t vertices = estimate_draw_vertices(visible_nodes, base, incremental);
  const double est_ms = static_cast<double>(vertices) * m_ms_per_vertex +
                        (vertices > 0 ? DRAW_CALL_OVERHEAD_MS : 0.0);
  if (est_ms <= 1e-6) {
    return std::clamp(base, 0.05, 64.0);
  }
  return std::clamp(base * target_draw_ms / est_ms, 0.05, 64.0);
}

void OctreeLASLayerRenderer::record_lod_sample(size_t vertices, double ms) {
  if (vertices == 0 || ms <= 0.0) {
    return;
  }
  constexpr double ALPHA = 0.2;
  const double instant = ms / static_cast<double>(vertices);
  m_ms_per_vertex =
      m_ms_per_vertex > 0.0 ? (1.0 - ALPHA) * m_ms_per_vertex + ALPHA * instant : instant;
}

void OctreeLASLayerRenderer::ensure_gpu_timer(QOpenGLExtraFunctions* gl) {
  if (m_gpu_timer_query != 0 || !gl) {
    return;
  }
  CHECK_GL(gl->glGenQueries(1, &m_gpu_timer_query));
}

void OctreeLASLayerRenderer::consume_gpu_timer_sample(QOpenGLExtraFunctions* gl) {
  if (!gl || m_gpu_timer_query == 0 || m_lod_query_vertices == 0) {
    return;
  }

  GLuint available = 0;
  CHECK_GL(gl->glGetQueryObjectuiv(m_gpu_timer_query, GL_QUERY_RESULT_AVAILABLE, &available));
  if (!available) {
    return;
  }

  GLuint elapsed_ns = 0;
  CHECK_GL(gl->glGetQueryObjectuiv(m_gpu_timer_query, GL_QUERY_RESULT, &elapsed_ns));
  const double gpu_ms = static_cast<double>(elapsed_ns) / 1'000'000.0;
  m_last_point_gpu_ms = gpu_ms;
  record_lod_sample(m_lod_query_vertices, gpu_ms);
}

size_t OctreeLASLayerRenderer::draw_octree_nodes(
    QOpenGLFunctions* f, const OctreePointVector& point_storage,
    const std::vector<PointOctree::VisibleNode>& visible_nodes,
    const Coordinate3D<double>& file_origin, const Coordinate3D<double>& scene_offset,
    double quality, bool incremental) {
  m_stream_backlog = false;

  if (!m_shader) {
    return 0;
  }
  m_point_gl.ensure_initialized(f);
  m_point_gl.bind(f);
  CHECK_GL_AFTER();

  const QVector3D point_offset(static_cast<float>(file_origin.x() - scene_offset.x()),
                               static_cast<float>(file_origin.y() - scene_offset.y()),
                               static_cast<float>(file_origin.z() - scene_offset.z()));
  m_shader->setUniformValue(m_point_offset_loc, point_offset);
  CHECK_GL_AFTER();

  if (!m_points_uploaded && !point_storage.empty()) {
    m_point_gl.upload_points(f, point_storage.data(), point_storage.size());
    m_points_uploaded = true;
    CHECK_GL_AFTER();
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

    const size_t first_index = node->begin_index + state.streamed_count;
    if (first_index > static_cast<size_t>(std::numeric_limits<GLint>::max())) {
      m_stream_backlog = true;
      continue;
    }
    m_firsts.push_back(static_cast<GLint>(first_index));
    m_counts.push_back(static_cast<GLsizei>(to_draw));

    state.streamed_count += to_draw;
    if (state.streamed_count < point_count) {
      m_stream_backlog = true;
    }
  }

  m_shader->setUniformValue(m_shader_layer_slot_loc, m_layer_slot > 0 ? m_layer_slot : 0);
  CHECK_GL_AFTER();
  return m_point_gl.draw_leaves(f, m_firsts.data(), m_counts.data(), m_firsts.size());
}

size_t OctreeLASLayerRenderer::draw_preview_points(QOpenGLFunctions* f,
                                                   const OctreePointVector& preview,
                                                   const Coordinate3D<double>& file_origin,
                                                   const Coordinate3D<double>& scene_offset) {
  if (preview.empty() || !m_shader) {
    return 0;
  }

  m_point_gl.ensure_initialized(f);
  m_point_gl.bind(f);
  CHECK_GL_AFTER();

  const size_t count = std::min(preview.size(), MAX_PREVIEW_DRAW_VERTICES);
  const QVector3D point_offset(static_cast<float>(file_origin.x() - scene_offset.x()),
                               static_cast<float>(file_origin.y() - scene_offset.y()),
                               static_cast<float>(file_origin.z() - scene_offset.z()));
  m_shader->setUniformValue(m_point_offset_loc, point_offset);
  m_shader->setUniformValue(m_shader_layer_slot_loc, 0);
  CHECK_GL_AFTER();

  const size_t total_vertices = m_point_gl.draw_points(f, preview.data(), count);
  m_stream_backlog = preview.size() > count;
  return total_vertices;
}

bool OctreeLASLayerRenderer::can_fbo_pick() const {
  auto layer = m_layer.lock();
  if (!layer || m_layer_slot == 0) {
    return false;
  }
  if (!layer->las_data().load_complete()) {
    return false;
  }
  auto snap = layer->las_data().snapshot();
  return snap && snap->octree.total_points() > 0;
}

std::optional<PointPickResult> OctreeLASLayerRenderer::point_from_index(
    uint32_t layer_slot, uint32_t pick_index, const Coordinate3D<double>& scene_offset) const {
  if (pick_index == 0 || layer_slot == 0) {
    return std::nullopt;
  }
  if (layer_slot != static_cast<uint32_t>(m_layer_slot)) {
    return std::nullopt;
  }
  const size_t idx = static_cast<size_t>(pick_index) - 1;
  auto layer = m_layer.lock();
  if (!layer) {
    return std::nullopt;
  }
  auto snap = layer->las_data().snapshot();
  if (!snap || idx >= snap->octree.points().size()) {
    return std::nullopt;
  }
  const OctreePoint& p = snap->octree.points()[idx];
  const Coordinate3D<double>& file_origin = layer->las_data().coordinate_origin();
  PointPickResult result;
  result.point = p;
  result.world_x = static_cast<double>(p.x) + file_origin.x() - scene_offset.x();
  result.world_y = static_cast<double>(p.y) + file_origin.y() - scene_offset.y();
  result.world_z = static_cast<double>(p.z) + file_origin.z() - scene_offset.z();
  result.layer_name = layer->name();
  return result;
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
    const double base_quality = std::max(m_lod_quality, 0.25);
    const double adjusted_quality = base_quality * layer->lod_quality_multiplier();
    collect_visible_octree_nodes(*snap, camera, adjusted_quality, file_origin, visible_nodes);
  }

  const bool camera_moved = stream_camera_changed(camera);
  const bool visible_changed = load_complete && !use_preview && visible_set_changed(visible_nodes);
  const bool reset_stream = camera_moved || visible_changed;

  if (camera_moved || visible_changed) {
    m_stream_camera_pos = camera.position();
    m_stream_camera_dir = camera.direction().normalized();
  }
  if (visible_changed) {
    m_visible_fingerprint = visible_nodes_fingerprint(visible_nodes);
  }

  if (m_data_update_required) {
    if (load_complete) {
      reset_stream_cache();
    }
    m_points_uploaded = false;
    m_data_update_required = false;
  }

  if (reset_stream) {
    reset_stream_cache();
    if (visible_changed) {
      emit stream_view_reset();
    }
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
    draw_quality =
        select_draw_quality(visible_nodes, incremental, stream_mode_changed, target_draw_ms);
  }

  const auto draw_start = std::chrono::steady_clock::now();

  if (!bind_shader(m_shader.get())) {
    return;
  }
  CHECK_GL(f->glEnable(GL_PROGRAM_POINT_SIZE));
  m_shader->setUniformValue(m_view_matrix_loc, camera.view_matrix());
  m_shader->setUniformValue(m_proj_matrix_loc, camera.projection_matrix());
  m_shader->setUniformValue(m_point_radius_loc, layer->point_radius_m());
  m_shader->setUniformValue(m_viewport_height_loc, ctx.viewport_height);
  m_shader->setUniformValue(m_fov_rad_loc, static_cast<float>(camera.fov_rad()));
  m_shader->setUniformValue(m_color_mode_loc, static_cast<int>(layer->point_color_mode()));
  const std::array<uint8_t, 3>& fixed = layer->fixed_point_color();
  m_shader->setUniformValue(m_fixed_color_loc,
                            QVector3D(fixed[0] / 255.f, fixed[1] / 255.f, fixed[2] / 255.f));
  m_shader->setUniformValue(m_point_alpha_loc, layer->point_alpha());
  if (m_light_direction_eye_loc >= 0) {
    m_shader->setUniformValue(m_light_direction_eye_loc, ctx.light_direction_eye);
  }
  if (m_ambient_light_loc >= 0) {
    m_shader->setUniformValue(m_ambient_light_loc, ctx.point_ambient_light);
  }
  if (m_diffuse_light_loc >= 0) {
    m_shader->setUniformValue(m_diffuse_light_loc, ctx.diffuse_light);
  }
  CHECK_GL_AFTER();

  CHECK_GL(f->glEnable(GL_DEPTH_TEST));
  CHECK_GL(f->glDepthFunc(ctx.incremental_points ? GL_LEQUAL : GL_LESS));
  CHECK_GL(f->glDepthMask(GL_TRUE));
  CHECK_GL(f->glDisable(GL_BLEND));

  const size_t expected_vertices =
      use_preview ? std::min(snap->preview_points.size(), MAX_PREVIEW_DRAW_VERTICES)
                  : estimate_draw_vertices(visible_nodes, draw_quality, incremental);
  const bool time_draw = expected_vertices > 0;
  ScopedGpuTimer gpu_timer(time_draw ? gl : nullptr, time_draw ? m_gpu_timer_query : 0);
  size_t vertices_drawn = 0;
  if (use_preview) {
    vertices_drawn = draw_preview_points(f, snap->preview_points, file_origin, scene_offset);
  } else {
    vertices_drawn = draw_octree_nodes(f, snap->octree.points(), visible_nodes, file_origin,
                                       scene_offset, draw_quality, incremental);
  }
  if (gpu_timer) {
    m_lod_query_vertices = vertices_drawn;
  }

  m_shader->release();
  CHECK_GL_AFTER();

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
