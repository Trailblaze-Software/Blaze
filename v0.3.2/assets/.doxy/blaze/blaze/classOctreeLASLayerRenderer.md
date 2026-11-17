

# Class OctreeLASLayerRenderer



[**ClassList**](annotated.md) **>** [**OctreeLASLayerRenderer**](classOctreeLASLayerRenderer.md)








Inherits the following classes: [LayerRenderer](classLayerRenderer.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**NodeStreamState**](structOctreeLASLayerRenderer_1_1NodeStreamState.md) <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**m\_ambient\_light\_loc**](#variable-m_ambient_light_loc)   = `-1`<br> |
|  int | [**m\_color\_mode\_loc**](#variable-m_color_mode_loc)   = `0`<br> |
|  std::vector&lt; GLsizei &gt; | [**m\_counts**](#variable-m_counts)  <br> |
|  int | [**m\_diffuse\_light\_loc**](#variable-m_diffuse_light_loc)   = `-1`<br> |
|  std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; | [**m\_draw\_batch**](#variable-m_draw_batch)  <br> |
|  std::vector&lt; GLint &gt; | [**m\_firsts**](#variable-m_firsts)  <br> |
|  int | [**m\_fixed\_color\_loc**](#variable-m_fixed_color_loc)   = `0`<br> |
|  int | [**m\_fov\_rad\_loc**](#variable-m_fov_rad_loc)   = `0`<br> |
|  GLuint | [**m\_gpu\_timer\_query**](#variable-m_gpu_timer_query)   = `0`<br> |
|  double | [**m\_inc\_lod\_quality**](#variable-m_inc_lod_quality)   = `1.0`<br> |
|  double | [**m\_last\_point\_draw\_ms**](#variable-m_last_point_draw_ms)   = `0.0`<br> |
|  double | [**m\_last\_point\_gpu\_ms**](#variable-m_last_point_gpu_ms)   = `0.0`<br> |
|  size\_t | [**m\_last\_point\_vertices\_drawn**](#variable-m_last_point_vertices_drawn)   = `0`<br> |
|  std::weak\_ptr&lt; [**LASLayer**](classLASLayer.md) &gt; | [**m\_layer**](#variable-m_layer)  <br> |
|  int | [**m\_layer\_slot**](#variable-m_layer_slot)   = `0`<br> |
|  int | [**m\_light\_direction\_eye\_loc**](#variable-m_light_direction_eye_loc)   = `-1`<br> |
|  double | [**m\_lod\_quality**](#variable-m_lod_quality)   = `1.0`<br> |
|  double | [**m\_lod\_query\_cpu\_ms**](#variable-m_lod_query_cpu_ms)   = `0.0`<br> |
|  size\_t | [**m\_lod\_query\_vertices**](#variable-m_lod_query_vertices)   = `0`<br> |
|  double | [**m\_ms\_per\_vertex**](#variable-m_ms_per_vertex)   = `30.0 / 800'000.0`<br> |
|  std::unordered\_map&lt; const [**PointOctreeNode**](classPointOctreeNode.md) \*, [**NodeStreamState**](structOctreeLASLayerRenderer_1_1NodeStreamState.md) &gt; | [**m\_node\_stream**](#variable-m_node_stream)  <br> |
|  int | [**m\_point\_alpha\_loc**](#variable-m_point_alpha_loc)   = `0`<br> |
|  [**PointCloudGL**](classPointCloudGL.md) | [**m\_point\_gl**](#variable-m_point_gl)  <br> |
|  int | [**m\_point\_offset\_loc**](#variable-m_point_offset_loc)   = `0`<br> |
|  int | [**m\_point\_radius\_loc**](#variable-m_point_radius_loc)   = `0`<br> |
|  bool | [**m\_points\_uploaded**](#variable-m_points_uploaded)   = `false`<br> |
|  bool | [**m\_prev\_incremental\_stream**](#variable-m_prev_incremental_stream)   = `false`<br> |
|  int | [**m\_proj\_matrix\_loc**](#variable-m_proj_matrix_loc)   = `0`<br> |
|  std::unique\_ptr&lt; QOpenGLShaderProgram &gt; | [**m\_shader**](#variable-m_shader)  <br> |
|  int | [**m\_shader\_layer\_slot\_loc**](#variable-m_shader_layer_slot_loc)   = `-1`<br> |
|  bool | [**m\_stream\_backlog**](#variable-m_stream_backlog)   = `false`<br> |
|  QVector3D | [**m\_stream\_camera\_dir**](#variable-m_stream_camera_dir)  <br> |
|  QVector3D | [**m\_stream\_camera\_pos**](#variable-m_stream_camera_pos)  <br> |
|  int | [**m\_view\_matrix\_loc**](#variable-m_view_matrix_loc)   = `0`<br> |
|  int | [**m\_viewport\_height\_loc**](#variable-m_viewport_height_loc)   = `0`<br> |
|  size\_t | [**m\_visible\_fingerprint**](#variable-m_visible_fingerprint)   = `0`<br> |


























## Public Signals inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
| signal void | [**repaint\_required**](classLayerRenderer.md#signal-repaint_required)  <br> |
| signal void | [**stream\_view\_reset**](classLayerRenderer.md#signal-stream_view_reset)  <br> |






## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OctreeLASLayerRenderer**](#function-octreelaslayerrenderer) (std::shared\_ptr&lt; [**LASLayer**](classLASLayer.md) &gt; layer, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & offset) <br> |
|  bool | [**can\_fbo\_pick**](#function-can_fbo_pick) () const<br> |
|  void | [**collect\_visible\_octree\_nodes**](#function-collect_visible_octree_nodes) (const [**LasRenderSnapshot**](structLasRenderSnapshot.md) & snap, const [**Camera**](classCamera.md) & camera, double vis\_quality, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & file\_origin, std::vector&lt; [**PointOctree::VisibleNode**](structPointOctree_1_1VisibleNode.md) &gt; & visible\_nodes) const<br> |
|  void | [**consume\_gpu\_timer\_sample**](#function-consume_gpu_timer_sample) (class QOpenGLExtraFunctions \* gl) <br> |
|  size\_t | [**draw\_octree\_nodes**](#function-draw_octree_nodes) (QOpenGLFunctions \* f, const OctreePointVector & point\_storage, const std::vector&lt; [**PointOctree::VisibleNode**](structPointOctree_1_1VisibleNode.md) &gt; & visible\_nodes, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & file\_origin, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & scene\_offset, double quality, bool incremental) <br> |
|  size\_t | [**draw\_preview\_points**](#function-draw_preview_points) (QOpenGLFunctions \* f, const OctreePointVector & preview, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & file\_origin, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & scene\_offset) <br> |
|  void | [**ensure\_gpu\_timer**](#function-ensure_gpu_timer) (class QOpenGLExtraFunctions \* gl) <br> |
|  void | [**ensure\_shader**](#function-ensure_shader) () <br> |
|  size\_t | [**estimate\_draw\_vertices**](#function-estimate_draw_vertices) (const std::vector&lt; [**PointOctree::VisibleNode**](structPointOctree_1_1VisibleNode.md) &gt; & visible\_nodes, double quality, bool incremental) const<br> |
|  bool | [**has\_stream\_backlog**](#function-has_stream_backlog) () const<br> |
|  double | [**last\_point\_draw\_ms**](#function-last_point_draw_ms) () const<br> |
|  double | [**last\_point\_gpu\_ms**](#function-last_point_gpu_ms) () const<br> |
|  size\_t | [**last\_point\_vertices\_drawn**](#function-last_point_vertices_drawn) () const<br> |
|  int | [**layer\_slot**](#function-layer_slot) () const<br> |
|  std::optional&lt; [**PointPickResult**](structPointPickResult.md) &gt; | [**point\_from\_index**](#function-point_from_index) (uint32\_t layer\_slot, uint32\_t pick\_index, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & scene\_offset) const<br> |
|  void | [**record\_lod\_sample**](#function-record_lod_sample) (size\_t vertices, double ms) <br> |
|  void | [**refresh\_after\_style\_change**](#function-refresh_after_style_change) () <br> |
| virtual void | [**render**](#function-render) (const [**Camera**](classCamera.md) & camera, const [**RenderContext**](structRenderContext.md) & ctx) override<br> |
|  void | [**reset\_stream\_cache**](#function-reset_stream_cache) () <br> |
|  double | [**select\_draw\_quality**](#function-select_draw_quality) (const std::vector&lt; [**PointOctree::VisibleNode**](structPointOctree_1_1VisibleNode.md) &gt; & visible\_nodes, bool incremental, bool lod\_base\_from\_incremental, double target\_draw\_ms) const<br> |
|  void | [**set\_layer\_slot**](#function-set_layer_slot) (int slot) <br> |
|  bool | [**stream\_camera\_changed**](#function-stream_camera_changed) (const [**Camera**](classCamera.md) & camera) const<br> |
|  size\_t | [**visible\_nodes\_fingerprint**](#function-visible_nodes_fingerprint) (const std::vector&lt; [**PointOctree::VisibleNode**](structPointOctree_1_1VisibleNode.md) &gt; & visible\_nodes) const<br> |
|  bool | [**visible\_set\_changed**](#function-visible_set_changed) (const std::vector&lt; [**PointOctree::VisibleNode**](structPointOctree_1_1VisibleNode.md) &gt; & visible\_nodes) const<br> |
|   | [**~OctreeLASLayerRenderer**](#function-octreelaslayerrenderer) () override<br> |


## Public Functions inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
|  void | [**data\_update\_required**](classLayerRenderer.md#function-data_update_required) () <br> |
| virtual void | [**render**](classLayerRenderer.md#function-render) (const [**Camera**](classCamera.md) & camera, const [**RenderContext**](structRenderContext.md) & ctx) = 0<br> |
|  void | [**set\_visible**](classLayerRenderer.md#function-set_visible) (bool visible) <br> |
| virtual  | [**~LayerRenderer**](classLayerRenderer.md#function-layerrenderer) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**sort\_visible\_by\_lod**](#function-sort_visible_by_lod) (std::vector&lt; [**PointOctree::VisibleNode**](structPointOctree_1_1VisibleNode.md) &gt; & visible\_nodes) <br> |


## Public Static Functions inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
|  std::unique\_ptr&lt; [**LayerRenderer**](classLayerRenderer.md) &gt; | [**create**](classLayerRenderer.md#function-create) (std::shared\_ptr&lt; [**Layer**](classLayer.md) &gt; layer, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & offset) <br> |












## Protected Attributes inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_data\_update\_required**](classLayerRenderer.md#variable-m_data_update_required)   = `true`<br> |
|  bool | [**m\_visible**](classLayerRenderer.md#variable-m_visible)   = `true`<br> |






































## Public Attributes Documentation




### variable m\_ambient\_light\_loc 

```C++
int OctreeLASLayerRenderer::m_ambient_light_loc;
```




<hr>



### variable m\_color\_mode\_loc 

```C++
int OctreeLASLayerRenderer::m_color_mode_loc;
```




<hr>



### variable m\_counts 

```C++
std::vector<GLsizei> OctreeLASLayerRenderer::m_counts;
```




<hr>



### variable m\_diffuse\_light\_loc 

```C++
int OctreeLASLayerRenderer::m_diffuse_light_loc;
```




<hr>



### variable m\_draw\_batch 

```C++
std::vector<OctreePoint> OctreeLASLayerRenderer::m_draw_batch;
```




<hr>



### variable m\_firsts 

```C++
std::vector<GLint> OctreeLASLayerRenderer::m_firsts;
```




<hr>



### variable m\_fixed\_color\_loc 

```C++
int OctreeLASLayerRenderer::m_fixed_color_loc;
```




<hr>



### variable m\_fov\_rad\_loc 

```C++
int OctreeLASLayerRenderer::m_fov_rad_loc;
```




<hr>



### variable m\_gpu\_timer\_query 

```C++
GLuint OctreeLASLayerRenderer::m_gpu_timer_query;
```




<hr>



### variable m\_inc\_lod\_quality 

```C++
double OctreeLASLayerRenderer::m_inc_lod_quality;
```




<hr>



### variable m\_last\_point\_draw\_ms 

```C++
double OctreeLASLayerRenderer::m_last_point_draw_ms;
```




<hr>



### variable m\_last\_point\_gpu\_ms 

```C++
double OctreeLASLayerRenderer::m_last_point_gpu_ms;
```




<hr>



### variable m\_last\_point\_vertices\_drawn 

```C++
size_t OctreeLASLayerRenderer::m_last_point_vertices_drawn;
```




<hr>



### variable m\_layer 

```C++
std::weak_ptr<LASLayer> OctreeLASLayerRenderer::m_layer;
```




<hr>



### variable m\_layer\_slot 

```C++
int OctreeLASLayerRenderer::m_layer_slot;
```




<hr>



### variable m\_light\_direction\_eye\_loc 

```C++
int OctreeLASLayerRenderer::m_light_direction_eye_loc;
```




<hr>



### variable m\_lod\_quality 

```C++
double OctreeLASLayerRenderer::m_lod_quality;
```




<hr>



### variable m\_lod\_query\_cpu\_ms 

```C++
double OctreeLASLayerRenderer::m_lod_query_cpu_ms;
```




<hr>



### variable m\_lod\_query\_vertices 

```C++
size_t OctreeLASLayerRenderer::m_lod_query_vertices;
```




<hr>



### variable m\_ms\_per\_vertex 

```C++
double OctreeLASLayerRenderer::m_ms_per_vertex;
```




<hr>



### variable m\_node\_stream 

```C++
std::unordered_map<const PointOctreeNode*, NodeStreamState> OctreeLASLayerRenderer::m_node_stream;
```




<hr>



### variable m\_point\_alpha\_loc 

```C++
int OctreeLASLayerRenderer::m_point_alpha_loc;
```




<hr>



### variable m\_point\_gl 

```C++
PointCloudGL OctreeLASLayerRenderer::m_point_gl;
```




<hr>



### variable m\_point\_offset\_loc 

```C++
int OctreeLASLayerRenderer::m_point_offset_loc;
```




<hr>



### variable m\_point\_radius\_loc 

```C++
int OctreeLASLayerRenderer::m_point_radius_loc;
```




<hr>



### variable m\_points\_uploaded 

```C++
bool OctreeLASLayerRenderer::m_points_uploaded;
```




<hr>



### variable m\_prev\_incremental\_stream 

```C++
bool OctreeLASLayerRenderer::m_prev_incremental_stream;
```




<hr>



### variable m\_proj\_matrix\_loc 

```C++
int OctreeLASLayerRenderer::m_proj_matrix_loc;
```




<hr>



### variable m\_shader 

```C++
std::unique_ptr<QOpenGLShaderProgram> OctreeLASLayerRenderer::m_shader;
```




<hr>



### variable m\_shader\_layer\_slot\_loc 

```C++
int OctreeLASLayerRenderer::m_shader_layer_slot_loc;
```




<hr>



### variable m\_stream\_backlog 

```C++
bool OctreeLASLayerRenderer::m_stream_backlog;
```




<hr>



### variable m\_stream\_camera\_dir 

```C++
QVector3D OctreeLASLayerRenderer::m_stream_camera_dir;
```




<hr>



### variable m\_stream\_camera\_pos 

```C++
QVector3D OctreeLASLayerRenderer::m_stream_camera_pos;
```




<hr>



### variable m\_view\_matrix\_loc 

```C++
int OctreeLASLayerRenderer::m_view_matrix_loc;
```




<hr>



### variable m\_viewport\_height\_loc 

```C++
int OctreeLASLayerRenderer::m_viewport_height_loc;
```




<hr>



### variable m\_visible\_fingerprint 

```C++
size_t OctreeLASLayerRenderer::m_visible_fingerprint;
```




<hr>
## Public Functions Documentation




### function OctreeLASLayerRenderer 

```C++
OctreeLASLayerRenderer::OctreeLASLayerRenderer (
    std::shared_ptr< LASLayer > layer,
    const Coordinate3D < double > & offset
) 
```




<hr>



### function can\_fbo\_pick 

```C++
bool OctreeLASLayerRenderer::can_fbo_pick () const
```




<hr>



### function collect\_visible\_octree\_nodes 

```C++
void OctreeLASLayerRenderer::collect_visible_octree_nodes (
    const LasRenderSnapshot & snap,
    const Camera & camera,
    double vis_quality,
    const Coordinate3D < double > & file_origin,
    std::vector< PointOctree::VisibleNode > & visible_nodes
) const
```




<hr>



### function consume\_gpu\_timer\_sample 

```C++
void OctreeLASLayerRenderer::consume_gpu_timer_sample (
    class QOpenGLExtraFunctions * gl
) 
```




<hr>



### function draw\_octree\_nodes 

```C++
size_t OctreeLASLayerRenderer::draw_octree_nodes (
    QOpenGLFunctions * f,
    const OctreePointVector & point_storage,
    const std::vector< PointOctree::VisibleNode > & visible_nodes,
    const Coordinate3D < double > & file_origin,
    const Coordinate3D < double > & scene_offset,
    double quality,
    bool incremental
) 
```




<hr>



### function draw\_preview\_points 

```C++
size_t OctreeLASLayerRenderer::draw_preview_points (
    QOpenGLFunctions * f,
    const OctreePointVector & preview,
    const Coordinate3D < double > & file_origin,
    const Coordinate3D < double > & scene_offset
) 
```




<hr>



### function ensure\_gpu\_timer 

```C++
void OctreeLASLayerRenderer::ensure_gpu_timer (
    class QOpenGLExtraFunctions * gl
) 
```




<hr>



### function ensure\_shader 

```C++
void OctreeLASLayerRenderer::ensure_shader () 
```




<hr>



### function estimate\_draw\_vertices 

```C++
size_t OctreeLASLayerRenderer::estimate_draw_vertices (
    const std::vector< PointOctree::VisibleNode > & visible_nodes,
    double quality,
    bool incremental
) const
```




<hr>



### function has\_stream\_backlog 

```C++
inline bool OctreeLASLayerRenderer::has_stream_backlog () const
```




<hr>



### function last\_point\_draw\_ms 

```C++
inline double OctreeLASLayerRenderer::last_point_draw_ms () const
```




<hr>



### function last\_point\_gpu\_ms 

```C++
inline double OctreeLASLayerRenderer::last_point_gpu_ms () const
```




<hr>



### function last\_point\_vertices\_drawn 

```C++
inline size_t OctreeLASLayerRenderer::last_point_vertices_drawn () const
```




<hr>



### function layer\_slot 

```C++
inline int OctreeLASLayerRenderer::layer_slot () const
```




<hr>



### function point\_from\_index 

```C++
std::optional< PointPickResult > OctreeLASLayerRenderer::point_from_index (
    uint32_t layer_slot,
    uint32_t pick_index,
    const Coordinate3D < double > & scene_offset
) const
```




<hr>



### function record\_lod\_sample 

```C++
void OctreeLASLayerRenderer::record_lod_sample (
    size_t vertices,
    double ms
) 
```




<hr>



### function refresh\_after\_style\_change 

```C++
void OctreeLASLayerRenderer::refresh_after_style_change () 
```




<hr>



### function render 

```C++
virtual void OctreeLASLayerRenderer::render (
    const Camera & camera,
    const RenderContext & ctx
) override
```



Implements [*LayerRenderer::render*](classLayerRenderer.md#function-render)


<hr>



### function reset\_stream\_cache 

```C++
void OctreeLASLayerRenderer::reset_stream_cache () 
```




<hr>



### function select\_draw\_quality 

```C++
double OctreeLASLayerRenderer::select_draw_quality (
    const std::vector< PointOctree::VisibleNode > & visible_nodes,
    bool incremental,
    bool lod_base_from_incremental,
    double target_draw_ms
) const
```




<hr>



### function set\_layer\_slot 

```C++
inline void OctreeLASLayerRenderer::set_layer_slot (
    int slot
) 
```




<hr>



### function stream\_camera\_changed 

```C++
bool OctreeLASLayerRenderer::stream_camera_changed (
    const Camera & camera
) const
```




<hr>



### function visible\_nodes\_fingerprint 

```C++
size_t OctreeLASLayerRenderer::visible_nodes_fingerprint (
    const std::vector< PointOctree::VisibleNode > & visible_nodes
) const
```




<hr>



### function visible\_set\_changed 

```C++
bool OctreeLASLayerRenderer::visible_set_changed (
    const std::vector< PointOctree::VisibleNode > & visible_nodes
) const
```




<hr>



### function ~OctreeLASLayerRenderer 

```C++
OctreeLASLayerRenderer::~OctreeLASLayerRenderer () override
```




<hr>
## Public Static Functions Documentation




### function sort\_visible\_by\_lod 

```C++
static void OctreeLASLayerRenderer::sort_visible_by_lod (
    std::vector< PointOctree::VisibleNode > & visible_nodes
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer_renderer.hpp`

