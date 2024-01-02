//
// Created by Mihail Dobroslavski on 30.12.23.
//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../Structure/GraphContainer.h"

TEST_CASE("GraphContainer Test") {
    GraphContainer graphContainer;

    SUBCASE("Parse File Test") {
        const std::string filePath = "InLineDatabase/test_input.txt";
        graphContainer.parseFile(filePath);

        REQUIRE(graphContainer.containsKey("1"));
        REQUIRE(graphContainer.containsKey("2"));

        Graph *graphA = graphContainer.getGraph("1");
        Graph *graphB = graphContainer.getGraph("2");

        REQUIRE(graphA != nullptr);
        REQUIRE(graphB != nullptr);

        const auto &adjListA = graphA->getAdjacencyList();
        REQUIRE(adjListA.size() == 1);
        REQUIRE(adjListA.begin()->first->getName() == "2");
        REQUIRE(adjListA.begin()->second == 50.0);
    }

    SUBCASE("File Open Error Test") {
        const std::string filePath = "/nonexistent_path/nonexistent_file.txt";
        REQUIRE_THROWS(graphContainer.parseFile(filePath));
    }

    SUBCASE("Contains a Key Test") {
        REQUIRE_FALSE(graphContainer.containsKey("NonExistent"));
    }

    SUBCASE("Add Graph Test") {
        graphContainer.addGraph("1");
        REQUIRE(graphContainer.containsKey("1"));
        REQUIRE(graphContainer.getGraph("1") != nullptr);
    }

    SUBCASE("Get Graph Test") {
        REQUIRE(graphContainer.getGraph("NonExistent") == nullptr);
    }

    SUBCASE("Get Graphs Test") {
        const auto &graphs = graphContainer.getGraphs();
        REQUIRE(graphs.size() == 0);

        graphContainer.addGraph("1");
        graphContainer.addGraph("2");

        const auto &newGraphs = graphContainer.getGraphs();
        REQUIRE(newGraphs.size() == 2);
        REQUIRE(newGraphs.find("1") != newGraphs.end());
        REQUIRE(newGraphs.find("2") != newGraphs.end());
    }

    SUBCASE("Add Road Test") {
        graphContainer.addRoad("1", "2", 50.0);

        REQUIRE(graphContainer.containsKey("1"));
        REQUIRE(graphContainer.containsKey("2"));

        Graph *graphA = graphContainer.getGraph("1");
        Graph *graphB = graphContainer.getGraph("2");

        REQUIRE(graphA != nullptr);
        REQUIRE(graphB != nullptr);

        const auto &adjListA = graphA->getAdjacencyList();
        REQUIRE(adjListA.size() == 1);
        REQUIRE(adjListA.begin()->first->getName() == "2");
        REQUIRE(adjListA.begin()->second == 50.0);
    }

    SUBCASE("Print Test") {
        graphContainer.addGraph("1");
        graphContainer.print();
    }
}

int main(int argc, char *argv[]) {
    doctest::Context context(argc, argv);
    return context.run();
}