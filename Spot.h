#ifndef SPOT_H
#define SPOT_H
#include <iostream>
using namespace std;

class Spot {
private:
    int loc_r; // Row location 
    int loc_c; // Column location

public:
    // Constructor
    Spot() : loc_r(0), loc_c(0) {}
    Spot(int row, int col) : loc_r(row), loc_c(col) {}

    // Getters
    int getLoc_r() const;
    int getLoc_c() const;

    // Setters
    void setLoc_r(int row);
    void setLoc_c(int col);
    friend ostream& operator<<(ostream& os, const Spot& spot);
};

#endif // SPOT_H