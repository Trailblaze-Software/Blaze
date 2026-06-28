

# File vegetation.hpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**vegetation**](dir_b743e47c5a2b15e05ebb68ed1bfc6ebf.md) **>** [**vegetation.hpp**](vegetation_8hpp.md)

[Go to the source code of this file](vegetation_8hpp_source.md)



* `#include <algorithm>`
* `#include <cstddef>`
* `#include <span>`
* `#include "config_input/config_input.hpp"`
* `#include "grid/grid.hpp"`
* `#include "las/las_point.hpp"`
* `#include "utilities/coordinate.hpp"`
* `#include "utilities/progress_tracker.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**GeoGrid**](classGeo.md)&lt; std::optional&lt; float &gt; &gt; | [**get\_blocked\_proportion**](#function-get_blocked_proportion) (const [**GeoGrid**](classGeo.md)&lt; std::span&lt; [**LASPoint**](classLASPoint.md) &gt; &gt; & grid, const [**GeoGrid**](classGeo.md)&lt; double &gt; & ground, const [**VegeHeightConfig**](structVegeHeightConfig.md) & vege\_config, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**GeoGrid**](classGeo.md)&lt; float &gt; | [**low\_pass**](#function-low_pass) (const [**GeoGrid**](classGeo.md)&lt; float &gt; & grid, int delta, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |
|  [**GeoGrid**](classGeo.md)&lt; float &gt; | [**low\_pass**](#function-low_pass) (const [**GeoGrid**](classGeo.md)&lt; std::optional&lt; float &gt; &gt; & grid, int delta, [**ProgressTracker**](classProgressTracker.md) && progress\_tracker) <br> |




























## Public Functions Documentation




### function get\_blocked\_proportion 

```C++
inline GeoGrid < std::optional< float > > get_blocked_proportion (
    const GeoGrid < std::span< LASPoint > > & grid,
    const GeoGrid < double > & ground,
    const VegeHeightConfig & vege_config,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function low\_pass 

```C++
inline GeoGrid < float > low_pass (
    const GeoGrid < float > & grid,
    int delta,
    ProgressTracker && progress_tracker
) 
```




<hr>



### function low\_pass 

```C++
inline GeoGrid < float > low_pass (
    const GeoGrid < std::optional< float > > & grid,
    int delta,
    ProgressTracker && progress_tracker
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/vegetation/vegetation.hpp`

