

# File proj\_data.hpp



[**FileList**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**proj\_data.hpp**](proj__data_8hpp.md)

[Go to the source code of this file](proj__data_8hpp_source.md)



* `#include <optional>`
* `#include <string>`
* `#include <vector>`
* `#include "utilities/filesystem.hpp"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::optional&lt; fs::path &gt; | [**configure\_bundled\_proj\_data**](#function-configure_bundled_proj_data) (const fs::path & executable) <br> |
|  std::optional&lt; fs::path &gt; | [**configure\_bundled\_proj\_data**](#function-configure_bundled_proj_data) () <br> |
|  bool | [**proj\_database\_available**](#function-proj_database_available) () <br> |
|  std::vector&lt; std::string &gt; | [**proj\_search\_paths**](#function-proj_search_paths) () <br> |




























## Public Functions Documentation




### function configure\_bundled\_proj\_data 

```C++
std::optional< fs::path > configure_bundled_proj_data (
    const fs::path & executable
) 
```




<hr>



### function configure\_bundled\_proj\_data 

```C++
std::optional< fs::path > configure_bundled_proj_data () 
```




<hr>



### function proj\_database\_available 

```C++
bool proj_database_available () 
```




<hr>



### function proj\_search\_paths 

```C++
std::vector< std::string > proj_search_paths () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/io/proj_data.hpp`

