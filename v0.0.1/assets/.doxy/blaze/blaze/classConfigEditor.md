

# Class ConfigEditor



[**ClassList**](annotated.md) **>** [**ConfigEditor**](classConfigEditor.md)








Inherits the following classes: QWidget






















## Public Slots

| Type | Name |
| ---: | :--- |
| slot [**void**](classCoordinate2D.md) | [**add\_las\_file**](classConfigEditor.md#slot-add_las_file)  <br> |
| slot [**void**](classCoordinate2D.md) | [**add\_las\_folder**](classConfigEditor.md#slot-add_las_folder)  <br> |
| slot [**void**](classCoordinate2D.md) | [**open\_config\_file**](classConfigEditor.md#slot-open_config_file)  <br> |
| slot [**void**](classCoordinate2D.md) | [**remove\_las\_file**](classConfigEditor.md#slot-remove_las_file)  <br> |
| slot [**void**](classCoordinate2D.md) | [**save\_config\_file**](classConfigEditor.md#slot-save_config_file)  <br> |








## Public Signals

| Type | Name |
| ---: | :--- |
| signal [**void**](classCoordinate2D.md) | [**config\_changed**](classConfigEditor.md#signal-config_changed)  <br> |




## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ConfigEditor**](#function-configeditor) (QWidget \* parent=[**nullptr**](classCoordinate2D.md)) <br> |
|  [**const**](classCoordinate2D.md) [**Config**](structConfig.md) & | [**get\_config**](#function-get_config) () <br> |
|  [**bool**](classCoordinate2D.md) | [**is\_valid**](#function-is_valid) () const<br> |
|   | [**~ConfigEditor**](#function-configeditor) () <br> |




























## Public Slots Documentation




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



### slot open\_config\_file 

```C++
void ConfigEditor::open_config_file;
```




<hr>



### slot remove\_las\_file 

```C++
void ConfigEditor::remove_las_file;
```




<hr>



### slot save\_config\_file 

```C++
void ConfigEditor::save_config_file;
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
inline const  Config & ConfigEditor::get_config () 
```




<hr>



### function is\_valid 

```C++
bool ConfigEditor::is_valid () const
```




<hr>



### function ~ConfigEditor 

```C++
ConfigEditor::~ConfigEditor () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/config_editor.hpp`

