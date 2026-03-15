include_directories(include)

add_executable(lab7_main
    main.cpp
    src/bear.cpp
    src/dungeon.cpp
    src/game.cpp
    src/npc_factory.cpp
    src/npc.cpp
    src/observer_console.cpp
    src/observer_file.cpp
    src/point.cpp
    src/random.cpp
    src/rogue.cpp
    src/task_queue.cpp
    src/thread_safe_cout.cpp
    src/werewolf.cpp
)

add_executable(lab7_tests
    tests/unit.cpp
    tests/bear.cpp
    tests/dungeon.cpp
    tests/game.cpp
    tests/npc_factory.cpp
    tests/npc.cpp
    tests/observer_console.cpp
    tests/observer_file.cpp
    tests/point.cpp
    tests/random.cpp
    tests/rogue.cpp
    tests/task_queue.cpp
    tests/thread_safe_cout.cpp
    tests/werewolf.cpp

    src/bear.cpp
    src/dungeon.cpp
    src/game.cpp
    src/npc_factory.cpp
    src/npc.cpp
    src/observer_console.cpp
    src/observer_file.cpp
    src/point.cpp
    src/random.cpp
    src/rogue.cpp
    src/task_queue.cpp
    src/thread_safe_cout.cpp
    src/werewolf.cpp
)

target_link_libraries(lab7_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab7_tests)
