

# Class LayerRenderer



[**ClassList**](annotated.md) **>** [**LayerRenderer**](classLayerRenderer.md)








Inherits the following classes: QObject


Inherited by the following classes: [LASLayerRenderer](classLASLayerRenderer.md)




























## Public Signals

| Type | Name |
| ---: | :--- |
| signal [**void**](classCoordinate2D.md) | [**repaint\_required**](classLayerRenderer.md#signal-repaint_required)  <br> |




## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**data\_update\_required**](#function-data_update_required) () <br> |
| virtual [**void**](classCoordinate2D.md) | [**render**](#function-render) ([**const**](classCoordinate2D.md) [**Camera**](classCamera.md) & camera) = 0<br> |
| virtual  | [**~LayerRenderer**](#function-layerrenderer) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::unique\_ptr&lt; [**LayerRenderer**](classLayerRenderer.md) &gt; | [**create**](#function-create) (std::shared\_ptr&lt; [**Layer**](classLayer.md) &gt; layer, [**const**](classCoordinate2D.md) [**Coordinate3D**](classCoordinate3D.md)&lt; [**double**](classCoordinate2D.md) &gt; & offset) <br> |






## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**bool**](classCoordinate2D.md) | [**m\_data\_update\_required**](#variable-m_data_update_required)   = `[**true**](classCoordinate2D.md)`<br> |




















## Public Signals Documentation




### signal repaint\_required 

```C++
void LayerRenderer::repaint_required;
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
    const  Camera & camera
) = 0
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
static inline std::unique_ptr< LayerRenderer > LayerRenderer::create (
    std::shared_ptr< Layer > layer,
    const  Coordinate3D < double > & offset
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_data\_update\_required 

```C++
bool LayerRenderer::m_data_update_required;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer_renderer.hpp`

