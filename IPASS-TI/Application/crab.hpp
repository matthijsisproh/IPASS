#ifndef CRAB_HPP
#define CRAB_HPP

#include "hwlib.hpp"

class Crab : public drawable{
public:
Crab(hwlib::glcd_oled & display, hwlib::xy location = hwlib::xy(10, 10), int lives = 1):
drawable( display, location, lives)
{}

void draw()override{
    const int size = 44;
    int array[size][2] = {{0, 5}, {0, 6}, {0,7}, {1, 4}, {1, 5}, {2, 1}, {2, 3}, {2, 4}, {2, 5},
                        {2, 6}, {2, 7}, {3, 2}, {3, 3}, {3, 5}, {3, 6}, {3, 8}, {4, 3}, {4, 4},
                        {4, 5}, {4, 6}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {6, 3}, {6, 4}, {6, 5},
                        {6, 6}, {7, 2}, {7, 3}, {7, 5}, {7, 6}, {7, 8}, {8, 1}, {8, 3}, {8, 4}, 
                        {8, 5}, {8, 6}, {8, 7}, {9, 4}, {9, 5}, {10, 5}, {10, 6}, {10, 7}};
    
    for(int i = 0; i < size; i++){
        display.write(hwlib::xy(location.x + array[i][0], location.y + array[i][1]));    
    }
}
};

#endif //CRAB_HPP