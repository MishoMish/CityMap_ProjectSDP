//
// Created by Mihail Dobroslavski on 24.12.23.
//

#ifndef CITYMAP_ROUTECHECKER_H
#define CITYMAP_ROUTECHECKER_H


#include "../Structure/Path.h"
#include "../Structure/GraphContainer.h"

#include <utility>
#include <unordered_set>
#include <set>

#include <vector>
#include <stack>

class RouteChecker {
public:
    static bool exists(Graph *, Graph *);

    static std::vector<Path> getPaths(Graph *, Graph *, const std::unordered_set<Graph *> &);

    static std::vector<Path> getPaths(Graph *, Graph *);

    static bool canReturnToStart(Graph *);

    static Path *hasPathAllGraph(GraphContainer *container);
    static Path *hasPathAllGraph(GraphContainer *container, Graph *start);

    static Path *findEulerPath(GraphContainer *container);
    static Path *findEulerPath(GraphContainer *container, Graph *start);

    static bool canReachAllNodes(GraphContainer *container, Graph *start);

    static std::vector<std::pair<Graph *, Graph *> > findAllDeadEnded(GraphContainer *container);

private:
    static void pathAllGraphUtil(GraphContainer *container, Graph *current, Graph *start, Path *path,
                                 std::set<std::pair<Graph *, Graph *> > &visitedEdges, bool &found);

    static void findEulerPathUtil(GraphContainer *container, Graph *current, Graph *start, Path *path,
                                  std::set<std::pair<Graph *, Graph *> > &visitedEdges, bool &found);

    static bool existsHelper(Graph *current, Graph *end, std::unordered_set<Graph *> &checked);

    static bool canReturnToStartHelper(Graph *current, Graph *start, std::unordered_set<Graph *> &visited);
};


#endif //CITYMAP_ROUTECHECKER_H
