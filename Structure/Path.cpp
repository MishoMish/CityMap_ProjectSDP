//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "Path.h"

void Path::print() {
    if(this == nullptr || nodes.size() == 0){
        std::cout << "No items in path" << std::endl;
        return;
    }
    for(auto item : nodes){
        std::cout << item->name << " -> ";
    }
    std::cout << " length = " << cost << std::endl;
}
