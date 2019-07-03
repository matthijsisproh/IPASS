#ifndef SQUID_HPP
#define SQUID_HPP

#include "hwlib.hpp"

class Squid : public drawable{
public:
Squid(hwlib::glcd_oled & display, hwlib::xy location = hwlib::xy(10, 10), int lives = 1):
drawable( display, location, lives)
{}

void draw()override{
    const int size = 36;
    int array[size][2] = {{0, 4}, {0, 5}, {0, 7}, {1, 3}, {1, 4}, 
                        {1, 5}, {1, 6}, {2, 4}, {2, 5}, {1, 8}, 
                        {2, 2}, {2, 3}, {2, 5}, {3, 1}, {3, 2}, 
                        {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 1}, 
                        {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, 
                        {5, 2}, {5, 3}, {5, 5}, {6, 3}, {6, 4}, 
                        {6, 5}, {6, 6}, {6, 8}, {7, 4}, {7, 5}, {7, 6}};
    
    for(int i = 0; i < size; i++){
        display.write(hwlib::xy(location.x + array[i][0], location.y + array[i][1]));    
    }
}

};

#endif //SQUID_HPP