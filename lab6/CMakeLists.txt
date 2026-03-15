include_directories(include)

add_executable(lab6_main
    main.cpp
    src/battle_visitor.cpp
    src/bear.cpp
    src/dungeon.cpp
    src/npc_factory.cpp
    src/npc.cpp
    src/observer_console.cpp
    src/observer_file.cpp
    src/point.cpp
    src/rogue.cpp
    src/werewolf.cpp
)

add_executable(lab6_tests
    tests/unit.cpp
    tests/battle_visitor.cpp
    tests/bear.cpp
    tests/dungeon.cpp
    tests/npc_factory.cpp
    tests/observer_console.cpp
    tests/observer_file.cpp
    tests/point.cpp
    tests/rogue.cpp
    tests/werewolf.cpp
    src/battle_visitor.cpp
    src/bear.cpp
    src/dungeon.cpp
    src/npc_factory.cpp
    src/npc.cpp
    src/observer_console.cpp
    src/observer_file.cpp
    src/point.cpp
    src/rogue.cpp
    src/werewolf.cpp
)

target_link_libraries(lab6_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab6_tests)
