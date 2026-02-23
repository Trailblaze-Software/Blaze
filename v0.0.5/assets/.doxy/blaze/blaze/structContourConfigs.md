

# Struct ContourConfigs



[**ClassList**](annotated.md) **>** [**ContourConfigs**](structContourConfigs.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; std::string, [**ContourConfig**](structContourConfig.md) &gt; | [**configs**](#variable-configs)  <br> |
|  [**double**](classCoordinate2D.md) | [**min\_interval**](#variable-min_interval)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ContourConfigs**](#function-contourconfigs-12) () <br> |
|   | [**ContourConfigs**](#function-contourconfigs-22) (std::map&lt; std::string, [**ContourConfig**](structContourConfig.md) &gt; in\_configs) <br> |
|  std::string | [**layer\_name\_from\_height**](#function-layer_name_from_height) ([**double**](classCoordinate2D.md) height) const<br> |
|  [**const**](classCoordinate2D.md) [**ContourConfig**](structContourConfig.md) & | [**operator[]**](#function-operator) ([**const**](classCoordinate2D.md) std::string & key) const<br> |
|  [**const**](classCoordinate2D.md) [**ContourConfig**](structContourConfig.md) & | [**pick\_from\_height**](#function-pick_from_height) ([**double**](classCoordinate2D.md) height) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**double**](classCoordinate2D.md) | [**minimum\_interval**](#function-minimum_interval) ([**const**](classCoordinate2D.md) std::map&lt; std::string, [**ContourConfig**](structContourConfig.md) &gt; & configs) <br> |


























## Public Attributes Documentation




### variable configs 

```C++
std::map<std::string, ContourConfig> ContourConfigs::configs;
```




<hr>



### variable min\_interval 

```C++
double ContourConfigs::min_interval;
```




<hr>
## Public Functions Documentation




### function ContourConfigs [1/2]

```C++
inline ContourConfigs::ContourConfigs () 
```




<hr>



### function ContourConfigs [2/2]

```C++
inline explicit ContourConfigs::ContourConfigs (
    std::map< std::string, ContourConfig > in_configs
) 
```




<hr>



### function layer\_name\_from\_height 

```C++
inline std::string ContourConfigs::layer_name_from_height (
    double height
) const
```




<hr>



### function operator[] 

```C++
inline const  ContourConfig & ContourConfigs::operator[] (
    const std::string & key
) const
```




<hr>



### function pick\_from\_height 

```C++
inline const  ContourConfig & ContourConfigs::pick_from_height (
    double height
) const
```




<hr>
## Public Static Functions Documentation




### function minimum\_interval 

```C++
static inline double ContourConfigs::minimum_interval (
    const std::map< std::string, ContourConfig > & configs
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/config_input/config_input.hpp`

