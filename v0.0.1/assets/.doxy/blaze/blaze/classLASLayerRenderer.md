

# Class LASLayerRenderer



[**ClassList**](annotated.md) **>** [**LASLayerRenderer**](classLASLayerRenderer.md)








Inherits the following classes: [LayerRenderer](classLayerRenderer.md)
















































## Public Signals inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
| signal [**void**](classCoordinate2D.md) | [**repaint\_required**](classLayerRenderer.md#signal-repaint_required)  <br> |






## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LASLayerRenderer**](#function-laslayerrenderer) (std::shared\_ptr&lt; [**LASLayer**](classLASLayer.md) &gt; layer, [**const**](classCoordinate2D.md) [**Coordinate3D**](classCoordinate3D.md)&lt; [**double**](classCoordinate2D.md) &gt; & offset) <br> |
|  [**void**](classCoordinate2D.md) | [**load\_data**](#function-load_data) (std::shared\_ptr&lt; [**LASLayer**](classLASLayer.md) &gt; layer, [**const**](classCoordinate2D.md) [**Coordinate3D**](classCoordinate3D.md)&lt; [**double**](classCoordinate2D.md) &gt; & offset) <br> |
| virtual [**void**](classCoordinate2D.md) | [**render**](#function-render) ([**const**](classCoordinate2D.md) [**Camera**](classCamera.md) & camera) override<br> |
| virtual  | [**~LASLayerRenderer**](#function-laslayerrenderer) () = default<br> |


## Public Functions inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**data\_update\_required**](classLayerRenderer.md#function-data_update_required) () <br> |
| virtual [**void**](classCoordinate2D.md) | [**render**](classLayerRenderer.md#function-render) ([**const**](classCoordinate2D.md) [**Camera**](classCamera.md) & camera) = 0<br> |
| virtual  | [**~LayerRenderer**](classLayerRenderer.md#function-layerrenderer) () = default<br> |




## Public Static Functions inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
|  std::unique\_ptr&lt; [**LayerRenderer**](classLayerRenderer.md) &gt; | [**create**](classLayerRenderer.md#function-create) (std::shared\_ptr&lt; [**Layer**](classLayer.md) &gt; layer, [**const**](classCoordinate2D.md) [**Coordinate3D**](classCoordinate3D.md)&lt; [**double**](classCoordinate2D.md) &gt; & offset) <br> |












## Protected Attributes inherited from LayerRenderer

See [LayerRenderer](classLayerRenderer.md)

| Type | Name |
| ---: | :--- |
|  [**bool**](classCoordinate2D.md) | [**m\_data\_update\_required**](classLayerRenderer.md#variable-m_data_update_required)   = `[**true**](classCoordinate2D.md)`<br> |






































## Public Functions Documentation




### function LASLayerRenderer 

```C++
inline LASLayerRenderer::LASLayerRenderer (
    std::shared_ptr< LASLayer > layer,
    const  Coordinate3D < double > & offset
) 
```




<hr>



### function load\_data 

```C++
inline void LASLayerRenderer::load_data (
    std::shared_ptr< LASLayer > layer,
    const  Coordinate3D < double > & offset
) 
```




<hr>



### function render 

```C++
inline virtual void LASLayerRenderer::render (
    const  Camera & camera
) override
```



Implements [*LayerRenderer::render*](classLayerRenderer.md#function-render)


<hr>



### function ~LASLayerRenderer 

```C++
virtual LASLayerRenderer::~LASLayerRenderer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer_renderer.hpp`

