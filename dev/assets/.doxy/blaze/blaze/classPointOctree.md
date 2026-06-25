

# Class PointOctree



[**ClassList**](annotated.md) **>** [**PointOctree**](classPointOctree.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**VisibleNode**](structPointOctree_1_1VisibleNode.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PointOctree**](#function-pointoctree-12) () <br> |
|   | [**PointOctree**](#function-pointoctree-22) (const [**Extent3D**](structExtent3D.md) & bounds) <br> |
|  void | [**collect\_visible**](#function-collect_visible) (const [**Frustum**](structFrustum.md) & frustum, double quality, const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & camera\_local, std::vector&lt; [**VisibleNode**](structPointOctree_1_1VisibleNode.md) &gt; & out) const<br> |
|  void | [**insert\_batch**](#function-insert_batch) (std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; && points, const std::function&lt; void(size\_t, size\_t)&gt; & progress={}, const std::atomic&lt; bool &gt; \* cancel=nullptr) <br> |
|  const std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; & | [**points**](#function-points) () const<br> |
|  const [**PointOctreeNode**](classPointOctreeNode.md) \* | [**root**](#function-root) () const<br> |
|  void | [**shuffle\_leaves**](#function-shuffle_leaves) () <br> |
|  size\_t | [**total\_points**](#function-total_points) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  size\_t | [**node\_draw\_chunk\_size**](#function-node_draw_chunk_size) (size\_t point\_count, double lod\_distance, double quality) <br> |


























## Public Functions Documentation




### function PointOctree [1/2]

```C++
inline PointOctree::PointOctree () 
```




<hr>



### function PointOctree [2/2]

```C++
inline explicit PointOctree::PointOctree (
    const Extent3D & bounds
) 
```




<hr>



### function collect\_visible 

```C++
inline void PointOctree::collect_visible (
    const Frustum & frustum,
    double quality,
    const Coordinate3D < double > & camera_local,
    std::vector< VisibleNode > & out
) const
```




<hr>



### function insert\_batch 

```C++
void PointOctree::insert_batch (
    std::vector< OctreePoint > && points,
    const std::function< void(size_t, size_t)> & progress={},
    const std::atomic< bool > * cancel=nullptr
) 
```




<hr>



### function points 

```C++
inline const std::vector< OctreePoint > & PointOctree::points () const
```




<hr>



### function root 

```C++
inline const PointOctreeNode * PointOctree::root () const
```




<hr>



### function shuffle\_leaves 

```C++
inline void PointOctree::shuffle_leaves () 
```




<hr>



### function total\_points 

```C++
inline size_t PointOctree::total_points () const
```




<hr>
## Public Static Functions Documentation




### function node\_draw\_chunk\_size 

```C++
static inline size_t PointOctree::node_draw_chunk_size (
    size_t point_count,
    double lod_distance,
    double quality
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/point_octree.hpp`

