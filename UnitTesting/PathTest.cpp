//
// Created by Mihail Dobroslavski on 30.12.23.
//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../Structure/Path.h"
#include "../Structure/Graph.h"

TEST_CASE("Path Test") {
    SUBCASE("Cost Test") {
        Path path;
        REQUIRE(path.cost == 0.0);

        path.cost = 100.0;
        REQUIRE(path.cost == 100.0);
    }

    SUBCASE("Node Test") {
        Path path;
        Graph graphA("1");
        Graph graphB("2");

        REQUIRE(path.nodes.empty());

        path.nodes.push_back(&graphA);
        path.nodes.push_back(&graphB);

        REQUIRE(path.nodes.size() == 2);
        REQUIRE(path.nodes[0]->getName() == "1");
        REQUIRE(path.nodes[1]->getName() == "2");
    }

    SUBCASE("Print Test - Contains") {
        Path path;
        Graph graphA("1");
        Graph graphB("2");

        path.nodes.push_back(&graphA);
        path.nodes.push_back(&graphB);
        path.cost = 50.0;

        std::ostringstream oss;

        doctest::Context context;
        context.setOption("no-breaks", true);

        auto cout_redirect = std::cout.rdbuf(oss.rdbuf());
        path.print();
        std::cout.rdbuf(cout_redirect);

        std::string expectedOutput = "1 -> 2 ->  length = 50\n";
        REQUIRE(oss.str() == expectedOutput);
    }

    SUBCASE("Print Test - Empty") {
        Path path;
        std::ostringstream oss;

        doctest::Context context;
        context.setOption("no-breaks", true);

        auto cout_redirect = std::cout.rdbuf(oss.rdbuf());
        path.print();
        std::cout.rdbuf(cout_redirect);

        std::string expectedOutput = "No items in path\n";
        REQUIRE(oss.str() == expectedOutput);
    }
}

int main(int argc, char *argv[]) {
    doctest::Context context(argc, argv);
    return context.run();
}