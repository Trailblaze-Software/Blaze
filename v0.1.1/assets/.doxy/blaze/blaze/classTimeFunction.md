

# Class TimeFunction



[**ClassList**](annotated.md) **>** [**TimeFunction**](classTimeFunction.md)








Inherits the following classes: [Timer](classTimer.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TimeFunction**](#function-timefunction-12) ([**const**](classCoordinate2D.md) std::string & name, [**ProgressTracker**](classProgressTracker.md) \* progress\_tracker=[**nullptr**](classCoordinate2D.md)) <br> |
|   | [**TimeFunction**](#function-timefunction-22) ([**const**](classCoordinate2D.md) std::string & name, std::optional&lt; [**ProgressTracker**](classProgressTracker.md) &gt; & progress\_tracker) <br> |
|   | [**~TimeFunction**](#function-timefunction) () <br> |


## Public Functions inherited from Timer

See [Timer](classTimer.md)

| Type | Name |
| ---: | :--- |
|   | [**Timer**](classTimer.md#function-timer) () <br> |
|  std::chrono::duration&lt; [**double**](classCoordinate2D.md) &gt; | [**duration**](classTimer.md#function-duration) () const<br> |






















































## Public Functions Documentation




### function TimeFunction [1/2]

```C++
inline TimeFunction::TimeFunction (
    const std::string & name,
    ProgressTracker * progress_tracker=nullptr
) 
```




<hr>



### function TimeFunction [2/2]

```C++
inline TimeFunction::TimeFunction (
    const std::string & name,
    std::optional< ProgressTracker > & progress_tracker
) 
```




<hr>



### function ~TimeFunction 

```C++
inline TimeFunction::~TimeFunction () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/timer.hpp`

