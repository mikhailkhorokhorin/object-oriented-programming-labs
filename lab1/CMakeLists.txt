lab_library(lab1_core
    SOURCES
        src/solution.cpp
)

lab_executable(lab1_main
    SOURCES app/main.cpp
    LINK lab1_core
)

lab_tests(lab1_tests
    SOURCES
        tests/e2e.cpp
        tests/solution.cpp
    LINK lab1_core
    BINARIES lab1_main
)
