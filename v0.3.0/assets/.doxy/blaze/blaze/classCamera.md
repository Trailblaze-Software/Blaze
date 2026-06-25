

# Class Camera



[**ClassList**](annotated.md) **>** [**Camera**](classCamera.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Camera**](#function-camera) (int width, int height) <br> |
|  double | [**current\_altitude\_angle**](#function-current_altitude_angle) () const<br> |
|  const QVector3D & | [**direction**](#function-direction) () const<br> |
|  void | [**fly**](#function-fly) (double dx, double dy, double dz) <br> |
|  double | [**fov\_rad**](#function-fov_rad) () const<br> |
|  void | [**look\_at\_target**](#function-look_at_target) (const QVector3D & target) <br> |
|  void | [**move\_towards**](#function-move_towards) (const QVector3D & world\_pos, double distance, bool shrink\_direction=false) <br> |
|  void | [**pan**](#function-pan) (double dx, double dy) <br> |
|  void | [**pan\_to\_target**](#function-pan_to_target) (const QVector3D & target) <br> |
|  QVector3D | [**planar\_direction**](#function-planar_direction) () const<br> |
|  const QVector3D & | [**position**](#function-position) () const<br> |
|  QMatrix4x4 | [**proj\_matrix**](#function-proj_matrix) () const<br> |
|  std::optional&lt; QPointF &gt; | [**project\_world\_to\_screen**](#function-project_world_to_screen) (const QVector3D & world\_pos) const<br> |
|  QMatrix4x4 | [**projection\_matrix**](#function-projection_matrix) () const<br> |
|  double | [**projection\_scale**](#function-projection_scale) () const<br> |
|  void | [**reset\_to\_origin**](#function-reset_to_origin) () <br> |
|  void | [**rotate\_around\_center**](#function-rotate_around_center) (double dx, double dy, const std::optional&lt; QVector3D &gt; & center=std::nullopt) <br> |
|  void | [**rotate\_view**](#function-rotate_view) (double dx, double dy) <br> |
|  int | [**screen\_height**](#function-screen_height) () const<br> |
|  int | [**screen\_width**](#function-screen_width) () const<br> |
|  void | [**set\_scene\_bounds**](#function-set_scene_bounds) (const QVector3D & center, float radius) <br> |
|  void | [**set\_screen\_size**](#function-set_screen_size) (int width, int height) <br> |
|  QVector3D | [**unproject**](#function-unproject) (const QPointF & screen\_pos) const<br> |
|  const QVector3D & | [**up**](#function-up) () const<br> |
|  QMatrix4x4 | [**view\_matrix**](#function-view_matrix) () const<br> |
|  QVector3D | [**view\_right**](#function-view_right) () const<br> |
|  QVector3D | [**view\_up**](#function-view_up) () const<br> |
|  const [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & | [**world\_offset**](#function-world_offset-12) () const<br> |
|  [**Coordinate3D**](classCoordinate3D.md)&lt; double &gt; & | [**world\_offset**](#function-world_offset-22) () <br> |
|  void | [**zoom\_to\_fit**](#function-zoom_to_fit) (const [**Extent3D**](structExtent3D.md) & extent) <br> |




























## Public Functions Documentation




### function Camera 

```C++
inline Camera::Camera (
    int width,
    int height
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
inline const QVector3D & Camera::direction () const
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



### function fov\_rad 

```C++
inline double Camera::fov_rad () const
```




<hr>



### function look\_at\_target 

```C++
inline void Camera::look_at_target (
    const QVector3D & target
) 
```




<hr>



### function move\_towards 

```C++
inline void Camera::move_towards (
    const QVector3D & world_pos,
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



### function pan\_to\_target 

```C++
inline void Camera::pan_to_target (
    const QVector3D & target
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
inline const QVector3D & Camera::position () const
```




<hr>



### function proj\_matrix 

```C++
inline QMatrix4x4 Camera::proj_matrix () const
```




<hr>



### function project\_world\_to\_screen 

```C++
inline std::optional< QPointF > Camera::project_world_to_screen (
    const QVector3D & world_pos
) const
```




<hr>



### function projection\_matrix 

```C++
inline QMatrix4x4 Camera::projection_matrix () const
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



### function screen\_height 

```C++
inline int Camera::screen_height () const
```




<hr>



### function screen\_width 

```C++
inline int Camera::screen_width () const
```




<hr>



### function set\_scene\_bounds 

```C++
inline void Camera::set_scene_bounds (
    const QVector3D & center,
    float radius
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
    const QPointF & screen_pos
) const
```




<hr>



### function up 

```C++
inline const QVector3D & Camera::up () const
```




<hr>



### function view\_matrix 

```C++
inline QMatrix4x4 Camera::view_matrix () const
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
inline const Coordinate3D < double > & Camera::world_offset () const
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
    const Extent3D & extent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/camera.hpp`

