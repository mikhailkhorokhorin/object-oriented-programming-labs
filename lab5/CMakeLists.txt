lab_library(lab5_core INTERFACE)

lab_executable(lab5_main
    SOURCES app/main.cpp
    LINK lab5_core
)

lab_tests(lab5_tests
    SOURCES
        tests/e2e.cpp
        tests/memory_resource.cpp
        tests/vector.cpp
        tests/vector_iterator.cpp
    LINK lab5_core
    BINARIES lab5_main
)
