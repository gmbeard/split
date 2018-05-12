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

### Building and Installing
*Split* uses [CMake][1] and requires at least
version `3.7`.

To build and install, use the following steps 
from the project's root directory...

```bash
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/tmp/split ..
cmake --build . --target install
```

*NOTE: I've used a temporary path as the install
location (`/tmp/split`). You can replace this with
whatever path is appropriate for your platform*

### Using Split in your own CMake projects
*Split*'s CMake config exports a `Split::SplitLibrary` 
target. Assuming that you used the path `/tmp/split` 
for the installation step (above), you can import 
the target into your own CMake project using the
`find_package(...)` command. 

Example of a top-level `CMakeLists.txt` file...

```cmake
cmake_minimum_required(VERSION 3.7)
project(MyApp)

find_package(
    Split
    PATHS /tmp/split
)

add_executable(
    MyProg
    main.cpp
#   ...
)

target_link_library(
    MyProg
    PRIVATE
        Split::SplitLibrary
)
```

[1]: https://cmake.org/download/
