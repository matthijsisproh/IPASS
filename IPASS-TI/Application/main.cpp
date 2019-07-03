#include "hwlib.hpp"
#include "drawable.hpp"
#include "crab.hpp"
#include "cuttlefish.hpp"
#include "squid.hpp"
#include "shooter.hpp"
#include "MPU6050.hpp"
#include "laser.hpp"
#include "mainfunctions.cpp"
#include <array>

//Address of modules:
const uint8_t accel_module = 0x68; 
const uint8_t display_module = 0x3c;

int main(){
    //Variable definitions:
    namespace target = hwlib::target;
    auto scl     = target::pin_oc( target::pins::d21 );
    auto sda     = target::pin_oc( target::pins::d20 );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto display = hwlib::glcd_oled( i2c_bus, display_module);    
    auto accel = MPU6050(i2c_bus, accel_module);
    auto fire = hwlib::target::pin_in( hwlib::target::pins::d2 );
    auto font    = hwlib::font_default_8x8();
    auto font1   = hwlib::font_default_16x16();
    auto d = hwlib::terminal_from( display, font );
    auto d1 = hwlib::terminal_from( display, font1);
    bool bosslevel = false;
    int16_t y, tilt;
    int count = 0;
    Crab alien0(display, hwlib::xy(0, 10));
    Crab alien1(display, hwlib::xy(14, 10));
    Crab alien2(display, hwlib::xy(28, 10));
    Crab alien3(display, hwlib::xy(42, 10));
    Crab alien4(display, hwlib::xy(56, 10));
    Crab alien5(display, hwlib::xy(70, 10));
    Crab alien6(display, hwlib::xy(84, 10));
    Crab alien7(display, hwlib::xy(97, 10));
    Crab alien8(display, hwlib::xy(111, 10));
    Cuttlefish alien9(display, hwlib::xy(0, 20));
    Cuttlefish alien10(display, hwlib::xy(15, 20));
    Cuttlefish alien11(display, hwlib::xy(30, 20));
    Cuttlefish alien12(display, hwlib::xy(45, 20));
    Cuttlefish alien13(display, hwlib::xy(60, 20));
    Cuttlefish alien14(display, hwlib::xy(75, 20));
    Cuttlefish alien15(display, hwlib::xy(90, 20));
    Cuttlefish alien16(display, hwlib::xy(105, 20));
    Cuttlefish alien17(display, hwlib::xy(120, 20));
    Squid alien18(display, hwlib::xy(0, 30));
    Squid alien19(display, hwlib::xy(14, 30));
    Squid alien20(display, hwlib::xy(28, 30));
    Squid alien21(display, hwlib::xy(42, 30));
    Squid alien22(display, hwlib::xy(56, 30));
    Squid alien23(display, hwlib::xy(70, 30));
    Squid alien24(display, hwlib::xy(84, 30));
    Squid alien25(display, hwlib::xy(97, 30));
    Squid alien26(display, hwlib::xy(111, 30));
    Shooter UFO(display, hwlib::xy(10, 20));
    Laser laser0(display);
    Laser laser1(display);
    Laser laser2(display);
    Shooter player(display, hwlib::xy(64 , 63));
    std::array< drawable *, 27> aliens = {&alien0, &alien1, &alien2, 
                                        &alien3, &alien4, &alien5, &alien6, 
                                        &alien7, &alien8, &alien9, &alien10, 
                                        &alien11, &alien12, &alien13, &alien14, 
                                        &alien15, &alien16, &alien17,
                                        &alien18, &alien19, &alien20, &alien21,
                                        &alien22, &alien23, &alien24, &alien25,
                                        &alien26};
                                        
                    
                                        
    //START SCREEN:
    start(fire, d, d1, display);
    
    hwlib::wait_ms(1000);
    
    //NORMAL LEVEL:
    while(bosslevel == false){
        count++;
        display.clear();
        
        //Header
        d << "\t0000" << "SC:" << laser0.score << "\t1100" << "Li:" << player.lives;
        
        //Tilting
        accel.disable_sleep();
        accel.updateAccel();
        y = accel.get_aY();
        tilt = accel.get_tilt(y, 65);
        
        //Loop through aliens
        for(auto & other : aliens){
            player.refresh(tilt);
            if(!(fire.read()) && count % 2 == 0){
                laser0.refresh(tilt);
                laser0.interact(*other);
            }
            
            if(other->alive){
                other->draw();
                other->update();
                
                // Count attack
                if(count == 3){
                    laser1.attack(other->location.x - 10, other->location.y);
                    player.interact(laser1);
                    count = 0;
              }
            }
        }
        display.flush();
        
        //Access next level
        if(laser0.score == 270){
            nextlevel(fire, d, d1, display);
            hwlib::wait_ms(1000);
            bosslevel = true;
        }
        
        //Gameover
        if(player.lives == 0){
            gameover(fire, d, display);
            hwlib::wait_ms(1000);
            break;
        }
    }
    
    while(bosslevel == true){
        count++;
        display.clear();
        
        //Header
        d << "\t0000" << "UFO:" << UFO.lives << "\t1100" << "Li:" << player.lives;
        
        //Tilting
        accel.disable_sleep();
        accel.updateAccel();
        y = accel.get_aY();
        tilt = accel.get_tilt(y, 65);
        
        //Loop through UFO
            player.refresh(tilt);
            if(!(fire.read()) && count % 2 == 0){
                laser0.refresh(tilt);
                laser0.interact(UFO);
            }
            
            if(UFO.alive){
                // Count attack
                if(count % 2 == 0){
                    laser2.attack(UFO.location.x, UFO.location.y);
                    player.interact(laser2);
                    count = 0;
              }
                UFO.draw();
                UFO.update();
            }
        
        display.flush();
        
        //Winner
        if(UFO.lives == 0){
            winner(fire, d1, display);
            hwlib::wait_ms(1000);
            break;
            
        }
        
        //Gameover
        if(player.lives == 0){
            gameover(fire, d, display);
            hwlib::wait_ms(1000);
            break;
            
        }
    }
    //Credits
    credits(fire, d, display);
}