

# File to\_string.hpp



[**FileList**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**printing**](dir_d9268aef91cea3e1dbca49ee670813aa.md) **>** [**to\_string.hpp**](to__string_8hpp.md)

[Go to the source code of this file](to__string_8hpp_source.md)



* `#include <iomanip>`
* `#include <iostream>`
* `#include <map>`
* `#include <optional>`
* `#include <set>`
* `#include <vector>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**double\_to\_string**](#function-double_to_string) ([**double**](classCoordinate2D.md) d, [**int**](classCoordinate2D.md) precision=2) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator) (std::ostream & os, [**const**](classCoordinate2D.md) std::vector&lt; T &gt; & vec) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_1) (std::ostream & os, [**const**](classCoordinate2D.md) std::set&lt; T &gt; & set) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_2) (std::ostream & os, [**const**](classCoordinate2D.md) std::pair&lt; T, [**U**](classCoordinate2D.md) &gt; & pair) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_3) (std::ostream & os, [**const**](classCoordinate2D.md) std::optional&lt; T &gt; & op) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_4) (std::ostream & os, [**const**](classCoordinate2D.md) std::map&lt; T, [**U**](classCoordinate2D.md) &gt; m) <br> |
|  std::string | [**to\_string**](#function-to_string) ([**const**](classCoordinate2D.md) T &... args) <br> |




























## Public Functions Documentation




### function double\_to\_string 

```C++
inline std::string double_to_string (
    double d,
    int precision=2
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<typename T>
inline std::ostream & operator<< (
    std::ostream & os,
    const std::vector< T > & vec
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<typename T>
inline std::ostream & operator<< (
    std::ostream & os,
    const std::set< T > & set
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<typename T, typename  U>
inline std::ostream & operator<< (
    std::ostream & os,
    const std::pair< T, U > & pair
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<typename T>
inline std::ostream & operator<< (
    std::ostream & os,
    const std::optional< T > & op
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<typename T, typename  U>
inline std::ostream & operator<< (
    std::ostream & os,
    const std::map< T, U > m
) 
```




<hr>



### function to\_string 

```C++
template<typename... T>
std::string to_string (
    const T &... args
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/printing/to_string.hpp`

