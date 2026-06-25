

# Class PointOctreeNode



[**ClassList**](annotated.md) **>** [**PointOctreeNode**](classPointOctreeNode.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  size\_t | [**begin\_index**](#variable-begin_index)   = `0`<br> |
|  [**Extent3D**](structExtent3D.md) | [**bounds**](#variable-bounds)  <br> |
|  std::array&lt; std::unique\_ptr&lt; [**PointOctreeNode**](classPointOctreeNode.md) &gt;, 8 &gt; | [**children**](#variable-children)  <br> |
|  int | [**depth**](#variable-depth)   = `0`<br> |
|  size\_t | [**end\_index**](#variable-end_index)   = `0`<br> |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr int | [**MAX\_DEPTH**](#variable-max_depth)   = `20`<br> |
|  constexpr size\_t | [**MAX\_POINTS**](#variable-max_points)   = `32'000`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**child\_index**](#function-child_index) (const [**OctreePoint**](structOctreePoint.md) & point) const<br> |
|  void | [**ensure\_child**](#function-ensure_child) (int idx) <br> |
|  bool | [**has\_children**](#function-has_children) () const<br> |
|  size\_t | [**point\_count**](#function-point_count) () const<br> |
|  void | [**shuffle\_range**](#function-shuffle_range) (std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; & points) const<br> |
|  void | [**shuffle\_recursive**](#function-shuffle_recursive) (std::vector&lt; [**OctreePoint**](structOctreePoint.md) &gt; & points) <br> |




























## Public Attributes Documentation




### variable begin\_index 

```C++
size_t PointOctreeNode::begin_index;
```




<hr>



### variable bounds 

```C++
Extent3D PointOctreeNode::bounds;
```




<hr>



### variable children 

```C++
std::array<std::unique_ptr<PointOctreeNode>, 8> PointOctreeNode::children;
```




<hr>



### variable depth 

```C++
int PointOctreeNode::depth;
```




<hr>



### variable end\_index 

```C++
size_t PointOctreeNode::end_index;
```




<hr>
## Public Static Attributes Documentation




### variable MAX\_DEPTH 

```C++
constexpr int PointOctreeNode::MAX_DEPTH;
```




<hr>



### variable MAX\_POINTS 

```C++
constexpr size_t PointOctreeNode::MAX_POINTS;
```




<hr>
## Public Functions Documentation




### function child\_index 

```C++
inline int PointOctreeNode::child_index (
    const OctreePoint & point
) const
```




<hr>



### function ensure\_child 

```C++
inline void PointOctreeNode::ensure_child (
    int idx
) 
```




<hr>



### function has\_children 

```C++
inline bool PointOctreeNode::has_children () const
```




<hr>



### function point\_count 

```C++
inline size_t PointOctreeNode::point_count () const
```




<hr>



### function shuffle\_range 

```C++
inline void PointOctreeNode::shuffle_range (
    std::vector< OctreePoint > & points
) const
```




<hr>



### function shuffle\_recursive 

```C++
inline void PointOctreeNode::shuffle_recursive (
    std::vector< OctreePoint > & points
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/point_octree.hpp`

