

# File coordinate.hpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**coordinate.hpp**](coordinate_8hpp.md)

[Go to the source code of this file](coordinate_8hpp_source.md)



* `#include <array>`
* `#include <cmath>`
* `#include <iostream>`
* `#include <limits>`
* `#include <ostream>`
* `#include <type_traits>`
* `#include <vector>`
* `#include "assert/assert.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Coordinate2D**](classCoordinate2D.md) &lt;typename T&gt;<br> |
| class | [**Coordinate3D**](classCoordinate3D.md) &lt;typename T&gt;<br> |
| class | [**Direction2D**](classDirection2D.md) <br> |
| struct | [**Extent2D**](structExtent2D.md) <br> |
| struct | [**Extent3D**](structExtent3D.md) <br> |
| class | [**LineCoord2D**](classLineCoord2D.md) &lt;typename T, typename&gt;<br> |
| class | [**LineCoord2DCrossing**](classLineCoord2DCrossing.md) &lt;typename T&gt;<br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  const std::array&lt; [**Direction2D**](classDirection2D.md), 8 &gt; | [**ALL\_DIRECTIONS**](#variable-all_directions)   = `/* multi line expression */`<br> |
|  const std::array&lt; [**Direction2D**](classDirection2D.md), 4 &gt; | [**ORTHOGONAL\_DIRECTIONS**](#variable-orthogonal_directions)   = `/* multi line expression */`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**estimate\_points\_in\_extent**](#function-estimate_points_in_extent) (std::size\_t total\_points, const [**Extent2D**](structExtent2D.md) & file\_extent, const [**Extent2D**](structExtent2D.md) & query\_extent) <br> |
|  std::array&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt;, 4 &gt; | [**orthogonal\_neighbors**](#function-orthogonal_neighbors) (const [**Coordinate2D**](classCoordinate2D.md)&lt; T &gt; & coord) <br> |




























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




### function estimate\_points\_in\_extent 

```C++
inline std::size_t estimate_points_in_extent (
    std::size_t total_points,
    const Extent2D & file_extent,
    const Extent2D & query_extent
) 
```




<hr>



### function orthogonal\_neighbors 

```C++
template<typename T, typename>
std::array< Coordinate2D < T >, 4 > orthogonal_neighbors (
    const Coordinate2D < T > & coord
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

