

# Class Polyline



[**ClassList**](annotated.md) **>** [**Polyline**](classPolyline.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::string | [**layer**](#variable-layer)  <br> |
|  std::string | [**name**](#variable-name)  <br> |
|  std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; | [**vertices**](#variable-vertices)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**write\_to\_dxf**](#function-write_to_dxf) (std::ofstream & dxfFile) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Polyline**](classPolyline.md) | [**read\_from\_dxf**](#function-read_from_dxf) (std::ifstream & dxfFile) <br> |


























## Public Attributes Documentation




### variable layer 

```C++
std::string Polyline::layer;
```




<hr>



### variable name 

```C++
std::string Polyline::name;
```




<hr>



### variable vertices 

```C++
std::vector<Coordinate2D<double> > Polyline::vertices;
```




<hr>
## Public Functions Documentation




### function write\_to\_dxf 

```C++
inline void Polyline::write_to_dxf (
    std::ofstream & dxfFile
) const
```




<hr>
## Public Static Functions Documentation




### function read\_from\_dxf 

```C++
static inline Polyline Polyline::read_from_dxf (
    std::ifstream & dxfFile
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/dxf/dxf.hpp`

