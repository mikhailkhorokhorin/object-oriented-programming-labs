include_directories(include)

add_executable(lab1_main
    main.cpp
    src/solution.cpp
)

add_executable(lab1_tests
    tests/unit.cpp
    tests/solution.cpp
    src/solution.cpp
)

target_link_libraries(lab1_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab1_tests)
