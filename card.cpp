// card.cpp
// Author: Jingyang Liu
// Implementation of the classes defined in card.h

#include "card.h"
#include <string>
using namespace std;

Card::Card() {}

Card::Card(char s, string v) {
    suit = s;
    value = v;
}

bool Card::operator==(const Card& rhs) const {
    return suit == rhs.suit && value == rhs.value;
}

bool Card::operator<(const Card& rhs) const {
    // change its suit
    int l_s, r_s;
        
    l_s = suitCp(suit);
    r_s = suitCp(rhs.suit);

    // change it value
    int l_v, r_v;

    l_v = valueCp(value);
    r_v = valueCp(rhs.value);

    // comparison
    if (l_s == r_s) {
        return l_v < r_v;
    }
    return l_s < r_s;
}

bool Card::operator>(const Card& rhs) const {
    // change its suit
    int l_s, r_s;
        
    l_s = suitCp(suit);
    r_s = suitCp(rhs.suit);

    // change it value
    int l_v, r_v;

    l_v = valueCp(value);
    r_v = valueCp(rhs.value);

    // comparison
    if (l_s == r_s) {
        return l_v > r_v;
    }
    return l_s > r_s;
}

int Card::suitCp(char s) const {
    if (s == 'c') return 1;
    else if (s == 'd') return 2;
    else if (s == 's') return 3;
    else return 4;
}

int Card::valueCp(string v) const {
    if (v == "a") return 1;
    else if (v == "j") return 11;
    else if (v == "q") return 12;
    else if (v == "k") return 13;
    else return stoi(v);
}