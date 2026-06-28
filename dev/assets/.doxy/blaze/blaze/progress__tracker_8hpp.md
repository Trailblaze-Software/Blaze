

# File progress\_tracker.hpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**progress\_tracker.hpp**](progress__tracker_8hpp.md)

[Go to the source code of this file](progress__tracker_8hpp_source.md)



* `#include <chrono>`
* `#include <cstdint>`
* `#include <memory>`
* `#include <optional>`
* `#include <source_location>`
* `#include <string>`
* `#include <utility>`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**AsyncProgressTracker**](classAsyncProgressTracker.md) <br> |
| class | [**ProgressBar**](classProgressBar.md) <br> |
| class | [**ProgressObserver**](classProgressObserver.md) <br> |
| class | [**ProgressTracker**](classProgressTracker.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**START\_TRACKER**](progress__tracker_8hpp.md#define-start_tracker) (...) `START\_TRACKER\_GET(\_\_VA\_ARGS\_\_, START\_TRACKER\_2, START\_TRACKER\_1)(\_\_VA\_ARGS\_\_)`<br> |
| define  | [**START\_TRACKER\_1**](progress__tracker_8hpp.md#define-start_tracker_1) (text) `(progress\_tracker).begin\_tracking((text), std::source\_location::current())`<br> |
| define  | [**START\_TRACKER\_2**](progress__tracker_8hpp.md#define-start_tracker_2) (tracker, text) `((tracker)).begin\_tracking((text), std::source\_location::current())`<br> |
| define  | [**START\_TRACKER\_GET**](progress__tracker_8hpp.md#define-start_tracker_get) (\_1, \_2, NAME, ...) `NAME`<br> |
| define  | [**SUBTRACKER**](progress__tracker_8hpp.md#define-subtracker) (...) `SUBTRACKER\_GET(\_\_VA\_ARGS\_\_, SUBTRACKER\_3, SUBTRACKER\_2)(\_\_VA\_ARGS\_\_)`<br> |
| define  | [**SUBTRACKER\_2**](progress__tracker_8hpp.md#define-subtracker_2) (start, end) `(progress\_tracker).subtracker((start), (end), "", std::source\_location::current())`<br> |
| define  | [**SUBTRACKER\_3**](progress__tracker_8hpp.md#define-subtracker_3) (start, end, tracker) `((tracker)).subtracker((start), (end), "", std::source\_location::current())`<br> |
| define  | [**SUBTRACKER\_GET**](progress__tracker_8hpp.md#define-subtracker_get) (\_1, \_2, \_3, NAME, ...) `NAME`<br> |
| define  | [**SUBTRACKER\_HIDDEN**](progress__tracker_8hpp.md#define-subtracker_hidden) (...) `SUBTRACKER\_GET(\_\_VA\_ARGS\_\_, SUBTRACKER\_HIDDEN\_3, SUBTRACKER\_HIDDEN\_2)(\_\_VA\_ARGS\_\_)`<br> |
| define  | [**SUBTRACKER\_HIDDEN\_2**](progress__tracker_8hpp.md#define-subtracker_hidden_2) (start, end) `(progress\_tracker).subtracker((start), (end), "", std::source\_location::current(), false)`<br> |
| define  | [**SUBTRACKER\_HIDDEN\_3**](progress__tracker_8hpp.md#define-subtracker_hidden_3) (start, end, tracker) `((tracker)).subtracker((start), (end), "", std::source\_location::current(), false)`<br> |
| define  | [**SUBTRACKER\_VISIBLE**](progress__tracker_8hpp.md#define-subtracker_visible) (...) `SUBTRACKER\_GET(\_\_VA\_ARGS\_\_, SUBTRACKER\_VISIBLE\_3, SUBTRACKER\_VISIBLE\_2)(\_\_VA\_ARGS\_\_)`<br> |
| define  | [**SUBTRACKER\_VISIBLE\_2**](progress__tracker_8hpp.md#define-subtracker_visible_2) (start, end) `(progress\_tracker).subtracker((start), (end), "", std::source\_location::current(), true)`<br> |
| define  | [**SUBTRACKER\_VISIBLE\_3**](progress__tracker_8hpp.md#define-subtracker_visible_3) (start, end, tracker) `((tracker)).subtracker((start), (end), "", std::source\_location::current(), true)`<br> |

## Macro Definition Documentation





### define START\_TRACKER 

```C++
#define START_TRACKER (
    ...
) `START_TRACKER_GET(__VA_ARGS__, START_TRACKER_2, START_TRACKER_1)(__VA_ARGS__)`
```




<hr>



### define START\_TRACKER\_1 

```C++
#define START_TRACKER_1 (
    text
) `(progress_tracker).begin_tracking((text), std::source_location::current())`
```




<hr>



### define START\_TRACKER\_2 

```C++
#define START_TRACKER_2 (
    tracker,
    text
) `((tracker)).begin_tracking((text), std::source_location::current())`
```




<hr>



### define START\_TRACKER\_GET 

```C++
#define START_TRACKER_GET (
    _1,
    _2,
    NAME,
    ...
) `NAME`
```




<hr>



### define SUBTRACKER 

```C++
#define SUBTRACKER (
    ...
) `SUBTRACKER_GET(__VA_ARGS__, SUBTRACKER_3, SUBTRACKER_2)(__VA_ARGS__)`
```




<hr>



### define SUBTRACKER\_2 

```C++
#define SUBTRACKER_2 (
    start,
    end
) `(progress_tracker).subtracker((start), (end), "", std::source_location::current())`
```




<hr>



### define SUBTRACKER\_3 

```C++
#define SUBTRACKER_3 (
    start,
    end,
    tracker
) `((tracker)).subtracker((start), (end), "", std::source_location::current())`
```




<hr>



### define SUBTRACKER\_GET 

```C++
#define SUBTRACKER_GET (
    _1,
    _2,
    _3,
    NAME,
    ...
) `NAME`
```




<hr>



### define SUBTRACKER\_HIDDEN 

```C++
#define SUBTRACKER_HIDDEN (
    ...
) `SUBTRACKER_GET(__VA_ARGS__, SUBTRACKER_HIDDEN_3, SUBTRACKER_HIDDEN_2)(__VA_ARGS__)`
```




<hr>



### define SUBTRACKER\_HIDDEN\_2 

```C++
#define SUBTRACKER_HIDDEN_2 (
    start,
    end
) `(progress_tracker).subtracker((start), (end), "", std::source_location::current(), false)`
```




<hr>



### define SUBTRACKER\_HIDDEN\_3 

```C++
#define SUBTRACKER_HIDDEN_3 (
    start,
    end,
    tracker
) `((tracker)).subtracker((start), (end), "", std::source_location::current(), false)`
```




<hr>



### define SUBTRACKER\_VISIBLE 

```C++
#define SUBTRACKER_VISIBLE (
    ...
) `SUBTRACKER_GET(__VA_ARGS__, SUBTRACKER_VISIBLE_3, SUBTRACKER_VISIBLE_2)(__VA_ARGS__)`
```




<hr>



### define SUBTRACKER\_VISIBLE\_2 

```C++
#define SUBTRACKER_VISIBLE_2 (
    start,
    end
) `(progress_tracker).subtracker((start), (end), "", std::source_location::current(), true)`
```




<hr>



### define SUBTRACKER\_VISIBLE\_3 

```C++
#define SUBTRACKER_VISIBLE_3 (
    start,
    end,
    tracker
) `((tracker)).subtracker((start), (end), "", std::source_location::current(), true)`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/progress_tracker.hpp`

