lab_library(lab6_core
    SOURCES
        src/battle_visitor.cpp
        src/bear.cpp
        src/dungeon.cpp
        src/npc.cpp
        src/npc_factory.cpp
        src/observer_console.cpp
        src/observer_file.cpp
        src/point.cpp
        src/rogue.cpp
        src/werewolf.cpp
)

lab_executable(lab6_main
    SOURCES app/main.cpp
    LINK lab6_core
)

lab_tests(lab6_tests
    SOURCES
        tests/battle_visitor.cpp
        tests/dungeon.cpp
        tests/e2e.cpp
        tests/npc.cpp
        tests/npc_factory.cpp
        tests/observer_console.cpp
        tests/observer_file.cpp
        tests/point.cpp
    LINK lab6_core
    BINARIES lab6_main
)
