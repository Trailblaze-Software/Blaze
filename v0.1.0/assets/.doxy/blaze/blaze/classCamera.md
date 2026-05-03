

# Class Camera



[**ClassList**](annotated.md) **>** [**Camera**](classCamera.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Camera**](#function-camera-12) ([**int**](classCoordinate2D.md) width, [**int**](classCoordinate2D.md) height) <br> |
|   | [**Camera**](#function-camera-22) ([**const**](classCoordinate2D.md) [**QVector3D**](classCoordinate2D.md) & position, [**const**](classCoordinate2D.md) [**QVector3D**](classCoordinate2D.md) & direction, [**const**](classCoordinate2D.md) [**QVector3D**](classCoordinate2D.md) & up) <br> |
|  [**double**](classCoordinate2D.md) | [**current\_altitude\_angle**](#function-current_altitude_angle) () const<br> |
|  [**const**](classCoordinate2D.md) [**QVector3D**](classCoordinate2D.md) & | [**direction**](#function-direction) () const<br> |
|  [**void**](classCoordinate2D.md) | [**fly**](#function-fly) ([**double**](classCoordinate2D.md) dx, [**double**](classCoordinate2D.md) dy, [**double**](classCoordinate2D.md) dz) <br> |
|  [**void**](classCoordinate2D.md) | [**move**](#function-move) ([**const**](classCoordinate2D.md) [**QVector3D**](classCoordinate2D.md) & direction) <br> |
|  [**void**](classCoordinate2D.md) | [**move\_towards**](#function-move_towards) ([**const**](classCoordinate2D.md) [**QVector3D**](classCoordinate2D.md) & world\_pos, [**double**](classCoordinate2D.md) distance, [**bool**](classCoordinate2D.md) shrink\_direction=[**false**](classCoordinate2D.md)) <br> |
|  [**void**](classCoordinate2D.md) | [**pan**](#function-pan) ([**double**](classCoordinate2D.md) dx, [**double**](classCoordinate2D.md) dy) <br> |
|  [**QVector3D**](classCoordinate2D.md) | [**planar\_direction**](#function-planar_direction) () const<br> |
|  [**const**](classCoordinate2D.md) [**QVector3D**](classCoordinate2D.md) & | [**position**](#function-position) () const<br> |
|  [**QMatrix4x4**](classCoordinate2D.md) | [**proj\_matrix**](#function-proj_matrix) () const<br> |
|  [**double**](classCoordinate2D.md) | [**projection\_scale**](#function-projection_scale) () const<br> |
|  [**void**](classCoordinate2D.md) | [**reset\_to\_origin**](#function-reset_to_origin) () <br> |
|  [**void**](classCoordinate2D.md) | [**rotate\_around\_center**](#function-rotate_around_center) ([**double**](classCoordinate2D.md) dx, [**double**](classCoordinate2D.md) dy, [**const**](classCoordinate2D.md) std::optional&lt; [**QVector3D**](classCoordinate2D.md) &gt; & center=std::nullopt) <br> |
|  [**void**](classCoordinate2D.md) | [**rotate\_view**](#function-rotate_view) ([**double**](classCoordinate2D.md) dx, [**double**](classCoordinate2D.md) dy) <br> |
|  [**void**](classCoordinate2D.md) | [**set\_screen\_size**](#function-set_screen_size) ([**int**](classCoordinate2D.md) width, [**int**](classCoordinate2D.md) height) <br> |
|  [**QVector3D**](classCoordinate2D.md) | [**unproject**](#function-unproject) ([**const**](classCoordinate2D.md) [**QPointF**](classCoordinate2D.md) & screen\_pos) const<br> |
|  [**const**](classCoordinate2D.md) [**QVector3D**](classCoordinate2D.md) & | [**up**](#function-up) () const<br> |
|  [**QVector3D**](classCoordinate2D.md) | [**view\_right**](#function-view_right) () const<br> |
|  [**QVector3D**](classCoordinate2D.md) | [**view\_up**](#function-view_up) () const<br> |
|  [**const**](classCoordinate2D.md) [**Coordinate3D**](classCoordinate3D.md)&lt; [**double**](classCoordinate2D.md) &gt; & | [**world\_offset**](#function-world_offset-12) () const<br> |
|  [**Coordinate3D**](classCoordinate3D.md)&lt; [**double**](classCoordinate2D.md) &gt; & | [**world\_offset**](#function-world_offset-22) () <br> |
|  [**void**](classCoordinate2D.md) | [**zoom\_to\_fit**](#function-zoom_to_fit) ([**const**](classCoordinate2D.md) [**Extent3D**](structExtent3D.md) & extent) <br> |




























## Public Functions Documentation




### function Camera [1/2]

```C++
inline Camera::Camera (
    int width,
    int height
) 
```




<hr>



### function Camera [2/2]

```C++
inline Camera::Camera (
    const  QVector3D & position,
    const  QVector3D & direction,
    const  QVector3D & up
) 
```




<hr>



### function current\_altitude\_angle 

```C++
inline double Camera::current_altitude_angle () const
```




<hr>



### function direction 

```C++
inline const  QVector3D & Camera::direction () const
```




<hr>



### function fly 

```C++
inline void Camera::fly (
    double dx,
    double dy,
    double dz
) 
```




<hr>



### function move 

```C++
inline void Camera::move (
    const  QVector3D & direction
) 
```




<hr>



### function move\_towards 

```C++
inline void Camera::move_towards (
    const  QVector3D & world_pos,
    double distance,
    bool shrink_direction=false
) 
```




<hr>



### function pan 

```C++
inline void Camera::pan (
    double dx,
    double dy
) 
```




<hr>



### function planar\_direction 

```C++
inline QVector3D Camera::planar_direction () const
```




<hr>



### function position 

```C++
inline const  QVector3D & Camera::position () const
```




<hr>



### function proj\_matrix 

```C++
inline QMatrix4x4 Camera::proj_matrix () const
```




<hr>



### function projection\_scale 

```C++
inline double Camera::projection_scale () const
```




<hr>



### function reset\_to\_origin 

```C++
inline void Camera::reset_to_origin () 
```




<hr>



### function rotate\_around\_center 

```C++
inline void Camera::rotate_around_center (
    double dx,
    double dy,
    const std::optional< QVector3D > & center=std::nullopt
) 
```




<hr>



### function rotate\_view 

```C++
inline void Camera::rotate_view (
    double dx,
    double dy
) 
```




<hr>



### function set\_screen\_size 

```C++
inline void Camera::set_screen_size (
    int width,
    int height
) 
```




<hr>



### function unproject 

```C++
inline QVector3D Camera::unproject (
    const  QPointF & screen_pos
) const
```




<hr>



### function up 

```C++
inline const  QVector3D & Camera::up () const
```




<hr>



### function view\_right 

```C++
inline QVector3D Camera::view_right () const
```




<hr>



### function view\_up 

```C++
inline QVector3D Camera::view_up () const
```




<hr>



### function world\_offset [1/2]

```C++
inline const  Coordinate3D < double > & Camera::world_offset () const
```




<hr>



### function world\_offset [2/2]

```C++
inline Coordinate3D < double > & Camera::world_offset () 
```




<hr>



### function zoom\_to\_fit 

```C++
inline void Camera::zoom_to_fit (
    const  Extent3D & extent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/camera.hpp`

