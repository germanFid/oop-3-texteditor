# AHO-CORASICK

My very own (i promise) implementation of Aho-Corasick algorithm

## Usage example

```cpp
#include "aho.h"

int main()
{
    int result = quick_search_aho("hello amazing world!", "amazing");
    std::cout << result << std::endl;
    return 0;
}
```

It will print `6` as a result
