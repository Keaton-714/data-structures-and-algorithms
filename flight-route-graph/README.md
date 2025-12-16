Flight Route Graph (C++)

Overview:
This project is a console-based C++ program that models flight routes between cities using a graph data structure. Cities are represented as vertices, and flights between them are directed edges with an associated distance.

The program allows users to:
    -Build a flight graph from a file
    -Display all available flight routes
    -Find the fastest route (fewest connections) between two cities
    -Find a route that must pass through two required layover cities
    -This project demonstrates the use of graphs, breadth-first search (BFS), file I/O, and STL containers in C++.

Features:
    -Directed graph implemented using an adjacency list
    -Breadth-First Search (BFS) for route discovery
    -Supports maximum layover constraints
    -Supports forced layover routing (A → B → C → D)
    -Reads flight data from an external file
    -Simple, interactive console interface

File Structure:
    -flightMain.cpp   // Program entry point, user interaction, file input
    -flight.h         // Graph class definition
    -flight.cpp       // Graph class implementation
    -flight.txt       // Flight data (required to run)

Input File Format (flight.txt)
Each line in the file should follow this format:
    -CityA, CityB, Distance

Example:
    -New York, Chicago, 790
    -Chicago, Denver, 1000
    -Denver, Los Angeles, 860

    -Routes are directed (CityA → CityB)
    -Distance is stored but not currently used for path weighting

How It Works:
    -Graph Representation
    -Uses an unordered_map<string, list<pair<string,int>>>
    -Each city maps to a list of destination cities and distances
    -BFS Route Search
    -BFS is used to find the route with the fewest number of connections
    -A parent map reconstructs the final path once the destination is found

Route Search Options:
1. Route Search with Maximum Layovers
    -Finds the fastest route between two cities and checks if it satisfies a user-defined layover limit.

2. Route Search with Required Layovers
    -Finds a route from:
    -Origin → Layover1 → Layover2 → Destination
    -Each segment is found independently using BFS and then combined.

Compilation & Execution:
Compile
    -g++ flightMain.cpp flight.cpp -o flight
Run
    -./flight || ./flight.exe
    -Make sure flight.txt is in the same directory as the executable.

Example Usage:
    -Enter origin: New York
    -Enter destination: Los Angeles
    -Enter maximum layovers: 2
    -Route found: New York Chicago Denver Los Angeles

Concepts Demonstrated:
    -Graphs and adjacency lists
    -Breadth-First Search (BFS)
    -STL containers (unordered_map, list, vector, queue)
    -File input/output
    -Path reconstruction using parent tracking
