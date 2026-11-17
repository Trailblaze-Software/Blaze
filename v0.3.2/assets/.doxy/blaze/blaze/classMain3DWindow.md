

# Class Main3DWindow



[**ClassList**](annotated.md) **>** [**Main3DWindow**](classMain3DWindow.md)








Inherits the following classes: QMainWindow


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Main3DWindow**](#function-main3dwindow) () <br> |
|  void | [**add\_layer**](#function-add_layer) (std::unique\_ptr&lt; [**Layer**](classLayer.md) &gt; layer, bool auto\_zoom=true) <br> |
|  [**AsyncProgressTracker**](classAsyncProgressTracker.md) | [**add\_progress\_tracker**](#function-add_progress_tracker) () <br> |
|  void | [**import\_blaze\_output\_from\_path**](#function-import_blaze_output_from_path) (const std::string & directory) <br> |
|  const std::string & | [**scene\_reference\_crs**](#function-scene_reference_crs) () const<br> |
|  void | [**set\_bench\_mode**](#function-set_bench_mode) (bool bench) <br> |
|  void | [**set\_defer\_render\_until\_loaded**](#function-set_defer_render_until_loaded) (bool defer) <br> |
|  void | [**set\_exit\_after\_load**](#function-set_exit_after_load) (bool exit\_after\_load) <br> |
|  void | [**set\_exit\_after\_render**](#function-set_exit_after_render) (bool exit\_after\_render) <br> |
|   | [**~Main3DWindow**](#function-main3dwindow) () override<br> |




























## Public Functions Documentation




### function Main3DWindow 

```C++
Main3DWindow::Main3DWindow () 
```




<hr>



### function add\_layer 

```C++
void Main3DWindow::add_layer (
    std::unique_ptr< Layer > layer,
    bool auto_zoom=true
) 
```




<hr>



### function add\_progress\_tracker 

```C++
AsyncProgressTracker Main3DWindow::add_progress_tracker () 
```




<hr>



### function import\_blaze\_output\_from\_path 

```C++
void Main3DWindow::import_blaze_output_from_path (
    const std::string & directory
) 
```




<hr>



### function scene\_reference\_crs 

```C++
inline const std::string & Main3DWindow::scene_reference_crs () const
```




<hr>



### function set\_bench\_mode 

```C++
inline void Main3DWindow::set_bench_mode (
    bool bench
) 
```




<hr>



### function set\_defer\_render\_until\_loaded 

```C++
void Main3DWindow::set_defer_render_until_loaded (
    bool defer
) 
```




<hr>



### function set\_exit\_after\_load 

```C++
void Main3DWindow::set_exit_after_load (
    bool exit_after_load
) 
```




<hr>



### function set\_exit\_after\_render 

```C++
inline void Main3DWindow::set_exit_after_render (
    bool exit_after_render
) 
```




<hr>



### function ~Main3DWindow 

```C++
Main3DWindow::~Main3DWindow () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/main_3d_window.hpp`

