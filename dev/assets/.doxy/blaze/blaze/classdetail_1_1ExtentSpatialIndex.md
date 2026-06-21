

# Class detail::ExtentSpatialIndex



[**ClassList**](annotated.md) **>** [**detail**](namespacedetail.md) **>** [**ExtentSpatialIndex**](classdetail_1_1ExtentSpatialIndex.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ExtentSpatialIndex**](#function-extentspatialindex) ([**double**](classCoordinate2D.md) cell\_size) <br> |
|  [**void**](classCoordinate2D.md) | [**insert**](#function-insert) ([**size\_t**](classCoordinate2D.md) index, [**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & ext) <br> |
|  [**void**](classCoordinate2D.md) | [**query**](#function-query) ([**const**](classCoordinate2D.md) [**Extent2D**](structExtent2D.md) & ext, std::vector&lt; [**size\_t**](classCoordinate2D.md) &gt; & out) const<br> |




























## Public Functions Documentation




### function ExtentSpatialIndex 

```C++
inline explicit detail::ExtentSpatialIndex::ExtentSpatialIndex (
    double cell_size
) 
```




<hr>



### function insert 

```C++
inline void detail::ExtentSpatialIndex::insert (
    size_t index,
    const  Extent2D & ext
) 
```




<hr>



### function query 

```C++
inline void detail::ExtentSpatialIndex::query (
    const  Extent2D & ext,
    std::vector< size_t > & out
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/geometry/polygon_subtract.hpp`

