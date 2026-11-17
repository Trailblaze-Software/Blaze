

# Class ContourLayer



[**ClassList**](annotated.md) **>** [**ContourLayer**](classContourLayer.md)








Inherits the following classes: [Layer](classLayer.md)
















































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
|   | [**ContourLayer**](#function-contourlayer) (const fs::path & gpkg\_path, [**AsyncProgressTracker**](classAsyncProgressTracker.md) async\_progress\_tracker, const std::string & target\_crs\_wkt={}) <br> |
|  const std::vector&lt; [**Contour**](classContour.md) &gt; & | [**contours**](#function-contours) () const<br> |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**copy\_contours**](#function-copy_contours) () const<br> |
| virtual [**Extent3D**](structExtent3D.md) | [**extent**](#function-extent) () override const<br> |
| virtual std::string | [**native\_projection**](#function-native_projection) () override const<br> |
| virtual std::string | [**projection**](#function-projection) () override const<br> |
|  bool | [**ready**](#function-ready) () const<br> |


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




### function ContourLayer 

```C++
inline ContourLayer::ContourLayer (
    const fs::path & gpkg_path,
    AsyncProgressTracker async_progress_tracker,
    const std::string & target_crs_wkt={}
) 
```




<hr>



### function contours 

```C++
inline const std::vector< Contour > & ContourLayer::contours () const
```




<hr>



### function copy\_contours 

```C++
inline std::vector< Contour > ContourLayer::copy_contours () const
```




<hr>



### function extent 

```C++
inline virtual Extent3D ContourLayer::extent () override const
```



Implements [*Layer::extent*](classLayer.md#function-extent)


<hr>



### function native\_projection 

```C++
inline virtual std::string ContourLayer::native_projection () override const
```



Implements [*Layer::native\_projection*](classLayer.md#function-native_projection)


<hr>



### function projection 

```C++
inline virtual std::string ContourLayer::projection () override const
```



Implements [*Layer::projection*](classLayer.md#function-projection)


<hr>



### function ready 

```C++
inline bool ContourLayer::ready () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer.hpp`

