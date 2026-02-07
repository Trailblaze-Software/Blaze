

# Class ProgressTrackerBar



[**ClassList**](annotated.md) **>** [**ProgressTrackerBar**](classProgressTrackerBar.md)








Inherits the following classes: QProgressBar,  [ProgressObserver](classProgressObserver.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProgressTrackerBar**](#function-progresstrackerbar) (QWidget \* parent) <br> |
| virtual [**void**](classCoordinate2D.md) | [**text\_update**](#function-text_update) ([**const**](classCoordinate2D.md) std::string & text, [**int**](classCoordinate2D.md) depth=0) override<br> |
|  [**AsyncProgressTracker**](classAsyncProgressTracker.md) | [**tracker**](#function-tracker) () <br> |
| virtual [**void**](classCoordinate2D.md) | [**update\_progress**](#function-update_progress) ([**double**](classCoordinate2D.md) progress) override<br> |


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
| virtual [**void**](classCoordinate2D.md) | [**text\_update**](classProgressObserver.md#function-text_update) ([**const**](classCoordinate2D.md) std::string & text, [**int**](classCoordinate2D.md) depth=0) = 0<br> |
| virtual [**void**](classCoordinate2D.md) | [**update\_progress**](classProgressObserver.md#function-update_progress) ([**double**](classCoordinate2D.md) progress) = 0<br> |






## Public Functions Documentation




### function ProgressTrackerBar 

```C++
inline explicit ProgressTrackerBar::ProgressTrackerBar (
    QWidget * parent
) 
```




<hr>



### function text\_update 

```C++
inline virtual void ProgressTrackerBar::text_update (
    const std::string & text,
    int depth=0
) override
```



Implements [*ProgressObserver::text\_update*](classProgressObserver.md#function-text_update)


<hr>



### function tracker 

```C++
inline AsyncProgressTracker ProgressTrackerBar::tracker () 
```




<hr>



### function update\_progress 

```C++
inline virtual void ProgressTrackerBar::update_progress (
    double progress
) override
```



Implements [*ProgressObserver::update\_progress*](classProgressObserver.md#function-update_progress)


<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/main_3d_window.hpp`

