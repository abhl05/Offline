#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value> {
private:
    /**
     * Node class for the binary search tree
     */
    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;
    
    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    void inorderPrint (Node* node) const {
        if(!node) return;
        inorderPrint(node->left);
        std::cout << "(" << node->key << ":" << node->value << ") ";
        inorderPrint(node->right);
    }

    void preorderPrint(Node* node) const {
        if(!node) return;
        std::cout << "(" << node->key << ":" << node->value << ") ";
        preorderPrint(node->left);
        preorderPrint(node->right);
    }

    void postorderPrint(Node* node) const {
        if(!node) return;
        postorderPrint(node->left);
        postorderPrint(node->right);
        std::cout << "(" << node->key << ":" << node->value << ") ";
    }
    
    void defaultPrint(Node* node) const {
        if(!node) return;
        std::cout << "(" << node->key << ":" << node->value;
        if(node->left) {
            std::cout << " ";
            defaultPrint(node->left);
        } else if(node->right) std::cout << " ()";
        if(node->right) {
            std::cout << " ";
            defaultPrint(node->right);
        } 
        std::cout << ")";
    }

    void clearSubTree(Node* node) {
        if(!node) return;
        clearSubTree(node->left);
        clearSubTree(node->right);
        delete node;
    }

    Node* removeNode(Node* node, Key& key, bool& found) {
        if(!node) return nullptr;

        if(node->key > key) {
            node->left = removeNode(node->left, key, found);
        }
        else if(node->key < key) {
            node->right = removeNode(node->right, key, found);
        }
        else {
            found = true;   
            if(!node->right && !node->left) {
                delete node;
                return nullptr;
            }
            if(!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            if(!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            
            Node* temp = node->right;
            while(temp->left) temp = temp->left;
            node->key = temp->key;
            node->value = temp->value;
            node->right = removeNode(node->right, temp->key, found);
        }
        return node;
    }
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}
    
    /**
     * Destructor
     */
    ~ListBST() {
        // TODO: Implement destructor to free memory
        clear();
    }
    
    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override {
        // TODO: Implement insertion logic
        if(!root) {
            root = new Node(key, value);
            if (!root) {
                std::cerr << "Memory allocation failed" << std::endl;
                return false;
            }
            node_count++;
            return true;
        }
        Node* node = root, *prev = nullptr;
        while(node) {
            prev = node;
            if(node->key > key) node = node->left;
            else if(node->key < key) node = node->right;
            else return false;
        }
        if(prev->key < key) {
            prev->right = new Node(key, value);
            if (!prev->right) {
                std::cerr << "Memory allocation failed" << std::endl;
                return false;
            }
        }
        else {
            prev->left = new Node(key, value);
            if (!prev->left) {
                std::cerr << "Memory allocation failed" << std::endl;
                return false;
            }
        }   
        node_count++;
        return true;
    }
    
    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override {
        // TODO: Implement removal logic
        bool res = false;
        root = removeNode(root, key, res);
        if(res) node_count--;
        return res;
    }
    
    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override {
        // TODO: Implement find logic
        Node* node = root;
        while(node) {
            if(node->key > key) node = node->left;
            else if(node->key < key) node = node->right;
            else return true;
        }
        return false;
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override {
        // TODO: Implement get logic
        Node* node = root;
        while(node) {
            if(node->key > key) node = node->left;
            else if(node->key < key) node = node->right;
            else return node->value;
        }
        throw std::runtime_error("key is not found");
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override {
        // TODO: Implement update logic
        Node* node = root;
        while(node) {
            if(node->key > key) node = node->left;
            else if(node->key < key) node = node->right;
            else {
                node->value = value;
                return;
            }
        }
        throw std::runtime_error("key is not found");
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override {
        // TODO: Implement clear logic
        clearSubTree(root);
        node_count = 0;
        root = nullptr;
    }
    
    /**
     * Get the number of keys in the BST
     */
    size_t size() const override {
        // TODO: Implement size logic
        return node_count;
    }
    
    /**
     * Check if the BST is empty
     */
    bool empty() const override {
        // TODO: Implement empty check logic
        return root == nullptr;
    }
    
    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override {
        // TODO: Implement find_min logic
        if(!root) throw std::runtime_error("BST is empty");
        Node* node = root;
        while(node->left) node = node->left;
        return node->key;
    }
    
    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override {
        // TODO: Implement find_max logic
        if(!root) throw std::runtime_error("BST is empty");
        Node* node = root;
        while(node->right) node = node->right;
        return node->key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override {
        // TODO: Implement print logic
        if(!root) {
            std::cout << "()\n";
            return;
        }
        if(traversal_type == 'D' || traversal_type == 'd') {
            defaultPrint(root);
        }
        else if(traversal_type == 'I' || traversal_type == 'i') {
            inorderPrint(root);
        }
        else if(traversal_type == 'P' || traversal_type == 'p') {
            preorderPrint(root);
        }
        else if(traversal_type == 'O' || traversal_type == 'o') {
            postorderPrint(root);
        }
        else throw std::invalid_argument("traversal_type is invalid");
    }
    
};

#endif // LISTBST_H