// GraphADT.h
#ifndef GRAPH_ADT_H
#define GRAPH_ADT_H
#include "queue.h"
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {};
};

class GraphADT {
public:
class LinkedList {
    public:
        int size;
        Node* head;
        Node* tail;
        LinkedList() {
            size = 0;
            head = nullptr;
            tail = nullptr;
        }

        void append(int data) {
            Node* newNode = new Node(data);
            if(!head) {
                head = newNode;
                tail = newNode;
                tail->next = nullptr;
            }
            else {
                tail->next = newNode;
                tail = newNode;
                tail->next = nullptr;
            }
            size++;
        }

        class Iterator {
            Node* current;
        public:
            Iterator(Node* node) : current(node) {}

            int& operator*() const {
                return current->data;
            }
            Iterator& operator++() {
                if(current) current = current->next;
                return *this;
            }
            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }
        };

        Iterator begin() {
            return Iterator(head);
        }
        Iterator end() {
            return Iterator(nullptr);
        }

        LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
            for (Node* curr = other.head; curr; curr = curr->next) {
                append(curr->data);
            }
        }

        bool empty() { 
            return size == 0; 
        }

        int getSize() { 
            return size; 
        } 
        
        LinkedList& operator=(const LinkedList& other) {
            if (this != &other) {
                Node* curr = head;
                while(curr) {
                    Node* next = curr->next;
                    delete curr;
                    curr = next;
                }
                tail = nullptr;
                size = 0;
                for (Node* curr = other.head; curr; curr = curr->next) {
                    append(curr->data);
                }
            }
            return *this;
        }

        ~LinkedList() {
            Node* curr = head;
            while(curr) {
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
            tail = nullptr;
            size = 0;
        }
    };
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~GraphADT() {}

    // Add a new node v to the graph
    virtual void AddNode(int v) = 0;

    // Add a new edge (u, v) in the graph
    virtual void AddEdge(int u, int v) = 0;

    // Check whether there is an edge (u, v) between node u and node v
    virtual bool CheckEdge(int u, int v) const = 0;

    // Remove node v from the graph
    virtual void RemoveNode(int v) = 0;

    // Remove an edge (u, v) from the graph
    virtual void RemoveEdge(int u, int v) = 0;

    // Check whether a path exists between node u and node v
    virtual bool CheckPath(int u, int v) const = 0;

    // Find the shortest path between node u and node v
    virtual void FindShortestPath(int u, int v) const = 0;

    // Find the length of the shortest path between node u and node v
    virtual int FindShortestPathLength(int u, int v) const = 0;

    // Find the neighbors of the node u. LinkedList is the data type of your own list.
    virtual LinkedList GetNeighbors(int u) const = 0;

};

#endif // GRAPH_ADT_H
