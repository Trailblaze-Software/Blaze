

# File gl\_check.hpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**gl\_check.hpp**](gl__check_8hpp.md)

[Go to the source code of this file](gl__check_8hpp_source.md)



* `#include <QOpenGLContext>`
* `#include <QOpenGLFunctions>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**drain\_gl\_errors**](#function-drain_gl_errors) (QOpenGLFunctions \* f, const char \* kind, const char \* file, int line, const char \* expr) <br> |
|  const char \* | [**gl\_error\_name**](#function-gl_error_name) (GLenum err) <br> |
|  void | [**log\_gl\_error**](#function-log_gl_error) (const char \* kind, GLenum err, const char \* file, int line, const char \* expr) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**CHECK\_GL**](gl__check_8hpp.md#define-check_gl) (expr) `/* multi line expression */`<br> |
| define  | [**CHECK\_GL\_AFTER**](gl__check_8hpp.md#define-check_gl_after) () `/* multi line expression */`<br> |

## Public Functions Documentation




### function drain\_gl\_errors 

```C++
inline void drain_gl_errors (
    QOpenGLFunctions * f,
    const char * kind,
    const char * file,
    int line,
    const char * expr
) 
```




<hr>



### function gl\_error\_name 

```C++
inline const char * gl_error_name (
    GLenum err
) 
```




<hr>



### function log\_gl\_error 

```C++
void log_gl_error (
    const char * kind,
    GLenum err,
    const char * file,
    int line,
    const char * expr
) 
```




<hr>
## Macro Definition Documentation





### define CHECK\_GL 

```C++
#define CHECK_GL (
    expr
) `/* multi line expression */`
```




<hr>



### define CHECK\_GL\_AFTER 

```C++
#define CHECK_GL_AFTER (
    
) `/* multi line expression */`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/gl_check.hpp`

