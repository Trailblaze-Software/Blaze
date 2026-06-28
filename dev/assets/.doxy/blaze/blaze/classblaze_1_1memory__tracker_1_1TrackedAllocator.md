

# Class blaze::memory\_tracker::TrackedAllocator

**template &lt;typename T, Tag MemoryTag&gt;**



[**ClassList**](annotated.md) **>** [**blaze**](namespaceblaze.md) **>** [**memory\_tracker**](namespaceblaze_1_1memory__tracker.md) **>** [**TrackedAllocator**](classblaze_1_1memory__tracker_1_1TrackedAllocator.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**rebind**](structblaze_1_1memory__tracker_1_1TrackedAllocator_1_1rebind.md) &lt;typename U&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::ptrdiff\_t | [**difference\_type**](#typedef-difference_type)  <br> |
| typedef std::true\_type | [**is\_always\_equal**](#typedef-is_always_equal)  <br> |
| typedef std::true\_type | [**propagate\_on\_container\_copy\_assignment**](#typedef-propagate_on_container_copy_assignment)  <br> |
| typedef std::true\_type | [**propagate\_on\_container\_move\_assignment**](#typedef-propagate_on_container_move_assignment)  <br> |
| typedef std::true\_type | [**propagate\_on\_container\_swap**](#typedef-propagate_on_container_swap)  <br> |
| typedef std::size\_t | [**size\_type**](#typedef-size_type)  <br> |
| typedef T | [**value\_type**](#typedef-value_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TrackedAllocator**](#function-trackedallocator-12) () noexcept<br> |
|   | [**TrackedAllocator**](#function-trackedallocator-22) (const [**TrackedAllocator**](classblaze_1_1memory__tracker_1_1TrackedAllocator.md)&lt; U, MemoryTag &gt; &) noexcept<br> |
|  T \* | [**allocate**](#function-allocate) (size\_type count) <br> |
|  void | [**deallocate**](#function-deallocate) (T \* pointer, size\_type count) noexcept<br> |
|  size\_type | [**max\_size**](#function-max_size) () noexcept const<br> |




























## Public Types Documentation




### typedef difference\_type 

```C++
using blaze::memory_tracker::TrackedAllocator< T, MemoryTag >::difference_type =  std::ptrdiff_t;
```




<hr>



### typedef is\_always\_equal 

```C++
using blaze::memory_tracker::TrackedAllocator< T, MemoryTag >::is_always_equal =  std::true_type;
```




<hr>



### typedef propagate\_on\_container\_copy\_assignment 

```C++
using blaze::memory_tracker::TrackedAllocator< T, MemoryTag >::propagate_on_container_copy_assignment =  std::true_type;
```




<hr>



### typedef propagate\_on\_container\_move\_assignment 

```C++
using blaze::memory_tracker::TrackedAllocator< T, MemoryTag >::propagate_on_container_move_assignment =  std::true_type;
```




<hr>



### typedef propagate\_on\_container\_swap 

```C++
using blaze::memory_tracker::TrackedAllocator< T, MemoryTag >::propagate_on_container_swap =  std::true_type;
```




<hr>



### typedef size\_type 

```C++
using blaze::memory_tracker::TrackedAllocator< T, MemoryTag >::size_type =  std::size_t;
```




<hr>



### typedef value\_type 

```C++
using blaze::memory_tracker::TrackedAllocator< T, MemoryTag >::value_type =  T;
```




<hr>
## Public Functions Documentation




### function TrackedAllocator [1/2]

```C++
blaze::memory_tracker::TrackedAllocator::TrackedAllocator () noexcept
```




<hr>



### function TrackedAllocator [2/2]

```C++
template<typename U>
inline blaze::memory_tracker::TrackedAllocator::TrackedAllocator (
    const TrackedAllocator < U, MemoryTag > &
) noexcept
```




<hr>



### function allocate 

```C++
inline T * blaze::memory_tracker::TrackedAllocator::allocate (
    size_type count
) 
```




<hr>



### function deallocate 

```C++
inline void blaze::memory_tracker::TrackedAllocator::deallocate (
    T * pointer,
    size_type count
) noexcept
```




<hr>



### function max\_size 

```C++
inline size_type blaze::memory_tracker::TrackedAllocator::max_size () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/utilities/tracked_allocator.hpp`

