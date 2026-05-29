

# Struct VegeHeightConfig



[**ClassList**](annotated.md) **>** [**VegeHeightConfig**](structVegeHeightConfig.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**BlockingThresholdColorPair**](structBlockingThresholdColorPair.md) &gt; | [**colors**](#variable-colors)  <br> |
|  [**double**](classCoordinate2D.md) | [**max\_height**](#variable-max_height)  <br> |
|  [**double**](classCoordinate2D.md) | [**min\_height**](#variable-min_height)  <br> |
|  std::string | [**name**](#variable-name)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::optional&lt; ColorVariant &gt; | [**pick\_from\_blocked\_proportion**](#function-pick_from_blocked_proportion) ([**double**](classCoordinate2D.md) bp) const<br> |




























## Public Attributes Documentation




### variable colors 

```C++
std::vector<BlockingThresholdColorPair> VegeHeightConfig::colors;
```




<hr>



### variable max\_height 

```C++
double VegeHeightConfig::max_height;
```




<hr>



### variable min\_height 

```C++
double VegeHeightConfig::min_height;
```




<hr>



### variable name 

```C++
std::string VegeHeightConfig::name;
```




<hr>
## Public Functions Documentation




### function pick\_from\_blocked\_proportion 

```C++
inline std::optional< ColorVariant > VegeHeightConfig::pick_from_blocked_proportion (
    double bp
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/config_input/config_input.hpp`

