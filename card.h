// card.h
// Author: Jingyang Liu
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;

class Card {
public:
    char suit;
    string value;

    Card();

    Card(char s, string v);

    bool operator==(const Card& rhs) const;

    bool operator<(const Card& rhs) const;

    bool operator>(const Card& rhs) const;

private:
    int suitCp(char s) const;

    int valueCp(string v) const;
};

#endif