

# File test\_progress\_tracker.cpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**utilities**](dir_f68f3bc40609949e989ead5b0b6dedfd.md) **>** [**tests**](dir_61cbaf6f69b3ff38c8740f6eb1724d7a.md) **>** [**test\_progress\_tracker.cpp**](test__progress__tracker_8cpp.md)

[Go to the source code of this file](test__progress__tracker_8cpp_source.md)



* `#include <gtest/gtest.h>`
* `#include <fstream>`
* `#include <string>`
* `#include <vector>`
* `#include "utilities/filesystem.hpp"`
* `#include "utilities/progress_tracker.hpp"`
* `#include "utilities/trace_recorder.hpp"`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**RecordingProgressBar**](classRecordingProgressBar.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), [**ProgressTracker**](classProgressTracker.md)) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), ForLoop) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), BackwardsSubtrackerUpdateFails) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), ParallelRowProgressIsMonotonic) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), ProgressScope) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), ParentSetProportionBlockedWhileChildActive) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), StartTrackerBeginsDeferredSubtracker) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), StartTrackerNamesRoot) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), RootScopeCompletesBeforeTraceWrite) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), StartTrackerPatchesCallSiteInTrace) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), StartTrackerRecordsCallSiteInScopeStack) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), SiblingSubtrackersRequireSequentialLifetime) <br> |
|   | [**TEST**](#function-test) ([**ProgressTracker**](classProgressTracker.md), ProgressScopeStackOnFailure) <br> |




























## Public Functions Documentation




### function TEST 

```C++
TEST (
    ProgressTracker,
    ProgressTracker
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    ForLoop
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    BackwardsSubtrackerUpdateFails
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    ParallelRowProgressIsMonotonic
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    ProgressScope
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    ParentSetProportionBlockedWhileChildActive
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    StartTrackerBeginsDeferredSubtracker
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    StartTrackerNamesRoot
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    RootScopeCompletesBeforeTraceWrite
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    StartTrackerPatchesCallSiteInTrace
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    StartTrackerRecordsCallSiteInScopeStack
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    SiblingSubtrackersRequireSequentialLifetime
) 
```




<hr>



### function TEST 

```C++
TEST (
    ProgressTracker,
    ProgressScopeStackOnFailure
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/tests/test_progress_tracker.cpp`

