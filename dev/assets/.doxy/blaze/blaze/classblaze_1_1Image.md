

# Class blaze::Image



[**ClassList**](annotated.md) **>** [**blaze**](namespaceblaze.md) **>** [**Image**](classblaze_1_1Image.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Image**](#function-image-14) () <br> |
|   | [**Image**](#function-image-24) (int width, int height) <br> |
|   | [**Image**](#function-image-34) (const [**Image**](classblaze_1_1Image.md) & other) <br> |
|   | [**Image**](#function-image-44) ([**Image**](classblaze_1_1Image.md) && other) noexcept<br> |
|  [**RGBColor**](classRGBColor.md) | [**at**](#function-at) (int row, int col) const<br> |
|  int | [**channels**](#function-channels) () const<br> |
|  int | [**cols**](#function-cols) () const<br> |
|  void | [**convert\_to**](#function-convert_to) ([**Image**](classblaze_1_1Image.md) & dst, double alpha=1.0, double beta=0.0) const<br> |
|  void | [**copy\_to**](#function-copy_to) ([**Image**](classblaze_1_1Image.md) & dst) const<br> |
|  uint8\_t \* | [**data**](#function-data-12) () <br> |
|  const uint8\_t \* | [**data**](#function-data-22) () const<br> |
|  void | [**draw\_circle**](#function-draw_circle) (const [**Point**](structblaze_1_1Point.md) & center, int radius, const [**RGBColor**](classRGBColor.md) & color, int thickness=-1) <br> |
|  void | [**draw\_polyline**](#function-draw_polyline) (const [**Point**](structblaze_1_1Point.md) \* points, int num\_points, bool closed, const [**RGBColor**](classRGBColor.md) & color, int thickness=1) <br> |
|  void | [**extract\_channel**](#function-extract_channel) ([**Image**](classblaze_1_1Image.md) & dst, int channel\_index) const<br> |
|  int | [**height**](#function-height) () const<br> |
|  [**Image**](classblaze_1_1Image.md) & | [**operator=**](#function-operator) (const [**Image**](classblaze_1_1Image.md) & other) <br> |
|  [**Image**](classblaze_1_1Image.md) & | [**operator=**](#function-operator_1) ([**Image**](classblaze_1_1Image.md) && other) noexcept<br> |
|  void | [**resize**](#function-resize) ([**Image**](classblaze_1_1Image.md) & dst, const [**Size**](structblaze_1_1Size.md) & size, InterpolationMode mode=InterpolationMode::NEAREST) const<br> |
|  uint8\_t \* | [**row\_ptr**](#function-row_ptr-12) (int row) <br> |
|  const uint8\_t \* | [**row\_ptr**](#function-row_ptr-22) (int row) const<br> |
|  int | [**rows**](#function-rows) () const<br> |
|  void | [**set**](#function-set) (int row, int col, const [**RGBColor**](classRGBColor.md) & color) <br> |
|  [**Image**](classblaze_1_1Image.md) | [**slice**](#function-slice) (const [**Rect**](structblaze_1_1Rect.md) & rect) const<br> |
|  int | [**width**](#function-width) () const<br> |
|   | [**~Image**](#function-image) () <br> |




























## Public Functions Documentation




### function Image [1/4]

```C++
blaze::Image::Image () 
```




<hr>



### function Image [2/4]

```C++
blaze::Image::Image (
    int width,
    int height
) 
```




<hr>



### function Image [3/4]

```C++
blaze::Image::Image (
    const Image & other
) 
```




<hr>



### function Image [4/4]

```C++
blaze::Image::Image (
    Image && other
) noexcept
```




<hr>



### function at 

```C++
RGBColor blaze::Image::at (
    int row,
    int col
) const
```




<hr>



### function channels 

```C++
inline int blaze::Image::channels () const
```




<hr>



### function cols 

```C++
inline int blaze::Image::cols () const
```




<hr>



### function convert\_to 

```C++
void blaze::Image::convert_to (
    Image & dst,
    double alpha=1.0,
    double beta=0.0
) const
```




<hr>



### function copy\_to 

```C++
void blaze::Image::copy_to (
    Image & dst
) const
```




<hr>



### function data [1/2]

```C++
inline uint8_t * blaze::Image::data () 
```




<hr>



### function data [2/2]

```C++
inline const uint8_t * blaze::Image::data () const
```




<hr>



### function draw\_circle 

```C++
void blaze::Image::draw_circle (
    const Point & center,
    int radius,
    const RGBColor & color,
    int thickness=-1
) 
```




<hr>



### function draw\_polyline 

```C++
void blaze::Image::draw_polyline (
    const Point * points,
    int num_points,
    bool closed,
    const RGBColor & color,
    int thickness=1
) 
```




<hr>



### function extract\_channel 

```C++
void blaze::Image::extract_channel (
    Image & dst,
    int channel_index
) const
```




<hr>



### function height 

```C++
inline int blaze::Image::height () const
```




<hr>



### function operator= 

```C++
Image & blaze::Image::operator= (
    const Image & other
) 
```




<hr>



### function operator= 

```C++
Image & blaze::Image::operator= (
    Image && other
) noexcept
```




<hr>



### function resize 

```C++
void blaze::Image::resize (
    Image & dst,
    const Size & size,
    InterpolationMode mode=InterpolationMode::NEAREST
) const
```




<hr>



### function row\_ptr [1/2]

```C++
inline uint8_t * blaze::Image::row_ptr (
    int row
) 
```




<hr>



### function row\_ptr [2/2]

```C++
inline const uint8_t * blaze::Image::row_ptr (
    int row
) const
```




<hr>



### function rows 

```C++
inline int blaze::Image::rows () const
```




<hr>



### function set 

```C++
void blaze::Image::set (
    int row,
    int col,
    const RGBColor & color
) 
```




<hr>



### function slice 

```C++
Image blaze::Image::slice (
    const Rect & rect
) const
```




<hr>



### function width 

```C++
inline int blaze::Image::width () const
```




<hr>



### function ~Image 

```C++
blaze::Image::~Image () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/grid/image.hpp`

