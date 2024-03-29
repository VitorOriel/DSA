#include <iostream>
#include "map.hpp"

int main() {
    ht::Map<std::string,int> map;
    map["test"] = 15;
    map["test2"] = map["test"];
    std::cout << map["test2"] << std::endl;
    try {
        std::cout << map.get("test3") << std::endl;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "erase: " << map.erase("test2") << std::endl;
    for (int i = 0; i < 100; ++i) {
        int k = i;
        map.set(std::to_string(i), k);
    }
    for (auto it : map)
        std::cout << it->key << ' ' << it->value << std::endl;
    return 0;
}