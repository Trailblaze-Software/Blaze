

# Struct WaterConfigs



[**ClassList**](annotated.md) **>** [**WaterConfigs**](structWaterConfigs.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; std::string, [**WaterConfig**](structWaterConfig.md) &gt; | [**configs**](#variable-configs)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**const**](classCoordinate2D.md) [**WaterConfig**](structWaterConfig.md) & | [**config\_from\_catchment**](#function-config_from_catchment) ([**double**](classCoordinate2D.md) catchment) const<br> |
|  [**double**](classCoordinate2D.md) | [**minimum\_catchment**](#function-minimum_catchment) () const<br> |




























## Public Attributes Documentation




### variable configs 

```C++
std::map<std::string, WaterConfig> WaterConfigs::configs;
```




<hr>
## Public Functions Documentation




### function config\_from\_catchment 

```C++
inline const  WaterConfig & WaterConfigs::config_from_catchment (
    double catchment
) const
```




<hr>



### function minimum\_catchment 

```C++
inline double WaterConfigs::minimum_catchment () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/config_input/config_input.hpp`

