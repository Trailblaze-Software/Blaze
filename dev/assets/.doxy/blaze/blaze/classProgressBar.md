

# Class ProgressBar



[**ClassList**](annotated.md) **>** [**ProgressBar**](classProgressBar.md)








Inherits the following classes: [ProgressObserver](classProgressObserver.md)
























































## Public Functions inherited from ProgressObserver

See [ProgressObserver](classProgressObserver.md)

| Type | Name |
| ---: | :--- |
|  [**ProgressTracker**](classProgressTracker.md) \* | [**child**](classProgressObserver.md#function-child) () <br> |
| virtual  | [**~ProgressObserver**](classProgressObserver.md#function-progressobserver) () <br> |














































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual [**void**](classCoordinate2D.md) | [**text\_update**](#function-text_update) ([**const**](classCoordinate2D.md) std::string & text, [**int**](classCoordinate2D.md) depth=0) override<br> |
| virtual [**void**](classCoordinate2D.md) | [**update\_progress**](#function-update_progress) ([**double**](classCoordinate2D.md) progress) override<br> |


## Protected Functions inherited from ProgressObserver

See [ProgressObserver](classProgressObserver.md)

| Type | Name |
| ---: | :--- |
|   | [**ProgressObserver**](classProgressObserver.md#function-progressobserver) () <br> |
| virtual [**void**](classCoordinate2D.md) | [**text\_update**](classProgressObserver.md#function-text_update) ([**const**](classCoordinate2D.md) std::string & text, [**int**](classCoordinate2D.md) depth=0) = 0<br> |
| virtual [**void**](classCoordinate2D.md) | [**update\_progress**](classProgressObserver.md#function-update_progress) ([**double**](classCoordinate2D.md) progress) = 0<br> |






## Protected Functions Documentation




### function text\_update 

```C++
virtual void ProgressBar::text_update (
    const std::string & text,
    int depth=0
) override
```



Implements [*ProgressObserver::text\_update*](classProgressObserver.md#function-text_update)


<hr>



### function update\_progress 

```C++
virtual void ProgressBar::update_progress (
    double progress
) override
```



Implements [*ProgressObserver::update\_progress*](classProgressObserver.md#function-update_progress)


<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/progress_tracker.hpp`

