

# Class GeoTransform



[**ClassList**](annotated.md) **>** [**GeoTransform**](classGeoTransform.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GeoTransform**](#function-geotransform-14) ([**double**](classCoordinate2D.md) upper\_left\_x, [**double**](classCoordinate2D.md) upper\_left\_y, [**double**](classCoordinate2D.md) dx=1.0, [**double**](classCoordinate2D.md) dy=-1.0) <br> |
|   | [**GeoTransform**](#function-geotransform-24) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & upper\_left, [**double**](classCoordinate2D.md) resolution) <br> |
|   | [**GeoTransform**](#function-geotransform-34) () <br> |
|   | [**GeoTransform**](#function-geotransform-44) ([**GDALDataset**](classCoordinate2D.md) & dataset) <br> |
|  [**double**](classCoordinate2D.md) | [**dx**](#function-dx) () const<br> |
|  [**double**](classCoordinate2D.md) | [**dy**](#function-dy) () const<br> |
|  [**const**](classCoordinate2D.md) [**double**](classCoordinate2D.md) \* | [**get\_raw**](#function-get_raw) () const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**pixel\_to\_projection**](#function-pixel_to_projection) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & coord) const<br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**projection\_to\_pixel**](#function-projection_to_pixel) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & coord) const<br> |
|  [**double**](classCoordinate2D.md) | [**rot\_x**](#function-rot_x) () const<br> |
|  [**double**](classCoordinate2D.md) | [**rot\_y**](#function-rot_y) () const<br> |
|  [**void**](classCoordinate2D.md) | [**set\_dx**](#function-set_dx) ([**double**](classCoordinate2D.md) dx) <br> |
|  [**void**](classCoordinate2D.md) | [**set\_dy**](#function-set_dy) ([**double**](classCoordinate2D.md) dy) <br> |
|  [**GeoTransform**](classGeoTransform.md) | [**with\_new\_resolution**](#function-with_new_resolution) ([**double**](classCoordinate2D.md) new\_resolution) const<br> |
|  [**double**](classCoordinate2D.md) | [**x**](#function-x) () const<br> |
|  [**double**](classCoordinate2D.md) | [**y**](#function-y) () const<br> |




























## Public Functions Documentation




### function GeoTransform [1/4]

```C++
inline GeoTransform::GeoTransform (
    double upper_left_x,
    double upper_left_y,
    double dx=1.0,
    double dy=-1.0
) 
```




<hr>



### function GeoTransform [2/4]

```C++
inline explicit GeoTransform::GeoTransform (
    const  Coordinate2D < double > & upper_left,
    double resolution
) 
```




<hr>



### function GeoTransform [3/4]

```C++
inline GeoTransform::GeoTransform () 
```




<hr>



### function GeoTransform [4/4]

```C++
explicit GeoTransform::GeoTransform (
    GDALDataset & dataset
) 
```




<hr>



### function dx 

```C++
inline double GeoTransform::dx () const
```




<hr>



### function dy 

```C++
inline double GeoTransform::dy () const
```




<hr>



### function get\_raw 

```C++
inline const  double * GeoTransform::get_raw () const
```




<hr>



### function pixel\_to\_projection 

```C++
inline Coordinate2D < double > GeoTransform::pixel_to_projection (
    const  Coordinate2D < double > & coord
) const
```




<hr>



### function projection\_to\_pixel 

```C++
inline Coordinate2D < double > GeoTransform::projection_to_pixel (
    const  Coordinate2D < double > & coord
) const
```




<hr>



### function rot\_x 

```C++
inline double GeoTransform::rot_x () const
```




<hr>



### function rot\_y 

```C++
inline double GeoTransform::rot_y () const
```




<hr>



### function set\_dx 

```C++
inline void GeoTransform::set_dx (
    double dx
) 
```




<hr>



### function set\_dy 

```C++
inline void GeoTransform::set_dy (
    double dy
) 
```




<hr>



### function with\_new\_resolution 

```C++
inline GeoTransform GeoTransform::with_new_resolution (
    double new_resolution
) const
```




<hr>



### function x 

```C++
inline double GeoTransform::x () const
```




<hr>



### function y 

```C++
inline double GeoTransform::y () const
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & GeoTransform::operator<< (
    std::ostream & os,
    const  GeoTransform & transform
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/grid.hpp`

