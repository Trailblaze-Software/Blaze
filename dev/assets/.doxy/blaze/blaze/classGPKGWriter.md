

# Class GPKGWriter



[**ClassList**](annotated.md) **>** [**GPKGWriter**](classGPKGWriter.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GPKGWriter**](#function-gpkgwriter-12) ([**const**](classCoordinate2D.md) std::string & filename, [**const**](classCoordinate2D.md) std::string & projection, [**const**](classCoordinate2D.md) std::string & default\_layer="default") <br> |
|   | [**GPKGWriter**](#function-gpkgwriter-22) ([**const**](classCoordinate2D.md) [**GPKGWriter**](classGPKGWriter.md) &) = delete<br> |
|  [**void**](classCoordinate2D.md) | [**add\_layer**](#function-add_layer) ([**const**](classCoordinate2D.md) std::string & layer\_name, [**OGRwkbGeometryType**](classCoordinate2D.md) geom\_type=[**wkbLineString**](classCoordinate2D.md)) <br> |
|  [**GPKGWriter**](classGPKGWriter.md) & | [**operator=**](#function-operator) ([**const**](classCoordinate2D.md) [**GPKGWriter**](classGPKGWriter.md) &) = delete<br> |
|  [**void**](classCoordinate2D.md) | [**write\_polygon**](#function-write_polygon) ([**const**](classCoordinate2D.md) std::string & layer\_name, [**const**](classCoordinate2D.md) std::string & name, [**const**](classCoordinate2D.md) std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; & exterior\_ring, [**const**](classCoordinate2D.md) std::vector&lt; std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; [**double**](classCoordinate2D.md) &gt; &gt; &gt; & holes, [**const**](classCoordinate2D.md) std::map&lt; std::string, std::variant&lt; [**int**](classCoordinate2D.md), [**double**](classCoordinate2D.md), std::string &gt; &gt; & data\_fields={}) <br> |
|  [**void**](classCoordinate2D.md) | [**write\_polyline**](#function-write_polyline) ([**const**](classCoordinate2D.md) [**Polyline**](classPolyline.md) & polyline, [**const**](classCoordinate2D.md) std::map&lt; std::string, std::variant&lt; [**int**](classCoordinate2D.md), [**double**](classCoordinate2D.md), std::string &gt; &gt; & data\_fields={}) <br> |
|   | [**~GPKGWriter**](#function-gpkgwriter) () <br> |




























## Public Functions Documentation




### function GPKGWriter [1/2]

```C++
inline GPKGWriter::GPKGWriter (
    const std::string & filename,
    const std::string & projection,
    const std::string & default_layer="default"
) 
```




<hr>



### function GPKGWriter [2/2]

```C++
GPKGWriter::GPKGWriter (
    const  GPKGWriter &
) = delete
```




<hr>



### function add\_layer 

```C++
inline void GPKGWriter::add_layer (
    const std::string & layer_name,
    OGRwkbGeometryType geom_type=wkbLineString
) 
```




<hr>



### function operator= 

```C++
GPKGWriter & GPKGWriter::operator= (
    const  GPKGWriter &
) = delete
```




<hr>



### function write\_polygon 

```C++
inline void GPKGWriter::write_polygon (
    const std::string & layer_name,
    const std::string & name,
    const std::vector< Coordinate2D < double > > & exterior_ring,
    const std::vector< std::vector< Coordinate2D < double > > > & holes,
    const std::map< std::string, std::variant< int , double , std::string > > & data_fields={}
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



### function ~GPKGWriter 

```C++
inline GPKGWriter::~GPKGWriter () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/io/gpkg.hpp`

