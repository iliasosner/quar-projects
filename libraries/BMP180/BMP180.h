/*
 * BMP180 Library Header File
 *
 * @file    BMP180.h
 * @author  Ilia Sosner - March 28, 2020
 * @description   This file defines a class and function prototypes for the BMP180 barometer
 * Library. This library utilizes the Wire library for i2c communication. 
 * Functions include setting configuration registers, pulling calibaration, pressure and 
 * tempreture data. 
 *
 *
 * https://github.com/iliasosner/quar-projects.git
 *
 * Development environment specifics:
 * 	IDE: Arduino 1.8.12
 * 	Hardware Platform: Teensy 3.6
 * 	BMP180 on GY89 Breakout
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

class BMP180{



    public:

            int16_t   configrr(void); //set configuration registers and start data following
            int   cal(void); //Pulls configurtation data from eprom on device
            int16_t read_2bytes(int8_t);
            int8_t write_byte(byte, byte);
            int8_t raw_temp(void);
            int8_t raw_pre(void);
            int8_t calc_temp(void);
            int8_t calc_pre(void);
            void get_data(void);
            int16_t read_byte(int8_t);
        
        private:

        /////calibration variables
        int16_t AC1=0;
        int16_t AC2=0;
        int16_t AC3=0;
        uint16_t AC4=0;
        uint16_t AC5=0;
        uint16_t AC6=0;
        int16_t BB1=0;
        int16_t B2=0;
        int16_t MB=0;
        int16_t MC=0;
        int16_t MD=0;
        int32_t UT=0;
        int32_t UP=0;
        
        ///for temp and presure calculations
        int32_t x1=0;
        int32_t x2=0;
        int32_t x3=0;

        int16_t B3=0;
        uint32_t B4=0;
        int16_t B5=0;
        int16_t B6=0;
        uint32_t B7=0;

        int16_t T=0;
        int32_t p=0;
        ////

        ////for i2c read and write functions 
        byte X0=0;
        byte X1=0;
        uint16_t X2=0;
        
};
