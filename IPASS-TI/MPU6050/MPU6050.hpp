// =========================================================
//
// File        :   MPU6050.hpp
// Part of     :   library for a mpu6050 module 
// Copyright   :   M.T.N. Koelewijn(2019)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// =========================================================

#ifndef MPU6050_HPP
#define MPU6050_HPP
#include "hwlib.hpp"

/// MPU6050 Accelerometer interface
//
/// This is a class of a MPU6050 Accelerometer and Gyrosensor with X, Y, Z values.
/// For communicating with the I2C protocol, hwlib is used.

class MPU6050{
private:
    /// Hwlib I2C bus object.
    //
    /// This object the bus where the data will be transported over.
    hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus;
    
    /// Address of MPU6050 Module.
    const uint8_t address;
    
    /// Uninitialised values used for return.
    int16_t aX, aY, aZ, gX, gY, gZ, tilt;
    
    /// Address of the HIGH values of X accelerometer.
    const uint8_t aX_OUT_H = 0x3b;
    
    /// Address of the LOW values of X accelerometer.
    const uint8_t aX_OUT_L = 0x3c;
    
    /// Address of the HIGH values of Y accelerometer.
    const uint8_t aY_OUT_H = 0x3d;
    
    /// Address of the LOW values of Y accelerometer.
    const uint8_t aY_OUT_L = 0x3e;
    
    /// Address of the HIGH values of Z accelerometer.
    const uint8_t aZ_OUT_H = 0x3f;
    
    /// Address of the LOW values of Z accelerometer.
    const uint8_t aZ_OUT_L = 0x40;
    
    /// Address of the HIGH values of X gyrosensor.
    const uint8_t gX_OUT_H = 0x43;
    
    /// Address of the LOW values of X gyrosensor.
    const uint8_t gX_OUT_L = 0x44;
    
    /// Address of the HIGH values of Y gyrosensor.
    const uint8_t gY_OUT_H = 0x45;
    
    /// Address of the LOW values of Y gyrosensor.
    const uint8_t gY_OUT_L = 0x46;
    
    /// Address of the HIGH values of Z gyrosensor.
    const uint8_t gZ_OUT_H = 0x47;
    
    /// Address of the LOW values of Z gyrosensor.
    const uint8_t gZ_OUT_L = 0x48;
    
    /// Maximum value
    const int max = 17128;
    
public:
    MPU6050(hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus, const uint8_t address);
    
    void enable_sleep();
    
    void disable_sleep();
    
    void updateAccel();
    
    void updateGyro();
    
    uint16_t compress(uint8_t high, uint8_t low);
    
    void print(const int16_t x, const int16_t y, const int16_t z);
    
    uint8_t readRegister(const uint8_t register_address);
    
    int16_t get_aX();
    
    int16_t get_aY();
    
    int16_t get_aZ();
    
    int16_t get_tilt(int16_t v, int add);
    
    int16_t get_gX();
    
    int16_t get_gY();
    
    int16_t get_gZ();
};


#endif //MPU6050_HPP