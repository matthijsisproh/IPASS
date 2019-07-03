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

void test(int & test_passed, int & test_failed){
    hwlib::cout << ":\n" << "PASSED: " 
    << test_passed << " FAILED: " << test_failed << "\n";
    test_passed = 0;
    test_failed = 0;
}

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
    
    
    Crab alien0(display, hwlib::xy(0, 0));
    Crab alien1(display, hwlib::xy(0, 0));
    Crab alien2(display, hwlib::xy(0, 0));
    Crab alien3(display, hwlib::xy(0, 0));
    Crab alien4(display, hwlib::xy(0, 0));
    Crab alien5(display, hwlib::xy(0, 0));
    Crab alien6(display, hwlib::xy(0, 0));
    Crab alien7(display, hwlib::xy(0, 0));
    Crab alien8(display, hwlib::xy(0, 0));
    Cuttlefish alien9(display, hwlib::xy(0, 0));
    Cuttlefish alien10(display, hwlib::xy(0, 0));
    Cuttlefish alien11(display, hwlib::xy(0, 0));
    Cuttlefish alien12(display, hwlib::xy(0, 0));
    Cuttlefish alien13(display, hwlib::xy(0, 0));
    Cuttlefish alien14(display, hwlib::xy(0, 0));
    Cuttlefish alien15(display, hwlib::xy(0, 0));
    Cuttlefish alien16(display, hwlib::xy(0, 0));
    Cuttlefish alien17(display, hwlib::xy(0, 0));
    Squid alien18(display, hwlib::xy(0, 0));
    Squid alien19(display, hwlib::xy(0, 0));
    Squid alien20(display, hwlib::xy(0, 0));
    Squid alien21(display, hwlib::xy(0, 0));
    Squid alien22(display, hwlib::xy(0, 0));
    Squid alien23(display, hwlib::xy(0, 0));
    Squid alien24(display, hwlib::xy(0, 0));
    Squid alien25(display, hwlib::xy(0, 0));
    Squid alien26(display, hwlib::xy(0, 0));
    Shooter UFO(display, hwlib::xy(0, 10));
    Laser laser0(display);
    Laser laser1(display);
    Shooter player(display, hwlib::xy(64 , 63));
    std::array< drawable *, 27> aliens = {&alien0, &alien1, &alien2, 
                                        &alien3, &alien4, &alien5, &alien6, 
                                        &alien7, &alien8, &alien9, &alien10, 
                                        &alien11, &alien12, &alien13, &alien14, 
                                        &alien15, &alien16, &alien17,
                                        &alien18, &alien19, &alien20, &alien21,
                                        &alien22, &alien23, &alien24, &alien25,
                                        &alien26};
    int testPassed = 0;
    int testFailed = 0;
    
    // Test player lives
    // player located at 64, 63 standard
    // player has 5 lives
    for(int i = 0; i < 4; i++){
        laser1.attack(65, 0);
    }
    if(player.lives == 0){
            testPassed++;
        }
        else{
            testFailed++;
        }
        
    hwlib::cout << "TEST PLAYER LIVES";
    test(testPassed, testFailed);
    
    
    
    // Test object lives
    // object located at 0, 0
    // object has 1 live
    for(auto & other : aliens){
        laser0.attack(0, 63);
        if(other->lives == 0){
            testPassed++;
        }
        else{
            testFailed++;
        }

    }
    hwlib::cout << "TEST OBJECT LIVES";
    test(testPassed, testFailed);
    
    
}
        
        

