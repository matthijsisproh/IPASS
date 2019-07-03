#include "hwlib.hpp"
#include "MPU6050.hpp"

const uint8_t MPU6050_module = 0x68; 
const uint8_t display_module = 0x3c;

void test(int & test_passed, int & test_failed){
    hwlib::cout << ":\n" << "PASSED: " 
    << test_passed << " FAILED: " << test_failed << "\n";
    test_passed = 0;
    test_failed = 0;
}

int main(){
    namespace target = hwlib::target;
    auto scl     = target::pin_oc( target::pins::d21 );
    auto sda     = target::pin_oc( target::pins::d20 );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto display = hwlib::glcd_oled( i2c_bus, display_module);    
    auto mpu6050 = MPU6050(i2c_bus, MPU6050_module);
    auto fire = hwlib::target::pin_in( hwlib::target::pins::d2 );
    
    int count = 0;
    int test_failed = 0;
    int test_passed = 0;
    
    //Test Sleep:
    hwlib::cout << "Enable Sleep";
    mpu6050.enable_sleep();
    mpu6050.updateGyro();
    mpu6050.updateAccel();
    for(int i = 0; i < 5; i++){
        count += mpu6050.get_aX();
        count += mpu6050.get_aY();
        count += mpu6050.get_aZ();
        count += mpu6050.get_gX();
        count += mpu6050.get_gY();
        count += mpu6050.get_gZ();
        // Loop five times, because of the small possibility that x, y, z can be equal to 0.
        // If count is not equal to zero the function failed.
        if(count != 0){
            test_failed++;
            count = 0;
        }
        else{
            test_passed++;
            count = 0;
        }
    }
    
    // print
    test(test_passed, test_failed);
    
    //==============================================================
    
    // Test Wake Up:
    hwlib::cout << "Disable Sleep";
    mpu6050.disable_sleep();
    mpu6050.updateGyro();
    mpu6050.updateAccel();
    for(int i = 0; i < 5; i ++){
        count += mpu6050.get_aX();
        count += mpu6050.get_aY();
        count += mpu6050.get_aZ();
        count += mpu6050.get_gX();
        count += mpu6050.get_gY();
        count += mpu6050.get_gZ();
        // Loop five times, because of the small possibility that x, y, z can be equal to 0.
        // If count is equal to zero the function failed.
        if(count == 0){
            test_failed++;
            count = 0;
        }
        else{
            test_passed++;
            count = 0;
        }
    }
    
    // print
    test(test_passed, test_failed);
   
   
   //===============================================================
   
   // Test Tilt:
   int add = 10;
   hwlib::cout << "Tilt";
   mpu6050.disable_sleep();
   mpu6050.updateGyro();
   for(int i = 0; i < 5; i++){
   int x = mpu6050.get_tilt(i, add);
   if(x == 10){
       test_passed++;
   }
   else{
       test_failed++;
   }
   }
   
   // print
   test(test_passed, test_failed);

}