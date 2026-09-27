lab_library(lab3_core
    SOURCES
        src/array.cpp
        src/figure.cpp
        src/point.cpp
        src/rectangle.cpp
        src/square.cpp
        src/trapezoid.cpp
)

lab_executable(lab3_main
    SOURCES app/main.cpp
    LINK lab3_core
)

lab_tests(lab3_tests
    SOURCES
        tests/array.cpp
        tests/e2e.cpp
        tests/point.cpp
        tests/rectangle.cpp
        tests/square.cpp
        tests/trapezoid.cpp
    LINK lab3_core
    BINARIES lab3_main
)
