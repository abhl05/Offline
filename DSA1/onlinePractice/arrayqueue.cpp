#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity
    capacity = initial_capacity;
    front_idx = rear_idx = -1;
    data = new int[capacity];
    if(data == nullptr) {
        cerr << "Memory allocation failed" << endl;
        exit(1);
    }
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
    if((rear_idx + 1) % capacity == front_idx) {
        resize(capacity * 2);
    }
    rear_idx = (rear_idx + 1) % capacity;
    data[rear_idx] = item;
    if(front_idx == -1) front_idx = 0;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the front of the queue
    // TODO: Update front index
    // TODO: Return the dequeued element
    if(empty()) {
        throw runtime_error("Queue is empty, cannot dequeue.");
    }
    int val = data[front_idx];
    if(front_idx == rear_idx) {
        front_idx = rear_idx = -1;
    }
    else {
        front_idx = (front_idx+1)%capacity;
    }
    if(front_idx < rear_idx) {
        if(size() <= capacity/4) {
            resize(capacity/2);
        }
    }
    return val;
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    delete[] data;
    capacity = 2;
    data = new int[capacity];
    front_idx = rear_idx = -1;
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    if(front_idx == -1) return 0;
    else if(rear_idx >= front_idx) return rear_idx - front_idx + 1;
    else return capacity - front_idx + rear_idx + 1;
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
    if(empty()) {
        throw runtime_error("Queue is empty, cannot find front.");
    }
    return data[front_idx];
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
    if(empty()) {
        throw runtime_error("Queue is empty, cannot find back.");
    }
    return data[rear_idx];
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    return rear_idx == -1;
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    int current_size = size();
    string result = "<";
    for (int i = 0; i < current_size; i++) {
        result += to_string(data[(front_idx + i) % capacity]);
        if (i < current_size - 1) {
            result += ", ";
        }
    }
    result += "|";
    return result;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices
    int current_size = size();
    int *temp = new int[new_capacity];
    if(temp == nullptr) {
        cerr << "Memory allocation failed" << endl;
        exit(1);
    }
    for(int i = 0; i < current_size; i++) {
        temp[i] = data[(front_idx + i) % capacity];
    }
    delete[] data;
    data = temp;
    capacity = new_capacity;
    front_idx = 0;
    rear_idx = current_size - 1; 
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}