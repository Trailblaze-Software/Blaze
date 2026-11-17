

# Class LASLayer



[**ClassList**](annotated.md) **>** [**LASLayer**](classLASLayer.md)








Inherits the following classes: [PointLayer](classPointLayer.md)






























































## Public Signals

| Type | Name |
| ---: | :--- |
| signal void | [**lod\_settings\_changed**](classLASLayer.md#signal-lod_settings_changed)  <br> |
| signal void | [**point\_colors\_changed**](classLASLayer.md#signal-point_colors_changed)  <br> |
| signal void | [**point\_opacity\_changed**](classLASLayer.md#signal-point_opacity_changed)  <br> |
| signal void | [**point\_size\_changed**](classLASLayer.md#signal-point_size_changed)  <br> |
| signal void | [**point\_stream\_budget\_changed**](classLASLayer.md#signal-point_stream_budget_changed)  <br> |




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
|   | [**LASLayer**](#function-laslayer) (const fs::path & file, [**AsyncProgressTracker**](classAsyncProgressTracker.md) progress\_tracker, const std::string & target\_crs\_wkt={}) <br> |
| virtual [**Extent3D**](structExtent3D.md) | [**extent**](#function-extent) () override const<br> |
|  const fs::path & | [**file\_path**](#function-file_path) () const<br> |
|  const std::array&lt; uint8\_t, 3 &gt; & | [**fixed\_point\_color**](#function-fixed_point_color) () const<br> |
|  const [**AsyncOctreeLASData**](classAsyncOctreeLASData.md) & | [**las\_data**](#function-las_data-12) () const<br> |
|  [**AsyncOctreeLASData**](classAsyncOctreeLASData.md) & | [**las\_data**](#function-las_data-22) () <br> |
|  float | [**lod\_quality\_multiplier**](#function-lod_quality_multiplier) () const<br> |
|  size\_t | [**max\_points\_per\_node**](#function-max_points_per_node) () const<br> |
| virtual std::string | [**native\_projection**](#function-native_projection) () override const<br> |
|  float | [**point\_alpha**](#function-point_alpha) () const<br> |
|  PointColorMode | [**point\_color\_mode**](#function-point_color_mode) () const<br> |
|  float | [**point\_radius\_m**](#function-point_radius_m) () const<br> |
|  float | [**point\_stream\_budget\_ms**](#function-point_stream_budget_ms) () const<br> |
| virtual std::string | [**projection**](#function-projection) () override const<br> |
|  void | [**set\_fixed\_point\_color**](#function-set_fixed_point_color) (const std::array&lt; uint8\_t, 3 &gt; & color) <br> |
|  void | [**set\_lod\_quality\_multiplier**](#function-set_lod_quality_multiplier) (float multiplier) <br> |
|  void | [**set\_max\_points\_per\_node**](#function-set_max_points_per_node) (size\_t max\_points) <br> |
|  void | [**set\_point\_alpha**](#function-set_point_alpha) (float alpha) <br> |
|  void | [**set\_point\_color\_mode**](#function-set_point_color_mode) (PointColorMode mode) <br> |
|  void | [**set\_point\_radius\_m**](#function-set_point_radius_m) (float radius\_m) <br> |
|  void | [**set\_point\_stream\_budget\_ms**](#function-set_point_stream_budget_ms) (float ms) <br> |


## Public Functions inherited from PointLayer

See [PointLayer](classPointLayer.md)

| Type | Name |
| ---: | :--- |
|   | [**PointLayer**](classPointLayer.md#function-pointlayer) (std::string name) <br> |
| virtual  | [**~PointLayer**](classPointLayer.md#function-pointlayer) () = default<br> |


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
























































## Public Signals Documentation




### signal lod\_settings\_changed 

```C++
void LASLayer::lod_settings_changed;
```




<hr>



### signal point\_colors\_changed 

```C++
void LASLayer::point_colors_changed;
```




<hr>



### signal point\_opacity\_changed 

```C++
void LASLayer::point_opacity_changed;
```




<hr>



### signal point\_size\_changed 

```C++
void LASLayer::point_size_changed;
```




<hr>



### signal point\_stream\_budget\_changed 

```C++
void LASLayer::point_stream_budget_changed;
```




<hr>
## Public Functions Documentation




### function LASLayer 

```C++
inline explicit LASLayer::LASLayer (
    const fs::path & file,
    AsyncProgressTracker progress_tracker,
    const std::string & target_crs_wkt={}
) 
```




<hr>



### function extent 

```C++
inline virtual Extent3D LASLayer::extent () override const
```



Implements [*Layer::extent*](classLayer.md#function-extent)


<hr>



### function file\_path 

```C++
inline const fs::path & LASLayer::file_path () const
```




<hr>



### function fixed\_point\_color 

```C++
inline const std::array< uint8_t, 3 > & LASLayer::fixed_point_color () const
```




<hr>



### function las\_data [1/2]

```C++
inline const AsyncOctreeLASData & LASLayer::las_data () const
```




<hr>



### function las\_data [2/2]

```C++
inline AsyncOctreeLASData & LASLayer::las_data () 
```




<hr>



### function lod\_quality\_multiplier 

```C++
inline float LASLayer::lod_quality_multiplier () const
```




<hr>



### function max\_points\_per\_node 

```C++
inline size_t LASLayer::max_points_per_node () const
```




<hr>



### function native\_projection 

```C++
inline virtual std::string LASLayer::native_projection () override const
```



Implements [*Layer::native\_projection*](classLayer.md#function-native_projection)


<hr>



### function point\_alpha 

```C++
inline float LASLayer::point_alpha () const
```




<hr>



### function point\_color\_mode 

```C++
inline PointColorMode LASLayer::point_color_mode () const
```




<hr>



### function point\_radius\_m 

```C++
inline float LASLayer::point_radius_m () const
```




<hr>



### function point\_stream\_budget\_ms 

```C++
inline float LASLayer::point_stream_budget_ms () const
```




<hr>



### function projection 

```C++
inline virtual std::string LASLayer::projection () override const
```



Implements [*Layer::projection*](classLayer.md#function-projection)


<hr>



### function set\_fixed\_point\_color 

```C++
inline void LASLayer::set_fixed_point_color (
    const std::array< uint8_t, 3 > & color
) 
```




<hr>



### function set\_lod\_quality\_multiplier 

```C++
inline void LASLayer::set_lod_quality_multiplier (
    float multiplier
) 
```




<hr>



### function set\_max\_points\_per\_node 

```C++
inline void LASLayer::set_max_points_per_node (
    size_t max_points
) 
```




<hr>



### function set\_point\_alpha 

```C++
inline void LASLayer::set_point_alpha (
    float alpha
) 
```




<hr>



### function set\_point\_color\_mode 

```C++
inline void LASLayer::set_point_color_mode (
    PointColorMode mode
) 
```




<hr>



### function set\_point\_radius\_m 

```C++
inline void LASLayer::set_point_radius_m (
    float radius_m
) 
```




<hr>



### function set\_point\_stream\_budget\_ms 

```C++
inline void LASLayer::set_point_stream_budget_ms (
    float ms
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer.hpp`

