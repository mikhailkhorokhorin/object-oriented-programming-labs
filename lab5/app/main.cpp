#include <iostream>
#include <string>

#include "memory_resource.hpp"
#include "vector.hpp"

namespace {

struct Person {
    int id;
    double score;
    std::string name;
};

}

int main() {
    MemoryResource resource;
    {
        Vector<int> numbers(&resource);
        for (int i = 1; i <= 5; ++i) {
            numbers.pushBack(i * i);
        }
        const char* separator = "";
        for (const int value : numbers) {
            std::cout << separator << value;
            separator = " ";
        }
        std::cout << "\nsize " << numbers.size() << ", capacity " << numbers.capacity() << '\n';

        Vector<Person> people(&resource);
        people.pushBack({1, 2.5, "Alice"});
        people.emplaceBack(Person{2, 4.75, "Bob"});
        for (const auto& person : people) {
            std::cout << person.id << ' ' << person.name << ' ' << person.score << '\n';
        }
        std::cout << "blocks in use: " << resource.usedBlockCount()
                  << ", free: " << resource.freeBlockCount() << '\n';
    }
    std::cout << "after scope: in use " << resource.usedBlockCount() << ", free "
              << resource.freeBlockCount() << '\n';
    return 0;
}
