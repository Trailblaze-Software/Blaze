

# File las\_point.hpp



[**FileList**](files.md) **>** [**las**](dir_50e4ddd575fc604ec1609997d931fab5.md) **>** [**las\_point.hpp**](las__point_8hpp.md)

[Go to the source code of this file](las__point_8hpp_source.md)



* `#include <cstdint>`
* `#include <utilities/coordinate.hpp>`
* `#include "assert/assert.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**LASPoint**](classLASPoint.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum [**uint8\_t**](classCoordinate2D.md) | [**LASClassification**](#enum-lasclassification)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator) (std::ostream & os, [**const**](classCoordinate2D.md) LASClassification & classification) <br> |




























## Public Types Documentation




### enum LASClassification 

```C++
enum LASClassification {
    CreatedNeverClassified = 0,
    Unclassified = 1,
    Ground = 2,
    LowVegetation = 3,
    MediumVegetation = 4,
    HighVegetation = 5,
    Building = 6,
    LowPoint = 7,
    ModelKeyPoint = 8,
    Water = 9
};
```




<hr>
## Public Functions Documentation




### function operator&lt;&lt; 

```C++
inline std::ostream & operator<< (
    std::ostream & os,
    const LASClassification & classification
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/las/las_point.hpp`

