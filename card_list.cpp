// card_list.cpp
// Author: Jingyang Liu
// Implementation of the classes defined in card_list.h

#include "card_list.h"

#include <iostream>
#include <string>
using namespace std;

// constructor sets up empty tree
CardBST::CardBST() { 
    root = nullptr;
}

// destructor deletes all nodes
CardBST::~CardBST() {
    clear(root);
}

// recursive helper for destructor
void CardBST::clear(Node *n) {
    if (n == nullptr) return;
    
    clear(n->left);
    clear(n->right);

    delete n;
}

// insert value in tree; return false if duplicate
bool CardBST::insert(char suit, string value) {
    Card c(suit, value);
    if (root == nullptr) {
        root = new Node(c);
        return true;
    }
    return insert(suit, value, root);
}

// recursive helper for insert (assumes n is never 0)
bool CardBST::insert(char suit, string value, Node *n) {
    Card c(suit, value);
    if (c == n->c) {
        return false;
    }
    if (c > n->c) {
        if (n->right == nullptr) {
            n->right = new Node(c);
            n->right->parent = n;
            return true;
        }
        else {
            return insert(suit, value, n->right);
        }
    }
    else {
        if (n->left == nullptr) {
            n->left = new Node(c);
            n->left->parent = n;
            return true;
        }
        else {
            return insert(suit, value, n->left);
        }
    }
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
CardBST::Node* CardBST::getNodeFor(char suit, string value, Node* n) const{
    if (n == nullptr) return nullptr;

    Card c(suit, value);

    if (n->c == c) {
        return n;
    }

    if (c > n->c) {
        return getNodeFor(suit, value, n->right);
    }
    else {
        return getNodeFor(suit, value, n->left);
    }
}

// returns true if value is in the tree; false if not
bool CardBST::contains(char suit, string value) const {
    Node* curr = root;
    Card c(suit, value);
    while (curr != nullptr) {
        if (curr->c == c) return true;
        if (c > curr->c) {
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
    }
    return false;
}

// returns the Node containing the predecessor of the given value
CardBST::Node* CardBST::getPredecessorNode(char suit, string value) const{
    Node* target = getNodeFor(suit, value, root);

    // Case 1: the target has left child
    if (target->left != nullptr) {
        target = target->left;
        while (target->right != nullptr) {
            target = target->right;
        }
        return target;
    }

    // Case 2: the target does not have left child
    // we need to find the predecessor from its parent node
    while (target->parent != nullptr) {
        if (target->parent->right == target) return target->parent;
        target = target->parent;
    }

    return nullptr;
}

Card CardBST::getPredecessor(char suit, string value) const{
    if (contains(suit, value) == false) return Card();
    Node* result = getPredecessorNode(suit, value);
    if (result == nullptr) return Card();
    return result->c;
}

// returns the Node containing the successor of the given value
CardBST::Node* CardBST::getSuccessorNode(char suit, string value) const{
    Node* target = getNodeFor(suit, value, root);

    // Case 1: the target has right child
    if (target->right != nullptr) {
        target = target->right;
        while (target->left != nullptr) {
            target = target->left;
        }
        return target;
    }

    // Case 2: the target does not have right child
    // we need to find the successor from its parent node
    while (target->parent != nullptr) {
        if (target->parent->left == target) return target->parent;
        target = target->parent;
    }

    return nullptr;
}

// returns the successor value of the given value or 0 if there is none
Card CardBST::getSuccessor(char suit, string value) const{
    if (contains(suit, value) == false) return Card();
    Node* result = getSuccessorNode(suit, value);
    if (result == nullptr) return Card();
    return result->c;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool CardBST::remove(char suit, string value){
    if (contains(suit, value) == false) return false;
    Node* target = getNodeFor(suit, value, root);

    // Case 1: the target node is leaf (no right / left child)
    if (target->left == nullptr && target->right == nullptr) {
        if (target->parent == nullptr) {
            root = nullptr;
            delete target;
            return true;
        }
        if (target->parent->left == target) {
            target->parent->left = nullptr;
        }
        else {
            target->parent->right = nullptr;
        }
        delete target;
        return true;
    }

    // Case 3: the target has both two child (left & right)
    else if (target->left != nullptr && target->right != nullptr) {
        Card succ = getSuccessor(suit, value);
        remove(succ.suit, succ.value);
        target->c = succ;
        return true;
    }

    // Case 2: the target has only one child (left / right)
    else {
        if (target->left != nullptr) {
            if (target->parent == nullptr) {
                root = target->left;
                target->left->parent = nullptr;
                delete target;
                return true;
            }
            if (target->parent->left == target) {
                target->parent->left = target->left;
            }
            else if (target->parent->right == target) {
                target->parent->right = target->left;
            }
            target->left->parent = target->parent;
        }
        else {
            if (target->parent == nullptr) {
                root = target->right;
                target->right->parent = nullptr;
                delete target;
                return true;
            }
            if (target->parent->left == target) {
                target->parent->left = target->right;
            }
            else if (target->parent->right == target) {
                target->parent->right = target->right;
            }
            target->right->parent = target->parent;
        }
        delete target;
        return true;
    }
}

void playGame(CardBST& A, CardBST& B) {
    bool conti = true;
    while (conti) {
        conti = false;
        // Alice
        for (auto it = A.begin(); it != A.end(); ++it) {
            if (B.contains((*it).suit, (*it).value)) {
                auto del = *it;
                cout << "Alice picked matching card " << del.suit << " " << del.value << endl;
                B.remove(del.suit, del.value);
                A.remove(del.suit, del.value);
                conti = true;
                break;
            }
        }
        // Bob
        for (auto it = B.rbegin(); it != B.rend(); --it) {
            if (A.contains((*it).suit, (*it).value)) {
                auto del = *it;
                cout << "Bob picked matching card " << del.suit << " " << del.value << endl;
                A.remove(del.suit, del.value);
                B.remove(del.suit, del.value);
                conti = true;
                break;
            }
        }
    }

    cout << endl;

    // print final result
    cout << "Alice's cards:" << endl;
    for (auto it = A.begin(); it != A.end(); ++it) {
        cout << (*it).suit << " " << (*it).value << endl;
    }

    cout << endl;

    cout << "Bob's cards:" << endl;
    for (auto it = B.begin(); it != B.end(); ++it) {
        cout << (*it).suit << " " << (*it).value << endl;
    }
}
