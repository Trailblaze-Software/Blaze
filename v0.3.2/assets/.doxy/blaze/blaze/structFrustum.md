

# Struct Frustum



[**ClassList**](annotated.md) **>** [**Frustum**](structFrustum.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::array&lt; QVector4D, 6 &gt; | [**m\_planes**](#variable-m_planes)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**intersects**](#function-intersects) (const [**Extent3D**](structExtent3D.md) & bounds) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Frustum**](structFrustum.md) | [**from\_matrix**](#function-from_matrix) (const QMatrix4x4 & clip) <br> |


























## Public Attributes Documentation




### variable m\_planes 

```C++
std::array<QVector4D, 6> Frustum::m_planes;
```




<hr>
## Public Functions Documentation




### function intersects 

```C++
inline bool Frustum::intersects (
    const Extent3D & bounds
) const
```




<hr>
## Public Static Functions Documentation




### function from\_matrix 

```C++
static inline Frustum Frustum::from_matrix (
    const QMatrix4x4 & clip
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/frustum.hpp`

