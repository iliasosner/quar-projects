/*
 * LS303D Library Source File
 *
 * @file    LSM303D.cpp
 * @author  Ilia Sosner - March 27, 2020
 * @description   This file defines function for the LS303D Accelerometer/Magnotometer
 * Library. This library untilizes the Wire library for i2c communication. 
 * Functions include setting configuration registers, pulling X,Y,Z accelerometer and magnetometer data. 
 *
 *
 * https://github.com/iliasosner/quar-projects.git
 *
 * Development environment specifics:
 * 	IDE: Arduino 1.8.12
 * 	Hardware Platform: Teensy 3.6
 * 	LS303D on GY89 Breakout
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

#include "LSM303D.h"

//constants
#define ADD 0x1D
#define CTRL0 0x1F
#define CTRL1 0x20
#define CTRL2 0x21
#define CTRL3 0x22
#define CTRL4 0x23
#define CTRL5 0x24
#define CTRL6 0x25
#define CTRL7 0x26
#define FIFO_CTRL 0x2E
#define STATUS_A 0x27
#define Xal 0x28
#define Xah 0x29
#define Yal 0x2A
#define Yah 0x2B
#define Zal 0x2C
#define Zah 0x2D
#define Xml 0x08
#define Xmh 0x09
#define Yml 0x0A
#define Ymh 0x0B
#define Zml 0x0C
#define Zmh 0x0D
#define Temp_l 0x05
#define Temp_h 0x06



int LSM303D::config(){

//This function sets all the configuration registers of the LSM303D IC to a working baseline.

//Write Control Register 0
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(CTRL0));
Wire.write(byte(B01000000)); // 
Wire.endTransmission();// End transmission
delay(25);

//Write Control Register 1
Wire.beginTransmission(ADD); 
Wire.write(byte(CTRL1));
Wire.write(byte(B01100111)); 
Wire.endTransmission();
delay(25);

//Write Control Register 2
Wire.beginTransmission(ADD); 
Wire.write(byte(CTRL2));
Wire.write(byte(B00001000)); 
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
Wire.write(byte(B00000000)); 
Wire.endTransmission();
delay(25);

//Write Control Register 5
Wire.beginTransmission(ADD); 
Wire.write(byte(CTRL5));
Wire.write(byte(B11110000));  
Wire.endTransmission();
delay(25);

//Write Control Register 6
Wire.beginTransmission(ADD);
Wire.write(byte(CTRL6));
Wire.write(byte(B00100000));  
Wire.endTransmission();
delay(25);

//Write Control Register 7
Wire.beginTransmission(ADD); 
Wire.write(byte(CTRL7));
Wire.write(byte(B00000000));  
Wire.endTransmission();
delay(25);

//Write FIFO Control register
Wire.beginTransmission(ADD);
Wire.write(byte(FIFO_CTRL));
Wire.write(byte(B01000000));  
Wire.endTransmission();
delay(25);

}

float LSM303D::mapf(int16_t x, float in_min, float in_max, float out_min, float out_max){

            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float LSM303D::Xa(){
///////////////////Read X Accel data Low
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Xal)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    }

///////////////////Read X Accel data High
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Xah)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}

float LSM303D::Ya(){
///////////////////Read Y Accel data Low
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Yal)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    }

///////////////////Read Y Accel data High
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Yah)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}

float LSM303D::Za(){
///////////////////Read Z Accel data Low
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Zal)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    }

///////////////////Read Z Accel data High
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Zah)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}

float LSM303D::Xm(){
///////////////////Read X Accel data Low
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Xml)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xml Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Xmh)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
       //Serial.print("Xmh Register:  ");
       //Serial.println(X1,BIN);
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
//Serial.println(X2);     // prints the signed int

X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}

float LSM303D::Ym(){
///////////////////Read X Accel data Low
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Yml)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xml Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Ymh)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
       //Serial.print("Xmh Register:  ");
       //Serial.println(X1,BIN);
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
//Serial.println(X2);     // prints the signed int

X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}

float LSM303D::Zm(){
///////////////////Read X Accel data Low
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Zml)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xml Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Zmh)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
       //Serial.print("Xmh Register:  ");
       //Serial.println(X1,BIN);
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
//Serial.println(X2);     // prints the signed int

X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}


float LSM303D::Temp(){

///////////////////Read X Accel data Low
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Temp_l)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xml Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(ADD); //begin transmission with LSM303D
Wire.write(byte(Temp_h)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(ADD,1);
  if(Wire.available()){
       X1=Wire.read();
       //Serial.print("Xmh Register:  ");
       //Serial.println(X1,BIN);
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
//Serial.println(X2);     // prints the signed int

if(X2&mask1){ /// 2's complement detect sign bit () 
  X4=-1;
}
else{
  X4=1;
}

//Serial.print("X2 Pre-scale: ");
//Serial.print(X2);

//Serial.print("   X4 int: ");
//Serial.print(X4);
///X2=((~X2)&mask2)+1;  ///2's complement Bit flip
///Serial.print("   X2: ");
///Serial.println(X2,HEX);
//X4=X4*X2;
X3=mapf(X2,-2040,2040,-40,85)+10; ///scale the signed int to +-4g's (current accel range)

//Serial.print("   X3 Post-scale: ");
//Serial.print(X3);
return X3;

}

