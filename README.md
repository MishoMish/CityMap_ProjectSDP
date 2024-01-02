# City Map Project Documentation

## Table of Contents

- [Introduction](#introduction)
   - [Project Overview](#project-overview)
   - [Project Purpose](#project-purpose)
   - [Benefits](#benefits)
   - [Development Timeline](#development-timeline)

- [Project Design](#project-design)
   - [Folder and Class Structure](#folder-and-class-structure)
   - [Key Classes and Functions](#key-classes-and-functions)

- [Upgrade Paths](#upgrade-paths)
   - [User Interface Improvement](#user-interface-improvement)
   - [Real-Time Data Integration](#real-time-data-integration)
   - [Advanced Algorithms](#advanced-algorithms)
   - [Geospatial Integration](#geospatial-integration)
   - [Mobile Application](#mobile-application)

- [References](#references)

---

## 1. Introduction <a name="introduction"></a>

### 1.1 Project Overview <a name="project-overview"></a>

Welcome to the City Map Project, a comprehensive tool designed to manage and analyze city infrastructure through graph-based representations. This project aims to provide a robust framework for visualizing, querying, and analyzing city maps, facilitating various applications such as route planning, path analysis, and connectivity assessments.

### 1.2 Project Purpose <a name="project-purpose"></a>

The City Map Project is developed with the following key objectives:

- **Graph-Based Representation:** Utilizes graph theory to model city infrastructure, allowing for an efficient representation of junctions, roads, and connections.
- **Route Planning:** Enables users to plan and analyze routes between different junctions, considering factors like distance, cost, and connectivity.
- **Connectivity Analysis:** Offers tools for analyzing the connectivity of the city map, identifying dead ends, checking for Hamiltonian paths, and ensuring accessibility to all areas.
- **Graph Visualization:** Integrates Graphviz to generate visual representations of the city map, aiding in the interpretation and understanding of the spatial relationships within the infrastructure.

### 1.3 Benefits <a name="benefits"></a>

By using the City Map Project, users can derive the following benefits:

- **Efficient Route Planning:** Plan optimal routes between different locations within the city, considering various constraints and preferences.
- **Infrastructure Analysis:** Gain insights into the connectivity and structure of the city map, identifying critical junctions, dead ends, and potential areas for improvement.
- **Graph Visualization:** Visualize the city map in an intuitive graph format, making it easier to interpret and communicate complex infrastructure relationships.
- **Enhanced Decision-Making:** Support urban planning decisions by leveraging analytical tools that assess the impact of changes to city infrastructure.

### 1.4 Development Timeline <a name="development-timeline"></a>

The City Map Project has been developed over a period of 4-5 days, focusing on code quality, functionality, and ease of use. The development process involved:

- **Requirements Gathering:** Understanding the project requirements, including the need for route planning, connectivity analysis, and graph visualization.
- **Design and Architecture:** Defining the class structure, interfaces, and relationships to create a modular and scalable codebase.
- **Implementation:** Writing the code for each class, adhering to best practices, and ensuring proper documentation for clarity and maintainability.
- **Testing:** Conducting thorough testing to identify and rectify any bugs or issues, ensuring the reliability and stability of the project.
- **Documentation:** Creating comprehensive documentation to aid users and developers in understanding the project structure, functionality, and usage.

---

## 2. Project Design <a name="project-design"></a>

### 2.1 Folder and Class Structure <a name="folder-and-class-structure"></a>

The City Map Project is organized into several key folders, each serving a distinct purpose in structuring the codebase. The "Interfaces" folder encapsulates classes responsible for user interaction, featuring the GraphvizController for graph visualization and TerminalProgram for terminal-based program execution. The "Structure" folder houses essential graph-related components, including the Graph, GraphContainer, and Path classes. Additionally, the "TaskFunctions" folder contains the RouteChecker class, providing static methods for various route and connectivity analyses. The main program, residing in the root directory, utilizes these components to create an interactive tool for city map exploration. The project is thoughtfully structured to enhance modularity, code readability, and maintainability.

### 2.2 Key Classes and Functions <a name="key-classes-and-functions"></a>

#### 2.2.1 GraphvizController <a name="graphviz-controller"></a>

The `GraphvizController` class is responsible for generating Dot files representing the city map and running Graphviz to produce visual representations.

##### Methods:

- `generateDotFile(GraphContainer *graphContainer, Graph *current, std::unordered_set<Graph *> closed)`: Generates a Dot file based on the given parameters.
- `runGraphvizAndOpenImage()`: Executes Graphviz and opens the generated image.

#### 2.2.2 TerminalProgram <a name="terminal-program"></a>

The `TerminalProgram` class handles the execution of the program in a terminal-based environment.

##### Constructor:

- `TerminalProgram(GraphContainer *map, Graph *start)`: Initializes the program with a map and starting graph.

##### Methods:

- `printIntroduction()`: Prints the introduction message.
- `printHelp()`: Prints the help message.
- `printHelp2()`: Prints the help2 message.
- `handleLocationCommand()`: Handles the location command.
- ... (and so on for other methods)

#### 2.2.3 Graph <a name="graph"></a>

The `Graph` class represents a junction in the city map.

##### Constructor:

- `Graph(std::string)`: Initializes the graph with a name.

##### Methods:

- `print()`: Prints information about the graph.
- `addEdge(Graph *, double)`: Adds an edge to the graph.
- `getAdjacencyList()`: Returns the adjacency list.
- `getName()`: Returns the name of the graph.

#### 2.2.4 GraphContainer <a name="graph-container"></a>

The `GraphContainer` class holds and manages multiple graphs in the city map.

##### Methods:

- `parseFile(const std::string &)`: Parses a file to populate the city map.
- `containsKey(const std::string &)`: Checks if a graph with a given key exists.
- `addGraph(const std::string &)`: Adds a graph to the map.
- `getGraph(const std::string &)`: Returns a graph based on the key.
- `getGraphs()`: Returns all graphs in the container.
- `addRoad(const std::string &, const std::string &, double)`: Adds a road between two graphs.
- `print()`: Prints information about the graphs.

#### 2.2.5 Path <a name="path"></a>

The `Path` class represents a path between junctions in the city map.

##### Methods:

- `print()`: Prints information about the path.

#### 2.2.6 RouteChecker <a name="route-checker"></a>

The `RouteChecker` class provides static methods for various route and connectivity analyses.

##### Methods:

- `exists(Graph *, Graph *)`: Checks if a path exists between two graphs.
- `getPaths(Graph *, Graph *, const std::unordered_set<Graph *> &)`: Gets paths between two graphs considering closed intersections.
- `canReturnToStart(Graph *)`: Checks if it's possible to return to the starting graph.
- `hasHamiltonianPath(GraphContainer *)`: Finds a Hamiltonian path in the city map.
- `canReachAllNodes(GraphContainer *, Graph *)`: Checks if it's possible to reach all nodes from a given starting graph.
- `findAllDeadEnded(GraphContainer *)`: Finds all dead-ended streets in the city map.

## 2.3 Project Design (Continued) <a name="project-design-continued"></a>

#### 2.3.1 Object-Oriented Design <a name="object-oriented-design"></a>

The City Map Project adopts an object-oriented design (OOD) approach to ensure modularity, flexibility, and maintainability. Key principles include encapsulation, inheritance, and polymorphism.

## 3. Implementation and Testing <a name="implementation-and-testing"></a>

### 3.1 Implementation of Classes <a name="implementation-of-classes"></a>

The implementation of each class adheres to best coding practices, promoting readability, efficiency, and maintainability. Significant aspects of the implementation are outlined below.

#### 3.1.1 GraphvizController <a name="implementation-of-graphviz-controller"></a>

- The `generateDotFile` method constructs a Dot file by utilizing information from the provided `GraphContainer`, current graph, and a set of closed intersections.
- The `runGraphvizAndOpenImage` method executes the Graphviz tool to generate a visual representation of the city map.

#### 3.1.2 TerminalProgram <a name="implementation-of-terminal-program"></a>

- The constructor initializes the program with a map and starting graph, facilitating seamless execution.
- Methods like `handleLocationCommand`, `handleChangeCommand`, `handleNeighboursCommand`, and others handle various user commands, ensuring interactive program behavior.

#### 3.1.3 Graph <a name="implementation-of-graph"></a>

- The `print` method outputs relevant information about the graph, aiding in debugging and user understanding.
- The `addEdge` method allows the addition of edges between graphs, contributing to the overall connectivity.

#### 3.1.4 GraphContainer <a name="implementation-of-graph-container"></a>

- The `parseFile` method reads a file to populate the city map with graphs and roads, promoting ease of data input.
- The `addRoad` method facilitates the addition of roads between specified graphs, enhancing the overall connectivity.

#### 3.1.5 Path <a name="implementation-of-path"></a>

- The `print` method displays details about the path, contributing to user understanding and debugging.

#### 3.1.6 RouteChecker <a name="implementation-of-route-checker"></a>

- Static methods like `exists`, `getPaths`, `canReturnToStart`, `hasHamiltonianPath`, `canReachAllNodes`, and `findAllDeadEnded` implement various route and connectivity analyses.

### 3.2 Memory Management, Algorithms, and Optimizations <a name="memory-management-algorithms-and-optimizations"></a>

The project incorporates efficient memory management practices, algorithms for various functionalities, and optimizations to ensure optimal performance. The choice of data structures and algorithms is aligned with the principles of scalability and code efficiency.

### 3.3 Test Scenario Planning and Execution <a name="test-scenario-planning-and-execution"></a>

Thorough testing has been conducted to identify and rectify any bugs or issues. Test scenarios cover a range of functionalities, ensuring the reliability and stability of the project. This includes positive and negative test cases for route planning, connectivity analysis, and graph visualization.

## 4. Conclusion <a name="conclusion"></a>

### 4.1 Summary of Initial Goals <a name="summary-of-initial-goals"></a>

The City Map Project has successfully achieved its initial goals, providing a versatile tool for city map exploration, route planning, and connectivity analysis. The use of graph-based representations and efficient algorithms contributes to the project's success in meeting its objectives.

### 4.2 Directions for Future Development and Improvement <a name="directions-for-future-development-and-improvement"></a>

As the City Map Project evolves, several paths for improvement are considered:

- **User Interface Improvement:** Develop a graphical user interface (GUI) for a more user-friendly experience.
- **Real-Time Data Integration:** Integrate real-time data sources for dynamic updates to the city map.
- **Advanced Algorithms:** Implement advanced graph algorithms for more sophisticated analyses.
- **Geospatial Integration:** Incorporate geospatial data for precise distance calculations and spatial analysis.
- **Mobile Application:** Develop a mobile application for on-the-go city map exploration.

## 5. References <a name="references"></a>

All references to external sources, literature, and frameworks used during the development of the City Map Project are listed here.

---

For the detailed code structure, class methods, and their functionalities, please refer to the source code in the respective folders and files within the project repository.

For a more detailed overview of the classes and their methods, the source code comments and documentation within the codebase serve as comprehensive guides.
