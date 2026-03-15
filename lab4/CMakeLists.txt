include_directories(include)

add_executable(lab4_main
    main.cpp
)

add_executable(lab4_tests
    tests/unit.cpp
    tests/array.cpp
    tests/point.cpp
    tests/hexagon.cpp
    tests/pentagon.cpp
    tests/rhombus.cpp
)

target_link_libraries(lab4_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab4_tests)
