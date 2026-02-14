

# File config\_editor.cpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**config\_editor.cpp**](config__editor_8cpp.md)

[Go to the source code of this file](config__editor_8cpp_source.md)



* `#include "config_editor.hpp"`
* `#include <qdebug.h>`
* `#include <QColorDialog>`
* `#include <QDoubleValidator>`
* `#include <QFileDialog>`
* `#include <QIntValidator>`
* `#include <QListWidget>`
* `#include <QPainter>`
* `#include <QPushButton>`
* `#include <QSpinBox>`
* `#include <QTableWidget>`
* `#include <filesystem>`
* `#include "assert/assert.hpp"`
* `#include "config_input/config_input.hpp"`
* `#include "printing/to_string.hpp"`
* `#include "ui_config_editor.h"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**ParentFolderExistsValidator**](classParentFolderExistsValidator.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**bool**](classCoordinate2D.md) | [**color\_equals**](#function-color_equals) ([**const**](classCoordinate2D.md) ColorVariant & v1, [**const**](classCoordinate2D.md) ColorVariant & v2) <br> |
|  [**QIcon**](classCoordinate2D.md) | [**create\_color\_icon**](#function-create_color_icon) ([**const**](classCoordinate2D.md) ColorVariant & color) <br> |
|  [**QString**](classCoordinate2D.md) | [**get\_color\_name**](#function-get_color_name) ([**const**](classCoordinate2D.md) ColorVariant & color) <br> |
|  [**bool**](classCoordinate2D.md) | [**validated**](#function-validated) (T \* box) <br> |




























## Public Functions Documentation




### function color\_equals 

```C++
bool color_equals (
    const ColorVariant & v1,
    const ColorVariant & v2
) 
```




<hr>



### function create\_color\_icon 

```C++
QIcon create_color_icon (
    const ColorVariant & color
) 
```




<hr>



### function get\_color\_name 

```C++
QString get_color_name (
    const ColorVariant & color
) 
```




<hr>



### function validated 

```C++
template<typename T>
bool validated (
    T * box
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/config_editor.cpp`

