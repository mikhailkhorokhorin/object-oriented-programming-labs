lab_library(lab2_core
    SOURCES
        src/money.cpp
)

lab_executable(lab2_main
    SOURCES app/main.cpp
    LINK lab2_core
)

lab_tests(lab2_tests
    SOURCES
        tests/e2e.cpp
        tests/money.cpp
    LINK lab2_core
    BINARIES lab2_main
)
