#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called";
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    // freopen("test_input_1.txt", "r", stdin); // Test Case 1
    freopen("test_input_2.txt", "r", stdin); // Test Case 2;
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;
    int timestamps[10000] = {-1};

    for (int i = 1;  i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        int op, id, timestamp;
        cin >> op;
        timestamps[id] = timestamp;

        if(op == 1) {
            cin >> id >> timestamp;
            cout << "Operation " << i << " (Arrival " << id << " " << timestamp << "): ";
            if(Q->empty()) {
                if(Q1->empty() && Q2->empty()) {
                if(randomQueue() == 1) Q1->enqueue(id);
                else Q2->enqueue(id);
                }
                else if(Q1->empty()) Q1->enqueue(id);
                else if(Q2->empty()) Q2->enqueue(id);
                else {
                    if(timestamps[Q1->back()] < timestamps[Q2->back()]) Q1->enqueue(id);
                    else Q2->enqueue(id);
                }
            }
            else Q->enqueue(id);
            cout << endl;
        }
        else if(op == 2) {
            cin >> id >> timestamp;
            cout << "Operation " << i << " (Leave " << id << " " << timestamp << "): \n";
            bool found = false;
            if(!Q->empty()) {
                for(int i = 0; i < Q->size(); i++) {
                    int cur_id = Q->dequeue();
                    if(cur_id != id) Q->enqueue(cur_id);
                    else {
                        found = true;
                        i--;
                    }
                }
            }
            else if(!Q1->empty() && !found) {
                for(int i = 0; i < Q1->size(); i++) {
                    int cur_id = Q1->dequeue();
                    if(cur_id != id) Q1->enqueue(cur_id);
                    else {
                        found = true;
                        i--;
                    }
                }
            }
            else if(!Q2->empty() && !found) {
                for(int i = 0; i < Q2->size(); i++) {
                    int cur_id = Q2->dequeue();
                    if(cur_id != id) Q2->enqueue(cur_id);
                    else {
                        found = true;
                        i--;
                    }
                }
            }
        }
        else if(op == 3) {
            cout << "Operation " << i << " (Merge): \n";
            while(!Q1->empty() && !Q2->empty()) {
                if(timestamps[Q1->front()] < timestamps[Q2->front()]) {
                    Q->enqueue(Q1->dequeue());
                }
                else {
                    Q->enqueue(Q2->dequeue());
                }
            }
            if(!Q2->empty()) {
                while(!Q2->empty()) Q->enqueue(Q2->dequeue());
            }
            if(!Q1->empty()) {
                while(!Q1->empty()) Q->enqueue(Q1->dequeue());
            }
            Q1->clear();
            Q2->clear();
        }
        else if(op == 4) {
            cout << "Operation " << i << " (Split): \n";
            int itr = 1;
            while(!Q->empty()) {
                if(itr%2) {
                    Q1->enqueue(Q->dequeue());
                }
                else Q2->enqueue(Q->dequeue());
                itr++;
            }
            Q->clear();
        }
        else if(op == 5) {
            cout << "Operation " << i << " (Departure): ";
            if(Q->empty()) {
                if(!Q1->empty() && !Q2->empty()) {
                if(randomQueue() == 1) Q1->dequeue();
                else Q2->dequeue();
                }
                else if(!Q1->empty()) Q1->dequeue();
                else if(!Q2->empty()) Q2->dequeue();
            }
            else Q->dequeue();
            cout << endl;
        }
        cout << "Q1: " + Q1->toString() << endl << "Q2: " + Q2->toString() << endl << "Q : " + Q->toString() << endl;

        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    return 0;
}