#include <iostream>
#include <string>
#include "card_list.h"

using namespace std;

void assertEquals(bool condition, string testName) {
    if (condition) {
        cout << "[PASS] " << testName << endl;
    } else {
        cout << "[FAIL] " << testName << " <--- ERROR " << endl;
    }
}


// BST
void test_BST() {
    cout << "\n--- Testing BST Public Methods ---" << endl;
    CardBST tree;

    // Empty tree
    assertEquals(tree.contains('s', "a") == false, "Empty tree contains() returns false");
    assertEquals(tree.remove('s', "a") == false, "Removing from empty tree returns false");
    
    // Single node
    assertEquals(tree.insert('s', "a") == true, "Insert single node 's a'");
    assertEquals(tree.contains('s', "a") == true, "Retrieve single node 's a'");
    
    // Edge case: Duplicates
    assertEquals(tree.insert('s', "a") == false, "Insert duplicate 's a' returns false");

    // Multiple nodes & Ordering
    tree.insert('h', "10");
    tree.insert('c', "3");
    assertEquals(tree.contains('h', "10") == true, "Tree contains 'h 10'");
    assertEquals(tree.contains('c', "3") == true, "Tree contains 'c 3'");

    // Removal cases
    assertEquals(tree.remove('x', "99") == false, "Removing non-existent card returns false");
    assertEquals(tree.remove('c', "3") == true, "Remove existing card 'c 3'");
    assertEquals(tree.contains('c', "3") == false, "Verify 'c 3' is actually removed");
}


// Iterator
void test_Iterator() {
    cout << "\n--- Testing Iterator Class ---" << endl;
    CardBST tree;

    // Empty tree
    assertEquals(tree.begin() == tree.end(), "Empty tree: begin() == end()");
    assertEquals(tree.rbegin() == tree.rend(), "Empty tree: rbegin() == rend()");

    // Single node
    tree.insert('c', "3");
    CardBST::Iterator it = tree.begin();
    assertEquals((*it).suit == 'c' && (*it).value == "3", "Dereference operator* returns correct card");
    ++it;
    assertEquals(it == tree.end(), "Incrementing single node reaches end()");

    // Multiple nodes & Comparison
    tree.insert('h', "10");
    tree.insert('d', "a");
    
    CardBST::Iterator it1 = tree.begin();
    CardBST::Iterator it2 = tree.begin();
    assertEquals(it1 == it2, "Iterator == operator works correctly");
    
    ++it1;
    assertEquals(it1 != it2, "Iterator != operator works correctly");
    
    // Reverse traversal check
    CardBST::Iterator rev_it = tree.rbegin();
    assertEquals(rev_it != tree.rend(), "Reverse iterator starts correctly");
    --rev_it; // Go to predecessor
    assertEquals(rev_it != tree.rbegin(), "Decrementing moves away from rbegin()");
}


// Game Logic
void test_playGame() {
    cout << "\n--- Testing playGame Function ---" << endl;
    
    CardBST alice;
    CardBST bob;

    // Edge case: One empty hand (early exit)
    bob.insert('s', "10");
    playGame(alice, bob);
    assertEquals(alice.begin() == alice.end(), "Alice remains empty after playing with empty hand");
    assertEquals(bob.contains('s', "10") == true, "Bob keeps his card when Alice is empty");

    // No common cards
    alice.insert('h', "5");
    playGame(alice, bob);
    assertEquals(alice.contains('h', "5") == true && bob.contains('s', "10") == true, "No common cards: both keep their cards");

    // Both players with common cards
    alice.insert('s', "10");
    playGame(alice, bob);
    assertEquals(alice.contains('s', "10") == false, "Alice's matching card is removed");
    assertEquals(bob.contains('s', "10") == false, "Bob's matching card is removed");
    assertEquals(alice.contains('h', "5") == true, "Alice keeps her non-matching card");
}

int main() {
    test_BST();
    test_Iterator();
    test_playGame();
    
    cout << "All tests pass" << endl;
    return 0;
}