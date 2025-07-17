#include <iostream>
#include <vector>
#include<cstdio>
using namespace std;

class Heap {
    int max_capacity;
    int heap_size;
    int* heap_array;
    void resize() {
        if(heap_size >= max_capacity) {
            max_capacity*=2;
            int* temp = new int[max_capacity];
            if (!temp) {
                std::cerr << "Memory allocation failed.\n";
                exit(1); 
            }
            for(int i = 0; i < heap_size; i++) {
                temp[i] = heap_array[i];
            }
            delete[] heap_array;
            heap_array = temp;
        }
        if(heap_size*4 <= max_capacity) {
            max_capacity/=2;
            int* temp = new int[max_capacity];
            if (!temp) {
                std::cerr << "Memory allocation failed.\n";
                exit(1); 
            }
            for(int i = 0; i < heap_size; i++) {
                temp[i] = heap_array[i];
            }
            delete[] heap_array;
            heap_array = temp;
        }
    }

    void heapifyUp(int idx) {
        if(idx < 0) return;
        int curidx = idx;
        int parentidx = (curidx-1)/2;
        if(parentidx >= 0 && heap_array[parentidx] < heap_array[curidx]) {
            int temp = heap_array[parentidx];
            heap_array[parentidx] = heap_array[curidx];
            heap_array[curidx] = temp;
            heapifyUp(parentidx);
        }
        return;
    }

    void heapifyDown(int idx) {
        if(idx >= heap_size) return;
        int curidx = idx;
        int leftchild = 2*curidx + 1;
        int rightchild = 2*curidx + 2;
        int maxidx = curidx;
        if(leftchild < heap_size && heap_array[leftchild] > heap_array[maxidx]) {
            maxidx = leftchild;
        }
        if(rightchild < heap_size && heap_array[rightchild] > heap_array[maxidx]) {
            maxidx = rightchild;
        }
        if(maxidx != curidx) {
            int temp = heap_array[maxidx];
            heap_array[maxidx] = heap_array[curidx];
            heap_array[curidx] = temp;
            heapifyDown(maxidx);
        }
        return;
    }

public:
    Heap(int capacity) : max_capacity(capacity), heap_size(0) {
        heap_array = new int[max_capacity];
        if (!heap_array) {
            std::cerr << "Memory allocation failed.\n";
            exit(1); 
        }
    }

    Heap(vector<int>& v) : Heap(v.size()) {
        for(int i = 0; i < v.size(); i++) {
            insert(v[i]);
        }
    }

    void insert(int data) {
        heap_size++;
        resize(); 
        heap_array[heap_size-1] = data;
        heapifyUp(heap_size-1);
    }

    int size() {
        return heap_size;
    }

    int getMax() {
        if (heap_size == 0) {
            throw runtime_error("Empty heap, can not get max");
        }
        return heap_array[0];
    }

    void deleteKey() {
        if (heap_size == 0) {
            throw runtime_error("Empty heap, can not delete key");
        }
        int temp = heap_array[heap_size-1];
        heap_array[heap_size-1] = heap_array[0];
        heap_array[0] = temp;
        heap_size--;
        resize();
        heapifyDown(0);
    }

    ~Heap() {
        delete[] heap_array;
    }
};

void heapsort(vector<int>&v) {
    Heap heap(v);
    for(int i = 0; i < v.size(); i++) {
        v[i] = heap.getMax();
        heap.deleteKey();
    }
}
