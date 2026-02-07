

# File coordinate.hpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**coordinate.hpp**](coordinate_8hpp.md)

[Go to the source code of this file](coordinate_8hpp_source.md)



* `#include <array>`
* `#include <cmath>`
* `#include <iostream>`
* `#include <ostream>`
* `#include <type_traits>`
* `#include <vector>`
* `#include "assert/assert.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Coordinate2D**](classCoordinate2D.md) &lt;[**typename**](classCoordinate2D.md) T&gt;<br> |
| class | [**Coordinate3D**](classCoordinate3D.md) &lt;[**typename**](classCoordinate2D.md) T&gt;<br> |
| class | [**Direction2D**](classDirection2D.md) <br> |
| struct | [**Extent2D**](structExtent2D.md) <br> |
| struct | [**Extent3D**](structExtent3D.md) <br> |
| class | [**LineCoord2D**](classLineCoord2D.md) &lt;[**typename**](classCoordinate2D.md) T, [**typename**](classCoordinate2D.md)&gt;<br> |
| class | [**LineCoord2DCrossing**](classLineCoord2DCrossing.md) &lt;[**typename**](classCoordinate2D.md) T&gt;<br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**const**](classCoordinate2D.md) std::array&lt; [**Direction2D**](classDirection2D.md), 8 &gt; | [**ALL\_DIRECTIONS**](#variable-all_directions)   = `/* multi line expression */`<br> |
|  [**const**](classCoordinate2D.md) std::array&lt; [**Direction2D**](classDirection2D.md), 4 &gt; | [**ORTHOGONAL\_DIRECTIONS**](#variable-orthogonal_directions)   = `/* multi line expression */`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::array&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt;, 4 &gt; | [**orthogonal\_neighbors**](#function-orthogonal_neighbors) ([**const**](classCoordinate2D.md) [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; & coord) <br> |




























## Public Attributes Documentation




### variable ALL\_DIRECTIONS 

```C++
const std::array<Direction2D, 8> ALL_DIRECTIONS;
```




<hr>



### variable ORTHOGONAL\_DIRECTIONS 

```C++
const std::array<Direction2D, 4> ORTHOGONAL_DIRECTIONS;
```




<hr>
## Public Functions Documentation




### function orthogonal\_neighbors 

```C++
template<typename T, typename>
std::array< Coordinate2D < T >, 4 > orthogonal_neighbors (
    const  Coordinate2D < T > & coord
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

