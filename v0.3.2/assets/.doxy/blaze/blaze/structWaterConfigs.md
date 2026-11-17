

# Struct WaterConfigs



[**ClassList**](annotated.md) **>** [**WaterConfigs**](structWaterConfigs.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  ColorVariant | [**classified\_overlay\_color**](#variable-classified_overlay_color)   = `ColorVariant([**CMYKColor**](classCMYKColor.md)(100, 0, 0, 0))`<br> |
|  std::map&lt; std::string, [**WaterConfig**](structWaterConfig.md) &gt; | [**configs**](#variable-configs)  <br> |
|  double | [**sink\_depth\_m**](#variable-sink_depth_m)   = `10.0`<br> |
|  double | [**sink\_min\_area\_m2**](#variable-sink_min_area_m2)   = `5000.0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  const [**WaterConfig**](structWaterConfig.md) & | [**config\_from\_catchment**](#function-config_from_catchment) (double catchment) const<br> |
|  double | [**minimum\_catchment**](#function-minimum_catchment) () const<br> |




























## Public Attributes Documentation




### variable classified\_overlay\_color 

```C++
ColorVariant WaterConfigs::classified_overlay_color;
```




<hr>



### variable configs 

```C++
std::map<std::string, WaterConfig> WaterConfigs::configs;
```




<hr>



### variable sink\_depth\_m 

```C++
double WaterConfigs::sink_depth_m;
```




<hr>



### variable sink\_min\_area\_m2 

```C++
double WaterConfigs::sink_min_area_m2;
```




<hr>
## Public Functions Documentation




### function config\_from\_catchment 

```C++
inline const WaterConfig & WaterConfigs::config_from_catchment (
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

