#ifndef CUTTLEFISH_HPP
#define CUTTLEFISH_HPP

#include "hwlib.hpp"
class Cuttlefish : public drawable{
public:
Cuttlefish(hwlib::glcd_oled & display, hwlib::xy location, int lives = 1):
drawable( display, location, lives)
{}

void draw()override{
    const int size = 31;
    int array[size][2] = {{0, 3}, {0, 4}, {1, 2}, 
                    {1, 3}, {1, 4}, {1, 5}, 
                    {2, 1}, {2, 2}, {2, 4},
                    {2, 6}, {3, 1}, {3, 2},
                    {3, 3}, {3, 4}, {3, 6},
                    {4, 1}, {4, 2}, {4, 3},
                    {4, 4}, {4, 6}, {5, 1},
                    {5, 2}, {5, 4}, {5, 5},
                    {5, 6}, {6, 2}, {6, 3},
                    {6, 4}, {6, 5}, {7, 3},
                    {7, 4}};
    
    for(int i = 0; i < size; i++){
        display.write(hwlib::xy(location.x + array[i][0], location.y + array[i][1]));    
    }
}

};

#endif //CUTTLEFISH_HPP