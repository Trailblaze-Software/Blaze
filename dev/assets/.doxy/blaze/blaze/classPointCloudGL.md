

# Class PointCloudGL



[**ClassList**](annotated.md) **>** [**PointCloudGL**](classPointCloudGL.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**bind**](#function-bind) (QOpenGLFunctions \* f) const<br> |
|  void | [**destroy**](#function-destroy) () <br> |
|  size\_t | [**draw\_leaves**](#function-draw_leaves) (QOpenGLFunctions \* f, const GLint \* firsts, const GLsizei \* counts, size\_t leaf\_count) <br> |
|  size\_t | [**draw\_points**](#function-draw_points) (QOpenGLFunctions \* f, const [**OctreePoint**](structOctreePoint.md) \* data, size\_t count) <br> |
|  void | [**ensure\_initialized**](#function-ensure_initialized) (QOpenGLFunctions \* f) <br> |
|  void | [**upload\_points**](#function-upload_points) (QOpenGLFunctions \* f, const [**OctreePoint**](structOctreePoint.md) \* data, size\_t count) <br> |
|   | [**~PointCloudGL**](#function-pointcloudgl) () <br> |




























## Public Functions Documentation




### function bind 

```C++
void PointCloudGL::bind (
    QOpenGLFunctions * f
) const
```




<hr>



### function destroy 

```C++
void PointCloudGL::destroy () 
```




<hr>



### function draw\_leaves 

```C++
size_t PointCloudGL::draw_leaves (
    QOpenGLFunctions * f,
    const GLint * firsts,
    const GLsizei * counts,
    size_t leaf_count
) 
```




<hr>



### function draw\_points 

```C++
size_t PointCloudGL::draw_points (
    QOpenGLFunctions * f,
    const OctreePoint * data,
    size_t count
) 
```




<hr>



### function ensure\_initialized 

```C++
void PointCloudGL::ensure_initialized (
    QOpenGLFunctions * f
) 
```




<hr>



### function upload\_points 

```C++
void PointCloudGL::upload_points (
    QOpenGLFunctions * f,
    const OctreePoint * data,
    size_t count
) 
```




<hr>



### function ~PointCloudGL 

```C++
inline PointCloudGL::~PointCloudGL () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/point_cloud_gl.hpp`

