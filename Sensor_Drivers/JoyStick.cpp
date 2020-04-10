/*
 * L3GD20 Library Header File
 *
 * @file    JoyStick.h
 * @author  Ilia Sosner - March 27, 2020
 * @description   This file defines class and function prototypes for a generic geeetech analog joystick
 * Library. This library utilizes the analog read functions of arduino/ teensyduino enviroment.
 * Functions include reading raw analog values from the joy stick and scaling them to a signed float value +/-1. 
 *
 *
 * https://github.com/iliasosner/quar-projects.git
 *
 * Development environment specifics:
 * 	IDE: Arduino 1.8.12
 * 	Hardware Platform: Teensy 3.6
 * 	Geeetech.com generic analog JoyStick.
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
 */
#include "JoyStick.h"




int8_t JoyStick::configrr(){

//This function sets analog input pins .
    pinMode(X_AXIS_PIN,INPUT);
    pinMode(Y_AXIS_PIN,INPUT);
    pinMode(Z_AXIS_PIN,INPUT);

}

float JoyStick::mapf(int16_t x, float in_min, float in_max, float out_min, float out_max){

            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float JoyStick::X(){

X0=analogRead(X_AXIS_PIN)-X_OFFSET;
return mapf(X0,76, 956,-1.0,1.0); ///scale the  int to +-1.0

}

float JoyStick::Y(){

X0=analogRead(Y_AXIS_PIN)-Y_OFFSET;
return mapf(X0,-3, 1019,-1.0,1.0); ///scale the int to +-1.0

}


float JoyStick::Z(){

X0=analogRead(Z_AXIS_PIN);
return (int)mapf(X0,155, 1022,0,1.0); ///scale the  int to 0 or 1

}






 
