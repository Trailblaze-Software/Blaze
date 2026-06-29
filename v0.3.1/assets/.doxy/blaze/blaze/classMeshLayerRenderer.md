

# Class MeshLayerRenderer



[**ClassList**](annotated.md) **>** [**MeshLayerRenderer**](classMeshLayerRenderer.md)








Inherits the following classes: [LayerRenderer](classLayerRenderer.md)
















































## Public Signals inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
| signal void | [**repaint\_required**](classLayerRenderer.md#signal-repaint_required)  <br> |
| signal void | [**stream\_view\_reset**](classLayerRenderer.md#signal-stream_view_reset)  <br> |






## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MeshLayerRenderer**](#function-meshlayerrenderer) (std::shared\_ptr&lt; [**Layer**](classLayer.md) &gt; layer, std::function&lt; const [**AsyncRasterData**](classAsyncRasterData.md) \*()&gt; data\_accessor, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & offset, bool gpu\_texture=false) <br> |
| virtual void | [**render**](#function-render) (const [**Camera**](classCamera.md) & camera, const [**RenderContext**](structRenderContext.md) & ctx) override<br> |


## Public Functions inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
|  void | [**data\_update\_required**](classLayerRenderer.md#function-data_update_required) () <br> |
| virtual void | [**render**](classLayerRenderer.md#function-render) (const [**Camera**](classCamera.md) & camera, const [**RenderContext**](structRenderContext.md) & ctx) = 0<br> |
|  void | [**set\_visible**](classLayerRenderer.md#function-set_visible) (bool visible) <br> |
| virtual  | [**~LayerRenderer**](classLayerRenderer.md#function-layerrenderer) () = default<br> |




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






































## Public Functions Documentation




### function MeshLayerRenderer 

```C++
MeshLayerRenderer::MeshLayerRenderer (
    std::shared_ptr< Layer > layer,
    std::function< const AsyncRasterData *()> data_accessor,
    const Coordinate3D < double > & offset,
    bool gpu_texture=false
) 
```




<hr>



### function render 

```C++
virtual void MeshLayerRenderer::render (
    const Camera & camera,
    const RenderContext & ctx
) override
```



Implements [*LayerRenderer::render*](classLayerRenderer.md#function-render)


<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer_renderer.hpp`

