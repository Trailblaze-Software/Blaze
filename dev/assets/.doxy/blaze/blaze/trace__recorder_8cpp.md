

# File trace\_recorder.cpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**trace\_recorder.cpp**](trace__recorder_8cpp.md)

[Go to the source code of this file](trace__recorder_8cpp_source.md)



* `#include "utilities/trace_recorder.hpp"`
* `#include <algorithm>`
* `#include <chrono>`
* `#include <cstdio>`
* `#include <fstream>`
* `#include <mutex>`
* `#include <nlohmann/json.hpp>`
* `#include <optional>`
* `#include <sstream>`
* `#include <string>`
* `#include <string_view>`
* `#include <thread>`
* `#include <vector>`
* `#include "utilities/env.hpp"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**blaze**](namespaceblaze.md) <br> |
| namespace | [**trace**](namespaceblaze_1_1trace.md) <br> |








## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::optional&lt; std::string &gt; | [**call\_file**](#variable-call_file)  <br> |
|  std::optional&lt; std::string &gt; | [**call\_function**](#variable-call_function)  <br> |
|  std::optional&lt; int &gt; | [**call\_line**](#variable-call_line)  <br> |
|  std::string | [**file**](#variable-file)  <br> |
|  std::string | [**function**](#variable-function)  <br> |
|  int | [**line**](#variable-line)   = `0`<br> |
|  std::string | [**name**](#variable-name)  <br> |
|  uint64\_t | [**scope\_id**](#variable-scope_id)   = `0`<br> |












































## Public Attributes Documentation




### variable call\_file 

```C++
std::optional<std::string> call_file;
```




<hr>



### variable call\_function 

```C++
std::optional<std::string> call_function;
```




<hr>



### variable call\_line 

```C++
std::optional<int> call_line;
```




<hr>



### variable file 

```C++
std::string file;
```




<hr>



### variable function 

```C++
std::string function;
```




<hr>



### variable line 

```C++
int line;
```




<hr>



### variable name 

```C++
std::string name;
```




<hr>



### variable scope\_id 

```C++
uint64_t scope_id;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/trace_recorder.cpp`

