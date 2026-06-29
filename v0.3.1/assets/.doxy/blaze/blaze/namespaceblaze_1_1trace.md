

# Namespace blaze::trace



[**Namespace List**](namespaces.md) **>** [**blaze**](namespaceblaze.md) **>** [**trace**](namespaceblaze_1_1trace.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**RecordTrace**](classblaze_1_1trace_1_1RecordTrace.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef nlohmann::json | [**json**](#typedef-json)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**enabled**](#function-enabled) () <br> |
|  std::string | [**format\_active\_scopes**](#function-format_active_scopes) () <br> |
|  void | [**memory\_counters**](#function-memory_counters) (const uint64\_t total\_bytes, const uint64\_t las\_bytes, const uint64\_t grid\_bytes) <br> |
|  void | [**progress\_end**](#function-progress_end) (const uint64\_t scope\_id, const double proportion) <br> |
|  void | [**progress\_scope\_set\_display**](#function-progress_scope_set_display) (const uint64\_t scope\_id, const std::string & name, const std::source\_location & callee\_location) <br> |
|  uint64\_t | [**register\_progress\_scope**](#function-register_progress_scope) (const std::source\_location & location, const double range\_start, const double range\_end, const std::string & name, const std::source\_location \* call\_site) <br> |
|  void | [**write\_chrome\_trace**](#function-write_chrome_trace) (const fs::path & path) <br> |
|  void | [**write\_chrome\_trace\_if\_configured**](#function-write_chrome_trace_if_configured) () <br> |




























## Public Types Documentation




### typedef json 

```C++
using blaze::trace::json = typedef nlohmann::json;
```




<hr>
## Public Functions Documentation




### function enabled 

```C++
bool blaze::trace::enabled () 
```




<hr>



### function format\_active\_scopes 

```C++
std::string blaze::trace::format_active_scopes () 
```




<hr>



### function memory\_counters 

```C++
void blaze::trace::memory_counters (
    const uint64_t total_bytes,
    const uint64_t las_bytes,
    const uint64_t grid_bytes
) 
```




<hr>



### function progress\_end 

```C++
void blaze::trace::progress_end (
    const uint64_t scope_id,
    const double proportion
) 
```




<hr>



### function progress\_scope\_set\_display 

```C++
void blaze::trace::progress_scope_set_display (
    const uint64_t scope_id,
    const std::string & name,
    const std::source_location & callee_location
) 
```




<hr>



### function register\_progress\_scope 

```C++
uint64_t blaze::trace::register_progress_scope (
    const std::source_location & location,
    const double range_start,
    const double range_end,
    const std::string & name,
    const std::source_location * call_site
) 
```




<hr>



### function write\_chrome\_trace 

```C++
void blaze::trace::write_chrome_trace (
    const fs::path & path
) 
```




<hr>



### function write\_chrome\_trace\_if\_configured 

```C++
void blaze::trace::write_chrome_trace_if_configured () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/trace_recorder.cpp`

