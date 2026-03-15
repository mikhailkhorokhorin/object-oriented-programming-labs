include_directories(include)

add_executable(lab3_main
    main.cpp
    src/array.cpp
    src/figure.cpp
    src/point.cpp
    src/rectangle.cpp
    src/square.cpp
    src/trapezoid.cpp
)

add_executable(lab3_tests
    tests/unit.cpp
    tests/array.cpp
    tests/point.cpp
    tests/rectangle.cpp
    tests/square.cpp
    tests/trapezoid.cpp
    src/array.cpp
    src/figure.cpp
    src/point.cpp
    src/rectangle.cpp
    src/square.cpp
    src/trapezoid.cpp
)

target_link_libraries(lab3_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab3_tests)
