#ifndef SHOOTER_HPP
#define SHOOTER_HPP

class Shooter : public drawable{
public:
    Shooter(hwlib::glcd_oled & display, hwlib::xy location, int lives = 5):
    drawable(display, location, lives)
    {}
    
    void draw()override{
    const int size = 59;
    int array[size][2] = {{0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5}, 
                        {2, 6}, {3, 2}, {3, 3}, {3, 5}, {3, 6}, {3, 7}, 
                        {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {5, 1}, 
                        {5, 2}, {5, 3}, {5, 4}, {5, 5}, {6, 1}, {6, 2}, 
                        {6, 3}, {6, 5}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, 
                        {7, 5}, {7, 6}, {8, 1}, {8, 2}, {8, 3}, {8, 4}, 
                        {8, 5}, {8, 6}, {9, 1}, {9, 2}, {9, 3}, {9, 5}, 
                        {10, 2}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {11, 2}, 
                        {11, 3}, {11, 5}, {11, 6}, {11, 7}, {12, 3}, {12, 4}, 
                        {12, 5}, {12, 6}, {13, 4}, {13, 5}, {14, 5}};
    
    for(int i = 0; i < size; i++){
        display.write(hwlib::xy(location.x + array[i][0], location.y + array[i][1]));    
    }
    }
    
    void refresh(int tilt)override{
        for(int i = tilt; i < tilt + 7; i++){
            display.write(hwlib::xy( i , 63 ));
      }
    }
    
    
    
    void interact( drawable & other ) override {
      if( this != &other){
         if( overlapx( other )){
             lives -= 1;
         }
      }
   }
};

#endif //SHOOTER_HPP