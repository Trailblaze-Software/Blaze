

# File contour.hpp



[**FileList**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**contour.hpp**](contour_8hpp.md)

[Go to the source code of this file](contour_8hpp_source.md)



* `#include <algorithm>`
* `#include <cmath>`
* `#include <limits>`
* `#include <utility>`
* `#include "config_input/config_input.hpp"`
* `#include "grid/grid.hpp"`
* `#include "grid/grid_ops.hpp"`
* `#include "utilities/coordinate.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Contour**](classContour.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**bool**](classCoordinate2D.md) | [**crosses\_contour**](#function-crosses_contour) (std::pair&lt; T, T &gt; hs, T contour\_interval) <br> |
|  std::set&lt; T &gt; | [**get\_contour\_heights**](#function-get_contour_heights) (std::pair&lt; T, T &gt; hs, T contour\_interval) <br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; | [**interpolate\_coordinates**](#function-interpolate_coordinates) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; & a, [**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; & b, [**const**](classCoordinate2D.md) [**U**](classCoordinate2D.md) & a\_val, [**const**](classCoordinate2D.md) [**U**](classCoordinate2D.md) & b\_val, [**const**](classCoordinate2D.md) [**U**](classCoordinate2D.md) & target) <br> |
|  T | [**round\_down**](#function-round_down) (T val, T interval) <br> |




























## Public Functions Documentation




### function crosses\_contour 

```C++
template<typename T>
inline bool crosses_contour (
    std::pair< T, T > hs,
    T contour_interval
) 
```




<hr>



### function get\_contour\_heights 

```C++
template<typename T>
inline std::set< T > get_contour_heights (
    std::pair< T, T > hs,
    T contour_interval
) 
```




<hr>



### function interpolate\_coordinates 

```C++
template<typename T, typename  U>
Coordinate2D < T > interpolate_coordinates (
    const  Coordinate2D < T > & a,
    const  Coordinate2D < T > & b,
    const  U & a_val,
    const  U & b_val,
    const  U & target
) 
```




<hr>



### function round\_down 

```C++
template<typename T>
T round_down (
    T val,
    T interval
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/contour.hpp`

