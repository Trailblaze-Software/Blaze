

# Class PointLayer



[**ClassList**](annotated.md) **>** [**PointLayer**](classPointLayer.md)








Inherits the following classes: [Layer](classLayer.md)


Inherited by the following classes: [LASLayer](classLASLayer.md)














































## Public Signals inherited from Layer

See [Layer](classLayer.md)

| Type | Name |
| ---: | :--- |
| signal void | [**data\_updated**](classLayer.md#signal-data_updated)  <br> |
| signal void | [**opacity\_changed**](classLayer.md#signal-opacity_changed)  <br> |
| signal void | [**vertical\_offset\_changed**](classLayer.md#signal-vertical_offset_changed)  <br> |
| signal void | [**visibility\_changed**](classLayer.md#signal-visibility_changed) (bool visible) <br> |






## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PointLayer**](#function-pointlayer) (std::string name) <br> |
| virtual  | [**~PointLayer**](#function-pointlayer) () = default<br> |


## Public Functions inherited from Layer

See [Layer](classLayer.md)

| Type | Name |
| ---: | :--- |
|   | [**Layer**](classLayer.md#function-layer) (std::string name, LayerKind kind) <br> |
| virtual [**Extent3D**](structExtent3D.md) | [**extent**](classLayer.md#function-extent) () const = 0<br> |
|  LayerKind | [**kind**](classLayer.md#function-kind) () const<br> |
| virtual std::string | [**name**](classLayer.md#function-name) () const<br> |
| virtual std::string | [**native\_projection**](classLayer.md#function-native_projection) () const<br> |
|  float | [**opacity**](classLayer.md#function-opacity) () const<br> |
| virtual std::string | [**projection**](classLayer.md#function-projection) () const = 0<br> |
|  void | [**set\_opacity**](classLayer.md#function-set_opacity) (float opacity) <br> |
|  void | [**set\_vertical\_offset**](classLayer.md#function-set_vertical_offset) (float vertical\_offset) <br> |
|  void | [**set\_visible**](classLayer.md#function-set_visible) (bool visible) <br> |
|  float | [**vertical\_offset**](classLayer.md#function-vertical_offset) () const<br> |
|  bool | [**visible**](classLayer.md#function-visible) () const<br> |
| virtual  | [**~Layer**](classLayer.md#function-layer) () = default<br> |
















## Protected Attributes inherited from Layer

See [Layer](classLayer.md)

| Type | Name |
| ---: | :--- |
|  LayerKind | [**m\_kind**](classLayer.md#variable-m_kind)  <br> |
|  std::string | [**m\_name**](classLayer.md#variable-m_name)  <br> |
|  float | [**m\_opacity**](classLayer.md#variable-m_opacity)   = `1.0f`<br> |
|  float | [**m\_vertical\_offset**](classLayer.md#variable-m_vertical_offset)   = `0.0f`<br> |
|  bool | [**m\_visible**](classLayer.md#variable-m_visible)   = `true`<br> |






































## Public Functions Documentation




### function PointLayer 

```C++
inline PointLayer::PointLayer (
    std::string name
) 
```




<hr>



### function ~PointLayer 

```C++
virtual PointLayer::~PointLayer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer.hpp`

