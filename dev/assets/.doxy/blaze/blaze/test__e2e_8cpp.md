

# File test\_e2e.cpp



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**tests**](dir_d93a1d4020dea85bb71b237545b5e722.md) **>** [**test\_e2e.cpp**](test__e2e_8cpp.md)

[Go to the source code of this file](test__e2e_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <cmath>`
* `#include <cstdlib>`
* `#include <filesystem>`
* `#include <fstream>`
* `#include <functional>`
* `#include <iomanip>`
* `#include <iostream>`
* `#include <numbers>`
* `#include "config_input/config_input.hpp"`
* `#include "contour/contour.hpp"`
* `#include "gdal_priv.h"`
* `#include "io/gdal_init.hpp"`
* `#include "io/gpkg.hpp"`
* `#include "isom/colors.hpp"`
* `#include "las/las_file.hpp"`
* `#include "las/las_point.hpp"`
* `#include "lib/grid/grid.hpp"`
* `#include "ogr_srs_api.h"`
* `#include "process.hpp"`
* `#include "testing/env.hpp"`
* `#include "testing/output_dir.hpp"`
* `#include "tif/tif.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/resources.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**E2ETerrainTest**](classE2ETerrainTest.md) <br> |
| struct | [**TerrainTestParams**](structTerrainTestParams.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**INSTANTIATE\_TEST\_SUITE\_P**](#function-instantiate_test_suite_p) (E2E\_New, [**E2ETerrainTest**](classE2ETerrainTest.md), ::testing::Values([**TerrainTestParams**](structTerrainTestParams.md){"FlatTerrainGroundOnly",[](double, double) { return 102.5;}, false, false}, [**TerrainTestParams**](structTerrainTestParams.md){"FlatTerrainWithVegetation",[](double, double) { return 102.5;}, true, false}, [**TerrainTestParams**](structTerrainTestParams.md){"SlopedTerrainGroundOnly",[](double x, double) { return 100.0+x \*0.2;}, false, true}, [**TerrainTestParams**](structTerrainTestParams.md){"SlopedTerrainWithVegetation",[](double x, double) { return 100.0+x \*0.2;}, true, true}, [**TerrainTestParams**](structTerrainTestParams.md){"HillTerrainGroundOnly",[](double x, double y) { double dist=std::sqrt(std::pow(x - 50, 2)+std::pow(y - 50, 2));return 99.0+std::max(0.0, 20.0 - dist \*0.5);}, false, true}, [**TerrainTestParams**](structTerrainTestParams.md){"HillTerrainWithVegetation",[](double x, double y) { double dist=std::sqrt(std::pow(x - 50, 2)+std::pow(y - 50, 2));return 99.0+std::max(0.0, 20.0 - dist \*0.5);}, true, true})) <br> |
|   | [**TEST**](#function-test) (E2E, ProcessSyntheticData) <br> |
|   | [**TEST**](#function-test) (E2E, ProcessEmptyData) <br> |
|   | [**TEST**](#function-test) (E2E, ProcessDifferentResolutions) <br> |
|   | [**TEST**](#function-test) (E2E, VerifyOutputStructure) <br> |
|   | [**TEST**](#function-test) (E2E, GroundEstimationSlopes) <br> |
|   | [**TEST**](#function-test) (WriteToImageTif, AbsoluteSlopeBounds) <br> |
|   | [**TEST**](#function-test) (WriteToImageTif, NodataPixelsMapToZero) <br> |
|   | [**TEST**](#function-test) (WriteToImageTif, PerTileBoundsDefault) <br> |
|   | [**TEST**](#function-test) (WriteToImageTif, ConstantGrid) <br> |
|   | [**TEST\_P**](#function-test_p) ([**E2ETerrainTest**](classE2ETerrainTest.md), ProcessTerrain) <br> |
|  [**Config**](structConfig.md) | [**create\_minimal\_test\_config**](#function-create_minimal_test_config) (const fs::path & output\_dir) <br> |
|  [**LASData**](classLASData.md) | [**create\_synthetic\_las\_data**](#function-create_synthetic_las_data) () <br> |
|  [**LASData**](classLASData.md) | [**create\_synthetic\_las\_data\_ext**](#function-create_synthetic_las_data_ext) (const [**Extent2D**](structExtent2D.md) & extent, const std::function&lt; double(double, double)&gt; & height\_function, bool with\_vegetation) <br> |
|  std::string | [**get\_wgs84\_wkt**](#function-get_wgs84_wkt) () <br> |
|  void | [**verify\_raw\_vegetation\_tif**](#function-verify_raw_vegetation_tif) (const fs::path & raw\_vege\_tif\_path, bool should\_have\_vegetation, const [**Config**](structConfig.md) & config) <br> |
|  void | [**verify\_vegetation\_tif**](#function-verify_vegetation_tif) (const fs::path & vege\_tif\_path, bool should\_have\_vegetation, const [**Config**](structConfig.md) & config) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; uint8\_t &gt; | [**read\_byte\_tif\_pixels**](#function-read_byte_tif_pixels) (const fs::path & path) <br> |


























## Public Functions Documentation




### function INSTANTIATE\_TEST\_SUITE\_P 

```C++
INSTANTIATE_TEST_SUITE_P (
    E2E_New,
    E2ETerrainTest,
    ::testing::Values( TerrainTestParams {"FlatTerrainGroundOnly",[](double, double) { return 102.5;}, false, false}, TerrainTestParams {"FlatTerrainWithVegetation",[](double, double) { return 102.5;}, true, false}, TerrainTestParams {"SlopedTerrainGroundOnly",[](double x, double) { return 100.0+x *0.2;}, false, true}, TerrainTestParams {"SlopedTerrainWithVegetation",[](double x, double) { return 100.0+x *0.2;}, true, true}, TerrainTestParams {"HillTerrainGroundOnly",[](double x, double y) { double dist=std::sqrt(std::pow(x - 50, 2)+std::pow(y - 50, 2));return 99.0+std::max(0.0, 20.0 - dist *0.5);}, false, true}, TerrainTestParams {"HillTerrainWithVegetation",[](double x, double y) { double dist=std::sqrt(std::pow(x - 50, 2)+std::pow(y - 50, 2));return 99.0+std::max(0.0, 20.0 - dist *0.5);}, true, true})
) 
```




<hr>



### function TEST 

```C++
TEST (
    E2E,
    ProcessSyntheticData
) 
```




<hr>



### function TEST 

```C++
TEST (
    E2E,
    ProcessEmptyData
) 
```




<hr>



### function TEST 

```C++
TEST (
    E2E,
    ProcessDifferentResolutions
) 
```




<hr>



### function TEST 

```C++
TEST (
    E2E,
    VerifyOutputStructure
) 
```




<hr>



### function TEST 

```C++
TEST (
    E2E,
    GroundEstimationSlopes
) 
```




<hr>



### function TEST 

```C++
TEST (
    WriteToImageTif,
    AbsoluteSlopeBounds
) 
```




<hr>



### function TEST 

```C++
TEST (
    WriteToImageTif,
    NodataPixelsMapToZero
) 
```




<hr>



### function TEST 

```C++
TEST (
    WriteToImageTif,
    PerTileBoundsDefault
) 
```




<hr>



### function TEST 

```C++
TEST (
    WriteToImageTif,
    ConstantGrid
) 
```




<hr>



### function TEST\_P 

```C++
TEST_P (
    E2ETerrainTest,
    ProcessTerrain
) 
```




<hr>



### function create\_minimal\_test\_config 

```C++
Config create_minimal_test_config (
    const fs::path & output_dir
) 
```




<hr>



### function create\_synthetic\_las\_data 

```C++
LASData create_synthetic_las_data () 
```




<hr>



### function create\_synthetic\_las\_data\_ext 

```C++
LASData create_synthetic_las_data_ext (
    const Extent2D & extent,
    const std::function< double(double, double)> & height_function,
    bool with_vegetation
) 
```




<hr>



### function get\_wgs84\_wkt 

```C++
std::string get_wgs84_wkt () 
```




<hr>



### function verify\_raw\_vegetation\_tif 

```C++
void verify_raw_vegetation_tif (
    const fs::path & raw_vege_tif_path,
    bool should_have_vegetation,
    const Config & config
) 
```




<hr>



### function verify\_vegetation\_tif 

```C++
void verify_vegetation_tif (
    const fs::path & vege_tif_path,
    bool should_have_vegetation,
    const Config & config
) 
```




<hr>
## Public Static Functions Documentation




### function read\_byte\_tif\_pixels 

```C++
static std::vector< uint8_t > read_byte_tif_pixels (
    const fs::path & path
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/tests/test_e2e.cpp`

