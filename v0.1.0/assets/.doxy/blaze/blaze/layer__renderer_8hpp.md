

# File layer\_renderer.hpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**layer\_renderer.hpp**](layer__renderer_8hpp.md)

[Go to the source code of this file](layer__renderer_8hpp_source.md)



* `#include <QOpenGLBuffer>`
* `#include <QOpenGLFunctions>`
* `#include <QOpenGLShaderProgram>`
* `#include <QOpenGLVertexArrayObject>`
* `#include <future>`
* `#include "gui/camera.hpp"`
* `#include "gui/layer.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**LASLayerRenderer**](classLASLayerRenderer.md) <br> |
| class | [**LayerRenderer**](classLayerRenderer.md) <br> |








## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**const**](classCoordinate2D.md) [**char**](classCoordinate2D.md) \* | [**fragmentShaderSource**](#variable-fragmentshadersource)   = `/* multi line expression */`<br> |
|  [**const**](classCoordinate2D.md) [**char**](classCoordinate2D.md) \* | [**vertexShaderSource**](#variable-vertexshadersource)   = `/* multi line expression */`<br> |









































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**CHECK\_SHADER\_BIND**](layer__renderer_8hpp.md#define-check_shader_bind) (shader) `/* multi line expression */`<br> |

## Public Static Attributes Documentation




### variable fragmentShaderSource 

```C++
const char* fragmentShaderSource;
```




<hr>



### variable vertexShaderSource 

```C++
const char* vertexShaderSource;
```




<hr>
## Macro Definition Documentation





### define CHECK\_SHADER\_BIND 

```C++
#define CHECK_SHADER_BIND (
    shader
) `/* multi line expression */`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer_renderer.hpp`

