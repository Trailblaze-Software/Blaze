

# File assert.hpp



[**FileList**](files.md) **>** [**assert**](dir_d1185b0cdad395d5facacbcb4739e037.md) **>** [**assert.hpp**](assert_8hpp.md)

[Go to the source code of this file](assert_8hpp_source.md)



* `#include <iostream>`
* `#include <optional>`
* `#include <experimental/source_location>`
* `#include <sstream>`
* `#include <string>`
* `#include "printing/to_string.hpp"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**std**](namespacestd.md) <br> |
























## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classCoordinate2D.md) | [**\_Assert**](#function-_assert) ([**bool**](classCoordinate2D.md) condition, [**const**](classCoordinate2D.md) std::string & condition\_str, [**const**](classCoordinate2D.md) std::optional&lt; std::string &gt; & message, [**const**](classCoordinate2D.md) std::source\_location & loc=std::source\_location::current()) <br> |
|  [**void**](classCoordinate2D.md) | [**\_AssertBinOp**](#function-_assertbinop) ([**const**](classCoordinate2D.md) [**A**](classCoordinate2D.md) & a, [**const**](classCoordinate2D.md) [**B**](classCoordinate2D.md) & b, [**const**](classCoordinate2D.md) std::string & a\_str, [**const**](classCoordinate2D.md) std::string & b\_str, [**bool**](classCoordinate2D.md) result, [**const**](classCoordinate2D.md) std::string & op, [**const**](classCoordinate2D.md) std::string & nop, [**const**](classCoordinate2D.md) std::source\_location & loc=std::source\_location::current()) <br> |
|  [**void**](classCoordinate2D.md) | [**unreachable**](#function-unreachable) () <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**Assert**](assert_8hpp.md#define-assert) (condition, ...) `[**if**](classCoordinate2D.md) (!([**condition**](classCoordinate2D.md))) \_Assert([**condition**](classCoordinate2D.md), #[**condition**](classCoordinate2D.md), std::optional&lt;std::string&gt;([**\_\_VA\_ARGS\_\_**](classCoordinate2D.md)));`<br> |
| define  | [**AssertBinOp**](assert_8hpp.md#define-assertbinop) (a, b, op, nop) `[**if**](classCoordinate2D.md) (!(([**a**](classCoordinate2D.md))[**op**](classCoordinate2D.md)([**b**](classCoordinate2D.md)))) \_AssertBinOp([**a**](classCoordinate2D.md), [**b**](classCoordinate2D.md), #[**a**](classCoordinate2D.md), #[**b**](classCoordinate2D.md), [**a**](classCoordinate2D.md) [**op**](classCoordinate2D.md) [**b**](classCoordinate2D.md), #[**op**](classCoordinate2D.md), #[**nop**](classCoordinate2D.md))`<br> |
| define  | [**AssertEQ**](assert_8hpp.md#define-asserteq) (expr, val) `AssertBinOp([**expr**](classCoordinate2D.md), [**val**](classCoordinate2D.md), ==, !=)`<br> |
| define  | [**AssertGE**](assert_8hpp.md#define-assertge) (expr, val) `AssertBinOp([**expr**](classCoordinate2D.md), [**val**](classCoordinate2D.md), &gt;=, &lt;)`<br> |
| define  | [**AssertGT**](assert_8hpp.md#define-assertgt) (expr, val) `AssertBinOp([**expr**](classCoordinate2D.md), [**val**](classCoordinate2D.md), &gt;, &lt;=)`<br> |
| define  | [**AssertLE**](assert_8hpp.md#define-assertle) (expr, val) `AssertBinOp([**expr**](classCoordinate2D.md), [**val**](classCoordinate2D.md), &lt;=, &gt;)`<br> |
| define  | [**AssertNE**](assert_8hpp.md#define-assertne) (expr, val) `AssertBinOp([**expr**](classCoordinate2D.md), [**val**](classCoordinate2D.md), !=, ==)`<br> |
| define  | [**Fail**](assert_8hpp.md#define-fail) (...) `/* multi line expression */`<br> |
| define  | [**HAS\_BUILTIN**](assert_8hpp.md#define-has_builtin) (x) `[**\_\_has\_builtin**](classCoordinate2D.md)(x)`<br> |
| define  | [**Unimplemented**](assert_8hpp.md#define-unimplemented) (...) `Assert([**false**](classCoordinate2D.md), "Unimplemented");`<br> |

## Public Functions Documentation




### function \_Assert 

```C++
inline void _Assert (
    bool condition,
    const std::string & condition_str,
    const std::optional< std::string > & message,
    const std::source_location & loc=std::source_location::current()
) 
```




<hr>



### function \_AssertBinOp 

```C++
template<typename  A, typename  B>
inline void _AssertBinOp (
    const  A & a,
    const  B & b,
    const std::string & a_str,
    const std::string & b_str,
    bool result,
    const std::string & op,
    const std::string & nop,
    const std::source_location & loc=std::source_location::current()
) 
```




<hr>



### function unreachable 

```C++
inline void unreachable () 
```




<hr>
## Macro Definition Documentation





### define Assert 

```C++
#define Assert (
    condition,
    ...
) `if (!( condition )) _Assert( condition , # condition , std::optional<std::string>( __VA_ARGS__ ));`
```




<hr>



### define AssertBinOp 

```C++
#define AssertBinOp (
    a,
    b,
    op,
    nop
) `if (!(( a ) op ( b ))) _AssertBinOp( a , b , # a , # b , a  op  b , # op , # nop )`
```




<hr>



### define AssertEQ 

```C++
#define AssertEQ (
    expr,
    val
) `AssertBinOp( expr , val , ==, !=)`
```




<hr>



### define AssertGE 

```C++
#define AssertGE (
    expr,
    val
) `AssertBinOp( expr , val , >=, <)`
```




<hr>



### define AssertGT 

```C++
#define AssertGT (
    expr,
    val
) `AssertBinOp( expr , val , >, <=)`
```




<hr>



### define AssertLE 

```C++
#define AssertLE (
    expr,
    val
) `AssertBinOp( expr , val , <=, >)`
```




<hr>



### define AssertNE 

```C++
#define AssertNE (
    expr,
    val
) `AssertBinOp( expr , val , !=, ==)`
```




<hr>



### define Fail 

```C++
#define Fail (
    ...
) `/* multi line expression */`
```




<hr>



### define HAS\_BUILTIN 

```C++
#define HAS_BUILTIN (
    x
) `__has_builtin (x)`
```




<hr>



### define Unimplemented 

```C++
#define Unimplemented (
    ...
) `Assert( false , "Unimplemented");`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/assert/assert.hpp`

