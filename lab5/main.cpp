#include <iostream>
#include <string>

#include "memory_resource.hpp"
#include "vector.hpp"

struct Struct {
    int x;
    double y;
    std::string name;
};

int main() {
    Vector<int> vecInt;
    vecInt.push_back(1);
    vecInt.push_back(2);
    vecInt.push_back(3);

    for (auto v : vecInt)
        std::cout << v << " ";
    std::cout << std::endl;

    Vector<Struct> vecStruct;
    vecStruct.push_back({1, 2.5, "Alice"});
    vecStruct.push_back({3, 4.7, "Bob"});

    for (auto& s : vecStruct)
        std::cout << s.name << ": " << s.x << ", " << s.y << std::endl;

    MemoryResource mr;
    void* p = mr.allocate(32);
    mr.deallocate(p, 32);

    return 0;
}
