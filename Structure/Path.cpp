//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "Path.h"

// Print method to display the nodes in the path and its total cost
void Path::print() {

    if (this == nullptr || nodes.empty() || nodes[0] == nullptr) {
        std::cout << "No items in path" << std::endl;
        return;
    }

    for (auto item: nodes) {
        std::cout << item->getName() << " -> ";
    }

    std::cout << " length = " << cost << std::endl;
}
