

# Class Layer



[**ClassList**](annotated.md) **>** [**Layer**](classLayer.md)








Inherits the following classes: QObject


Inherited by the following classes: [ContourLayer](classContourLayer.md),  [DemLayer](classDemLayer.md),  [PointLayer](classPointLayer.md),  [SlopeLayer](classSlopeLayer.md),  [TexturedDemLayer](classTexturedDemLayer.md)




























## Public Signals

| Type | Name |
| ---: | :--- |
| signal void | [**data\_updated**](classLayer.md#signal-data_updated)  <br> |
| signal void | [**opacity\_changed**](classLayer.md#signal-opacity_changed)  <br> |
| signal void | [**vertical\_offset\_changed**](classLayer.md#signal-vertical_offset_changed)  <br> |
| signal void | [**visibility\_changed**](classLayer.md#signal-visibility_changed) (bool visible) <br> |




## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Layer**](#function-layer) (std::string name, LayerKind kind) <br> |
| virtual [**Extent3D**](structExtent3D.md) | [**extent**](#function-extent) () const = 0<br> |
|  LayerKind | [**kind**](#function-kind) () const<br> |
| virtual std::string | [**name**](#function-name) () const<br> |
| virtual std::string | [**native\_projection**](#function-native_projection) () const<br> |
|  float | [**opacity**](#function-opacity) () const<br> |
| virtual std::string | [**projection**](#function-projection) () const = 0<br> |
|  void | [**set\_opacity**](#function-set_opacity) (float opacity) <br> |
|  void | [**set\_vertical\_offset**](#function-set_vertical_offset) (float vertical\_offset) <br> |
|  void | [**set\_visible**](#function-set_visible) (bool visible) <br> |
|  float | [**vertical\_offset**](#function-vertical_offset) () const<br> |
|  bool | [**visible**](#function-visible) () const<br> |
| virtual  | [**~Layer**](#function-layer) () = default<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  LayerKind | [**m\_kind**](#variable-m_kind)  <br> |
|  std::string | [**m\_name**](#variable-m_name)  <br> |
|  float | [**m\_opacity**](#variable-m_opacity)   = `1.0f`<br> |
|  float | [**m\_vertical\_offset**](#variable-m_vertical_offset)   = `0.0f`<br> |
|  bool | [**m\_visible**](#variable-m_visible)   = `true`<br> |




















## Public Signals Documentation




### signal data\_updated 

```C++
void Layer::data_updated;
```




<hr>



### signal opacity\_changed 

```C++
void Layer::opacity_changed;
```




<hr>



### signal vertical\_offset\_changed 

```C++
void Layer::vertical_offset_changed;
```




<hr>



### signal visibility\_changed 

```C++
void Layer::visibility_changed;
```




<hr>
## Public Functions Documentation




### function Layer 

```C++
inline Layer::Layer (
    std::string name,
    LayerKind kind
) 
```




<hr>



### function extent 

```C++
virtual Extent3D Layer::extent () const = 0
```




<hr>



### function kind 

```C++
inline LayerKind Layer::kind () const
```




<hr>



### function name 

```C++
inline virtual std::string Layer::name () const
```




<hr>



### function native\_projection 

```C++
inline virtual std::string Layer::native_projection () const
```




<hr>



### function opacity 

```C++
inline float Layer::opacity () const
```




<hr>



### function projection 

```C++
virtual std::string Layer::projection () const = 0
```




<hr>



### function set\_opacity 

```C++
inline void Layer::set_opacity (
    float opacity
) 
```




<hr>



### function set\_vertical\_offset 

```C++
inline void Layer::set_vertical_offset (
    float vertical_offset
) 
```




<hr>



### function set\_visible 

```C++
inline void Layer::set_visible (
    bool visible
) 
```




<hr>



### function vertical\_offset 

```C++
inline float Layer::vertical_offset () const
```




<hr>



### function visible 

```C++
inline bool Layer::visible () const
```




<hr>



### function ~Layer 

```C++
virtual Layer::~Layer () = default
```




<hr>
## Protected Attributes Documentation




### variable m\_kind 

```C++
LayerKind Layer::m_kind;
```




<hr>



### variable m\_name 

```C++
std::string Layer::m_name;
```




<hr>



### variable m\_opacity 

```C++
float Layer::m_opacity;
```




<hr>



### variable m\_vertical\_offset 

```C++
float Layer::m_vertical_offset;
```




<hr>



### variable m\_visible 

```C++
bool Layer::m_visible;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer.hpp`

