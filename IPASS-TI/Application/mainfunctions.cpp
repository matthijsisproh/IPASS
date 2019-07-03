#include "hwlib.hpp"


void start(auto fire, auto d, auto d1, auto display){
     while(fire.read()){
        d1 << "\t0000" << "SPACE\nINVADERS" << hwlib::flush;
        hwlib::wait_ms(100);
        d << "\t0305" << "Hold button\n" << "\t0406to play!" << hwlib::flush;
        hwlib::wait_ms(100);
        display.clear();
    }
    hwlib::wait_ms(1000);
}

void nextlevel(auto fire, auto d, auto d1, auto display){
    while(fire.read()){
        d1 << "\t0000" << "NEXT\nLEVEL!" << hwlib::flush;
        hwlib::wait_ms(100);
        d << "\t0205" << "Hold button!" << hwlib::flush;
        hwlib::wait_ms(100);
        display.clear();
    }
    hwlib::wait_ms(1000);
}

void winner(auto fire, auto d1, auto display){
    while(fire.read()){
        d1 << "\t0000" << "WINNER!" << hwlib::flush;
        hwlib::wait_ms(100);
        display.clear();
    }
    hwlib::wait_ms(1000);
    
}

void gameover(auto fire, auto d, auto display){
    while(fire.read()){
        display.clear();
        d << "\t0000" << " " << "\t0303GAME OVER!" << hwlib::flush;
    }
    hwlib::wait_ms(1000);
}

void credits(auto fire, auto d1, auto display){
    display.clear();
    d1 << "\t0000" << "MADE BY:\n" << "M.T.N. Koelewijn" << hwlib::flush;
}