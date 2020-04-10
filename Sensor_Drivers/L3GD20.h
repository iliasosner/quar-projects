/*
 * L3GD20 Library Header File
 *
 * @file    L3GD20.h
 * @author  Ilia Sosner - March 27, 2020
 * @description   This file defines function prototypes for the L3GD20 3-axis Gyroscope
 * Library. This library utilizes the Wire library for i2c communication. 
 * Functions include setting configuration registers, pulling X,Y,Z gyroscope data. 
 *
 *
 * https://github.com/iliasosner/quar-projects.git
 *
 * Development environment specifics:
 * 	IDE: Arduino 1.8.12
 * 	Hardware Platform: Teensy 3.6
 * 	L3GD20 on GY89 Breakout
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

#include <Wire.h>

class L3GD20{



    public:

            int   config(void); //set configuration registers and start data following
            float Xg(void);//returns X accelerometer data in g's
            float Yg(void);//returns Y accelerometer data in g's
            float Zg(void);//returns Z accelerometer data in g's
            float Temp(void);// returns Temperture of IC
            float mapf(int16_t, float, float, float , float ); ///internal scaling function that works with floats
        
        
        private:
int X0=0;
int X1=0;
int16_t X2=0;
int16_t X4=0;
float X3=0;
int8_t X5=0;
int16_t mask1=0x0800; ///b0000100000000000
int16_t mask2=0x0FFF; ///b0000111111111111

};
