//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "Path.h"

void Path::print() {
    if (this == nullptr || nodes.empty()) {
        std::cout << "No items in path" << std::endl;
        return;
    }

    for (auto item: nodes) {
        std::cout << item->getName() << " -> ";
    }

    std::cout << " length = " << cost << std::endl;
}

