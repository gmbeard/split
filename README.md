### Split
A simple, lightweight library for splitting strings. The
splitting is done without any allocations. It uses `std`
compatible iterators.

*License: MIT (See `LICENSE.txt`)*

### Example

```c++
#include "split/split.hpp"
#include <iostream>

auto main(int, char const**) -> int {
    constexpr char PHRASE[] = "Hello, World!";

    auto parts = split::split(PHRASE, ", ");

    // Prints `Found: 2 parts`
    std::cout << "Found: " << parts.size() << " parts\n";

    // Iterate through each part...
    for (auto const& s : parts) {
        std::cout << split::to_string(s) << "\n";
    }

    return 0;
}
```
