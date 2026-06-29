

# Namespace blaze::memory\_tracker



[**Namespace List**](namespaces.md) **>** [**blaze**](namespaceblaze.md) **>** [**memory\_tracker**](namespaceblaze_1_1memory__tracker.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**tracked\_allocator\_detail**](namespaceblaze_1_1memory__tracker_1_1tracked__allocator__detail.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**TrackedAllocator**](classblaze_1_1memory__tracker_1_1TrackedAllocator.md) &lt;typename T, MemoryTag&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef TrackedVector&lt; T, Tag::GRID &gt; | [**GridVector**](#typedef-gridvector)  <br> |
| typedef TrackedVector&lt; T, Tag::LAS &gt; | [**LasVector**](#typedef-lasvector)  <br> |
| enum uint8\_t | [**Tag**](#enum-tag)  <br> |
| typedef std::vector&lt; T, [**TrackedAllocator**](classblaze_1_1memory__tracker_1_1TrackedAllocator.md)&lt; T, MemoryTag &gt; &gt; | [**TrackedVector**](#typedef-trackedvector)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**add\_bytes**](#function-add_bytes) (Tag tag, uint64\_t bytes) <br> |
|  std::string | [**format\_summary**](#function-format_summary) () <br> |
|  bool | [**operator!=**](#function-operator) (const [**TrackedAllocator**](classblaze_1_1memory__tracker_1_1TrackedAllocator.md)&lt; T, MemoryTag &gt; & lhs, const [**TrackedAllocator**](classblaze_1_1memory__tracker_1_1TrackedAllocator.md)&lt; U, MemoryTag &gt; & rhs) noexcept<br> |
|  bool | [**operator==**](#function-operator_1) (const [**TrackedAllocator**](classblaze_1_1memory__tracker_1_1TrackedAllocator.md)&lt; T, MemoryTag &gt; &, const [**TrackedAllocator**](classblaze_1_1memory__tracker_1_1TrackedAllocator.md)&lt; U, MemoryTag &gt; &) noexcept<br> |
|  void | [**remove\_bytes**](#function-remove_bytes) (Tag tag, uint64\_t bytes) <br> |
|  uint64\_t | [**tag\_bytes**](#function-tag_bytes) (Tag tag) <br> |
|  const char \* | [**tag\_name**](#function-tag_name) (Tag tag) <br> |
|  uint64\_t | [**total\_bytes**](#function-total_bytes) () <br> |




























## Public Types Documentation




### typedef GridVector 

```C++
using blaze::memory_tracker::GridVector = typedef TrackedVector<T, Tag::GRID>;
```




<hr>



### typedef LasVector 

```C++
using blaze::memory_tracker::LasVector = typedef TrackedVector<T, Tag::LAS>;
```




<hr>



### enum Tag 

```C++
enum blaze::memory_tracker::Tag {
    LAS = 0,
    GRID = 1
};
```




<hr>



### typedef TrackedVector 

```C++
using blaze::memory_tracker::TrackedVector = typedef std::vector<T, TrackedAllocator<T, MemoryTag> >;
```




<hr>
## Public Functions Documentation




### function add\_bytes 

```C++
void blaze::memory_tracker::add_bytes (
    Tag tag,
    uint64_t bytes
) 
```




<hr>



### function format\_summary 

```C++
std::string blaze::memory_tracker::format_summary () 
```




<hr>



### function operator!= 

```C++
template<typename T, typename U, Tag MemoryTag>
bool blaze::memory_tracker::operator!= (
    const TrackedAllocator < T, MemoryTag > & lhs,
    const TrackedAllocator < U, MemoryTag > & rhs
) noexcept
```




<hr>



### function operator== 

```C++
template<typename T, typename U, Tag MemoryTag>
bool blaze::memory_tracker::operator== (
    const TrackedAllocator < T, MemoryTag > &,
    const TrackedAllocator < U, MemoryTag > &
) noexcept
```




<hr>



### function remove\_bytes 

```C++
void blaze::memory_tracker::remove_bytes (
    Tag tag,
    uint64_t bytes
) 
```




<hr>



### function tag\_bytes 

```C++
uint64_t blaze::memory_tracker::tag_bytes (
    Tag tag
) 
```




<hr>



### function tag\_name 

```C++
const char * blaze::memory_tracker::tag_name (
    Tag tag
) 
```




<hr>



### function total\_bytes 

```C++
uint64_t blaze::memory_tracker::total_bytes () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/memory_tracker.cpp`

