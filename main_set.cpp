// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argc, char** argv){
  if(argc < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argv[1]);
  ifstream cardFile2 (argv[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argv[2];
    return 1;
  }

  set<Card> A;
  set<Card> B;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    A.insert(Card(line[0], line.substr(2)));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    B.insert(Card(line[0], line.substr(2)));
  }
  cardFile2.close();
  
  bool conti = true;

  while (conti) {
    conti = false;
    // Alice
    for (auto it = A.begin(); it != A.end(); ++it) {
      if (B.find(*it) != B.end()) {
        auto del = *it;
        cout << "Alice picked matching card " << del.suit << " " << del.value << endl;
        B.erase(del);
        A.erase(del);
        conti = true;
        break;
      }
    }
    // Bob
    for (auto it = B.rbegin(); it != B.rend(); --it) {
      if (A.find(*it) != A.end()) {
        auto del = *it;
        cout << "Bob picked matching card " << del.suit << " " << del.value << endl;
        A.erase(del);
        B.erase(del);
        conti = true;
        break;
      }
    }
  }

  cout << endl;

  // print final result
  cout << "Alice's cards:" << endl;
  for (auto it = A.begin(); it != A.end(); ++it) {
    cout << it->suit << " " << it->value << endl;
  }

  cout << endl;

  cout << "Bob's cards:" << endl;
  for (auto it = B.begin(); it != B.end(); ++it) {
    cout << it->suit << " " << it->value << endl;
  }

  return 0;
}
