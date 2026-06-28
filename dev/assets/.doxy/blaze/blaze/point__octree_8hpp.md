

# File point\_octree.hpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**point\_octree.hpp**](point__octree_8hpp.md)

[Go to the source code of this file](point__octree_8hpp_source.md)



* `#include <algorithm>`
* `#include <array>`
* `#include <atomic>`
* `#include <cmath>`
* `#include <cstdint>`
* `#include <functional>`
* `#include <memory>`
* `#include <random>`
* `#include <vector>`
* `#include "gui/frustum.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/tracked_allocator.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**OctreePoint**](structOctreePoint.md) <br> |
| class | [**PointOctree**](classPointOctree.md) <br> |
| struct | [**VisibleNode**](structPointOctree_1_1VisibleNode.md) <br> |
| class | [**PointOctreeNode**](classPointOctreeNode.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef blaze::memory\_tracker::LasVector&lt; [**OctreePoint**](structOctreePoint.md) &gt; | [**OctreePointVector**](#typedef-octreepointvector)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**octree\_shuffle\_range**](#function-octree_shuffle_range) (OctreePointVector & points, size\_t begin, size\_t end) <br> |




























## Public Types Documentation




### typedef OctreePointVector 

```C++
using OctreePointVector =  blaze::memory_tracker::LasVector<OctreePoint>;
```




<hr>
## Public Functions Documentation




### function octree\_shuffle\_range 

```C++
inline void octree_shuffle_range (
    OctreePointVector & points,
    size_t begin,
    size_t end
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/point_octree.hpp`

