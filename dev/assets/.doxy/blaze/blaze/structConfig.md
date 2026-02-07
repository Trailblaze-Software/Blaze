

# Struct Config



[**ClassList**](annotated.md) **>** [**Config**](structConfig.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**double**](classCoordinate2D.md) | [**border\_width**](#variable-border_width)  <br> |
|  [**BuildingsConfig**](structBuildingsConfig.md) | [**buildings**](#variable-buildings)  <br> |
|  [**ContourConfigs**](structContourConfigs.md) | [**contours**](#variable-contours)  <br> |
|  [**GridConfig**](structGridConfig.md) | [**grid**](#variable-grid)  <br> |
|  [**GroundConfig**](structGroundConfig.md) | [**ground**](#variable-ground)  <br> |
|  std::vector&lt; fs::path &gt; | [**las\_files**](#variable-las_files)  <br> |
|  fs::path | [**output\_directory**](#variable-output_directory)  <br> |
|  std::set&lt; ProcessingStep &gt; | [**processing\_steps**](#variable-processing_steps)  <br> |
|  fs::path | [**relative\_path\_to\_config**](#variable-relative_path_to_config)  <br> |
|  [**RenderConfig**](structRenderConfig.md) | [**render**](#variable-render)  <br> |
|  [**VegeConfig**](structVegeConfig.md) | [**vege**](#variable-vege)  <br> |
|  [**WaterConfigs**](structWaterConfigs.md) | [**water**](#variable-water)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Config**](#function-config-13) ([**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config) = delete<br> |
|   | [**Config**](#function-config-23) ([**Config**](structConfig.md) && config) = default<br> |
|   | [**Config**](#function-config-33) () = default<br> |
|  std::vector&lt; fs::path &gt; | [**get\_las\_files**](#function-get_las_files) ([**const**](classCoordinate2D.md) fs::path & las\_path) const<br> |
|  std::vector&lt; fs::path &gt; | [**las\_filepaths**](#function-las_filepaths) () const<br> |
|  [**Config**](structConfig.md) & | [**operator=**](#function-operator) ([**const**](classCoordinate2D.md) [**Config**](structConfig.md) & config) = default<br> |
|  fs::path | [**output\_path**](#function-output_path) () const<br> |
|  [**void**](classCoordinate2D.md) | [**set\_output\_directory**](#function-set_output_directory) ([**const**](classCoordinate2D.md) fs::path & output\_dir) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_to\_file**](#function-write_to_file) ([**const**](classCoordinate2D.md) fs::path & filename) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Config**](structConfig.md) | [**Default**](#function-default) () <br> |
|  [**Config**](structConfig.md) | [**FromFile**](#function-fromfile) ([**const**](classCoordinate2D.md) fs::path & filename) <br> |


























## Public Attributes Documentation




### variable border\_width 

```C++
double Config::border_width;
```




<hr>



### variable buildings 

```C++
BuildingsConfig Config::buildings;
```




<hr>



### variable contours 

```C++
ContourConfigs Config::contours;
```




<hr>



### variable grid 

```C++
GridConfig Config::grid;
```




<hr>



### variable ground 

```C++
GroundConfig Config::ground;
```




<hr>



### variable las\_files 

```C++
std::vector<fs::path> Config::las_files;
```




<hr>



### variable output\_directory 

```C++
fs::path Config::output_directory;
```




<hr>



### variable processing\_steps 

```C++
std::set<ProcessingStep> Config::processing_steps;
```




<hr>



### variable relative\_path\_to\_config 

```C++
fs::path Config::relative_path_to_config;
```




<hr>



### variable render 

```C++
RenderConfig Config::render;
```




<hr>



### variable vege 

```C++
VegeConfig Config::vege;
```




<hr>



### variable water 

```C++
WaterConfigs Config::water;
```




<hr>
## Public Functions Documentation




### function Config [1/3]

```C++
Config::Config (
    const  Config & config
) = delete
```




<hr>



### function Config [2/3]

```C++
Config::Config (
    Config && config
) = default
```




<hr>



### function Config [3/3]

```C++
Config::Config () = default
```




<hr>



### function get\_las\_files 

```C++
inline std::vector< fs::path > Config::get_las_files (
    const fs::path & las_path
) const
```




<hr>



### function las\_filepaths 

```C++
inline std::vector< fs::path > Config::las_filepaths () const
```




<hr>



### function operator= 

```C++
Config & Config::operator= (
    const  Config & config
) = default
```




<hr>



### function output\_path 

```C++
inline fs::path Config::output_path () const
```




<hr>



### function set\_output\_directory 

```C++
inline void Config::set_output_directory (
    const fs::path & output_dir
) 
```




<hr>



### function write\_to\_file 

```C++
void Config::write_to_file (
    const fs::path & filename
) const
```




<hr>
## Public Static Functions Documentation




### function Default 

```C++
static inline Config Config::Default () 
```




<hr>



### function FromFile 

```C++
static Config Config::FromFile (
    const fs::path & filename
) 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
std::ostream & Config::operator<< (
    std::ostream & os,
    const  Config & config
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/config_input/config_input.hpp`

