//
// Created by Mihail Dobroslavski on 30.12.23.
//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../Structure/Graph.h"

TEST_CASE("Graph Test") {
    Graph graph("1");

    SUBCASE("Correct Creation Test") {
        CHECK(graph.getName() == "1");
        REQUIRE(graph.getAdjacencyList().empty());
    }

    SUBCASE("Print Test - Empty") {
        graph.print();
    }

    SUBCASE("Print Test - contains element") {
        Graph graph2("2");
        graph.addEdge(&graph2, 1);
        graph.print();
    }

    SUBCASE("Add Edge + Get Adjacency Test") {
        Graph toGraph("2");
        graph.addEdge(&toGraph, 50.0);

        const auto &adjList = graph.getAdjacencyList();
        REQUIRE(adjList.size() == 1);
        REQUIRE(adjList.begin()->first->getName() == "2");
        REQUIRE(adjList.begin()->second == 50.0);
    }

    SUBCASE("Get Name Test") {
        CHECK(graph.getName() == "1");
    }
}

int main(int argc, char *argv[]) {
    doctest::Context context(argc, argv);
    return context.run();
}