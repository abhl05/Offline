#include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst) {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    
    try {
        while (in_file >> c) {
            // TODO: Implement the logic to read commands from the file and output accordingly
            // After every insertion and removal, print the BST in nested parentheses format
            // Handle exceptions where necessary and print appropriate error messages
            
            // Start your code here
            if(c == 'F') {
                int key;
                in_file >> key;
                if(bst->find(key)) cout << "Key " << key << " found in BST.\n";
                else cout << "Key " << key << " not found in BST.\n";
            }
            else if(c == 'E') {
                if(bst->empty()) cout << "Empty\n";
                else cout << "Not empty\n";
            }
            else if(c == 'I') {
                int num;
                in_file >> num;
                if(bst->insert(num, num)) cout << "Key " << num << " inserted into BST, ";
                else cout << "Insertion failed! Key " << num << " already exists in BST, ";
                cout << "BST (Default): ";
                bst->print();
                cout << endl;
            }
            else if(c == 'M') {
                // string s;
                in_file >> str;
                if(str[2] == 'n') {
                    cout << "Minimum value: " << bst->find_min() << endl;
                }
                else if(str[2] == 'x') {
                    cout << "Maximum value: " << bst->find_max() << endl;
                }
            }
            else if(c == 'D') {
                int key;
                in_file >> key;
                if(bst->remove(key)) cout << "Key " << key << " removed from BST, ";
                else cout << "Removal failed! Key " << key << " not found in BST, ";
                cout << "BST (Default): ";
                bst->print();
                cout << endl;
            }
            else if(c == 'T') {
                // string s;
                in_file >> str;
                if(str[1] == 'n') {
                    cout << "BST (In-order): ";
                    bst->print('I');
                    cout << endl;
                }
                if(str[1] == 'r') {
                    cout << "BST (Pre-order): ";
                    bst->print('P');
                    cout << endl;
                }
                if(str[1] == 'o') {
                    cout << "BST (Post-order): ";
                    bst->print('O');
                    cout << endl;
                }
            }
            else if(c == 'S') {
                cout << "Size: " << bst->size() << endl;
            }
            else {
                throw invalid_argument("Invalid operation");
            }
            // End your code here
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    in_file.close();
    // cout << "Test print to stdout" << endl;
    delete bst;
    return 0;
}
