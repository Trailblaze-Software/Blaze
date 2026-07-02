

# Class ConfigEditor



[**ClassList**](annotated.md) **>** [**ConfigEditor**](classConfigEditor.md)








Inherits the following classes: QWidget






















## Public Slots

| Type | Name |
| ---: | :--- |
| slot void | [**add\_color**](classConfigEditor.md#slot-add_color)  <br> |
| slot void | [**add\_contour**](classConfigEditor.md#slot-add_contour)  <br> |
| slot void | [**add\_las\_file**](classConfigEditor.md#slot-add_las_file)  <br> |
| slot void | [**add\_las\_folder**](classConfigEditor.md#slot-add_las_folder)  <br> |
| slot void | [**add\_vege**](classConfigEditor.md#slot-add_vege)  <br> |
| slot void | [**add\_vege\_color**](classConfigEditor.md#slot-add_vege_color)  <br> |
| slot void | [**add\_water**](classConfigEditor.md#slot-add_water)  <br> |
| slot void | [**handle\_color\_selected**](classConfigEditor.md#slot-handle_color_selected)  <br> |
| slot void | [**handle\_color\_type\_changed**](classConfigEditor.md#slot-handle_color_type_changed) (int index) <br> |
| slot void | [**handle\_contour\_selected**](classConfigEditor.md#slot-handle_contour_selected)  <br> |
| slot void | [**handle\_vege\_selected**](classConfigEditor.md#slot-handle_vege_selected)  <br> |
| slot void | [**handle\_water\_selected**](classConfigEditor.md#slot-handle_water_selected)  <br> |
| slot void | [**open\_config\_file**](classConfigEditor.md#slot-open_config_file)  <br> |
| slot void | [**pick\_color**](classConfigEditor.md#slot-pick_color)  <br> |
| slot void | [**remove\_color**](classConfigEditor.md#slot-remove_color)  <br> |
| slot void | [**remove\_contour**](classConfigEditor.md#slot-remove_contour)  <br> |
| slot void | [**remove\_las\_file**](classConfigEditor.md#slot-remove_las_file)  <br> |
| slot void | [**remove\_vege**](classConfigEditor.md#slot-remove_vege)  <br> |
| slot void | [**remove\_vege\_color**](classConfigEditor.md#slot-remove_vege_color)  <br> |
| slot void | [**remove\_water**](classConfigEditor.md#slot-remove_water)  <br> |
| slot void | [**reset\_to\_defaults**](classConfigEditor.md#slot-reset_to_defaults)  <br> |
| slot void | [**save\_config\_file**](classConfigEditor.md#slot-save_config_file)  <br> |
| slot void | [**set\_las\_files**](classConfigEditor.md#slot-set_las_files) (const std::vector&lt; fs::path &gt; & files) <br> |
| slot void | [**update\_color\_from\_ui**](classConfigEditor.md#slot-update_color_from_ui)  <br> |
| slot void | [**update\_contour\_from\_ui**](classConfigEditor.md#slot-update_contour_from_ui)  <br> |
| slot void | [**update\_general\_from\_ui**](classConfigEditor.md#slot-update_general_from_ui)  <br> |
| slot void | [**update\_vege\_color\_from\_ui**](classConfigEditor.md#slot-update_vege_color_from_ui) (int row, int column) <br> |
| slot void | [**update\_vege\_from\_ui**](classConfigEditor.md#slot-update_vege_from_ui)  <br> |
| slot void | [**update\_vege\_globals\_from\_ui**](classConfigEditor.md#slot-update_vege_globals_from_ui)  <br> |
| slot void | [**update\_water\_from\_ui**](classConfigEditor.md#slot-update_water_from_ui)  <br> |
| slot void | [**update\_water\_globals\_from\_ui**](classConfigEditor.md#slot-update_water_globals_from_ui)  <br> |








## Public Signals

| Type | Name |
| ---: | :--- |
| signal void | [**config\_changed**](classConfigEditor.md#signal-config_changed)  <br> |




## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ConfigEditor**](#function-configeditor) (QWidget \* parent=nullptr) <br> |
|  const [**Config**](structConfig.md) & | [**get\_config**](#function-get_config) () <br> |
|  bool | [**is\_valid**](#function-is_valid) () const<br> |
|  std::size\_t | [**last\_file\_count**](#function-last_file_count) () const<br> |
|  double | [**last\_total\_area\_m2**](#function-last_total_area_m2) () const<br> |
|  std::uint64\_t | [**last\_total\_points**](#function-last_total_points) () const<br> |
|   | [**~ConfigEditor**](#function-configeditor) () <br> |




























## Public Slots Documentation




### slot add\_color 

```C++
void ConfigEditor::add_color;
```




<hr>



### slot add\_contour 

```C++
void ConfigEditor::add_contour;
```




<hr>



### slot add\_las\_file 

```C++
void ConfigEditor::add_las_file;
```




<hr>



### slot add\_las\_folder 

```C++
void ConfigEditor::add_las_folder;
```




<hr>



### slot add\_vege 

```C++
void ConfigEditor::add_vege;
```




<hr>



### slot add\_vege\_color 

```C++
void ConfigEditor::add_vege_color;
```




<hr>



### slot add\_water 

```C++
void ConfigEditor::add_water;
```




<hr>



### slot handle\_color\_selected 

```C++
void ConfigEditor::handle_color_selected;
```




<hr>



### slot handle\_color\_type\_changed 

```C++
void ConfigEditor::handle_color_type_changed;
```




<hr>



### slot handle\_contour\_selected 

```C++
void ConfigEditor::handle_contour_selected;
```




<hr>



### slot handle\_vege\_selected 

```C++
void ConfigEditor::handle_vege_selected;
```




<hr>



### slot handle\_water\_selected 

```C++
void ConfigEditor::handle_water_selected;
```




<hr>



### slot open\_config\_file 

```C++
void ConfigEditor::open_config_file;
```




<hr>



### slot pick\_color 

```C++
void ConfigEditor::pick_color;
```




<hr>



### slot remove\_color 

```C++
void ConfigEditor::remove_color;
```




<hr>



### slot remove\_contour 

```C++
void ConfigEditor::remove_contour;
```




<hr>



### slot remove\_las\_file 

```C++
void ConfigEditor::remove_las_file;
```




<hr>



### slot remove\_vege 

```C++
void ConfigEditor::remove_vege;
```




<hr>



### slot remove\_vege\_color 

```C++
void ConfigEditor::remove_vege_color;
```




<hr>



### slot remove\_water 

```C++
void ConfigEditor::remove_water;
```




<hr>



### slot reset\_to\_defaults 

```C++
void ConfigEditor::reset_to_defaults;
```




<hr>



### slot save\_config\_file 

```C++
void ConfigEditor::save_config_file;
```




<hr>



### slot set\_las\_files 

```C++
void ConfigEditor::set_las_files;
```




<hr>



### slot update\_color\_from\_ui 

```C++
void ConfigEditor::update_color_from_ui;
```




<hr>



### slot update\_contour\_from\_ui 

```C++
void ConfigEditor::update_contour_from_ui;
```




<hr>



### slot update\_general\_from\_ui 

```C++
void ConfigEditor::update_general_from_ui;
```




<hr>



### slot update\_vege\_color\_from\_ui 

```C++
void ConfigEditor::update_vege_color_from_ui;
```




<hr>



### slot update\_vege\_from\_ui 

```C++
void ConfigEditor::update_vege_from_ui;
```




<hr>



### slot update\_vege\_globals\_from\_ui 

```C++
void ConfigEditor::update_vege_globals_from_ui;
```




<hr>



### slot update\_water\_from\_ui 

```C++
void ConfigEditor::update_water_from_ui;
```




<hr>



### slot update\_water\_globals\_from\_ui 

```C++
void ConfigEditor::update_water_globals_from_ui;
```




<hr>
## Public Signals Documentation




### signal config\_changed 

```C++
void ConfigEditor::config_changed;
```




<hr>
## Public Functions Documentation




### function ConfigEditor 

```C++
explicit ConfigEditor::ConfigEditor (
    QWidget * parent=nullptr
) 
```




<hr>



### function get\_config 

```C++
inline const Config & ConfigEditor::get_config () 
```




<hr>



### function is\_valid 

```C++
bool ConfigEditor::is_valid () const
```




<hr>



### function last\_file\_count 

```C++
inline std::size_t ConfigEditor::last_file_count () const
```




<hr>



### function last\_total\_area\_m2 

```C++
inline double ConfigEditor::last_total_area_m2 () const
```




<hr>



### function last\_total\_points 

```C++
inline std::uint64_t ConfigEditor::last_total_points () const
```




<hr>



### function ~ConfigEditor 

```C++
ConfigEditor::~ConfigEditor () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/config_editor.hpp`

