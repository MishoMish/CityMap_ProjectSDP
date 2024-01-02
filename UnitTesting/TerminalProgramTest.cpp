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
    container->addGraph("1");
    Graph *cityA = container->getGraph("1");

    container->addGraph("2");
    Graph *cityB = container->getGraph("2");

    Graph *start = cityA;

    TerminalProgram terminalProgram = TerminalProgram(container, start);

    SUBCASE("Constructor Test") {
        REQUIRE(terminalProgram.getMap() == container);
        REQUIRE(terminalProgram.getCurrent() == start);
        REQUIRE(terminalProgram.getClosedJunctions().empty());
    }

    SUBCASE("All Print Test") {
        (terminalProgram.printIntroduction());
        CHECK_NOTHROW(terminalProgram.printIntroduction());
        CHECK_NOTHROW(terminalProgram.printHelp());
        CHECK_NOTHROW(terminalProgram.printHelp2());
        CHECK_THROWS(terminalProgram.printHelpCommand("NoNameFolder/NoNameFile.txt"));
    }


    SUBCASE("Location Test") {
        std::stringstream buffer;
        std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
        terminalProgram.handleLocationCommand();
        std::cout.rdbuf(oldCout);
        REQUIRE(buffer.str() == "Current location: 1\n");
    }

    SUBCASE("Test handleChangeCommand") {
        SUBCASE("Valid location") {
            std::stringstream ss("1");
            terminalProgram.handleChangeCommand(ss);
        }

        SUBCASE("Invalid location") {
            std::stringstream ss("InvalidLocation");
            terminalProgram.handleChangeCommand(ss);
        }
    }

    SUBCASE("Close Test") {
        SUBCASE("Close Existing") {
            std::stringstream outputBuffer;
            std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());

            std::stringstream input("2");
            terminalProgram.handleCloseCommand(input);

            std::cout.rdbuf(oldCoutBuffer);

            std::string expectedOutput = "Closed location: 2\n";
            REQUIRE(outputBuffer.str() == expectedOutput);
            REQUIRE(terminalProgram.getClosedJunctions().count(container->getGraph("2")) == 1);
        }

        SUBCASE("Close non-Existing") {
            std::stringstream outputBuffer;
            std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());

            std::stringstream input("1234567");
            terminalProgram.handleCloseCommand(input);

            std::cout.rdbuf(oldCoutBuffer);

            std::string expectedOutput = "Invalid location: 1234567\n";
            REQUIRE(outputBuffer.str() == expectedOutput);
            REQUIRE(terminalProgram.getClosedJunctions().size() == 0);
        }

    }
    SUBCASE("Open Test") {
        SUBCASE("Open Existing") {
            std::stringstream outputBuffer;
            std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());

            terminalProgram.getClosedJunctions().insert(container->getGraph("2"));

            std::stringstream input("2");
            terminalProgram.handleOpenCommand(input);

            std::cout.rdbuf(oldCoutBuffer);

            std::string expectedOutput = "Opened location: 2\n";
            REQUIRE(outputBuffer.str() == expectedOutput);
            REQUIRE(terminalProgram.getClosedJunctions().count(container->getGraph("2")) == 0);
        }
        SUBCASE("Open non-Existing") {
            std::stringstream outputBuffer;
            std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());

            std::stringstream input("1234567");
            terminalProgram.handleCloseCommand(input);

            std::cout.rdbuf(oldCoutBuffer);

            std::string expectedOutput = "Invalid location: 1234567\n";
            REQUIRE(outputBuffer.str() == expectedOutput);
            REQUIRE(terminalProgram.getClosedJunctions().size() == 0);
        }
    }

    SUBCASE("Closed (getClosed) Test") {
        container->addGraph("3");
        Graph *cityC = container->getGraph("CityC");

        std::stringstream input("2 3");
        terminalProgram.handleCloseCommand(input);
        terminalProgram.handleCloseCommand(input);

        std::stringstream outputBuffer;
        std::streambuf *oldCoutBuffer = std::cout.rdbuf(outputBuffer.rdbuf());

        terminalProgram.handleClosedCommand();

        std::cout.rdbuf(oldCoutBuffer);

        std::string expectedOutput1 = "Closed locations: 2 3 \n";
        std::string expectedOutput2 = "Closed locations: 3 2 \n";

        REQUIRE((outputBuffer.str() == expectedOutput1 || outputBuffer.str() == expectedOutput2));
    }
}


int main(int argc, char *argv[]) {
    doctest::Context context(argc, argv);
    return context.run();
}
