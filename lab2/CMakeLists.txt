include_directories(include)

add_executable(lab2_main
    main.cpp
    src/money.cpp
)

add_executable(lab2_tests
    tests/unit.cpp
    tests/money.cpp
    src/money.cpp
)

target_link_libraries(lab2_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab2_tests)
