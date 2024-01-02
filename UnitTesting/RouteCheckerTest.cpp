//
// Created by Mihail Dobroslavski on 30.12.23.
//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../TaskFunctions/RouteChecker.h"
#include "../Structure/GraphContainer.h"
#include "../Structure/Graph.h"

TEST_CASE("RouteChecker Test") {
    GraphContainer container;

    container.addGraph("1");
    container.addGraph("2");
    container.addGraph("3");
    container.addGraph("4");

    container.addRoad("1", "2", 10.0);
    container.addRoad("1", "3", 20.0);
    container.addRoad("2", "3", 5.0);
    container.addRoad("2", "4", 15.0);
    container.addRoad("3", "1", 20.0);


    // Add some graphs to the container for testing
    Graph *graphA = container.getGraph("1");
    Graph *graphB = container.getGraph("2");
    Graph *graphC = container.getGraph("3");
    Graph *graphD = container.getGraph("4");

    SUBCASE("Exists Test") {
        CHECK(RouteChecker::exists(graphA, graphB));
        CHECK(RouteChecker::exists(graphA, graphC));
        CHECK(RouteChecker::exists(graphA, graphD));
        CHECK_FALSE(RouteChecker::exists(graphD, graphB));
    }

    SUBCASE("Get Paths Test - closed junctions") {
        // Define a set of closed junctions
        std::unordered_set<Graph *> closedJunctions = {graphB};
        std::vector<Path> paths = RouteChecker::getPaths(graphA, graphC, closedJunctions);
        REQUIRE(paths.size() == 1);
        CHECK(paths[0].cost == 20.0);
        CHECK(paths[0].nodes.size() == 2);
        CHECK(paths[0].nodes[0]->getName() == "1");
        CHECK(paths[0].nodes[1]->getName() == "3");
    }

    SUBCASE("Get Paths Test - NO closed junctions") {
        std::vector<Path> paths = RouteChecker::getPaths(graphA, graphC);
        REQUIRE(paths.size() == 2);
        CHECK(paths[0].cost == 15.0);
        CHECK(paths[0].nodes.size() == 3);
        CHECK(paths[1].cost == 20.0);
        CHECK(paths[1].nodes.size() == 2);
    }

    SUBCASE("Can Return to Start Test") {
        CHECK(RouteChecker::canReturnToStart(graphA));
        CHECK_FALSE(RouteChecker::canReturnToStart(graphD));
    }

    SUBCASE("Hamiltonian Path Test - NO starting junction") {
        Path *path = RouteChecker::hasHamiltonianPath(&container);
        REQUIRE(path != nullptr);
    }

    SUBCASE("Hamiltonian Path Test - starting junction") {
        Path *path = RouteChecker::hasHamiltonianPath(&container, graphA);
        REQUIRE(path != nullptr);
    }

    SUBCASE("Can reach all other Test") {
        CHECK(RouteChecker::canReachAllNodes(&container, graphA));
        CHECK(RouteChecker::canReachAllNodes(&container, graphB));
        CHECK(RouteChecker::canReachAllNodes(&container, graphC));
        CHECK_FALSE(RouteChecker::canReachAllNodes(&container, graphD));
    }

    SUBCASE("Find dead ends test") {
        std::vector<std::pair<Graph *, Graph *>> deadEnds = RouteChecker::findAllDeadEnded(&container);
        REQUIRE(deadEnds.size() == 1);
        CHECK(deadEnds[0].first->getName() == "2");
        CHECK(deadEnds[0].second->getName() == "4");
    }
}

int main(int argc, char *argv[]) {
    doctest::Context context(argc, argv);
    return context.run();
}

