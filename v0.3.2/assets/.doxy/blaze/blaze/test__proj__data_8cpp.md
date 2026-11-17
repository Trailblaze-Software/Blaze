

# File test\_proj\_data.cpp



[**FileList**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**tests**](dir_48b62e9add78df78566b95ab9cc595a8.md) **>** [**test\_proj\_data.cpp**](test__proj__data_8cpp.md)

[Go to the source code of this file](test__proj__data_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <string>`
* `#include <thread>`
* `#include <vector>`
* `#include "io/crs.hpp"`
* `#include "io/proj_data.hpp"`
* `#include "las/las_file.hpp"`
* `#include "testing/output_dir.hpp"`
* `#include "utilities/env.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) (ProjData, GeoKeysOnlyLasHasEmbeddedCrs) <br> |
|   | [**TEST**](#function-test) (ProjData, MissingProjDbHidesEmbeddedCrs) <br> |
|   | [**TEST**](#function-test) (ProjData, ConfigureUsesDataInsideAppBundle) <br> |
|   | [**TEST**](#function-test) (ProjData, BareEpsgCodeIsAccepted) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    ProjData,
    GeoKeysOnlyLasHasEmbeddedCrs
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProjData,
    MissingProjDbHidesEmbeddedCrs
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProjData,
    ConfigureUsesDataInsideAppBundle
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProjData,
    BareEpsgCodeIsAccepted
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/io/tests/test_proj_data.cpp`

