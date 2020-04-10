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
 *
 * 
 */
#include <Wire.h> //used because it includes int16_t type definition


//Constants
#define X_AXIS_PIN A0 //define pin you are using for X axis analog signal
#define Y_AXIS_PIN A1//define pin you are using for Y axis analog signal
#define Z_AXIS_PIN A2//define pin you are using for Z axis analog signal
#define X_OFFSET 66 
#define Y_OFFSET 4

class JoyStick{



    public:
            int8_t configrr();//Initializes analog read pins for the x,y and z axis.
            float X(void);//returns joysitck X position (+/-1);
            float Y(void);//returns joysitck y position (+/-1);
            float Z(void);//returns joysitck z position (button press) (0 or 1);
            float mapf(int16_t, float, float, float , float ); ///internal scaling function that works with floats
        
        
        private:

            int16_t X0=0;
            int16_t X1=0;
            int16_t X2=0;

};
