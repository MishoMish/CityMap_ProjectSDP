//
// Created by Mihail Dobroslavski on 30.12.23.
//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../Structure/Graph.h"

TEST_CASE("Graph Test") {
    Graph graph("CityA");

    SUBCASE("Correct Creation Test") {
        CHECK(graph.getName() == "CityA");
        REQUIRE(graph.getAdjacencyList().empty());
    }

    SUBCASE("Print Test - Empty") {
        graph.print();
    }

    SUBCASE("Print Test - contains element") {
        Graph graph2("CityB");
        graph.addEdge(&graph2, 1);
        graph.print();
    }

    SUBCASE("Add Edge + Get Adjacency Test") {
        Graph toGraph("CityB");
        graph.addEdge(&toGraph, 50.0);

        const auto &adjList = graph.getAdjacencyList();
        REQUIRE(adjList.size() == 1);
        REQUIRE(adjList.begin()->first->getName() == "CityB");
        REQUIRE(adjList.begin()->second == 50.0);
    }

    SUBCASE("Get Name Test") {
        CHECK(graph.getName() == "CityA");
    }
}

int main(int argc, char *argv[]) {
    doctest::Context context(argc, argv);
    return context.run();
}