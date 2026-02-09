

# Class Layer



[**ClassList**](annotated.md) **>** [**Layer**](classLayer.md)








Inherits the following classes: QObject


Inherited by the following classes: [PointLayer](classPointLayer.md)




























## Public Signals

| Type | Name |
| ---: | :--- |
| signal [**void**](classCoordinate2D.md) | [**data\_updated**](classLayer.md#signal-data_updated)  <br> |




## Public Functions

| Type | Name |
| ---: | :--- |
| virtual [**Extent3D**](structExtent3D.md) | [**extent**](#function-extent) () const = 0<br> |
| virtual std::string | [**name**](#function-name) () <br> |
| virtual std::string | [**projection**](#function-projection) () const = 0<br> |
| virtual  | [**~Layer**](#function-layer) () = default<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::string | [**m\_name**](#variable-m_name)  <br> |




















## Public Signals Documentation




### signal data\_updated 

```C++
void Layer::data_updated;
```




<hr>
## Public Functions Documentation




### function extent 

```C++
virtual Extent3D Layer::extent () const = 0
```




<hr>



### function name 

```C++
inline virtual std::string Layer::name () 
```




<hr>



### function projection 

```C++
virtual std::string Layer::projection () const = 0
```




<hr>



### function ~Layer 

```C++
virtual Layer::~Layer () = default
```




<hr>
## Protected Attributes Documentation




### variable m\_name 

```C++
std::string Layer::m_name;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer.hpp`

