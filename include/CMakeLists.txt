add_library(SplitIncludes INTERFACE)
target_include_directories(SplitIncludes
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(SplitIncludes
    INTERFACE
        cxx_decltype_auto
)

target_compile_options(SplitIncludes
    INTERFACE
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Werror -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

install(
    DIRECTORY
        split
    DESTINATION
        include
)

install(
    TARGETS 
        SplitIncludes
    EXPORT 
        SplitIncludesExport
)
