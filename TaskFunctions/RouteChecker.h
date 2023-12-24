//
// Created by Mihail Dobroslavski on 24.12.23.
//

#ifndef CITYMAP_ROUTECHECKER_H
#define CITYMAP_ROUTECHECKER_H


#include "../Structure/Path.h"
#include <unordered_set>
#include <vector>
#include <stack>

class RouteChecker {
public:
    static bool exists(Graph*, Graph*);
    static std::vector<Path> getPaths(bool, Graph*, Graph*);
    static std::vector<Path> getTopThreePaths(bool, Graph*, Graph*);
private:
    static bool existsHelper(Graph* current, Graph* end, std::unordered_set<Graph*> checked);
};


#endif //CITYMAP_ROUTECHECKER_H
