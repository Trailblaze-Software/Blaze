

# Class ProgressObserver



[**ClassList**](annotated.md) **>** [**ProgressObserver**](classProgressObserver.md)










Inherited by the following classes: [ProgressBar](classProgressBar.md),  [ProgressBox](classProgressBox.md),  [ProgressTracker](classProgressTracker.md),  [ProgressTrackerBar](classProgressTrackerBar.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**ProgressTracker**](classProgressTracker.md) \* | [**child**](#function-child) () <br> |
| virtual  | [**~ProgressObserver**](#function-progressobserver) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**ProgressObserver**](#function-progressobserver) () <br> |
| virtual [**void**](classCoordinate2D.md) | [**text\_update**](#function-text_update) ([**const**](classCoordinate2D.md) std::string & text, [**int**](classCoordinate2D.md) depth=0) = 0<br> |
| virtual [**void**](classCoordinate2D.md) | [**update\_progress**](#function-update_progress) ([**double**](classCoordinate2D.md) progress) = 0<br> |




## Public Functions Documentation




### function child 

```C++
inline ProgressTracker * ProgressObserver::child () 
```




<hr>



### function ~ProgressObserver 

```C++
virtual ProgressObserver::~ProgressObserver () 
```




<hr>
## Protected Functions Documentation




### function ProgressObserver 

```C++
inline ProgressObserver::ProgressObserver () 
```




<hr>



### function text\_update 

```C++
virtual void ProgressObserver::text_update (
    const std::string & text,
    int depth=0
) = 0
```




<hr>



### function update\_progress 

```C++
virtual void ProgressObserver::update_progress (
    double progress
) = 0
```




<hr>## Friends Documentation





### friend ProgressTracker 

```C++
class ProgressObserver::ProgressTracker (
    ProgressTracker
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/progress_tracker.hpp`

