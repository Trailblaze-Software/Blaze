#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QPoint>
#include <cstdint>
#include <deque>
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
};

struct RenderContext {
  // When false, the FBO is cleared and stream indices reset for a fresh preview frame.
  // When true, newly drawn points accumulate on the existing FBO (Displaz-style).
  bool incremental_points = false;
};

class LayerRenderer : public QObject {
  Q_OBJECT

 protected:
  bool m_data_update_required = true;
  bool m_visible = true;

 signals:
  void repaint_required() const;

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
  struct DrawSample {
    size_t vertices = 0;
    double ms = 0.0;
  };

  std::weak_ptr<LASLayer> m_layer;

  QOpenGLVertexArrayObject m_highlight_vao;
  QOpenGLBuffer m_highlight_vbo;
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

  std::unique_ptr<QOpenGLShaderProgram> m_crosshair_shader;
  int m_crosshair_proj_loc = 0;
  int m_crosshair_color_loc = 0;

  double m_lod_quality = 1.0;
  double m_inc_lod_quality = 1.0;
  double m_ms_per_vertex = 30.0 / 800'000.0;
  std::deque<DrawSample> m_draw_samples;
  bool m_stream_backlog = false;
  bool m_prev_incremental_stream = false;
  double m_last_point_draw_ms = 0.0;
  size_t m_last_point_vertices_drawn = 0;
  std::optional<PointPickResult> m_highlight;

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
  void ensure_crosshair_shader();
  size_t estimate_draw_vertices(const std::vector<PointOctree::VisibleNode>& visible_nodes,
                                double quality, bool incremental) const;
  double select_draw_quality(const std::vector<PointOctree::VisibleNode>& visible_nodes,
                             bool incremental, bool lod_base_from_incremental,
                             double target_draw_ms) const;
  void record_draw_sample(size_t vertices, double ms);
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
  size_t last_point_vertices_drawn() const { return m_last_point_vertices_drawn; }
  void refresh_after_style_change();
  void set_highlight(const std::optional<PointPickResult>& pick);
  void render_selection_highlight(const Camera& camera, const RenderContext& ctx);
  std::optional<PointPickResult> pick_point(const Camera& camera, const QPoint& pixel) const;
  virtual void render(const Camera& camera, const RenderContext& ctx) override;
};

class MeshLayerRenderer : public LayerRenderer {
  std::function<const AsyncRasterData*()> m_data_accessor;
  Coordinate3D<double> m_offset;
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
  int m_texture_sampler_loc = 0;

  void upload_mesh(const DemMeshData& mesh, const Coordinate3D<double>& offset);
  void upload_texture(const Geo<MultiBand<FlexGrid>>& texture);

 public:
  MeshLayerRenderer(std::function<const AsyncRasterData*()> data_accessor,
                    const Coordinate3D<double>& offset, bool gpu_texture = false);

  virtual void render(const Camera& camera, const RenderContext& ctx) override;
};

class ContourLayerRenderer : public LayerRenderer {
  std::weak_ptr<ContourLayer> m_layer;
  Coordinate3D<double> m_offset;

  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  QOpenGLBuffer m_ibo{QOpenGLBuffer::IndexBuffer};
  std::unique_ptr<QOpenGLShaderProgram> m_shader;
  bool m_uploaded = false;
  size_t m_index_count = 0;
  int m_proj_matrix_loc = 0;

  void upload_contours(const std::vector<Contour>& contours, const Coordinate3D<double>& offset);

 public:
  ContourLayerRenderer(std::shared_ptr<ContourLayer> layer, const Coordinate3D<double>& offset);

  virtual void render(const Camera& camera, const RenderContext& ctx) override;
};
