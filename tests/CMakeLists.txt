# Add a test executable
add_executable(ActiveObjectTests
    src/test_activeobject.cpp
)

# Link your library and Catch2
target_link_libraries(ActiveObjectTests
    PRIVATE
        ActiveObject
        Catch2::Catch2WithMain
)

# Enable CTest
include(CTest)
include(Catch)
catch_discover_tests(ActiveObjectTests)