

# Class Contour



[**ClassList**](annotated.md) **>** [**Contour**](classContour.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Contour**](#function-contour) (double height, std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; && points, std::string layer\_name="") <br> |
|  void | [**close\_loop**](#function-close_loop) () <br> |
|  double | [**height**](#function-height) () const<br> |
|  bool | [**is\_loop**](#function-is_loop) () const<br> |
|  const std::string & | [**layer\_name**](#function-layer_name) () const<br> |
|  void | [**orient\_consistent**](#function-orient_consistent) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & value\_grid) <br> |
|  const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & | [**points**](#function-points-12) () const<br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & | [**points**](#function-points-22) () <br> |
|  void | [**push\_back**](#function-push_back) (const [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; & point) <br> |
|  [**Polyline**](classPolyline.md) | [**to\_polyline**](#function-to_polyline) (const [**ContourConfigs**](structContourConfigs.md) & configs) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Contour**](classContour.md) | [**FromGridGraph**](#function-fromgridgraph) (const [**LineCoord2D**](classLineCoord2D.md)&lt; size\_t &gt; & starting\_point, double height, const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**GridGraph**](classGridGraph.md)&lt; std::set&lt; double &gt; &gt; & contour\_heights) <br> |
|  [**Contour**](classContour.md) | [**from\_polyline**](#function-from_polyline) (const [**Polyline**](classPolyline.md) & polyline) <br> |


























## Public Functions Documentation




### function Contour 

```C++
inline Contour::Contour (
    double height,
    std::vector< Coordinate2D < double > > && points,
    std::string layer_name=""
) 
```




<hr>



### function close\_loop 

```C++
inline void Contour::close_loop () 
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



### function layer\_name 

```C++
inline const std::string & Contour::layer_name () const
```




<hr>



### function orient\_consistent 

```C++
template<typename T>
inline void Contour::orient_consistent (
    const GeoGrid < T > & value_grid
) 
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
    const Coordinate2D < double > & point
) 
```




<hr>



### function to\_polyline 

```C++
Polyline Contour::to_polyline (
    const ContourConfigs & configs
) const
```




<hr>
## Public Static Functions Documentation




### function FromGridGraph 

```C++
template<typename T>
static inline Contour Contour::FromGridGraph (
    const LineCoord2D < size_t > & starting_point,
    double height,
    const GeoGrid < T > & grid,
    GridGraph < std::set< double > > & contour_heights
) 
```




<hr>



### function from\_polyline 

```C++
static Contour Contour::from_polyline (
    const Polyline & polyline
) 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Contour::operator<< (
    std::ostream & os,
    const Contour & contour
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/contour.hpp`

