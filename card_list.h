// card_list.h
// Author: Jingyang Liu
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <string>
#include "card.h"
using namespace std;

class CardBST {

private:
    struct Node {
        Card c;
        Node *left;
        Node *right;
        Node *parent;

        Node(Card card) : c(card), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(char s, string v, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(char s, string v, Node *n); // note overloading names for simplicity

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(char s, string v) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(char s, string v) const; // returns the Node containing the predecessor of the given value 


public:
    // ctor, dtor, insert and one print method already done in intbst.cpp:
    CardBST();                 // constructor
    ~CardBST();                  // destructor
    bool insert(char suit, string value);     // insert value; return false if duplicate
    bool contains(char suit, string value) const;  // true if value is in tree

    // THESE ARE HARDER! DO THESE LAST
    Card getPredecessor(char suit, string value) const;       // returns the predecessor value of the given value or 0 if there is none
    Card getSuccessor(char suit, string value) const;         // returns the successor value of the given value or 0 if there is none
    bool remove(char suit, string value);                    // deletes the Node containing the given value from the tree

    class Iterator {
    private:
        Node* n;
    
    public:
        Iterator(Node* ptr) {
            n = ptr;
        }

        Card operator*() const {
            return n->c;
        }

        Iterator& operator++() {   // find Successor
            if (n == nullptr) return *this;

            if (n->right != nullptr) {
                n = n->right;
                while (n->left != nullptr) {
                    n = n->left;
                }
                return *this;
            }
            Node* p = n->parent;
            while (p != nullptr && n == p->right) {
                n = p;
                p = p->parent;
            }
            n = p;
            return *this;
        }

        Iterator& operator--() {   // find Predecessor
            if (n == nullptr) return *this;

            if (n->left != nullptr) {
                n = n->left;
                while (n->right != nullptr) {
                    n = n->right;
                }
                return *this;
            }
            Node* p = n->parent;
            while (p != nullptr && n == p->left) {
                n = p;
                p = p->parent;
            }
            n = p;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return this->n == other.n;
        }

        bool operator!=(const Iterator& other) const {
            return this->n != other.n;
        }
    };

    Iterator begin() const {
        if (root == nullptr) return Iterator(nullptr);
        Node* curr = root;
        while (curr->left) {
            curr = curr->left;
        }
        return Iterator(curr);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    Iterator rbegin() const {
        if (root == nullptr) return Iterator(nullptr);
        Node* curr = root;
        while (curr->right != nullptr) {
            curr = curr->right;
        }
        return Iterator(curr);
    }

    Iterator rend() {
        return Iterator(nullptr);
    }
};

void playGame(CardBST& A, CardBST& B);

#endif
