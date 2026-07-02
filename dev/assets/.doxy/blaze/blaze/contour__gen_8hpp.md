

# File contour\_gen.hpp



[**FileList**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**contour\_gen.hpp**](contour__gen_8hpp.md)

[Go to the source code of this file](contour__gen_8hpp_source.md)



* `#include <map>`
* `#include <optional>`
* `#include <set>`
* `#include <vector>`
* `#include "config_input/config_input.hpp"`
* `#include "contour.hpp"`
* `#include "geometry/polygon.hpp"`
* `#include "utilities/progress_tracker.hpp"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**detail**](namespacedetail.md) <br> |
























## Public Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**generate\_contours**](#function-generate_contours) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const [**ContourConfigs**](structContourConfigs.md) & contour\_config, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  std::map&lt; double, std::vector&lt; [**Contour**](classContour.md) &gt; &gt; | [**generate\_contours\_at\_heights**](#function-generate_contours_at_heights) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const std::vector&lt; double &gt; & heights, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, size\_t min\_points=3, std::optional&lt; T &gt; pad\_value=std::nullopt, SaddlePolicy saddle\_policy=SaddlePolicy::AlwaysOutside) <br> |
|  std::map&lt; double, std::vector&lt; [**Contour**](classContour.md) &gt; &gt; | [**generate\_contours\_at\_heights**](#function-generate_contours_at_heights) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const std::vector&lt; double &gt; & heights, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, size\_t min\_points, T pad\_value, SaddlePolicy saddle\_policy=SaddlePolicy::AlwaysOutside) <br> |
|  [**GeoGrid**](classGeo.md)&lt; std::optional&lt; std::byte &gt; &gt; | [**generate\_naive\_contours**](#function-generate_naive_contours) (const [**GeoGrid**](classGeo.md)&lt; double &gt; & ground) <br> |
|  [**GridGraph**](classGridGraph.md)&lt; std::set&lt; double &gt; &gt; | [**identify\_contours**](#function-identify_contours) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, T contour\_interval, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**GridGraph**](classGridGraph.md)&lt; std::set&lt; double &gt; &gt; | [**identify\_contours\_at\_heights**](#function-identify_contours_at_heights) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const std::set&lt; double &gt; & heights, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, std::optional&lt; T &gt; pad\_value=std::nullopt) <br> |
|  [**GridGraph**](classGridGraph.md)&lt; std::set&lt; double &gt; &gt; | [**identify\_contours\_at\_heights**](#function-identify_contours_at_heights) (const [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, const std::set&lt; double &gt; & heights, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker, T pad\_value) <br> |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**join\_contours**](#function-join_contours) (std::vector&lt; [**Contour**](classContour.md) &gt; contours, double max\_dist) <br> |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**trim\_contours**](#function-trim_contours) (const std::vector&lt; [**Contour**](classContour.md) &gt; & contours, const [**Extent2D**](structExtent2D.md) & bounds) <br> |




























## Public Functions Documentation




### function generate\_contours 

```C++
template<typename T>
std::vector< Contour > generate_contours (
    const GeoGrid < T > & grid,
    const ContourConfigs & contour_config,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function generate\_contours\_at\_heights 

```C++
template<typename T>
std::map< double, std::vector< Contour > > generate_contours_at_heights (
    const GeoGrid < T > & grid,
    const std::vector< double > & heights,
    ProgressTracker && progress_tracker,
    size_t min_points=3,
    std::optional< T > pad_value=std::nullopt,
    SaddlePolicy saddle_policy=SaddlePolicy::AlwaysOutside
) 
```




<hr>



### function generate\_contours\_at\_heights 

```C++
template<typename T>
std::map< double, std::vector< Contour > > generate_contours_at_heights (
    const GeoGrid < T > & grid,
    const std::vector< double > & heights,
    ProgressTracker && progress_tracker,
    size_t min_points,
    T pad_value,
    SaddlePolicy saddle_policy=SaddlePolicy::AlwaysOutside
) 
```




<hr>



### function generate\_naive\_contours 

```C++
inline GeoGrid < std::optional< std::byte > > generate_naive_contours (
    const GeoGrid < double > & ground
) 
```




<hr>



### function identify\_contours 

```C++
template<typename T>
GridGraph < std::set< double > > identify_contours (
    const GeoGrid < T > & grid,
    T contour_interval,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function identify\_contours\_at\_heights 

```C++
template<typename T>
GridGraph < std::set< double > > identify_contours_at_heights (
    const GeoGrid < T > & grid,
    const std::set< double > & heights,
    ProgressTracker && progress_tracker,
    std::optional< T > pad_value=std::nullopt
) 
```




<hr>



### function identify\_contours\_at\_heights 

```C++
template<typename T>
GridGraph < std::set< double > > identify_contours_at_heights (
    const GeoGrid < T > & grid,
    const std::set< double > & heights,
    ProgressTracker && progress_tracker,
    T pad_value
) 
```




<hr>



### function join\_contours 

```C++
inline std::vector< Contour > join_contours (
    std::vector< Contour > contours,
    double max_dist
) 
```




<hr>



### function trim\_contours 

```C++
inline std::vector< Contour > trim_contours (
    const std::vector< Contour > & contours,
    const Extent2D & bounds
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/contour_gen.hpp`

