

# Class GLWidget



[**ClassList**](annotated.md) **>** [**GLWidget**](classGLWidget.md)








Inherits the following classes: QOpenGLWidget,  QOpenGLFunctions


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GLWidget**](#function-glwidget) (QWidget \* parent=[**nullptr**](classCoordinate2D.md)) <br> |
|  [**void**](classCoordinate2D.md) | [**add\_layer**](#function-add_layer) (std::unique\_ptr&lt; [**Layer**](classLayer.md) &gt; layer) <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**Layer**](classLayer.md) &gt; &gt; | [**layers**](#function-layers) () const<br> |
|   | [**~GLWidget**](#function-glwidget) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**initializeGL**](#function-initializegl) () override<br> |
|  [**void**](classCoordinate2D.md) | [**keyPressEvent**](#function-keypressevent) ([**QKeyEvent**](classCoordinate2D.md) \* event) override<br> |
|  [**void**](classCoordinate2D.md) | [**mouseMoveEvent**](#function-mousemoveevent) ([**QMouseEvent**](classCoordinate2D.md) \* event) override<br> |
|  [**void**](classCoordinate2D.md) | [**mousePressEvent**](#function-mousepressevent) ([**QMouseEvent**](classCoordinate2D.md) \* event) override<br> |
|  [**void**](classCoordinate2D.md) | [**paintGL**](#function-paintgl) () override<br> |
|  [**QSize**](classCoordinate2D.md) | [**sizeHint**](#function-sizehint) () override const<br> |
|  [**void**](classCoordinate2D.md) | [**wheelEvent**](#function-wheelevent) ([**QWheelEvent**](classCoordinate2D.md) \* event) override<br> |




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
    std::unique_ptr< Layer > layer
) 
```




<hr>



### function layers 

```C++
inline std::vector< std::shared_ptr< Layer > > GLWidget::layers () const
```




<hr>



### function ~GLWidget 

```C++
GLWidget::~GLWidget () 
```




<hr>
## Protected Functions Documentation




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



### function paintGL 

```C++
void GLWidget::paintGL () override
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

