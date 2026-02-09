

# Class Contour



[**ClassList**](annotated.md) **>** [**Contour**](classContour.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Contour**](#function-contour) ([**double**](classCoordinate2D.md) height, std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; && points) <br> |
|  [**double**](classCoordinate2D.md) | [**height**](#function-height) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**is\_loop**](#function-is_loop) () const<br> |
|  [**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & | [**points**](#function-points-12) () const<br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & | [**points**](#function-points-22) () <br> |
|  [**void**](classCoordinate2D.md) | [**push\_back**](#function-push_back) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; & point) <br> |
|  [**Polyline**](classPolyline.md) | [**to\_polyline**](#function-to_polyline) ([**const**](classCoordinate2D.md) [**ContourConfigs**](structContourConfigs.md) & configs) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Contour**](classContour.md) | [**FromGridGraph**](#function-fromgridgraph) ([**const**](classCoordinate2D.md) [**LineCoord2D**](classLineCoord2D.md)&lt; [**size\_t**](classCoordinate2D.md) &gt; & starting\_point, [**double**](classCoordinate2D.md) height, [**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; & grid, [**GridGraph**](classGridGraph.md)&lt; std::set&lt; [**double**](classCoordinate2D.md) &gt; &gt; & contour\_heights) <br> |
|  [**Contour**](classContour.md) | [**from\_polyline**](#function-from_polyline) ([**const**](classCoordinate2D.md) [**Polyline**](classPolyline.md) & polyline) <br> |


























## Public Functions Documentation




### function Contour 

```C++
inline Contour::Contour (
    double height,
    std::vector< Coordinate2D < double > > && points
) 
```




<hr>



### function height 

```C++
inline double Contour::height () const
```




<hr>



### function is\_loop 

```C++
inline bool Contour::is_loop () const
```




<hr>



### function points [1/2]

```C++
inline const std::vector< Coordinate2D < double > > & Contour::points () const
```




<hr>



### function points [2/2]

```C++
inline std::vector< Coordinate2D < double > > & Contour::points () 
```




<hr>



### function push\_back 

```C++
inline void Contour::push_back (
    const  Coordinate2D < double > & point
) 
```




<hr>



### function to\_polyline 

```C++
Polyline Contour::to_polyline (
    const  ContourConfigs & configs
) const
```




<hr>
## Public Static Functions Documentation




### function FromGridGraph 

```C++
static inline Contour Contour::FromGridGraph (
    const  LineCoord2D < size_t > & starting_point,
    double height,
    const  GeoGrid < double > & grid,
    GridGraph < std::set< double > > & contour_heights
) 
```




<hr>



### function from\_polyline 

```C++
static Contour Contour::from_polyline (
    const  Polyline & polyline
) 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Contour::operator<< (
    std::ostream & os,
    const  Contour & contour
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/contour.hpp`

