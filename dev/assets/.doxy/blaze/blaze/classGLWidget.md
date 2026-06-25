

# Class GLWidget



[**ClassList**](annotated.md) **>** [**GLWidget**](classGLWidget.md)








Inherits the following classes: QOpenGLWidget,  QOpenGLFunctions














## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**AnimType**](#enum-animtype)  <br> |
| enum  | [**PickAction**](#enum-pickaction)  <br> |
| typedef std::function&lt; void(const std::optional&lt; [**PointPickResult**](structPointPickResult.md) &gt; &)&gt; | [**PointPickCallback**](#typedef-pointpickcallback)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GLWidget**](#function-glwidget) (QWidget \* parent=nullptr) <br> |
|  void | [**add\_layer**](#function-add_layer) (std::shared\_ptr&lt; [**Layer**](classLayer.md) &gt; layer, bool auto\_zoom=true) <br> |
|  float | [**ambient\_light**](#function-ambient_light) () const<br> |
|  int | [**anim\_type**](#function-anim_type) () const<br> |
|  float | [**camera\_light\_azimuth\_deg**](#function-camera_light_azimuth_deg) () const<br> |
|  float | [**camera\_light\_elevation\_deg**](#function-camera_light_elevation_deg) () const<br> |
|  float | [**diffuse\_light**](#function-diffuse_light) () const<br> |
|  bool | [**is\_anim\_active**](#function-is_anim_active) () const<br> |
|  std::vector&lt; std::shared\_ptr&lt; [**Layer**](classLayer.md) &gt; &gt; | [**layers**](#function-layers) () const<br> |
|  double | [**orbit\_period**](#function-orbit_period) () const<br> |
|  float | [**point\_ambient\_light**](#function-point_ambient_light) () const<br> |
|  const std::string & | [**reference\_crs\_wkt**](#function-reference_crs_wkt) () const<br> |
|  void | [**refresh\_point\_cloud\_style**](#function-refresh_point_cloud_style) () <br> |
|  void | [**remove\_layer**](#function-remove_layer) ([**Layer**](classLayer.md) \* layer) <br> |
|  void | [**restart\_render**](#function-restart_render) () <br> |
|  void | [**set\_anim\_type**](#function-set_anim_type) (int t) <br> |
|  void | [**set\_camera\_light\_angles**](#function-set_camera_light_angles) (float azimuth\_deg, float elevation\_deg) <br> |
|  void | [**set\_layer\_visible**](#function-set_layer_visible) ([**Layer**](classLayer.md) \* layer, bool visible) <br> |
|  void | [**set\_lighting\_strength**](#function-set_lighting_strength) (float ambient\_light, float diffuse\_light) <br> |
|  void | [**set\_load\_only\_mode**](#function-set_load_only_mode) (bool load\_only) <br> |
|  void | [**set\_orbit\_period**](#function-set_orbit_period) (double secs) <br> |
|  void | [**set\_point\_ambient\_light**](#function-set_point_ambient_light) (float point\_ambient\_light) <br> |
|  void | [**set\_point\_pick\_callback**](#function-set_point_pick_callback) (PointPickCallback callback) <br> |
|  void | [**set\_selected\_point**](#function-set_selected_point) (const std::optional&lt; [**PointPickResult**](structPointPickResult.md) &gt; & pick, bool repaint=true) <br> |
|  void | [**set\_wobble\_amplitude**](#function-set_wobble_amplitude) (double deg) <br> |
|  void | [**set\_wobble\_period**](#function-set_wobble_period) (double secs) <br> |
|  void | [**start\_animation**](#function-start_animation) (AnimType type) <br> |
|  void | [**start\_bench\_orbit**](#function-start_bench_orbit) (double duration\_seconds=10.0) <br> |
|  void | [**stop\_animation**](#function-stop_animation) () <br> |
|  double | [**wobble\_amplitude**](#function-wobble_amplitude) () const<br> |
|  double | [**wobble\_period**](#function-wobble_period) () const<br> |
|  void | [**zoom\_to\_all\_layers**](#function-zoom_to_all_layers) () <br> |
|  void | [**zoom\_to\_layer**](#function-zoom_to_layer) (const [**Layer**](classLayer.md) \* layer) <br> |
|   | [**~GLWidget**](#function-glwidget) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**begin\_camera\_interaction**](#function-begin_camera_interaction) () <br> |
|  void | [**initializeGL**](#function-initializegl) () override<br> |
|  void | [**keyPressEvent**](#function-keypressevent) (QKeyEvent \* event) override<br> |
|  void | [**leaveEvent**](#function-leaveevent) (QEvent \* event) override<br> |
|  QSize | [**minimumSizeHint**](#function-minimumsizehint) () override const<br> |
|  void | [**mouseMoveEvent**](#function-mousemoveevent) (QMouseEvent \* event) override<br> |
|  void | [**mousePressEvent**](#function-mousepressevent) (QMouseEvent \* event) override<br> |
|  void | [**mouseReleaseEvent**](#function-mousereleaseevent) (QMouseEvent \* event) override<br> |
|  void | [**note\_camera\_motion**](#function-note_camera_motion) () <br> |
|  void | [**paintGL**](#function-paintgl) () override<br> |
|  void | [**resizeGL**](#function-resizegl) (int w, int h) override<br> |
|  void | [**schedule\_camera\_idle**](#function-schedule_camera_idle) () <br> |
|  void | [**showEvent**](#function-showevent) (QShowEvent \* event) override<br> |
|  QSize | [**sizeHint**](#function-sizehint) () override const<br> |
|  void | [**wheelEvent**](#function-wheelevent) (QWheelEvent \* event) override<br> |




## Public Types Documentation




### enum AnimType 

```C++
enum GLWidget::AnimType {
    None,
    Orbit,
    Wobble
};
```




<hr>



### enum PickAction 

```C++
enum GLWidget::PickAction {
    None,
    PanToPoint,
    LookAtPoint
};
```




<hr>



### typedef PointPickCallback 

```C++
using GLWidget::PointPickCallback =  std::function<void(const std::optional<PointPickResult>&)>;
```




<hr>
## Public Functions Documentation




### function GLWidget 

```C++
GLWidget::GLWidget (
    QWidget * parent=nullptr
) 
```




<hr>



### function add\_layer 

```C++
inline void GLWidget::add_layer (
    std::shared_ptr< Layer > layer,
    bool auto_zoom=true
) 
```




<hr>



### function ambient\_light 

```C++
inline float GLWidget::ambient_light () const
```




<hr>



### function anim\_type 

```C++
inline int GLWidget::anim_type () const
```




<hr>



### function camera\_light\_azimuth\_deg 

```C++
inline float GLWidget::camera_light_azimuth_deg () const
```




<hr>



### function camera\_light\_elevation\_deg 

```C++
inline float GLWidget::camera_light_elevation_deg () const
```




<hr>



### function diffuse\_light 

```C++
inline float GLWidget::diffuse_light () const
```




<hr>



### function is\_anim\_active 

```C++
inline bool GLWidget::is_anim_active () const
```




<hr>



### function layers 

```C++
inline std::vector< std::shared_ptr< Layer > > GLWidget::layers () const
```




<hr>



### function orbit\_period 

```C++
inline double GLWidget::orbit_period () const
```




<hr>



### function point\_ambient\_light 

```C++
inline float GLWidget::point_ambient_light () const
```




<hr>



### function reference\_crs\_wkt 

```C++
inline const std::string & GLWidget::reference_crs_wkt () const
```




<hr>



### function refresh\_point\_cloud\_style 

```C++
void GLWidget::refresh_point_cloud_style () 
```




<hr>



### function remove\_layer 

```C++
void GLWidget::remove_layer (
    Layer * layer
) 
```




<hr>



### function restart\_render 

```C++
void GLWidget::restart_render () 
```




<hr>



### function set\_anim\_type 

```C++
void GLWidget::set_anim_type (
    int t
) 
```




<hr>



### function set\_camera\_light\_angles 

```C++
void GLWidget::set_camera_light_angles (
    float azimuth_deg,
    float elevation_deg
) 
```




<hr>



### function set\_layer\_visible 

```C++
inline void GLWidget::set_layer_visible (
    Layer * layer,
    bool visible
) 
```




<hr>



### function set\_lighting\_strength 

```C++
void GLWidget::set_lighting_strength (
    float ambient_light,
    float diffuse_light
) 
```




<hr>



### function set\_load\_only\_mode 

```C++
inline void GLWidget::set_load_only_mode (
    bool load_only
) 
```




<hr>



### function set\_orbit\_period 

```C++
inline void GLWidget::set_orbit_period (
    double secs
) 
```




<hr>



### function set\_point\_ambient\_light 

```C++
void GLWidget::set_point_ambient_light (
    float point_ambient_light
) 
```




<hr>



### function set\_point\_pick\_callback 

```C++
inline void GLWidget::set_point_pick_callback (
    PointPickCallback callback
) 
```




<hr>



### function set\_selected\_point 

```C++
void GLWidget::set_selected_point (
    const std::optional< PointPickResult > & pick,
    bool repaint=true
) 
```




<hr>



### function set\_wobble\_amplitude 

```C++
inline void GLWidget::set_wobble_amplitude (
    double deg
) 
```




<hr>



### function set\_wobble\_period 

```C++
inline void GLWidget::set_wobble_period (
    double secs
) 
```




<hr>



### function start\_animation 

```C++
void GLWidget::start_animation (
    AnimType type
) 
```




<hr>



### function start\_bench\_orbit 

```C++
void GLWidget::start_bench_orbit (
    double duration_seconds=10.0
) 
```




<hr>



### function stop\_animation 

```C++
void GLWidget::stop_animation () 
```




<hr>



### function wobble\_amplitude 

```C++
inline double GLWidget::wobble_amplitude () const
```




<hr>



### function wobble\_period 

```C++
inline double GLWidget::wobble_period () const
```




<hr>



### function zoom\_to\_all\_layers 

```C++
inline void GLWidget::zoom_to_all_layers () 
```




<hr>



### function zoom\_to\_layer 

```C++
inline void GLWidget::zoom_to_layer (
    const Layer * layer
) 
```




<hr>



### function ~GLWidget 

```C++
GLWidget::~GLWidget () 
```




<hr>
## Protected Functions Documentation




### function begin\_camera\_interaction 

```C++
void GLWidget::begin_camera_interaction () 
```




<hr>



### function initializeGL 

```C++
void GLWidget::initializeGL () override
```




<hr>



### function keyPressEvent 

```C++
void GLWidget::keyPressEvent (
    QKeyEvent * event
) override
```




<hr>



### function leaveEvent 

```C++
void GLWidget::leaveEvent (
    QEvent * event
) override
```




<hr>



### function minimumSizeHint 

```C++
QSize GLWidget::minimumSizeHint () override const
```




<hr>



### function mouseMoveEvent 

```C++
void GLWidget::mouseMoveEvent (
    QMouseEvent * event
) override
```




<hr>



### function mousePressEvent 

```C++
void GLWidget::mousePressEvent (
    QMouseEvent * event
) override
```




<hr>



### function mouseReleaseEvent 

```C++
void GLWidget::mouseReleaseEvent (
    QMouseEvent * event
) override
```




<hr>



### function note\_camera\_motion 

```C++
void GLWidget::note_camera_motion () 
```




<hr>



### function paintGL 

```C++
void GLWidget::paintGL () override
```




<hr>



### function resizeGL 

```C++
void GLWidget::resizeGL (
    int w,
    int h
) override
```




<hr>



### function schedule\_camera\_idle 

```C++
void GLWidget::schedule_camera_idle () 
```




<hr>



### function showEvent 

```C++
void GLWidget::showEvent (
    QShowEvent * event
) override
```




<hr>



### function sizeHint 

```C++
QSize GLWidget::sizeHint () override const
```




<hr>



### function wheelEvent 

```C++
void GLWidget::wheelEvent (
    QWheelEvent * event
) override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/gl_widget.hpp`

