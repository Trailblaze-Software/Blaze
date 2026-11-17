

# Class RecordingProgressBar



[**ClassList**](annotated.md) **>** [**RecordingProgressBar**](classRecordingProgressBar.md)








Inherits the following classes: [ProgressBar](classProgressBar.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|  const std::vector&lt; double &gt; & | [**updates**](#function-updates) () const<br> |


## Public Functions inherited from ProgressBar

See [ProgressBar](classProgressBar.md)

| Type | Name |
| ---: | :--- |
|   | [**~ProgressBar**](classProgressBar.md#function-progressbar) () override<br> |


## Public Functions inherited from ProgressObserver

See [ProgressObserver](classProgressObserver.md)

| Type | Name |
| ---: | :--- |
|  [**ProgressTracker**](classProgressTracker.md) \* | [**child**](classProgressObserver.md#function-child) () <br> |
| virtual  | [**~ProgressObserver**](classProgressObserver.md#function-progressobserver) () <br> |




































































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**update\_progress**](#function-update_progress) (double progress) override<br> |


## Protected Functions inherited from ProgressBar

See [ProgressBar](classProgressBar.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**text\_update**](classProgressBar.md#function-text_update) (const std::string & text, int depth=0) override<br> |
| virtual void | [**update\_progress**](classProgressBar.md#function-update_progress) (double progress) override<br> |


## Protected Functions inherited from ProgressObserver

See [ProgressObserver](classProgressObserver.md)

| Type | Name |
| ---: | :--- |
|   | [**ProgressObserver**](classProgressObserver.md#function-progressobserver) () <br> |
| virtual void | [**text\_update**](classProgressObserver.md#function-text_update) (const std::string & text, int depth=0) = 0<br> |
| virtual void | [**update\_progress**](classProgressObserver.md#function-update_progress) (double progress) = 0<br> |








## Public Functions Documentation




### function updates 

```C++
inline const std::vector< double > & RecordingProgressBar::updates () const
```




<hr>
## Protected Functions Documentation




### function update\_progress 

```C++
inline virtual void RecordingProgressBar::update_progress (
    double progress
) override
```



Implements [*ProgressBar::update\_progress*](classProgressBar.md#function-update_progress)


<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/tests/test_progress_tracker.cpp`

