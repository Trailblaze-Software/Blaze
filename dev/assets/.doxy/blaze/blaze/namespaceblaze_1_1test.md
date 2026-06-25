

# Namespace blaze::test



[**Namespace List**](namespaces.md) **>** [**blaze**](namespaceblaze.md) **>** [**test**](namespaceblaze_1_1test.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  const char \* | [**get\_env**](#function-get_env) (const char \* name) <br> |
|  std::string | [**sanitize\_for\_path**](#function-sanitize_for_path) (std::string\_view s) <br> |
|  std::filesystem::path | [**unique\_test\_output\_dir**](#function-unique_test_output_dir) (std::string\_view label={}) <br> |
|  std::filesystem::path | [**unique\_test\_output\_path**](#function-unique_test_output_path) (std::string\_view label, std::string\_view extension) <br> |




























## Public Functions Documentation




### function get\_env 

```C++
inline const char * blaze::test::get_env (
    const char * name
) 
```




<hr>



### function sanitize\_for\_path 

```C++
inline std::string blaze::test::sanitize_for_path (
    std::string_view s
) 
```




<hr>



### function unique\_test\_output\_dir 

```C++
inline std::filesystem::path blaze::test::unique_test_output_dir (
    std::string_view label={}
) 
```




<hr>



### function unique\_test\_output\_path 

```C++
inline std::filesystem::path blaze::test::unique_test_output_path (
    std::string_view label,
    std::string_view extension
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `/home/runner/work/Blaze/Blaze/src/lib/testing/env.hpp`

