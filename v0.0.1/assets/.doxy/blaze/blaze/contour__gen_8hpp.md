

# File contour\_gen.hpp



[**FileList**](files.md) **>** [**contour**](dir_168d7404e8aa1148a0abea8bd7ba0546.md) **>** [**contour\_gen.hpp**](contour__gen_8hpp.md)

[Go to the source code of this file](contour__gen_8hpp_source.md)



* `#include "config_input/config_input.hpp"`
* `#include "contour.hpp"`
* `#include "utilities/timer.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**generate\_contours**](#function-generate_contours) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, [**const**](classCoordinate2D.md) [**ContourConfigs**](structContourConfigs.md) & contour\_config, [**ProgressTracker**](classProgressTracker.md) progress\_tracker) <br> |
|  [**GeoGrid**](classGeo.md)&lt; std::optional&lt; std::byte &gt; &gt; | [**generate\_naive\_contours**](#function-generate_naive_contours) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; [**double**](classCoordinate2D.md) &gt; & ground) <br> |
|  [**GridGraph**](classGridGraph.md)&lt; std::set&lt; [**double**](classCoordinate2D.md) &gt; &gt; | [**identify\_contours**](#function-identify_contours) ([**const**](classCoordinate2D.md) [**GeoGrid**](classGeo.md)&lt; T &gt; & grid, T contour\_interval) <br> |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**join\_contours**](#function-join_contours) (std::vector&lt; [**Contour**](classContour.md) &gt; contours, [**double**](classCoordinate2D.md) max\_dist=15.0) <br> |
|  std::vector&lt; [**Contour**](classContour.md) &gt; | [**trim\_contours**](#function-trim_contours) ([**const**](classCoordinate2D.md) std::vector&lt; [**Contour**](classContour.md) &gt; & contours, [**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & bounds) <br> |




























## Public Functions Documentation




### function generate\_contours 

```C++
template<typename T>
std::vector< Contour > generate_contours (
    const  GeoGrid < T > & grid,
    const  ContourConfigs & contour_config,
    ProgressTracker progress_tracker
) 
```




<hr>



### function generate\_naive\_contours 

```C++
inline GeoGrid < std::optional< std::byte > > generate_naive_contours (
    const  GeoGrid < double > & ground
) 
```




<hr>



### function identify\_contours 

```C++
template<typename T>
GridGraph < std::set< double > > identify_contours (
    const  GeoGrid < T > & grid,
    T contour_interval
) 
```




<hr>



### function join\_contours 

```C++
inline std::vector< Contour > join_contours (
    std::vector< Contour > contours,
    double max_dist=15.0
) 
```




<hr>



### function trim\_contours 

```C++
inline std::vector< Contour > trim_contours (
    const std::vector< Contour > & contours,
    const  Extent2D & bounds
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/contour/contour_gen.hpp`

