include_directories(include)

add_executable(lab5_main
    main.cpp
)

add_executable(lab5_tests
    tests/memory_resource.cpp
    tests/unit.cpp
    tests/vector_iterator.cpp
    tests/vector.cpp
)

target_link_libraries(lab5_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab5_tests)
