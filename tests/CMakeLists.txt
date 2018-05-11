enable_testing()

set(SplitTestSources
    main.cpp
    split_tests.cpp
)

add_executable(SplitTests
    ${SplitTestSources}
)

target_link_libraries(SplitTests
    PRIVATE
        SplitLibrary
        Catch2::Catch
)

add_test(NAME Tests
    COMMAND SplitTests -s
)
