

# File env.hpp

[**File List**](files.md) **>** [**lib**](dir_c85d3e3c5052e9ad9ce18c6863244a25.md) **>** [**testing**](dir_30341ad8f18900961f37cfbd7fe13068.md) **>** [**env.hpp**](testing_2env_8hpp.md)

[Go to the documentation of this file](testing_2env_8hpp.md)


```C++
#pragma once

#include "utilities/env.hpp"

namespace blaze::test {

inline const char* get_env(const char* name) { return blaze::get_env(name); }

}  // namespace blaze::test
```


