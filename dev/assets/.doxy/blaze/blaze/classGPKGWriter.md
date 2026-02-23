

# Class GPKGWriter



[**ClassList**](annotated.md) **>** [**GPKGWriter**](classGPKGWriter.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GPKGWriter**](#function-gpkgwriter) ([**const**](classCoordinate2D.md) std::string & filename, [**const**](classCoordinate2D.md) std::string & projection, [**const**](classCoordinate2D.md) std::string & default\_layer="default") <br> |
|  [**void**](classCoordinate2D.md) | [**add\_layer**](#function-add_layer) ([**const**](classCoordinate2D.md) std::string & layer\_name) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_polyline**](#function-write_polyline) ([**const**](classCoordinate2D.md) [**Polyline**](classPolyline.md) & polyline, [**const**](classCoordinate2D.md) std::map&lt; std::string, std::variant&lt; [**int**](classCoordinate2D.md), [**double**](classCoordinate2D.md), std::string &gt; &gt; & data\_fields={}) <br> |




























## Public Functions Documentation




### function GPKGWriter 

```C++
inline GPKGWriter::GPKGWriter (
    const std::string & filename,
    const std::string & projection,
    const std::string & default_layer="default"
) 
```




<hr>



### function add\_layer 

```C++
inline void GPKGWriter::add_layer (
    const std::string & layer_name
) 
```




<hr>



### function write\_polyline 

```C++
inline void GPKGWriter::write_polyline (
    const  Polyline & polyline,
    const std::map< std::string, std::variant< int , double , std::string > > & data_fields={}
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/io/gpkg.hpp`

