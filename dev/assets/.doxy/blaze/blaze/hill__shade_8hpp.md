

# File hill\_shade.hpp



[**FileList**](files.md) **>** [**hill\_shade**](dir_e03c0efc459c079af38b3a453937aed0.md) **>** [**hill\_shade.hpp**](hill__shade_8hpp.md)

[Go to the source code of this file](hill__shade_8hpp_source.md)



* `#include <cmath>`
* `#include <limits>`
* `#include <numbers>`
* `#include "grid/grid.hpp"`
* `#include "utilities/progress_tracker.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**GeoGrid**](classGeo.md)&lt; double &gt; | [**hill\_shade**](#function-hill_shade) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, double azimuth, double altitude, const bool multidirectional, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DEG2RAD**](hill__shade_8hpp.md#define-deg2rad) (x) `((x) \* std::numbers::pi / 180)`<br> |
| define  | [**SQ**](hill__shade_8hpp.md#define-sq) (x) `((x) \* (x))`<br> |

## Public Functions Documentation




### function hill\_shade 

```C++
template<typename T>
GeoGrid < double > hill_shade (
    const GeoGrid < T > & grid,
    double azimuth,
    double altitude,
    const bool multidirectional,
    ProgressTracker && progress_tracker
) 
```




<hr>
## Macro Definition Documentation





### define DEG2RAD 

```C++
#define DEG2RAD (
    x
) `((x) * std::numbers::pi / 180)`
```




<hr>



### define SQ 

```C++
#define SQ (
    x
) `((x) * (x))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/methods/hill_shade/hill_shade.hpp`

