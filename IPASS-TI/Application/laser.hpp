#ifndef LASER_HPP
#define LASER_HPP

class Laser : public drawable{
private:
    int tilt;
    
    
public:
    Laser(hwlib::glcd_oled & display, hwlib::xy location = hwlib::xy(0, 60), int tilt = 0, int lives = 1):
    drawable(display, location, lives), tilt(tilt)
    {}
    void draw()override{
    }
    
    void interact( drawable & other ) override {
      if( this != &other){
         if( overlapx( other )){
             other.lives -= 1;
             boom();
             if(other.lives == 0){
                 score += 10;
                 other.alive = false;
                 clear();
             }
         }
      }
   }
    
    void refresh(int tilt)override{
        for(int j = 10; j > 0; j--){
            location = hwlib::xy(tilt + 3, j * 5);
            display.write(location);
        }
    }
};


#endif //LASER_HPP