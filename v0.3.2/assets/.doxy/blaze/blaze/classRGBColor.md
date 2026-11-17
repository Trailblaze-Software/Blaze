

# Class RGBColor



[**ClassList**](annotated.md) **>** [**RGBColor**](classRGBColor.md)








Inherits the following classes: [Color](classColor.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RGBColor**](#function-rgbcolor-12) (unsigned char r, unsigned char g, unsigned char b, unsigned char a=255) <br> |
|   | [**RGBColor**](#function-rgbcolor-22) () <br> |
|  unsigned char | [**getAlpha**](#function-getalpha) () const<br> |
|  unsigned char | [**getBlue**](#function-getblue) () const<br> |
|  unsigned char | [**getGreen**](#function-getgreen) () const<br> |
|  unsigned char | [**getRed**](#function-getred) () const<br> |
|  const unsigned char & | [**operator[]**](#function-operator) (size\_t index) const<br> |
|  unsigned char & | [**operator[]**](#function-operator_1) (size\_t index) <br> |
| virtual [**CMYKColor**](classCMYKColor.md) | [**toCMYK**](#function-tocmyk) () override const<br> |
| virtual [**RGBColor**](classRGBColor.md) | [**toRGB**](#function-torgb) () override const<br> |


## Public Functions inherited from Color

See [Color](classColor.md)

| Type | Name |
| ---: | :--- |
|   | [**Color**](classColor.md#function-color-12) (const [**Color**](classColor.md) &) = default<br> |
|   | [**Color**](classColor.md#function-color-22) () = default<br> |
|  [**Color**](classColor.md) & | [**operator=**](classColor.md#function-operator) (const [**Color**](classColor.md) &) = default<br> |
| virtual [**CMYKColor**](classCMYKColor.md) | [**toCMYK**](classColor.md#function-tocmyk) () const = 0<br> |
| virtual [**RGBColor**](classRGBColor.md) | [**toRGB**](classColor.md#function-torgb) () const = 0<br> |
| virtual  | [**~Color**](classColor.md#function-color) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**RGBColor**](classRGBColor.md) | [**FromCMYK**](#function-fromcmyk) (const [**CMYKColor**](classCMYKColor.md) & cmyk) <br> |




















































## Public Functions Documentation




### function RGBColor [1/2]

```C++
RGBColor::RGBColor (
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a=255
) 
```




<hr>



### function RGBColor [2/2]

```C++
inline RGBColor::RGBColor () 
```




<hr>



### function getAlpha 

```C++
inline unsigned char RGBColor::getAlpha () const
```




<hr>



### function getBlue 

```C++
inline unsigned char RGBColor::getBlue () const
```




<hr>



### function getGreen 

```C++
inline unsigned char RGBColor::getGreen () const
```




<hr>



### function getRed 

```C++
inline unsigned char RGBColor::getRed () const
```




<hr>



### function operator[] 

```C++
inline const unsigned char & RGBColor::operator[] (
    size_t index
) const
```




<hr>



### function operator[] 

```C++
inline unsigned char & RGBColor::operator[] (
    size_t index
) 
```




<hr>



### function toCMYK 

```C++
virtual CMYKColor RGBColor::toCMYK () override const
```



Implements [*Color::toCMYK*](classColor.md#function-tocmyk)


<hr>



### function toRGB 

```C++
inline virtual RGBColor RGBColor::toRGB () override const
```



Implements [*Color::toRGB*](classColor.md#function-torgb)


<hr>
## Public Static Functions Documentation




### function FromCMYK 

```C++
static RGBColor RGBColor::FromCMYK (
    const CMYKColor & cmyk
) 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & RGBColor::operator<< (
    std::ostream & os,
    const RGBColor & c
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/isom/colors.hpp`

