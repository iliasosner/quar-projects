/*
 * L3GD20 Library Source File
 *
 * @file    L3GD20.cpp
 * @author  Ilia Sosner - March 27, 2020
 * @description   This file defines function for the L3GD20 gyroscope
 * Library. This library untilizes the Wire library for i2c communication. 
 * Functions include setting configuration registers and pulling X,Y,Z gyroscope data. 
 *
 *
 * https://github.com/iliasosner/quar-projects.git
 *
 * Development environment specifics:
 * 	IDE: Arduino 1.8.12
 * 	Hardware Platform: Teensy 3.6
 *  L3GD20 on GY89 Breakout
 *
 * @section LICENSE
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without 
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
 * of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or substantial
 *  portions of the Software.
 *
 *  HE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 *  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 *
 * 
 */

#include "L3GD20.h"

//constants
#define ADD 0x6B
#define CTRL1 0x20
#define CTRL2 0x21
#define CTRL3 0x22
#define CTRL4 0x23
#define CTRL5 0x24
#define FIFO_CTRL 0x2E
#define STATUS_A 0x27
#define Xl 0x28
#define Xh 0x29
#define Yl 0x2A
#define Yh 0x2B
#define Zl 0x2C
#define Zh 0x2D
#define Temp_l 0x26




int L3GD20::config(){

//This function sets all the configuration registers of the LSM303D IC to a working baseline.


//Write Control Register 1
Wire.beginTransmission(ADD); 
Wire.write(byte(CTRL1));
Wire.write(byte(B00011111)); 
Wire.endTransmission();
delay(25);

//Write Control Register 2
Wire.beginTransmission(ADD); 
Wire.write(byte(CTRL2));
Wire.write(byte(B00100101)); 
Wire.endTransmission();
delay(25);

//Write Control Register 3
Wire.beginTransmission(ADD);
Wire.write(byte(CTRL3));
Wire.write(byte(B00000000)); 
Wire.endTransmission();
delay(25);

//Write Control Register 4
Wire.beginTransmission(ADD); 
Wire.write(byte(CTRL4));
Wire.write(byte(B00010000)); 
Wire.endTransmission();
delay(25);

//Write Control Register 5
Wire.beginTransmission(ADD); 
Wire.write(byte(CTRL5));
Wire.write(byte(B01000000));  
Wire.endTransmission();
delay(25);

//Write FIFO Control register
Wire.beginTransmission(ADD);
Wire.write(byte(FIFO_CTRL));
Wire.write(byte(B01000000));  
Wire.endTransmission();
delay(25);

}

float L3GD20::mapf(int16_t x, float in_min, float in_max, float out_min, float out_max){

            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float L3GD20::Xg(){
///////////////////Read X Gyro data Low
Wire.beginTransmission(ADD); 
Wire.write(byte(Xl)); 
Wire.endTransmission(); 
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    }

///////////////////Read X Gyro data High
Wire.beginTransmission(ADD); 
Wire.write(byte(Xh)); 
Wire.endTransmission();
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
X3=mapf(X2,-32768, 32768,-500.0,500.0); ///scale the signed int to +-500 dps
return X3;

}

float L3GD20::Yg(){
///////////////////Read Y Gyro data Low
Wire.beginTransmission(ADD); 
Wire.write(byte(Yl)); 
Wire.endTransmission();
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    }

///////////////////Read Y Gyro data High
Wire.beginTransmission(ADD); 
Wire.write(byte(Yh));  
Wire.endTransmission();
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
      }
X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
X3=mapf(X2,-32768, 32768,-500.0,500.0); ///scale the signed int to +-500 dps
return X3;
}



float L3GD20::Zg(){
///////////////////Read Z Gyro data Low
Wire.beginTransmission(ADD); 
Wire.write(byte(Zl)); 
Wire.endTransmission();
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    }

///////////////////Read Z Gyro data High
Wire.beginTransmission(ADD); 
Wire.write(byte(Zh));
Wire.endTransmission();
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
X3=mapf(X2,-32768, 32768,-500.0,500.0); ///scale the signed int to +-500 dps
return X3;
}




float L3GD20::Temp(){
///////////////////Read Temp Data
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Temp_l)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X5=Wire.read();
    }




X3=mapf(X5,-2040,2040,-40,85); 


return X3;

}

