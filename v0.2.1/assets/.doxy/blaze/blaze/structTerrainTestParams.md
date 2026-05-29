

# Struct TerrainTestParams



[**ClassList**](annotated.md) **>** [**TerrainTestParams**](structTerrainTestParams.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**bool**](classCoordinate2D.md) | [**expect\_contours**](#variable-expect_contours)  <br> |
|  std::function&lt; [**double**](classCoordinate2D.md)([**double**](classCoordinate2D.md), [**double**](classCoordinate2D.md))&gt; | [**height\_function**](#variable-height_function)  <br> |
|  std::string | [**name**](#variable-name)  <br> |
|  [**bool**](classCoordinate2D.md) | [**with\_vegetation**](#variable-with_vegetation)  <br> |












































## Public Attributes Documentation




### variable expect\_contours 

```C++
bool TerrainTestParams::expect_contours;
```




<hr>



### variable height\_function 

```C++
std::function<double(double, double)> TerrainTestParams::height_function;
```




<hr>



### variable name 

```C++
std::string TerrainTestParams::name;
```




<hr>



### variable with\_vegetation 

```C++
bool TerrainTestParams::with_vegetation;
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & TerrainTestParams::operator<< (
    std::ostream & os,
    const  TerrainTestParams & params
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/tests/test_e2e.cpp`

