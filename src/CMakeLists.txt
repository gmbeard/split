set(SplitLibrarySources
    split.cpp
)

add_library(SplitLibrary STATIC
    ${SplitLibrarySources}
)

target_link_libraries(SplitLibrary
    PUBLIC
        SplitIncludes
)

install(
    TARGETS 
        SplitLibrary
    EXPORT 
        SplitLibraryExport
    ARCHIVE DESTINATION lib
)
