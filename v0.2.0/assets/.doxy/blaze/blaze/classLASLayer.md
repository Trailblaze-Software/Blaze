

# Class LASLayer



[**ClassList**](annotated.md) **>** [**LASLayer**](classLASLayer.md)








Inherits the following classes: [PointLayer](classPointLayer.md)


































































## Public Signals inherited from Layer

See [Layer](classLayer.md)

| Type | Name |
| ---: | :--- |
| signal [**void**](classCoordinate2D.md) | [**data\_updated**](classLayer.md#signal-data_updated)  <br> |








## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LASLayer**](#function-laslayer) ([**const**](classCoordinate2D.md) fs::path & file, [**AsyncProgressTracker**](classAsyncProgressTracker.md) progress\_tracker) <br> |
| virtual [**Extent3D**](structExtent3D.md) | [**extent**](#function-extent) () override const<br> |
|  [**const**](classCoordinate2D.md) [**AsyncLASData**](classAsyncLASData.md) & | [**las\_file**](#function-las_file-12) () const<br> |
|  [**AsyncLASData**](classAsyncLASData.md) & | [**las\_file**](#function-las_file-22) () <br> |
| virtual std::string | [**projection**](#function-projection) () override const<br> |


## Public Functions inherited from PointLayer

See [PointLayer](classPointLayer.md)

| Type | Name |
| ---: | :--- |
| virtual  | [**~PointLayer**](classPointLayer.md#function-pointlayer) () = default<br> |


## Public Functions inherited from Layer

See [Layer](classLayer.md)

| Type | Name |
| ---: | :--- |
| virtual [**Extent3D**](structExtent3D.md) | [**extent**](classLayer.md#function-extent) () const = 0<br> |
| virtual std::string | [**name**](classLayer.md#function-name) () <br> |
| virtual std::string | [**projection**](classLayer.md#function-projection) () const = 0<br> |
| virtual  | [**~Layer**](classLayer.md#function-layer) () = default<br> |
























## Protected Attributes inherited from Layer

See [Layer](classLayer.md)

| Type | Name |
| ---: | :--- |
|  std::string | [**m\_name**](classLayer.md#variable-m_name)  <br> |
























































## Public Functions Documentation




### function LASLayer 

```C++
inline explicit LASLayer::LASLayer (
    const fs::path & file,
    AsyncProgressTracker progress_tracker
) 
```




<hr>



### function extent 

```C++
inline virtual Extent3D LASLayer::extent () override const
```



Implements [*Layer::extent*](classLayer.md#function-extent)


<hr>



### function las\_file [1/2]

```C++
inline const  AsyncLASData & LASLayer::las_file () const
```




<hr>



### function las\_file [2/2]

```C++
inline AsyncLASData & LASLayer::las_file () 
```




<hr>



### function projection 

```C++
inline virtual std::string LASLayer::projection () override const
```



Implements [*Layer::projection*](classLayer.md#function-projection)


<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/layer.hpp`

