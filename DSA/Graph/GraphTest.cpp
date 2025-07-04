#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GraphADT.h"
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"

// Toggle between implementations
#define USE_ADJACENCY_LIST
// #define USE_ADJACENCY_MATRIX

int main()
{
#ifdef USE_ADJACENCY_LIST
    std::cout << "Using Adjacency List Implementation\n";
    GraphADT* graph = new AdjacencyListGraph();
#elif defined(USE_ADJACENCY_MATRIX)
    std::cout << "Using Adjacency Matrix Implementation\n";
    GraphADT* graph = new AdjacencyMatrixGraph();
#else
    std::cerr << "Please define a graph implementation macro.\n";
    return 1;
#endif

    std::ifstream infile("input.txt");
    freopen("my_output_list.txt", "w", stdout);
    if (!freopen("my_output_list.txt", "w", stdout)) {
        std::cerr << "Failed to open output file\n";
        return 1;
    }
    if (!infile.is_open())
    {
        std::cerr << "Failed to open input.txt\n";
        delete graph;
        return 1;
    }

    // int u, v;
    // while (infile >> u >> v)
    // {
    //     graph->AddEdge(u, v);
    // }
    // std::cout << "Graph loaded from file.\n\n";

    // // Test shortest paths and their lengths
    // int testPairs[][2] = {{1, 10}, {3, 15}, {5, 14}, {2, 8}, {7, 12},{1,12},{2, 11},{6,13}};
    // for (auto& pair : testPairs)
    // {
    //     std::cout << "Shortest path from " << pair[0] << " to " << pair[1] << ":\n";
    //     graph->FindShortestPath(pair[0], pair[1]);
    //     std::cout << "Length: " << graph->FindShortestPathLength(pair[0], pair[1]) << "\n\n";
    // }

    // // Test CheckEdge and RemoveEdge
    // std::cout << "Edge (5,6) exists? " << graph->CheckEdge(5, 6) << "\n";
    // graph->RemoveEdge(5, 6);
    // std::cout << "Edge (5,6) exists after removal? " << graph->CheckEdge(5, 6) << "\n\n";

    // // Test CheckPath (connectivity)
    // int pathTests[][2] = {{1, 15}, {10, 5}, {8, 14}, {1, 100}};
    // for (auto& pair : pathTests)
    // {
    //     std::cout << "Path exists from " << pair[0] << " to " << pair[1] << "? ";
    //     std::cout << (graph->CheckPath(pair[0], pair[1]) ? "Yes" : "No") << "\n";
    // }
    // std::cout << "\n";

    // // Test RemoveNode
    // std::cout << "Removing node 7...\n";
    // graph->RemoveNode(7);
    // std::cout << "Path exists from 1 to 7? " << (graph->CheckPath(1, 7) ? "Yes" : "No") << "\n";
    // std::cout << "Edge (6,7) exists? " << graph->CheckEdge(6, 7) << "\n\n";

    // // Add some edges/nodes dynamically
    // std::cout << "Adding edge (7, 20)...\n";
    // graph->AddEdge(7, 20);
    // std::cout << "Path exists from 7 to 20? " << (graph->CheckPath(7, 20) ? "Yes" : "No") << "\n";

    // // Shortest path after addition
    // graph->FindShortestPath(7, 20);
    // std::cout << "Length: " << graph->FindShortestPathLength(7, 20) << "\n";

    // std::cout << "Neighbors of node 3: ";
    // auto neighbors = graph->GetNeighbors(3);
    // for (int n : neighbors)
    // {
    //     std::cout << n << " ";
    // }
    // std::cout << "\n";
    // Additional test cases to add to your main() function
std::cout << "\n===== Positive Node Test Cases =====\n";

// Test 1: Chain connectivity
std::cout << "\nTest 1: Chain connectivity\n";
graph->AddEdge(1, 2);
graph->AddEdge(2, 3);
graph->AddEdge(3, 4);
std::cout << "Path 1->4 exists? " << graph->CheckPath(1, 4) << " (Expected: 1)\n";
std::cout << "Path length 1->4: " << graph->FindShortestPathLength(1, 4) << " (Expected: 3)\n";
graph->FindShortestPath(1, 4); // Expected: 1 2 3 4

// Test 2: Star topology
std::cout << "\nTest 2: Star topology\n";
graph->AddEdge(10, 11);
graph->AddEdge(10, 12);
graph->AddEdge(10, 13);
std::cout << "Path 11->13 exists? " << graph->CheckPath(11, 13) << " (Expected: 1)\n";
std::cout << "Path length 11->13: " << graph->FindShortestPathLength(11, 13) << " (Expected: 2)\n";
graph->FindShortestPath(11, 13); // Expected: 11 10 13

// Test 3: Disconnected components
std::cout << "\nTest 3: Disconnected components\n";
graph->AddEdge(20, 21);
graph->AddEdge(22, 23);
std::cout << "Path 1->20 exists? " << graph->CheckPath(1, 20) << " (Expected: 0)\n";
std::cout << "Path 20->21 exists? " << graph->CheckPath(20, 21) << " (Expected: 1)\n";

// Test 4: Node removal
std::cout << "\nTest 4: Node removal\n";
graph->RemoveNode(10);
std::cout << "Path 11->13 exists after removal? " << graph->CheckPath(11, 13) << " (Expected: 0)\n";
std::cout << "Edge 10->11 exists? " << graph->CheckEdge(10, 11) << " (Expected: 0)\n";

// Test 5: Reconnect components
std::cout << "\nTest 5: Reconnect components\n";
graph->AddEdge(4, 20);
std::cout << "Path 1->21 exists after reconnect? " << graph->CheckPath(1, 21) << " (Expected: 1)\n";
std::cout << "Path length 1->21: " << graph->FindShortestPathLength(1, 21) << " (Expected: 5)\n";

// Test 6: Large node numbers
std::cout << "\nTest 6: Large node numbers\n";
graph->AddEdge(1000, 1001);
std::cout << "Edge 1000->1001 exists? " << graph->CheckEdge(1000, 1001) << " (Expected: 1)\n";
std::cout << "Path length 1000->1001: " << graph->FindShortestPathLength(1000, 1001) << " (Expected: 1)\n";

// Test 7: Self-connection
std::cout << "\nTest 7: Self-connection\n";
std::cout << "Path 5->5 exists? " << graph->CheckPath(5, 5) << " (Expected: 1)\n";
std::cout << "Path length 5->5: " << graph->FindShortestPathLength(5, 5) << " (Expected: 0)\n";

    delete graph;
    return 0;
}
