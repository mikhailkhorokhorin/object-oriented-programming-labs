lab_library(lab4_core INTERFACE)

lab_executable(lab4_main
    SOURCES app/main.cpp
    LINK lab4_core
)

lab_tests(lab4_tests
    SOURCES
        tests/array.cpp
        tests/e2e.cpp
        tests/hexagon.cpp
        tests/pentagon.cpp
        tests/point.cpp
        tests/rhombus.cpp
    LINK lab4_core
    BINARIES lab4_main
)
