

# Class CMYKColor



[**ClassList**](annotated.md) **>** [**CMYKColor**](classCMYKColor.md)








Inherits the following classes: [Color](classColor.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CMYKColor**](#function-cmykcolor-12) ([**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) c, [**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) m, [**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) y, [**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) k) <br> |
|   | [**CMYKColor**](#function-cmykcolor-22) () <br> |
|  [**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) | [**getBlack**](#function-getblack) () const<br> |
|  [**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) | [**getCyan**](#function-getcyan) () const<br> |
|  [**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) | [**getMagenta**](#function-getmagenta) () const<br> |
|  [**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) | [**getYellow**](#function-getyellow) () const<br> |
|  [**CMYKColor**](classCMYKColor.md) | [**operator\***](#function-operator) ([**double**](classCoordinate2D.md) factor) const<br> |
|  [**CMYKColor**](classCMYKColor.md) | [**operator+**](#function-operator_1) ([**const**](classCoordinate2D.md) [**CMYKColor**](classCMYKColor.md) & other) const<br> |
|  [**unsigned**](classCoordinate2D.md) [**char**](classCoordinate2D.md) | [**operator[]**](#function-operator_2) ([**int**](classCoordinate2D.md) index) const<br> |
| virtual [**CMYKColor**](classCMYKColor.md) | [**toCMYK**](#function-tocmyk) () override const<br> |
| virtual [**RGBColor**](classRGBColor.md) | [**toRGB**](#function-torgb) () override const<br> |


## Public Functions inherited from Color

See [Color](classColor.md)

| Type | Name |
| ---: | :--- |
|   | [**Color**](classColor.md#function-color-12) ([**const**](classCoordinate2D.md) [**Color**](classColor.md) &) = default<br> |
|   | [**Color**](classColor.md#function-color-22) () = default<br> |
|  [**Color**](classColor.md) & | [**operator=**](classColor.md#function-operator) ([**const**](classCoordinate2D.md) [**Color**](classColor.md) &) = default<br> |
| virtual [**CMYKColor**](classCMYKColor.md) | [**toCMYK**](classColor.md#function-tocmyk) () const = 0<br> |
| virtual [**RGBColor**](classRGBColor.md) | [**toRGB**](classColor.md#function-torgb) () const = 0<br> |
| virtual  | [**~Color**](classColor.md#function-color) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**CMYKColor**](classCMYKColor.md) | [**FromRGB**](#function-fromrgb) ([**const**](classCoordinate2D.md) [**RGBColor**](classRGBColor.md) & rgb) <br> |




















































## Public Functions Documentation




### function CMYKColor [1/2]

```C++
CMYKColor::CMYKColor (
    unsigned  char c,
    unsigned  char m,
    unsigned  char y,
    unsigned  char k
) 
```




<hr>



### function CMYKColor [2/2]

```C++
inline CMYKColor::CMYKColor () 
```




<hr>



### function getBlack 

```C++
inline unsigned  char CMYKColor::getBlack () const
```




<hr>



### function getCyan 

```C++
inline unsigned  char CMYKColor::getCyan () const
```




<hr>



### function getMagenta 

```C++
inline unsigned  char CMYKColor::getMagenta () const
```




<hr>



### function getYellow 

```C++
inline unsigned  char CMYKColor::getYellow () const
```




<hr>



### function operator\* 

```C++
inline CMYKColor CMYKColor::operator* (
    double factor
) const
```




<hr>



### function operator+ 

```C++
inline CMYKColor CMYKColor::operator+ (
    const  CMYKColor & other
) const
```




<hr>



### function operator[] 

```C++
inline unsigned  char CMYKColor::operator[] (
    int index
) const
```




<hr>



### function toCMYK 

```C++
inline virtual CMYKColor CMYKColor::toCMYK () override const
```



Implements [*Color::toCMYK*](classColor.md#function-tocmyk)


<hr>



### function toRGB 

```C++
inline virtual RGBColor CMYKColor::toRGB () override const
```



Implements [*Color::toRGB*](classColor.md#function-torgb)


<hr>
## Public Static Functions Documentation




### function FromRGB 

```C++
static CMYKColor CMYKColor::FromRGB (
    const  RGBColor & rgb
) 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & CMYKColor::operator<< (
    std::ostream & os,
    const  CMYKColor & c
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/isom/colors.hpp`

