#include "Spot.h"
#include <iostream>
using namespace std;
// Constructor

//Spot::Spot(int row, int col) : loc_r(row), loc_c(col) {}

// Getter for loc_r coordinate
int Spot::getLoc_r() const {
    return loc_r;
}

// Getter for loc_c coordinate
int Spot::getLoc_c() const {
    return loc_c;
}

// Setter for loc_r coordinate
void Spot::setLoc_r(int loc_r) {
    this->loc_r = loc_r;
}

// Setter for loc_c coordinate
void Spot::setLoc_c(int loc_c) {
    this->loc_c = loc_c;
}


ostream& operator<<(ostream& os, const Spot& spot) {
    os << "(" << spot.getLoc_r() << ", " << spot.getLoc_c() << ")";
    return os;
}