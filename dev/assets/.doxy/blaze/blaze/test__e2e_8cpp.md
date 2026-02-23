

# File test\_e2e.cpp



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**tests**](dir_d93a1d4020dea85bb71b237545b5e722.md) **>** [**test\_e2e.cpp**](test__e2e_8cpp.md)

[Go to the source code of this file](test__e2e_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <cmath>`
* `#include <cstdlib>`
* `#include <filesystem>`
* `#include <fstream>`
* `#include <iostream>`
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
* `#include "tif/tif.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/resources.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**E2ETerrainTest**](classE2ETerrainTest.md) <br> |
| struct | [**TerrainTestParams**](structTerrainTestParams.md) <br> |
| class | [**TestGrid**](classTestGrid.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**INSTANTIATE\_TEST\_SUITE\_P**](#function-instantiate_test_suite_p) ([**E2E\_New**](classCoordinate2D.md), [**E2ETerrainTest**](classE2ETerrainTest.md), ::testing::Values([**TerrainTestParams**](structTerrainTestParams.md){"FlatTerrainGroundOnly",[]([**double**](classCoordinate2D.md), [**double**](classCoordinate2D.md)) { [**return**](classCoordinate2D.md) 102.5;}, [**false**](classCoordinate2D.md), [**false**](classCoordinate2D.md)}, [**TerrainTestParams**](structTerrainTestParams.md){"FlatTerrainWithVegetation",[]([**double**](classCoordinate2D.md), [**double**](classCoordinate2D.md)) { [**return**](classCoordinate2D.md) 102.5;}, [**true**](classCoordinate2D.md), [**false**](classCoordinate2D.md)}, [**TerrainTestParams**](structTerrainTestParams.md){"SlopedTerrainGroundOnly",[]([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md)) { [**return**](classCoordinate2D.md) 100.0+x \*0.2;}, [**false**](classCoordinate2D.md), [**true**](classCoordinate2D.md)}, [**TerrainTestParams**](structTerrainTestParams.md){"SlopedTerrainWithVegetation",[]([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md)) { [**return**](classCoordinate2D.md) 100.0+x \*0.2;}, [**true**](classCoordinate2D.md), [**true**](classCoordinate2D.md)}, [**TerrainTestParams**](structTerrainTestParams.md){"HillTerrainGroundOnly",[]([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) y) { [**double**](classCoordinate2D.md) [**dist**](classCoordinate2D.md)=std::sqrt(std::pow(x - 50, 2)+std::pow(y - 50, 2));[**return**](classCoordinate2D.md) 99.0+std::max(0.0, 20.0 - [**dist**](classCoordinate2D.md) \*0.5);}, [**false**](classCoordinate2D.md), [**true**](classCoordinate2D.md)}, [**TerrainTestParams**](structTerrainTestParams.md){"HillTerrainWithVegetation",[]([**double**](classCoordinate2D.md) x, [**double**](classCoordinate2D.md) y) { [**double**](classCoordinate2D.md) [**dist**](classCoordinate2D.md)=std::sqrt(std::pow(x - 50, 2)+std::pow(y - 50, 2));[**return**](classCoordinate2D.md) 99.0+std::max(0.0, 20.0 - [**dist**](classCoordinate2D.md) \*0.5);}, [**true**](classCoordinate2D.md), [**true**](classCoordinate2D.md)})) <br> |
|   | [**TEST**](#function-test) ([**E2E**](classCoordinate2D.md), [**ProcessSyntheticData**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**E2E**](classCoordinate2D.md), [**ProcessEmptyData**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**E2E**](classCoordinate2D.md), [**ProcessDifferentResolutions**](classCoordinate2D.md)) <br> |
|   | [**TEST**](#function-test) ([**E2E**](classCoordinate2D.md), [**VerifyOutputStructure**](classCoordinate2D.md)) <br> |
|   | [**TEST\_P**](#function-test_p) ([**E2ETerrainTest**](classE2ETerrainTest.md), [**ProcessTerrain**](classCoordinate2D.md)) <br> |
|  [**Config**](structConfig.md) | [**create\_minimal\_test\_config**](#function-create_minimal_test_config) ([**const**](classCoordinate2D.md) fs::path & output\_dir) <br> |
|  [**LASData**](classLASData.md) | [**create\_synthetic\_las\_data**](#function-create_synthetic_las_data) () <br> |
|  [**LASData**](classLASData.md) | [**create\_synthetic\_las\_data\_ext**](#function-create_synthetic_las_data_ext) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & extent, [**const**](classCoordinate2D.md) std::function&lt; [**double**](classCoordinate2D.md)([**double**](classCoordinate2D.md), [**double**](classCoordinate2D.md))&gt; & height\_function, [**bool**](classCoordinate2D.md) with\_vegetation) <br> |
|  std::string | [**get\_wgs84\_wkt**](#function-get_wgs84_wkt) () <br> |
|  [**void**](classCoordinate2D.md) | [**verify\_raw\_vegetation\_tif**](#function-verify_raw_vegetation_tif) ([**const**](classCoordinate2D.md) fs::path & raw\_vege\_tif\_path, [**bool**](classCoordinate2D.md) should\_have\_vegetation, [**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config) <br> |
|  [**void**](classCoordinate2D.md) | [**verify\_vegetation\_tif**](#function-verify_vegetation_tif) ([**const**](classCoordinate2D.md) fs::path & vege\_tif\_path, [**bool**](classCoordinate2D.md) should\_have\_vegetation, [**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config) <br> |




























## Public Functions Documentation




### function INSTANTIATE\_TEST\_SUITE\_P 

```C++
INSTANTIATE_TEST_SUITE_P (
    E2E_New,
    E2ETerrainTest,
    ::testing::Values( TerrainTestParams {"FlatTerrainGroundOnly",[]( double , double ) { return 102.5;}, false , false }, TerrainTestParams {"FlatTerrainWithVegetation",[]( double , double ) { return 102.5;}, true , false }, TerrainTestParams {"SlopedTerrainGroundOnly",[]( double x, double ) { return 100.0+x *0.2;}, false , true }, TerrainTestParams {"SlopedTerrainWithVegetation",[]( double x, double ) { return 100.0+x *0.2;}, true , true }, TerrainTestParams {"HillTerrainGroundOnly",[]( double x, double y) { double  dist =std::sqrt(std::pow(x - 50, 2)+std::pow(y - 50, 2)); return 99.0+std::max(0.0, 20.0 - dist *0.5);}, false , true }, TerrainTestParams {"HillTerrainWithVegetation",[]( double x, double y) { double  dist =std::sqrt(std::pow(x - 50, 2)+std::pow(y - 50, 2)); return 99.0+std::max(0.0, 20.0 - dist *0.5);}, true , true })
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
    const  Extent2D & extent,
    const std::function< double ( double , double )> & height_function,
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
    const  Config & config
) 
```




<hr>



### function verify\_vegetation\_tif 

```C++
void verify_vegetation_tif (
    const fs::path & vege_tif_path,
    bool should_have_vegetation,
    const  Config & config
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/tests/test_e2e.cpp`

