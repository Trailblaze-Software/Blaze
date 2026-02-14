

# File dxf.hpp



[**FileList**](files.md) **>** [**dxf**](dir_f79adc6b9298312518c9c9a103ddabe7.md) **>** [**dxf.hpp**](dxf_8hpp.md)

[Go to the source code of this file](dxf_8hpp_source.md)



* `#include <fstream>`
* `#include <iomanip>`
* `#include <iostream>`
* `#include <methods/water/water.hpp>`
* `#include <string>`
* `#include "contour/contour.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/timer.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Polyline**](classPolyline.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**dxf\_entities**](#function-dxf_entities) () <br> |
|  std::string | [**dxf\_footer**](#function-dxf_footer) () <br> |
|  std::string | [**dxf\_header**](#function-dxf_header) () <br> |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**read\_dxf**](#function-read_dxf) ([**const**](classCoordinate2D.md) fs::path & filename) <br> |
|  [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; | [**vertex\_from\_dxf**](#function-vertex_from_dxf) (std::ifstream & dxfFile) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_to\_crt**](#function-write_to_crt) ([**const**](classCoordinate2D.md) fs::path & filename) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_to\_dxf**](#function-write_to_dxf) ([**const**](classCoordinate2D.md) std::vector&lt; [**Polyline**](classPolyline.md) &gt; & polylines, [**const**](classCoordinate2D.md) fs::path & filename) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_to\_dxf**](#function-write_to_dxf) (std::vector&lt; [**Contour**](classContour.md) &gt; contours, [**const**](classCoordinate2D.md) fs::path & filename, [**const**](classCoordinate2D.md) [**ContourConfigs**](structContourConfigs.md) & contour\_configs) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_to\_dxf**](#function-write_to_dxf) ([**const**](classCoordinate2D.md) std::vector&lt; [**Stream**](structStream.md) &gt; & streams, [**const**](classCoordinate2D.md) fs::path & filename, [**const**](classCoordinate2D.md) std::string & layer\_name) <br> |




























## Public Functions Documentation




### function dxf\_entities 

```C++
inline std::string dxf_entities () 
```




<hr>



### function dxf\_footer 

```C++
inline std::string dxf_footer () 
```




<hr>



### function dxf\_header 

```C++
inline std::string dxf_header () 
```




<hr>



### function read\_dxf 

```C++
inline std::vector< Contour > read_dxf (
    const fs::path & filename
) 
```




<hr>



### function vertex\_from\_dxf 

```C++
inline Coordinate2D < double > vertex_from_dxf (
    std::ifstream & dxfFile
) 
```




<hr>



### function write\_to\_crt 

```C++
inline void write_to_crt (
    const fs::path & filename
) 
```




<hr>



### function write\_to\_dxf 

```C++
inline void write_to_dxf (
    const std::vector< Polyline > & polylines,
    const fs::path & filename
) 
```




<hr>



### function write\_to\_dxf 

```C++
inline void write_to_dxf (
    std::vector< Contour > contours,
    const fs::path & filename,
    const  ContourConfigs & contour_configs
) 
```




<hr>



### function write\_to\_dxf 

```C++
inline void write_to_dxf (
    const std::vector< Stream > & streams,
    const fs::path & filename,
    const std::string & layer_name
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/dxf/dxf.hpp`

