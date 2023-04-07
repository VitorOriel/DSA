#include <iostream>
#include "map.hpp"

int main() {
    HT::Map<std::string,int> map;
    map["test"] = 15;
    map["test2"] = map["test"];
    std::cout << map["test2"] << std::endl;
    try {
        std::cout << map.get("test3") << std::endl;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "erase: " << map.erase("test2") << std::endl;
    for (size_t i = 0; i < 100; ++i)
        map[std::to_string(i)] = 1;
    for (size_t i = 0; i < 100; ++i)
        std::cout << map.erase(std::to_string(i)) << std::endl;
    return 0;
}