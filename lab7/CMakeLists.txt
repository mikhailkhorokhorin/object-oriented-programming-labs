lab_library(lab7_core
    SOURCES
        src/bear.cpp
        src/dungeon.cpp
        src/game.cpp
        src/npc.cpp
        src/npc_factory.cpp
        src/observer_console.cpp
        src/observer_file.cpp
        src/point.cpp
        src/random.cpp
        src/rogue.cpp
        src/synced_stream.cpp
        src/task_queue.cpp
        src/werewolf.cpp
)

lab_executable(lab7_main
    SOURCES app/main.cpp
    LINK lab7_core
)

lab_tests(lab7_tests
    SOURCES
        tests/dungeon.cpp
        tests/e2e.cpp
        tests/game.cpp
        tests/npc.cpp
        tests/npc_factory.cpp
        tests/observer_console.cpp
        tests/observer_file.cpp
        tests/point.cpp
        tests/random.cpp
        tests/task_queue.cpp
    LINK lab7_core
    LABEL threads
    BINARIES lab7_main
)
