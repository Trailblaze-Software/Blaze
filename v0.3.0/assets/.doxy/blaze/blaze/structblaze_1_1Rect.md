

# Struct blaze::Rect



[**ClassList**](annotated.md) **>** [**blaze**](namespaceblaze.md) **>** [**Rect**](structblaze_1_1Rect.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**height**](#variable-height)  <br> |
|  int | [**width**](#variable-width)  <br> |
|  int | [**x**](#variable-x)  <br> |
|  int | [**y**](#variable-y)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Rect**](#function-rect-12) () <br> |
|   | [**Rect**](#function-rect-22) (int x\_, int y\_, int w, int h) <br> |
|  int | [**bottom**](#function-bottom) () const<br> |
|  bool | [**contains**](#function-contains) (int px, int py) const<br> |
|  [**Rect**](structblaze_1_1Rect.md) | [**operator&**](#function-operator) (const [**Rect**](structblaze_1_1Rect.md) & other) const<br> |
|  int | [**right**](#function-right) () const<br> |




























## Public Attributes Documentation




### variable height 

```C++
int blaze::Rect::height;
```




<hr>



### variable width 

```C++
int blaze::Rect::width;
```




<hr>



### variable x 

```C++
int blaze::Rect::x;
```




<hr>



### variable y 

```C++
int blaze::Rect::y;
```




<hr>
## Public Functions Documentation




### function Rect [1/2]

```C++
inline blaze::Rect::Rect () 
```




<hr>



### function Rect [2/2]

```C++
inline blaze::Rect::Rect (
    int x_,
    int y_,
    int w,
    int h
) 
```




<hr>



### function bottom 

```C++
inline int blaze::Rect::bottom () const
```




<hr>



### function contains 

```C++
inline bool blaze::Rect::contains (
    int px,
    int py
) const
```




<hr>



### function operator& 

```C++
inline Rect blaze::Rect::operator& (
    const Rect & other
) const
```




<hr>



### function right 

```C++
inline int blaze::Rect::right () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/image.hpp`

