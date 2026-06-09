

# Class Color



[**ClassList**](annotated.md) **>** [**Color**](classColor.md)










Inherited by the following classes: [CMYKColor](classCMYKColor.md),  [RGBColor](classRGBColor.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Color**](#function-color-12) ([**const**](classCoordinate2D.md) [**Color**](classColor.md) &) = default<br> |
|   | [**Color**](#function-color-22) () = default<br> |
|  [**Color**](classColor.md) & | [**operator=**](#function-operator) ([**const**](classCoordinate2D.md) [**Color**](classColor.md) &) = default<br> |
| virtual [**CMYKColor**](classCMYKColor.md) | [**toCMYK**](#function-tocmyk) () const = 0<br> |
| virtual [**RGBColor**](classRGBColor.md) | [**toRGB**](#function-torgb) () const = 0<br> |
| virtual  | [**~Color**](#function-color) () = default<br> |




























## Public Functions Documentation




### function Color [1/2]

```C++
Color::Color (
    const  Color &
) = default
```




<hr>



### function Color [2/2]

```C++
Color::Color () = default
```




<hr>



### function operator= 

```C++
Color & Color::operator= (
    const  Color &
) = default
```




<hr>



### function toCMYK 

```C++
virtual CMYKColor Color::toCMYK () const = 0
```




<hr>



### function toRGB 

```C++
virtual RGBColor Color::toRGB () const = 0
```




<hr>



### function ~Color 

```C++
virtual Color::~Color () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/isom/colors.hpp`

