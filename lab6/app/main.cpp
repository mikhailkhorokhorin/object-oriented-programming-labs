#include <cstddef>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "dungeon.hpp"
#include "observer_console.hpp"
#include "observer_file.hpp"

namespace {

void execute(Dungeon& dungeon, const std::string& line) {
    std::istringstream stream(line);
    std::string command;
    if (!(stream >> command)) {
        return;
    }
    if (command == "add") {
        std::string type;
        std::string name;
        int x = 0;
        int y = 0;
        if (!(stream >> type >> name >> x >> y) || !dungeon.addNPC(type, name, x, y)) {
            throw std::invalid_argument("cannot add NPC: " + line);
        }
    } else if (command == "print") {
        dungeon.printAll(std::cout);
    } else if (command == "battle") {
        double range = 0;
        if (!(stream >> range)) {
            throw std::invalid_argument("battle needs a range");
        }
        const std::size_t killed = dungeon.battle(range);
        std::cout << "Killed: " << killed << '\n';
    } else if (command == "save" || command == "load") {
        std::string path;
        if (!(stream >> path)) {
            throw std::invalid_argument(command + " needs a file name");
        }
        if (command == "save") {
            dungeon.saveToFile(path);
        } else {
            dungeon.loadFromFile(path);
        }
    } else {
        throw std::invalid_argument("unknown command: " + command);
    }
}

}

int main(int argc, char* argv[]) {
    try {
        ConsoleLogger consoleLogger(std::cout);
        FileLogger fileLogger(argc > 1 ? argv[1] : "log.txt");
        Dungeon dungeon;
        dungeon.addObserver(&consoleLogger);
        dungeon.addObserver(&fileLogger);
        std::string line;
        while (std::getline(std::cin, line)) {
            execute(dungeon, line);
        }
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
