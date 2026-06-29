

# File main\_3d.cpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**main\_3d.cpp**](main__3d_8cpp.md)

[Go to the source code of this file](main__3d_8cpp_source.md)



* `#include <QApplication>`
* `#include <QMainWindow>`
* `#include <QMatrix4x4>`
* `#include <chrono>`
* `#include <cstdio>`
* `#include <cstdlib>`
* `#include <fstream>`
* `#include <functional>`
* `#include <iostream>`
* `#include <limits>`
* `#include <optional>`
* `#include <sstream>`
* `#include <string>`
* `#include <thread>`
* `#include "gl_widget.hpp"`
* `#include "main_3d_window.hpp"`
* `#include "utilities/env.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/resources.hpp"`
* `#include "gui/frustum.hpp"`
* `#include "gui/octree_las_data.hpp"`
* `#include "gui/point_octree.hpp"`
* `#include "las/las_file.hpp"`
* `#include "las_reader.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**LaunchOptions**](structLaunchOptions.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**main**](#function-main) (int argc, char \* argv) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**LaunchOptions**](structLaunchOptions.md) | [**parse\_args**](#function-parse_args) (int argc, char \* argv) <br> |
|  void | [**print\_usage**](#function-print_usage) (const char \* program) <br> |
|  int | [**probe\_las\_file**](#function-probe_las_file) (const fs::path & filename) <br> |


























## Public Functions Documentation




### function main 

```C++
int main (
    int argc,
    char * argv
) 
```




<hr>
## Public Static Functions Documentation




### function parse\_args 

```C++
static LaunchOptions parse_args (
    int argc,
    char * argv
) 
```




<hr>



### function print\_usage 

```C++
static void print_usage (
    const char * program
) 
```




<hr>



### function probe\_las\_file 

```C++
static int probe_las_file (
    const fs::path & filename
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/main_3d.cpp`

