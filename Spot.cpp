#include "Spot.h"

// Constructor

Spot::Spot(int loc_r, int loc_c) : loc_r(loc_r), loc_c(loc_c) {}

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

void Spot::moveSpot(string dir, spot &mouse) { //Mover esto a la clase spot
    if(dir == "up") {
        mouse.setLoc_c(mouse.setLoc_c - 1);
    } else if(dir == "down") {
        mouse.setLoc_c(mouse.setLoc_c + 1);
    } if(dir == "right") {
        mouse.setLoc_r(mouse.setLoc_r + 1);
    } else if(dir == "left") {
        mouse.setLoc_r(mouse.setLoc_r - 1);
    }
}