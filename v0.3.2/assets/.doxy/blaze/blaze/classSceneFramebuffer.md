

# Class SceneFramebuffer



[**ClassList**](annotated.md) **>** [**SceneFramebuffer**](classSceneFramebuffer.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**bind**](#function-bind) () const<br> |
|  void | [**blit\_depth\_to\_widget\_fbo**](#function-blit_depth_to_widget_fbo) (GLuint widget\_fbo, int width, int height) const<br> |
|  void | [**blit\_to\_widget\_fbo**](#function-blit_to_widget_fbo) (GLuint widget\_fbo, int width, int height) const<br> |
|  void | [**composite\_to\_widget\_fbo**](#function-composite_to_widget_fbo) (QOpenGLExtraFunctions \* gl, GLuint widget\_fbo, int width, int height) <br> |
|  void | [**ensure\_size**](#function-ensure_size) (int width, int height) <br> |
|  bool | [**valid**](#function-valid) () const<br> |




























## Public Functions Documentation




### function bind 

```C++
inline void SceneFramebuffer::bind () const
```




<hr>



### function blit\_depth\_to\_widget\_fbo 

```C++
inline void SceneFramebuffer::blit_depth_to_widget_fbo (
    GLuint widget_fbo,
    int width,
    int height
) const
```




<hr>



### function blit\_to\_widget\_fbo 

```C++
inline void SceneFramebuffer::blit_to_widget_fbo (
    GLuint widget_fbo,
    int width,
    int height
) const
```




<hr>



### function composite\_to\_widget\_fbo 

```C++
void SceneFramebuffer::composite_to_widget_fbo (
    QOpenGLExtraFunctions * gl,
    GLuint widget_fbo,
    int width,
    int height
) 
```




<hr>



### function ensure\_size 

```C++
inline void SceneFramebuffer::ensure_size (
    int width,
    int height
) 
```




<hr>



### function valid 

```C++
inline bool SceneFramebuffer::valid () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/scene_framebuffer.hpp`

