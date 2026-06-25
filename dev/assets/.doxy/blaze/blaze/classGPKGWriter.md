

# Class GPKGWriter



[**ClassList**](annotated.md) **>** [**GPKGWriter**](classGPKGWriter.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GPKGWriter**](#function-gpkgwriter-12) (const std::string & filename, const std::string & projection, const std::string & default\_layer="default") <br> |
|   | [**GPKGWriter**](#function-gpkgwriter-22) (const [**GPKGWriter**](classGPKGWriter.md) &) = delete<br> |
|  void | [**add\_layer**](#function-add_layer) (const std::string & layer\_name, OGRwkbGeometryType geom\_type=wkbLineString) <br> |
|  [**GPKGWriter**](classGPKGWriter.md) & | [**operator=**](#function-operator) (const [**GPKGWriter**](classGPKGWriter.md) &) = delete<br> |
|  void | [**write\_polygon**](#function-write_polygon) (const std::string & layer\_name, const std::string & name, const std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; & exterior\_ring, const std::vector&lt; std::vector&lt; [**Coordinate2D**](classCoordinate2D.md)&lt; double &gt; &gt; &gt; & holes, const std::map&lt; std::string, std::variant&lt; int, double, std::string &gt; &gt; & data\_fields={}) <br> |
|  void | [**write\_polyline**](#function-write_polyline) (const [**Polyline**](classPolyline.md) & polyline, const std::map&lt; std::string, std::variant&lt; int, double, std::string &gt; &gt; & data\_fields={}) <br> |
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
    const GPKGWriter &
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
    const GPKGWriter &
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
    const std::map< std::string, std::variant< int, double, std::string > > & data_fields={}
) 
```




<hr>



### function write\_polyline 

```C++
inline void GPKGWriter::write_polyline (
    const Polyline & polyline,
    const std::map< std::string, std::variant< int, double, std::string > > & data_fields={}
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

