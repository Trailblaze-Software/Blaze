

# Class Direction2D



[**ClassList**](annotated.md) **>** [**Direction2D**](classDirection2D.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Dir**](#enum-dir)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Direction2D**](#function-direction2d) (Dir dir) <br> |
|  [**int**](classCoordinate2D.md) | [**dx**](#function-dx) () const<br> |
|  [**int**](classCoordinate2D.md) | [**dy**](#function-dy) () const<br> |
|   | [**operator Dir**](#function-operator-dir) () const<br> |
|  [**Direction2D**](classDirection2D.md) | [**opposite**](#function-opposite) () const<br> |
|  std::array&lt; [**Direction2D**](classDirection2D.md), 2 &gt; | [**orthogonal\_dirs**](#function-orthogonal_dirs) () const<br> |
|  [**bool**](classCoordinate2D.md) | [**orthogonal\_to**](#function-orthogonal_to) ([**Direction2D**](classDirection2D.md) other) const<br> |




























## Public Types Documentation




### enum Dir 

```C++
enum Direction2D::Dir {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UR,
    UL,
    DR,
    DL
};
```




<hr>
## Public Functions Documentation




### function Direction2D 

```C++
inline Direction2D::Direction2D (
    Dir dir
) 
```




<hr>



### function dx 

```C++
inline int Direction2D::dx () const
```




<hr>



### function dy 

```C++
inline int Direction2D::dy () const
```




<hr>



### function operator Dir 

```C++
inline Direction2D::operator Dir () const
```




<hr>



### function opposite 

```C++
inline Direction2D Direction2D::opposite () const
```




<hr>



### function orthogonal\_dirs 

```C++
inline std::array< Direction2D , 2 > Direction2D::orthogonal_dirs () const
```




<hr>



### function orthogonal\_to 

```C++
inline bool Direction2D::orthogonal_to (
    Direction2D other
) const
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & Direction2D::operator<< (
    std::ostream & os,
    const  Direction2D & dir
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/coordinate.hpp`

