//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "Path.h"

void Path::print() {
    for(auto item : nodes){
        std::cout << item->getName() << " -> ";
    }
    std::cout << cost << std::endl;
}
