#include "queue.h"
#include <iostream>
#include "stack.h"
using namespace std;

int main() {
    Stack* s = new ArrayStack();
    int tcase;
    cin >> tcase;
    cout << "-------------TestingVisibleBuildings-------------\n";
    for(int i = 1; i <= tcase; i++) {
        cout << "Test Case " << i << ": ";
        int n;
        cin >> n;
        while(n--) {
            int x;
            cin >> x;
            if(s->empty()) {
                s->push(x);
                continue;
            }
            while(!s->empty() && s->top() < x) {
                s->pop();
            }
            s->push(x);
        }
        cout << "Visible Buildings: ";
        while(!s->empty()) {
            cout << s->top() << " ";
            s->pop();
        }
    }

    
    delete s; // Clean up the stack object
    return 0;
}