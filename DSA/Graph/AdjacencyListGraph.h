#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"


class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members
    int node_count;
    LinkedList** adjacencyList;
    int listSize;
    int capacity;

    void resize() {
        if(listSize >= capacity) {
            int newCapacity = capacity*2 > listSize ? capacity*2 : listSize;
            LinkedList** tempList = new LinkedList*[newCapacity];
            if(!tempList) {
                std::cerr << "Memory Allocation Failed.\n";
                exit(0);
            }
            for(int i = 0; i < capacity; i++) {
                tempList[i] = adjacencyList[i];
            }
            for(int i = capacity; i < newCapacity; i++) {
                tempList[i] = nullptr;
            }
            delete[] adjacencyList;
            adjacencyList = tempList;
            capacity = newCapacity;
        }
        if(listSize*4 <= capacity) {
            int newCapacity = capacity/2;
            LinkedList** tempList = new LinkedList*[newCapacity];
            if(!tempList) {
                std::cerr << "Memory Allocation Failed.\n";
                exit(0);
            }
            for(int i = 0; i < newCapacity; i++) {
                tempList[i] = adjacencyList[i];
            }
            delete[] adjacencyList;
            adjacencyList = tempList;
            capacity = newCapacity;
        }
    }

    int bfsShortestPathLength(int start, int end, Queue* q) const {
        if(start == end) return 0;
        int n = listSize;   
        int dist[n];
        for(int i = 0; i < n; i++) dist[i] = -1;
        int parent[n];
        q->enqueue(start);
        parent[start] = -1;
        dist[start] = 0;

        while(!q->empty()) {
            int u = q->dequeue();
            Node* node = adjacencyList[u]->head;
            while(node) {
                if(dist[node->data] == -1) {
                    dist[node->data] = dist[u] + 1;
                    parent[node->data] = u;
                    q->enqueue(node->data);
                    if(node->data == end) return dist[node->data];
                }
                node = node->next;
            }
        }
        return -1;
    }

    void bfsShortestPath(int start, int end, Queue* q) const {
        int n = listSize;
        q->enqueue(start);
        int parent[n];
        int visited[n];
        for(int i = 0; i < n; i++) visited[i] = 0;
        parent[start] = -1;
        visited[start] = 1;

        while(!q->empty()) {
            int u = q->dequeue();
            Node* node = adjacencyList[u]->head;
            while(node) {
                if(!visited[node->data]) {
                    visited[node->data] = 1;
                    parent[node->data] = u;
                    q->enqueue(node->data);
                    
                }
                node = node->next;
            }
        }
        if(visited[end]) {
            int path[listSize];
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
        int n = listSize;
        int visited[n];
        for(int i = 0; i < n; i++) visited[i] = 0;
        q->enqueue(start);
        visited[start] = 1;

        while(!q->empty()) {
            int u = q->dequeue();
            if(u == end) return true;
            Node* node = adjacencyList[u]->head;
            while(node) {
                if(!visited[node->data]) {
                    visited[node->data] = 1;
                    q->enqueue(node->data);
                }
                node = node->next;
            }
        }
        return false;
    }

public:
    AdjacencyListGraph(int size = 10) {
        adjacencyList = new LinkedList*[size];
        if(!adjacencyList) {
            std::cerr << "Memory Allocation Failed.\n";
            exit(0);
        }
        capacity = size;
        listSize = size;
        node_count = 0;
        for(int i = 0; i < listSize; i++) {
            adjacencyList[i] = nullptr;
        }
    }
    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        listSize = v > listSize ? v + 1 : listSize;
        resize();
        if (!adjacencyList[v]) {
            adjacencyList[v] = new LinkedList;
            if(!adjacencyList[v]) {
                std::cerr << "Memory Allocation Failed.\n";
                exit(0);
            }
            node_count++;
        }
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        if(CheckEdge(u, v)) return;
        AddNode(u);
        AddNode(v);
        adjacencyList[v]->append(u);
        adjacencyList[u]->append(v);
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        if(u >= listSize || v >= listSize || !adjacencyList[u] || !adjacencyList[v]) {
            return false;
        }

        Node* node = adjacencyList[u]->head;
        while(node) {
            if(node->data == v) return true;
            node = node->next;
        }
        return false;
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        if(v >= listSize || !adjacencyList[v]) {
            return;
        }
        Node* node = adjacencyList[v]->head;
        int neighbours[listSize];
        int idx = 0;
        while(node) {
            neighbours[idx++] = node->data;
            node = node->next;
        }
        for(int i = 0; i < idx; i++) {
            RemoveEdge(v, neighbours[i]);
        }
        delete adjacencyList[v];
        adjacencyList[v] = nullptr;
        node_count--;
        resize();
    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        if (u >= listSize || v >= listSize || u == v || !adjacencyList[u] || !adjacencyList[v]) {
            return;
        }
        Node* temp = adjacencyList[u]->head, *prev = nullptr;
        while(temp && temp->data != v) {
            prev = temp;
            temp = temp->next;
        }
        if(temp) {
            if(prev) prev->next = temp->next;
            else adjacencyList[u]->head = temp->next;
            temp->next = nullptr;
            delete temp;
        }
        temp = adjacencyList[v]->head;
        prev = nullptr;
        while(temp && temp->data != u) {
            prev = temp;
            temp = temp->next;
        }
        if(temp) {
            if(prev) prev->next = temp->next;
            else adjacencyList[v]->head = temp->next;
            temp->next = nullptr;
            delete temp;
        }
    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        if (u >= listSize || v >= listSize || !adjacencyList[u] || !adjacencyList[v]) return false;
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
        //TODO: Return the list of neighbors.
        if (u < 0 || u >= listSize || !adjacencyList[u]) {
            return LinkedList();
        }
        return *adjacencyList[u];
    }
    ~AdjacencyListGraph() {
        for (int i = 0; i < listSize; ++i) {
            delete adjacencyList[i]; 
        }
        delete[] adjacencyList;
    }
};

#endif // ADJACENCY_LIST_GRAPH_H
