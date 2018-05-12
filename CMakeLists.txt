cmake_minimum_required(VERSION 3.7)

project(Split CXX)

add_subdirectory(include)
add_subdirectory(src)

set(SPLIT_ENABLE_TESTS 
    OFF
    CACHE 
    BOOL 
    "Build the unit tests along with the library"
)

if(SPLIT_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(submodules/catch)
    add_subdirectory(tests)
endif()

install(
    EXPORT 
        SplitIncludesExport
    NAMESPACE 
        Split::
    FILE 
        SplitIncludes.cmake
    DESTINATION 
        lib/cmake/split
)

install(
    EXPORT 
        SplitLibraryExport
    NAMESPACE 
        Split::
    FILE 
        SplitLibrary.cmake
    DESTINATION 
        lib/cmake/split
)

install(
    FILES
        cmake/SplitConfig.cmake
    DESTINATION
        lib/cmake/split
)
