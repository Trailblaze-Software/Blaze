

# Struct LasRenderSnapshot



[**ClassList**](annotated.md) **>** [**LasRenderSnapshot**](structLasRenderSnapshot.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Extent3D**](structExtent3D.md) | [**bounds**](#variable-bounds)  <br> |
|  bool | [**bounds\_valid**](#variable-bounds_valid)   = `false`<br> |
|  [**PointOctree**](classPointOctree.md) | [**octree**](#variable-octree)  <br> |
|  size\_t | [**points\_loaded**](#variable-points_loaded)   = `0`<br> |
|  std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; | [**preview\_points**](#variable-preview_points)  <br> |












































## Public Attributes Documentation




### variable bounds 

```C++
Extent3D LasRenderSnapshot::bounds;
```




<hr>



### variable bounds\_valid 

```C++
bool LasRenderSnapshot::bounds_valid;
```




<hr>



### variable octree 

```C++
PointOctree LasRenderSnapshot::octree;
```




<hr>



### variable points\_loaded 

```C++
size_t LasRenderSnapshot::points_loaded;
```




<hr>



### variable preview\_points 

```C++
std::vector<OctreePoint> LasRenderSnapshot::preview_points;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/octree_las_data.hpp`

