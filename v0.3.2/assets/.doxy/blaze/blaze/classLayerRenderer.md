

# Class LayerRenderer



[**ClassList**](annotated.md) **>** [**LayerRenderer**](classLayerRenderer.md)








Inherits the following classes: QObject


Inherited by the following classes: [ContourLayerRenderer](classContourLayerRenderer.md),  [MeshLayerRenderer](classMeshLayerRenderer.md),  [OctreeLASLayerRenderer](classOctreeLASLayerRenderer.md)




























## Public Signals

| Type | Name |
| ---: | :--- |
| signal void | [**repaint\_required**](classLayerRenderer.md#signal-repaint_required)  <br> |
| signal void | [**stream\_view\_reset**](classLayerRenderer.md#signal-stream_view_reset)  <br> |




## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**data\_update\_required**](#function-data_update_required) () <br> |
| virtual void | [**render**](#function-render) (const [**Camera**](classCamera.md) & camera, const [**RenderContext**](structRenderContext.md) & ctx) = 0<br> |
|  void | [**set\_visible**](#function-set_visible) (bool visible) <br> |
| virtual  | [**~LayerRenderer**](#function-layerrenderer) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::unique\_ptr&lt; [**LayerRenderer**](classLayerRenderer.md) &gt; | [**create**](#function-create) (std::shared\_ptr&lt; [**Layer**](classLayer.md) &gt; layer, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & offset) <br> |






## Protected Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**m\_data\_update\_required**](#variable-m_data_update_required)   = `true`<br> |
|  bool | [**m\_visible**](#variable-m_visible)   = `true`<br> |




















## Public Signals Documentation




### signal repaint\_required 

```C++
void LayerRenderer::repaint_required;
```




<hr>



### signal stream\_view\_reset 

```C++
void LayerRenderer::stream_view_reset;
```




<hr>
## Public Functions Documentation




### function data\_update\_required 

```C++
inline void LayerRenderer::data_update_required () 
```




<hr>



### function render 

```C++
virtual void LayerRenderer::render (
    const Camera & camera,
    const RenderContext & ctx
) = 0
```




<hr>



### function set\_visible 

```C++
inline void LayerRenderer::set_visible (
    bool visible
) 
```




<hr>



### function ~LayerRenderer 

```C++
virtual LayerRenderer::~LayerRenderer () = default
```




<hr>
## Public Static Functions Documentation




### function create 

```C++
static std::unique_ptr< LayerRenderer > LayerRenderer::create (
    std::shared_ptr< Layer > layer,
    const Coordinate3D < double > & offset
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_data\_update\_required 

```C++
bool LayerRenderer::m_data_update_required;
```




<hr>



### variable m\_visible 

```C++
bool LayerRenderer::m_visible;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer_renderer.hpp`

