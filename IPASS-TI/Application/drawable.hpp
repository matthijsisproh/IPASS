#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include "hwlib.hpp"

class drawable {
protected:
   hwlib::glcd_oled & display;
   
public:
    hwlib::xy location;
    int lives;
    bool alive;
    int score;
   drawable( hwlib::glcd_oled & display, const hwlib::xy & location, int lives):
      display( display ),
      location( location ), 
      lives(lives),
      alive(1),
      score(0)
   {}      
   
   virtual void clear(){
       location = hwlib::xy(-1000, -1000);
   }
   
   virtual void draw()= 0;
   
   virtual void update(){
       if(location.x <= 105){
        location.x += 15;
    }
    else{
        location.x = 0;
        location.y += 10;
    }
    if(location.y == 40){
            location.y = 10;
            location.x = 0;
    }
    }
    
   bool within( int x, int a, int b ){
    return ( x >= a ) && ( x <= b );
    }

    bool overlapx( const drawable & other ){
       
       bool x_overlap = within( 
          location.x, 
          other.location.x, 
          other.location.x + 10
       ) || within( 
          other.location.x, 
          location.x, 
          location.x + 10
       );
       return x_overlap;
    }
    
   virtual void interact( drawable & other ){}
   
   virtual void refresh(int tilt){}
   
   virtual void boom(){
    int size = 16;
    int array[size][2] = {{2 , 3}, {2 , 7}, {2, 10}, 
                    {3, 5}, {3, 7}, {3, 9}, 
                    {5, 4}, {5, 5}, {5, 9}, 
                    {5, 10}, {7, 5}, {7, 7}, 
                    {7, 9}, {8, 4}, {8, 7}, {8, 10}};   
    for(int i = 0; i < size; i++){
        display.write(hwlib::xy(location.x + array[i][0], location.y + array[i][1]));    
    }
    }

   virtual void attack(int x, int y){
       for(int i = y; i < 63; i++){
           location = hwlib::xy(x, 63);
           if(i % 10 == 0){
               display.write(hwlib::xy(x + 3, i + 5));
               display.write(hwlib::xy(x + 3, i + 4));
               display.write(hwlib::xy(x + 3, i + 3));
           }
       }
   }
};

#endif //DRAWABLE_HPP