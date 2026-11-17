

# File blaze\_output\_loader.hpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**blaze\_output\_loader.hpp**](blaze__output__loader_8hpp.md)

[Go to the source code of this file](blaze__output__loader_8hpp_source.md)



* `#include <algorithm>`
* `#include <functional>`
* `#include <memory>`
* `#include <optional>`
* `#include <set>`
* `#include <sstream>`
* `#include <string>`
* `#include <vector>`
* `#include "gui/layer.hpp"`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**detail**](namespacedetail.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**BlazeOutputDiscovery**](structBlazeOutputDiscovery.md) <br> |
| struct | [**BlazeOutputSet**](structBlazeOutputSet.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**append\_flat\_grid\_dem\_layers**](#function-append_flat_grid_dem_layers) (std::vector&lt; std::unique\_ptr&lt; [**Layer**](classLayer.md) &gt; &gt; & layers, const [**BlazeOutputSet**](structBlazeOutputSet.md) & outputs, const std::function&lt; [**AsyncProgressTracker**](classAsyncProgressTracker.md)()&gt; & progress\_factory, const std::string & target\_crs) <br> |
|  [**BlazeOutputSet**](structBlazeOutputSet.md) | [**discover\_blaze\_output**](#function-discover_blaze_output) (const fs::path & directory) <br> |
|  [**BlazeOutputDiscovery**](structBlazeOutputDiscovery.md) | [**discover\_blaze\_output\_with\_info**](#function-discover_blaze_output_with_info) (const fs::path & directory) <br> |
|  std::string | [**format\_blaze\_output\_discovery\_error**](#function-format_blaze_output_discovery_error) (const fs::path & directory, const [**BlazeOutputDiscovery**](structBlazeOutputDiscovery.md) & discovery) <br> |
|  std::vector&lt; std::unique\_ptr&lt; [**Layer**](classLayer.md) &gt; &gt; | [**load\_blaze\_outputs**](#function-load_blaze_outputs) (const [**BlazeOutputSet**](structBlazeOutputSet.md) & outputs, const std::function&lt; [**AsyncProgressTracker**](classAsyncProgressTracker.md)()&gt; & progress\_factory, const std::function&lt; std::string()&gt; & reference\_crs\_factory=[] { return std::string{};}) <br> |




























## Public Functions Documentation




### function append\_flat\_grid\_dem\_layers 

```C++
inline void append_flat_grid_dem_layers (
    std::vector< std::unique_ptr< Layer > > & layers,
    const BlazeOutputSet & outputs,
    const std::function< AsyncProgressTracker ()> & progress_factory,
    const std::string & target_crs
) 
```




<hr>



### function discover\_blaze\_output 

```C++
inline BlazeOutputSet discover_blaze_output (
    const fs::path & directory
) 
```




<hr>



### function discover\_blaze\_output\_with\_info 

```C++
inline BlazeOutputDiscovery discover_blaze_output_with_info (
    const fs::path & directory
) 
```




<hr>



### function format\_blaze\_output\_discovery\_error 

```C++
inline std::string format_blaze_output_discovery_error (
    const fs::path & directory,
    const BlazeOutputDiscovery & discovery
) 
```




<hr>



### function load\_blaze\_outputs 

```C++
inline std::vector< std::unique_ptr< Layer > > load_blaze_outputs (
    const BlazeOutputSet & outputs,
    const std::function< AsyncProgressTracker ()> & progress_factory,
    const std::function< std::string()> & reference_crs_factory=[] { return std::string{};}
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/blaze_output_loader.hpp`

