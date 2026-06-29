

# File progress\_box.cpp



[**FileList**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**progress\_box.cpp**](progress__box_8cpp.md)

[Go to the source code of this file](progress__box_8cpp_source.md)



* `#include "progress_box.hpp"`
* `#include <QException>`
* `#include <QFutureWatcher>`
* `#include <QProgressBar>`
* `#include <QTimer>`
* `#include <QtConcurrent>`
* `#include <chrono>`
* `#include <cmath>`
* `#include <sstream>`
* `#include "error_dialog.hpp"`
* `#include "ui_progress_box.h"`
* `#include "utilities/memory_tracker.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/trace_recorder.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**TaskException**](classTaskException.md) <br> |
























## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**format\_duration**](#function-format_duration) (double seconds) <br> |


























## Public Static Functions Documentation




### function format\_duration 

```C++
static std::string format_duration (
    double seconds
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/progress_box.cpp`

