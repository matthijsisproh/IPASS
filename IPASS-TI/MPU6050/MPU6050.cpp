// =========================================================
//
// File        :   MPU6050.cpp
// Part of     :   library for a mpu6050 module
// Copyright   :   M.T.N. Koelewijn(2019)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// =========================================================

#include "MPU6050.hpp"

/// Constructor MPU6050 module
//
/// Can be used to get the raw values of the right address.
MPU6050::MPU6050(hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus, const uint8_t address):
i2c_bus(i2c_bus), address(address)
{}


/// Sleep
void MPU6050::enable_sleep(){
    /// These bytes are needed to write a 0 byte to the register to sleep after it has been turned off.
    const uint8_t array[2] = {0x6b, 0xC0};
    
    /// This writes the bytes array which is used to sleep after it has been turned off.
    hwlib::i2c_write_transaction(i2c_bus, address).write(array, 2);
    hwlib::wait_ms(100);
}

/// Wake up
void MPU6050::disable_sleep(){
    /// These bytes are needed to write a 0 byte to the register to wake up after it has been turned off.
    const uint8_t array[2] = {0x6b, 0x00};
    
    /// This writes the bytes array which is used to wake up after it has been turned off.
    hwlib::i2c_write_transaction(i2c_bus, address).write(array, 2);
    hwlib::wait_ms(100);
}

/// Updates
//
/// This function updates the values of the Accelerometer by reading the register his values.
void MPU6050::updateAccel(){
    uint8_t x_high = readRegister(aX_OUT_H);
    uint8_t x_low = readRegister(aX_OUT_L);
    aX = compress(x_high, x_low);
    uint8_t y_high = readRegister(aY_OUT_H);
    uint8_t y_low = readRegister(aY_OUT_L);
    aY = compress(y_high, y_low);
    uint8_t z_high = readRegister(aZ_OUT_H);
    uint8_t z_low = readRegister(aZ_OUT_L);
    aZ = compress(z_high, z_low);
}

/// Updates
//
/// This function updates the values of the Gyrosensor by reading the register his values.
void MPU6050::updateGyro(){
    uint8_t x_high = readRegister(gX_OUT_H);
    uint8_t x_low = readRegister(gX_OUT_L);
    gX = compress(x_high, x_low);
    uint8_t y_high = readRegister(gY_OUT_H);
    uint8_t y_low = readRegister(gY_OUT_L);
    gY = compress(y_high, y_low);
    uint8_t z_high = readRegister(gZ_OUT_H);
    uint8_t z_low = readRegister(gZ_OUT_L);
    gZ = compress(z_high, z_low);
}

/// Compresses
//
/// This function takes the high byte and low byte values and put it in one value.
uint16_t MPU6050::compress(uint8_t high, uint8_t low){
    uint16_t bytes = 0;
    bytes = (high << 8) | (low);
    return bytes;
}

/// Prints
//
/// This function gives an overview of all the values by printing it.
void MPU6050::print(const int16_t x, const int16_t y, const int16_t z){
        hwlib::cout << "X: " << x << "\t" 
        << "Y: " << y << "\t" 
        << "Z: " << z << "\n";
}
    
/// Reads the registers
//
/// This function reads the registers and returns a byte by the given address.
uint8_t MPU6050::readRegister(const uint8_t register_address){
        hwlib::i2c_write_transaction(i2c_bus, address).write(register_address);
        return hwlib::i2c_read_transaction(i2c_bus, address).read_byte();
    }

/// X getter accelerometer
//
/// This function is a specific getter for the X value.
int16_t MPU6050::get_aX(){
        return aX;
    }

/// Y getter accelerometer
//
/// This function is a specific getter for the Y value.
int16_t MPU6050::get_aY(){
        return aY;
    }
    
/// Z getter accelerometer
//
/// This function is a specific getter for the Z value.
int16_t MPU6050::get_aZ(){
        return aZ;
    }

/// Tilting
//
/// This function returns a value after a formula for calibrating tilt is applied .
int16_t MPU6050::get_tilt(int16_t v, int add){
    return tilt = -((v * 100) / max) + add;
}

/// X getter gyrosensor
//
/// This function is a specific getter for the X value.
int16_t MPU6050::get_gX(){
        return gX;
    }

/// Y getter gyrosensor
//
/// This function is a specific getter for the Y value.
int16_t MPU6050::get_gY(){
        return gY;
    }
    
/// Z getter gyrosensor
//
/// This function is a specific getter for the Z value.
int16_t MPU6050::get_gZ(){
        return gZ;
    }