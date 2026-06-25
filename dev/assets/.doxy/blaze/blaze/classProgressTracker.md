

# Class ProgressTracker



[**ClassList**](annotated.md) **>** [**ProgressTracker**](classProgressTracker.md)








Inherits the following classes: [ProgressObserver](classProgressObserver.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProgressTracker**](#function-progresstracker-13) ([**ProgressObserver**](classProgressObserver.md) \* observer=nullptr) <br> |
|   | [**ProgressTracker**](#function-progresstracker-23) (const [**ProgressTracker**](classProgressTracker.md) & other) = delete<br> |
|   | [**ProgressTracker**](#function-progresstracker-33) ([**ProgressTracker**](classProgressTracker.md) && other) <br> |
|  bool | [**is\_visible**](#function-is_visible) () const<br> |
|  [**ProgressTracker**](classProgressTracker.md) & | [**operator=**](#function-operator) (const [**ProgressTracker**](classProgressTracker.md) & other) = delete<br> |
|  [**ProgressTracker**](classProgressTracker.md) & | [**operator=**](#function-operator_1) ([**ProgressTracker**](classProgressTracker.md) && other) = delete<br> |
|  double | [**proportion**](#function-proportion) () const<br> |
|  void | [**report\_parallel\_progress**](#function-report_parallel_progress) (double proportion) <br> |
|  void | [**set\_proportion**](#function-set_proportion) (double proportion) <br> |
|  void | [**set\_visible**](#function-set_visible) (bool v) <br> |
|  [**ProgressTracker**](classProgressTracker.md) | [**subtracker**](#function-subtracker) (double start, double end, std::optional&lt; bool &gt; visible=std::nullopt) <br> |
| virtual void | [**text\_update**](#function-text_update) (const std::string & text, int depth=0) override<br> |
| virtual  | [**~ProgressTracker**](#function-progresstracker) () <br> |


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


## Protected Functions inherited from ProgressObserver

See [ProgressObserver](classProgressObserver.md)

| Type | Name |
| ---: | :--- |
|   | [**ProgressObserver**](classProgressObserver.md#function-progressobserver) () <br> |
| virtual void | [**text\_update**](classProgressObserver.md#function-text_update) (const std::string & text, int depth=0) = 0<br> |
| virtual void | [**update\_progress**](classProgressObserver.md#function-update_progress) (double progress) = 0<br> |






## Public Functions Documentation




### function ProgressTracker [1/3]

```C++
explicit ProgressTracker::ProgressTracker (
    ProgressObserver * observer=nullptr
) 
```




<hr>



### function ProgressTracker [2/3]

```C++
ProgressTracker::ProgressTracker (
    const ProgressTracker & other
) = delete
```




<hr>



### function ProgressTracker [3/3]

```C++
ProgressTracker::ProgressTracker (
    ProgressTracker && other
) 
```




<hr>



### function is\_visible 

```C++
inline bool ProgressTracker::is_visible () const
```




<hr>



### function operator= 

```C++
ProgressTracker & ProgressTracker::operator= (
    const ProgressTracker & other
) = delete
```




<hr>



### function operator= 

```C++
ProgressTracker & ProgressTracker::operator= (
    ProgressTracker && other
) = delete
```




<hr>



### function proportion 

```C++
inline double ProgressTracker::proportion () const
```




<hr>



### function report\_parallel\_progress 

```C++
void ProgressTracker::report_parallel_progress (
    double proportion
) 
```




<hr>



### function set\_proportion 

```C++
void ProgressTracker::set_proportion (
    double proportion
) 
```




<hr>



### function set\_visible 

```C++
inline void ProgressTracker::set_visible (
    bool v
) 
```




<hr>



### function subtracker 

```C++
ProgressTracker ProgressTracker::subtracker (
    double start,
    double end,
    std::optional< bool > visible=std::nullopt
) 
```




<hr>



### function text\_update 

```C++
virtual void ProgressTracker::text_update (
    const std::string & text,
    int depth=0
) override
```



Implements [*ProgressObserver::text\_update*](classProgressObserver.md#function-text_update)


<hr>



### function ~ProgressTracker 

```C++
virtual ProgressTracker::~ProgressTracker () 
```




<hr>
## Protected Functions Documentation




### function update\_progress 

```C++
virtual void ProgressTracker::update_progress (
    double progress
) override
```



Implements [*ProgressObserver::update\_progress*](classProgressObserver.md#function-update_progress)


<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/progress_tracker.hpp`

