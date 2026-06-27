#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QPoint>
#include <QVector3D>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

#include "gui/camera.hpp"
#include "gui/layer.hpp"
#include "gui/point_cloud_gl.hpp"
#include "gui/point_octree.hpp"

struct PointPickResult {
  OctreePoint point;
  double world_x = 0.0;
  double world_y = 0.0;
  double world_z = 0.0;
  std::string layer_name;

  bool operator==(const PointPickResult& other) const {
    return layer_name == other.layer_name && world_x == other.world_x && world_y == other.world_y &&
           world_z == other.world_z;
  }
  bool operator!=(const PointPickResult& other) const { return !(*this == other); }
};

struct RenderContext {
  // When false, the FBO is cleared and stream indices reset for a fresh preview frame.
  // When true, newly drawn points accumulate on the existing FBO (Inspired by Displaz).
  bool incremental_points = false;
  // OpenGL viewport height in framebuffer pixels (must match glViewport for point sizing).
  float viewport_height = 0.0f;
  // Global light direction in world space for mesh/contour shading.
  QVector3D light_direction_world{0.0f, 0.0f, 1.0f};
  // Global light direction in eye space for point-sphere shading.
  QVector3D light_direction_eye{0.0f, 0.0f, 1.0f};
  // Ambient floor and direct-light contribution for mesh/contour layers.
  float ambient_light = 0.30f;
  float diffuse_light = 1.00f;
  // Separate ambient floor for point rendering.
  float point_ambient_light = 0.55f;
};

class LayerRenderer : public QObject {
  Q_OBJECT

 protected:
  bool m_data_update_required = true;
  bool m_visible = true;

 signals:
  void repaint_required() const;
  // Emitted when the visible octree set or view changes enough to invalidate
  // incremental point/pick FBO accumulation.
  void stream_view_reset() const;

 public:
  virtual void render(const Camera& camera, const RenderContext& ctx) = 0;
  virtual ~LayerRenderer() = default;
  void data_update_required() {
    m_data_update_required = true;
    emit repaint_required();
  }
  void set_visible(bool visible) { m_visible = visible; }

  static std::unique_ptr<LayerRenderer> create(std::shared_ptr<Layer> layer,
                                               const Coordinate3D<double>& offset);
};

class OctreeLASLayerRenderer : public LayerRenderer {
 public:
  ~OctreeLASLayerRenderer() override;
  std::weak_ptr<LASLayer> m_layer;

  PointCloudGL m_point_gl;
  std::vector<OctreePoint> m_draw_batch;

  std::unique_ptr<QOpenGLShaderProgram> m_shader;
  int m_view_matrix_loc = 0;
  int m_proj_matrix_loc = 0;
  int m_point_radius_loc = 0;
  int m_viewport_height_loc = 0;
  int m_fov_rad_loc = 0;
  int m_color_mode_loc = 0;
  int m_fixed_color_loc = 0;
  int m_point_alpha_loc = 0;
  int m_point_offset_loc = 0;
  int m_shader_layer_slot_loc = -1;
  int m_light_direction_eye_loc = -1;
  int m_ambient_light_loc = -1;
  int m_diffuse_light_loc = -1;

  double m_lod_quality = 1.0;
  double m_inc_lod_quality = 1.0;
  double m_ms_per_vertex = 30.0 / 800'000.0;
  bool m_stream_backlog = false;
  bool m_prev_incremental_stream = false;
  double m_last_point_draw_ms = 0.0;
  double m_last_point_gpu_ms = 0.0;
  size_t m_last_point_vertices_drawn = 0;
  int m_layer_slot = 0;  // assigned once in add_layer(), 1-based, 0 = unset

  GLuint m_gpu_timer_query = 0;
  size_t m_lod_query_vertices = 0;
  double m_lod_query_cpu_ms = 0.0;

  struct NodeStreamState {
    size_t point_count = 0;
    size_t streamed_count = 0;
    size_t locked_chunk_size = 0;
  };

  std::unordered_map<const PointOctreeNode*, NodeStreamState> m_node_stream;
  bool m_points_uploaded = false;
  std::vector<GLint> m_firsts;
  std::vector<GLsizei> m_counts;
  QVector3D m_stream_camera_pos;
  QVector3D m_stream_camera_dir;
  size_t m_visible_fingerprint = 0;

  void reset_stream_cache();
  bool stream_camera_changed(const Camera& camera) const;
  bool visible_set_changed(const std::vector<PointOctree::VisibleNode>& visible_nodes) const;
  size_t visible_nodes_fingerprint(
      const std::vector<PointOctree::VisibleNode>& visible_nodes) const;
  static void sort_visible_by_lod(std::vector<PointOctree::VisibleNode>& visible_nodes);
  void collect_visible_octree_nodes(const LasRenderSnapshot& snap, const Camera& camera,
                                    double vis_quality, const Coordinate3D<double>& file_origin,
                                    std::vector<PointOctree::VisibleNode>& visible_nodes) const;

  void ensure_shader();
  size_t estimate_draw_vertices(const std::vector<PointOctree::VisibleNode>& visible_nodes,
                                double quality, bool incremental) const;
  double select_draw_quality(const std::vector<PointOctree::VisibleNode>& visible_nodes,
                             bool incremental, bool lod_base_from_incremental,
                             double target_draw_ms) const;
  void record_lod_sample(size_t vertices, double ms);
  void ensure_gpu_timer(class QOpenGLExtraFunctions* gl);
  void consume_gpu_timer_sample(class QOpenGLExtraFunctions* gl);
  size_t draw_octree_nodes(QOpenGLFunctions* f, const std::vector<OctreePoint>& point_storage,
                           const std::vector<PointOctree::VisibleNode>& visible_nodes,
                           const Coordinate3D<double>& file_origin,
                           const Coordinate3D<double>& scene_offset, double quality,
                           bool incremental);
  size_t draw_preview_points(QOpenGLFunctions* f, const std::vector<OctreePoint>& preview,
                             const Coordinate3D<double>& file_origin,
                             const Coordinate3D<double>& scene_offset);

 public:
  OctreeLASLayerRenderer(std::shared_ptr<LASLayer> layer, const Coordinate3D<double>& offset);

  bool has_stream_backlog() const { return m_stream_backlog; }
  double last_point_draw_ms() const { return m_last_point_draw_ms; }
  double last_point_gpu_ms() const { return m_last_point_gpu_ms; }
  size_t last_point_vertices_drawn() const { return m_last_point_vertices_drawn; }
  void refresh_after_style_change();
  virtual void render(const Camera& camera, const RenderContext& ctx) override;

  void set_layer_slot(int slot) { m_layer_slot = slot; }
  int layer_slot() const { return m_layer_slot; }
  bool can_fbo_pick() const;
  std::optional<PointPickResult> point_from_index(uint32_t layer_slot, uint32_t pick_index,
                                                  const Coordinate3D<double>& scene_offset) const;
};

class MeshLayerRenderer : public LayerRenderer {
  std::weak_ptr<Layer> m_layer;
  std::function<const AsyncRasterData*()> m_data_accessor;
  bool m_gpu_texture = false;

  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  QOpenGLBuffer m_ibo{QOpenGLBuffer::IndexBuffer};
  std::unique_ptr<QOpenGLShaderProgram> m_shader;
  std::unique_ptr<QOpenGLTexture> m_texture;
  bool m_mesh_uploaded = false;
  bool m_texture_uploaded = false;
  size_t m_index_count = 0;
  int m_proj_matrix_loc = 0;
  int m_light_direction_loc = -1;
  int m_camera_position_loc = -1;
  int m_ambient_light_loc = -1;
  int m_diffuse_light_loc = -1;
  int m_texture_sampler_loc = 0;
  int m_layer_alpha_loc = -1;
  int m_vertical_offset_loc = -1;

  void upload_mesh(const DemMeshData& mesh, const Coordinate3D<double>& offset);
  void upload_texture(const Geo<MultiBand<FlexGrid>>& texture);

 public:
  MeshLayerRenderer(std::shared_ptr<Layer> layer,
                    std::function<const AsyncRasterData*()> data_accessor,
                    const Coordinate3D<double>& offset, bool gpu_texture = false);

  virtual void render(const Camera& camera, const RenderContext& ctx) override;
};

class ContourLayerRenderer : public LayerRenderer {
  std::weak_ptr<ContourLayer> m_layer;

  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  QOpenGLBuffer m_ibo{QOpenGLBuffer::IndexBuffer};
  std::unique_ptr<QOpenGLShaderProgram> m_shader;
  bool m_uploaded = false;
  size_t m_index_count = 0;
  int m_proj_matrix_loc = 0;
  int m_light_direction_loc = -1;
  int m_camera_position_loc = -1;
  int m_ambient_light_loc = -1;
  int m_diffuse_light_loc = -1;
  int m_layer_alpha_loc = -1;
  int m_vertical_offset_loc = -1;

  void upload_contours(const std::vector<Contour>& contours, const Coordinate3D<double>& offset);

 public:
  ContourLayerRenderer(std::shared_ptr<ContourLayer> layer, const Coordinate3D<double>& offset);

  virtual void render(const Camera& camera, const RenderContext& ctx) override;
};
