#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H
#include "GraphADT.h"
#include <iostream>

class AdjacencyMatrixGraph : public GraphADT
{
private:
    //TODO: Consider necessary private members as per your discretion
    int node_count;
    int matrix_size;
    int max_capacity;
    int temp_matrixsize;
    int* nodeList;
    int** adjacencyMatrix;

    void resizeMatrix()
    {
        //TODO: you need to resize your matrix when you will less data or more data
        if(temp_matrixsize >= max_capacity) {
            max_capacity = 2*temp_matrixsize;
            int** tempMatrix = new int*[max_capacity];
            if(!tempMatrix) {
                std::cerr << "Memory Allocation Failed.\n";
                exit(0);
            }
            for(int i = 0; i < max_capacity; i++) {
                tempMatrix[i] = new int[max_capacity];
                if(!tempMatrix[i]) {
                    std::cerr << "Memory Allocation Failed.\n";
                    exit(0);
                }
            }
            for(int i = 0; i < max_capacity; i++) {
                for(int j = 0; j < max_capacity; j++) {
                    if(i < matrix_size && j < matrix_size) {
                        tempMatrix[i][j] = adjacencyMatrix[i][j];
                    } else {
                        tempMatrix[i][j] = 0;
                    }
                }
            }
            for(int i = 0; i < matrix_size; i++) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;
            adjacencyMatrix = tempMatrix;
            int* tempNodeList = new int[max_capacity];
            if(!tempNodeList) {
                std::cerr << "Memory Allocation Failed.\n";
                exit(0);
            }
            for(int i = 0; i < max_capacity; i++) {
                if(i < matrix_size) {
                    tempNodeList[i] = nodeList[i];
                } else {
                    tempNodeList[i] = 0;
                }
            }
            delete[] nodeList;
            nodeList = tempNodeList;
        }
    }

    int bfsShortestPathLength(int start, int end, Queue* q) const {
        if(start == end) return 0;
        int n = matrix_size;    
        int dist[n];
        for(int i = 0; i < n; i++) dist[i] = -1;
        int parent[n];
        q->enqueue(start);
        parent[start] = -1;
        dist[start] = 0;

        while(!q->empty()) {
            int u = q->dequeue();
            for(int i = 0; i < n; i++) {
                if(adjacencyMatrix[u][i] == 1 && dist[i] == -1) {
                    dist[i] = dist[u] + 1;
                    parent[i] = u;
                    q->enqueue(i);
                    if(i == end) return dist[i];
                }
            }
        }
        return -1;
    }

    void bfsShortestPath(int start, int end, Queue* q) const {
        int n = matrix_size;
        q->enqueue(start);
        int parent[n];
        int visited[n];
        for(int i = 0; i < n; i++) visited[i] = 0;
        parent[start] = -1;
        visited[start] = 1;

        while(!q->empty()) {
            int u = q->dequeue();
            for(int i = 0; i < n; i++) {
                if(adjacencyMatrix[u][i] == 1 && !visited[i]) {
                    visited[i] = 1;
                    parent[i] = u;
                    q->enqueue(i);
                }
            }
        }
        if(visited[end]) {
            int path[matrix_size];
            int idx = 0;
            for(int i = end; i != -1; i = parent[i]) {
                path[idx++] = i;
            }
            cout << "Shortest path: ";
            for(int i = idx-1; i >= 0; i--) {
                cout << path[i] << " ";
            }
        }
        else cout << "Unreachable";
        cout << "\n";
        return;
    }

    bool bfsCheckPath(int start, int end, Queue* q) const {
        if(start == end) return true;
        int n = matrix_size;
        int visited[n];
        for(int i = 0; i < n; i++) visited[i] = 0;
        q->enqueue(start);
        visited[start] = 1;

        while(!q->empty()) {
            int u = q->dequeue();
            if(u == end) return true;
            for(int i = 0; i < n; i++) {
                if(adjacencyMatrix[u][i] == 1 && !visited[i]) {
                    visited[i] = 1;
                    q->enqueue(i);
                }
            }
        }
        return false;
    }

public:
    AdjacencyMatrixGraph(int size = 100) {
        node_count = 0;
        matrix_size = max_capacity = size;
        adjacencyMatrix = new int*[max_capacity];
        if(!adjacencyMatrix) {
            std::cerr << "Memory Allocation Failed.\n";
            exit(0);
        }
        for(int i = 0; i < max_capacity; i++) {
            adjacencyMatrix[i] = new int[max_capacity];
            if(!adjacencyMatrix[i]) {
                std::cerr << "Memory Allocation Failed.\n";
                exit(0);
            }
        }
        for(int i = 0; i < max_capacity; i++) {
            for(int j = 0; j < max_capacity; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
        nodeList = new int[max_capacity];
        if(!nodeList) {
            std::cerr << "Memory Allocation Failed.\n";
            exit(0);
        }
        for(int i = 0; i < max_capacity; i++) {
            nodeList[i] = 0; 
        }
    }
    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        temp_matrixsize = v > matrix_size ? v + 1 : matrix_size;
        resizeMatrix();
        matrix_size = temp_matrixsize;
        nodeList[v] = 1;
        node_count++;
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        AddNode(u);
        AddNode(v);
        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1;
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        if(nodeList[u] && nodeList[v]) return adjacencyMatrix[u][v];
        return false;
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        if (v < 0 || v >= matrix_size || nodeList[v] == 0) return;
        nodeList[v] = 0;
        node_count--;
        for (int i = 0; i < matrix_size; ++i) {
            adjacencyMatrix[i][v] = 0;
            adjacencyMatrix[v][i] = 0;
        }
    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        if(u < matrix_size && v < matrix_size && nodeList[u] && nodeList[v]) {
            adjacencyMatrix[u][v] = 0;
            adjacencyMatrix[v][u] = 0;
        }
    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        if(u > matrix_size || v > matrix_size || !nodeList[u] || !nodeList[v]) return false;
        Queue* q = new ArrayQueue();
        if(!q) {
            std::cerr << "Memory Allocation Failed.\n";
            exit(0);
        }
        bool pathExists = bfsCheckPath(u, v, q);
        delete q;
        return pathExists;
    }

    void FindShortestPath(int u, int v) const override
    {
        //TODO: Find the shortest path between the nodes u and v and print it.
        Queue* q = new ArrayQueue();
        if(!q) {
            std::cerr << "Memory Allocation Failed.\n";
            exit(0);
        }
        bfsShortestPath(u, v, q);
        delete q;
    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        Queue* q = new ArrayQueue();
        if(!q) {
            std::cerr << "Memory Allocation Failed.\n";
            exit(0);
        }
        int path = bfsShortestPathLength(u, v, q);
        delete q;
        return path;
    }
    LinkedList GetNeighbors(int u) const override
    {
        //TODO return a list of neighbors of node u
        LinkedList neighbours;
        for(int i = 0; i < matrix_size; i++) {
            if(adjacencyMatrix[u][i] == 1) neighbours.append(i);
        }
        return neighbours;
    }

    ~AdjacencyMatrixGraph() {
        for(int i = 0; i < matrix_size; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
        delete[] nodeList;
    }

};

#endif // ADJACENCY_MATRIX_GRAPH_H
