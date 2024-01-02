//
// Created by Mihail Dobroslavski on 30.12.23.
//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../Interfaces/TerminalProgram.h"
#include "../Structure/GraphContainer.h"
#include "../Structure/Graph.h"

TEST_CASE("TerminalProgram Test") {
    auto *container = new GraphContainer();
    container->addGraph("CityA");
    Graph *cityA = container->getGraph("CityA");

    container->addGraph("CityB");
    Graph *cityB = container->getGraph("CityB");

    Graph *start = cityA;

    TerminalProgram terminalProgram = TerminalProgram(container, start);

    SUBCASE("Constructor Test") {
        REQUIRE(terminalProgram.getMap() == container);
        REQUIRE(terminalProgram.getCurrent() == start);
        REQUIRE(terminalProgram.getClosedJunctions().empty());
    }

    SUBCASE("Location Test") {
        std::stringstream buffer;
        std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
        terminalProgram.handleLocationCommand();
        std::cout.rdbuf(oldCout);
        REQUIRE(buffer.str() == "Current location: CityA\n");
    }

    // Add more SUBCASEs for other test scenarios

    SUBCASE("Close Test") {

        std::stringstream outputBuffer;
        std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());

        // Close CityB
        std::stringstream input("CityB");
        terminalProgram.handleCloseCommand(input);

        // Reset cout to the original buffer
        std::cout.rdbuf(oldCoutBuffer);

        // Verify the output
        std::string expectedOutput = "Closed location: CityB\n";
        REQUIRE(outputBuffer.str() == expectedOutput);
        REQUIRE(terminalProgram.getClosedJunctions().count(container->getGraph("CityB")) == 1);
    }

    SUBCASE("Open Test") {

        // Redirect cout to capture the output
        std::stringstream outputBuffer;
        std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());

        // Close CityB first
        terminalProgram.getClosedJunctions().insert(container->getGraph("CityB"));

        // Open CityB
        std::stringstream input("CityB");
        terminalProgram.handleOpenCommand(input);

        // Reset cout to the original buffer
        std::cout.rdbuf(oldCoutBuffer);

        // Verify the output
        std::string expectedOutput = "Opened location: CityB\n";
        REQUIRE(outputBuffer.str() == expectedOutput);
        REQUIRE(terminalProgram.getClosedJunctions().count(container->getGraph("CityB")) == 0);
    }

    SUBCASE("Closed (getClosed) Test") {
        container->addGraph("CityC");
        Graph *cityC = container->getGraph("CityC");

        std::stringstream input("CityB CityC");
        terminalProgram.handleCloseCommand(input);
        terminalProgram.handleCloseCommand(input);

        std::stringstream outputBuffer;
        std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());

        terminalProgram.handleClosedCommand();

        std::cout.rdbuf(oldCoutBuffer);

        std::string expectedOutput1 = "Closed locations: CityB CityC \n";
        std::string expectedOutput2 = "Closed locations: CityC CityB \n";

        REQUIRE((outputBuffer.str() == expectedOutput1 || outputBuffer.str() == expectedOutput2));
    }
}


int main(int argc, char *argv[]) {
    doctest::Context context(argc, argv);
    return context.run();
}
