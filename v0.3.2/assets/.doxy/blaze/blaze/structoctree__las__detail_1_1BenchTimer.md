

# Struct octree\_las\_detail::BenchTimer



[**ClassList**](annotated.md) **>** [**octree\_las\_detail**](namespaceoctree__las__detail.md) **>** [**BenchTimer**](structoctree__las__detail_1_1BenchTimer.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::chrono::high\_resolution\_clock | [**Clock**](#typedef-clock)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  const char \* | [**m\_label**](#variable-m_label)  <br> |
|  size\_t | [**m\_point\_count**](#variable-m_point_count)  <br> |
|  Clock::time\_point | [**m\_start**](#variable-m_start)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BenchTimer**](#function-benchtimer) (const char \* label, size\_t n=0) <br> |
|   | [**~BenchTimer**](#function-benchtimer) () <br> |




























## Public Types Documentation




### typedef Clock 

```C++
using octree_las_detail::BenchTimer::Clock =  std::chrono::high_resolution_clock;
```




<hr>
## Public Attributes Documentation




### variable m\_label 

```C++
const char* octree_las_detail::BenchTimer::m_label;
```




<hr>



### variable m\_point\_count 

```C++
size_t octree_las_detail::BenchTimer::m_point_count;
```




<hr>



### variable m\_start 

```C++
Clock::time_point octree_las_detail::BenchTimer::m_start;
```




<hr>
## Public Functions Documentation




### function BenchTimer 

```C++
inline octree_las_detail::BenchTimer::BenchTimer (
    const char * label,
    size_t n=0
) 
```




<hr>



### function ~BenchTimer 

```C++
inline octree_las_detail::BenchTimer::~BenchTimer () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/gui/octree_las_data.hpp`

