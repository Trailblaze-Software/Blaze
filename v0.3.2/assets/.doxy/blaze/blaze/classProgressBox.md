

# Class ProgressBox



[**ClassList**](annotated.md) **>** [**ProgressBox**](classProgressBox.md)








Inherits the following classes: QDialog,  [ProgressObserver](classProgressObserver.md)














































## Public Signals

| Type | Name |
| ---: | :--- |
| signal void | [**send\_progress\_bars**](classProgressBox.md#signal-send_progress_bars) (std::vector&lt; std::pair&lt; double, bool &gt; &gt; bars) <br> |
| signal void | [**send\_status\_text**](classProgressBox.md#signal-send_status_text) (std::string text, int depth) <br> |








## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProgressBox**](#function-progressbox) (QWidget \* parent=nullptr) <br> |
|  void | [**start\_task**](#function-start_task) (std::function&lt; void()&gt; task, std::function&lt; void()&gt; on\_finish=[] {}, std::function&lt; void(const QString &)&gt; on\_error={}) <br> |
| virtual void | [**text\_update**](#function-text_update) (const std::string & text, int depth=0) override<br> |
| virtual void | [**update\_progress**](#function-update_progress) (double proportion) override<br> |


## Public Functions inherited from ProgressObserver

See [ProgressObserver](classProgressObserver.md)

| Type | Name |
| ---: | :--- |
|  [**ProgressTracker**](classProgressTracker.md) \* | [**child**](classProgressObserver.md#function-child) () <br> |
| virtual  | [**~ProgressObserver**](classProgressObserver.md#function-progressobserver) () <br> |
















































## Protected Functions inherited from ProgressObserver

See [ProgressObserver](classProgressObserver.md)

| Type | Name |
| ---: | :--- |
|   | [**ProgressObserver**](classProgressObserver.md#function-progressobserver) () <br> |
| virtual void | [**text\_update**](classProgressObserver.md#function-text_update) (const std::string & text, int depth=0) = 0<br> |
| virtual void | [**update\_progress**](classProgressObserver.md#function-update_progress) (double progress) = 0<br> |






## Public Signals Documentation




### signal send\_progress\_bars 

```C++
void ProgressBox::send_progress_bars;
```




<hr>



### signal send\_status\_text 

```C++
void ProgressBox::send_status_text;
```




<hr>
## Public Functions Documentation




### function ProgressBox 

```C++
explicit ProgressBox::ProgressBox (
    QWidget * parent=nullptr
) 
```




<hr>



### function start\_task 

```C++
void ProgressBox::start_task (
    std::function< void()> task,
    std::function< void()> on_finish=[] {},
    std::function< void(const QString &)> on_error={}
) 
```




<hr>



### function text\_update 

```C++
virtual void ProgressBox::text_update (
    const std::string & text,
    int depth=0
) override
```



Implements [*ProgressObserver::text\_update*](classProgressObserver.md#function-text_update)


<hr>



### function update\_progress 

```C++
virtual void ProgressBox::update_progress (
    double proportion
) override
```



Implements [*ProgressObserver::update\_progress*](classProgressObserver.md#function-update_progress)


<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/progress_box.hpp`

