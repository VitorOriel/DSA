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
    return 0;
}