/*
 * BMP180 Library Header File
 *
 * @file    BMP180.h
 * @author  Ilia Sosner - March 28, 2020
 * @description   This file defines class functions for the BMP180 barometer
 * Library. This library utilizes the Wire library for i2c communication. 
 * Functions include setting configuration registers, pulling calibaration, pressure and 
 * tempreture data and calculating final values. Currently set at lowest resolution.
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
*/
#include "BMP180.h"


//constants
#define ADD 0x77 //device i2c address
#define oss 0 ///0-3 resoultion setting, "oversampling_setting"


int16_t BMP180::configrr(){

X0=0xF0;
Serial.println(X0,HEX);
X1=0x0E;
Serial.println(X1,HEX);
X2=X1+(X0<<8);          //combines 2 bytes into a 16-bit signed int

Serial.println(X2,HEX);
Serial.println(X2);

}



int16_t BMP180::read_byte(int8_t address){
    ///////////////////Reads one byte from start address
        Wire.beginTransmission(ADD); 
        Wire.write(byte(address)); 
        Wire.endTransmission(); 
        Wire.requestFrom(ADD,1);
             if(Wire.available()){
                X0=Wire.read();
            }
     
        return X0;
}




int16_t BMP180::read_2bytes(int8_t address){
    ///////////////////Reads two consecutive bytes from start address
        Wire.beginTransmission(ADD); 
        Wire.write(byte(address)); 
        Wire.endTransmission(); 
        Wire.requestFrom(ADD,1);
             if(Wire.available()){
                X0=Wire.read();
            }
        Wire.beginTransmission(ADD); 
        Wire.write(byte(address+0x01)); 
        Wire.endTransmission();
        Wire.requestFrom(ADD,1);
            if(Wire.available()){
              X1=Wire.read();
            }

        X2=X1|(X0<<8);          //combines 2 bytes into a 16-bit signed int
        return X2;
}


int8_t BMP180::write_byte(byte address, byte data){

        Wire.beginTransmission(ADD);
        Wire.write(byte(address));
        Wire.write(byte(data));  
        Wire.endTransmission();

}




int BMP180::cal(){

        AC1= read_2bytes(0xAA);
        delay(200);
        AC2= read_2bytes(0xAC);
        delay(200);
        AC3= read_2bytes(0xAE);
        delay(200);
        AC4= read_2bytes(0xB0);
        delay(200);
        AC5= read_2bytes(0xB2);
        delay(200);
        AC6= read_2bytes(0xB4);
        delay(200);
        BB1=  read_2bytes(0xB6);
        delay(200);
        B2= read_2bytes(0xB8);
        delay(200);
        MB= read_2bytes(0xBA);
        delay(200);
        MC= read_2bytes(0xBC);
        delay(200);
        MD= read_2bytes(0xBE);
        delay(200);
}



int8_t BMP180::raw_temp(){

        write_byte(0xF4,0x2E);
        delay(10);
        UT=read_2bytes(0xF6);

}


int8_t BMP180::raw_pre(){

        write_byte(0xF4,0x34+(oss<<6));
        delay(30);

          ///////////////////Reads three consecutive bytes from start address
        Wire.beginTransmission(ADD); 
        Wire.write(byte(0xF6)); 
        Wire.endTransmission(); 
        Wire.requestFrom(ADD,1);
            if(Wire.available()){
                X0=Wire.read();
                }

        Wire.beginTransmission(ADD); 
        Wire.write(byte(0xF7)); 
        Wire.endTransmission();
        Wire.requestFrom(ADD,1);
            if(Wire.available()){
                X1=Wire.read();
                }

        Wire.beginTransmission(ADD); 
        Wire.write(byte(0xF8)); 
        Wire.endTransmission();
        Wire.requestFrom(ADD,1);
            if(Wire.available()){
                X2=Wire.read();
                } 

        UP=(((X0<<16)+(X1<<8)+X2)>>(8-oss));

}




int8_t BMP180::calc_temp(){

        x1=(UT-AC6)*(AC5/pow(2,15));
        x2=MC*pow(2,11)/(x1+MD);
        B5=x1+x2;
        T=(B5+8)/pow(2,4);
}




int8_t BMP180::calc_pre(){

        B6=B5-4000;
        x1=(B2*(B6*B6/pow(2,12)))/pow(2,11);
        x2=AC2*B6/pow(2,11);
        x3=x1+x2;
        B3=(((AC1*4+x3)<<oss)+2)/4;
        x1=AC3*B6/pow(2,13);
        x2=(BB1*(B6*B6/pow(2,12)))/pow(2,16);
        x3=((x1+x2)+2)/pow(2,2);
        B4=AC4*(unsigned long)(x3+32768)/pow(2,15);
        B7=((unsigned long)UP-B3)*(50000>>oss);

            if (B7<0x80000000){
                  p=(B7*2)/B4;
            }
            else{
                  p=(B7/B4)*2;
            }
        x1=(p/pow(2,8))*(p/pow(2,8));
        x1=(x1*3038)/pow(2,16);
        x2=(-7357*p)/pow(2,16);
        p=p+(X1+X2+3791)/pow(2,4);

}

void BMP180::get_data(){

        raw_temp();
        raw_pre();
        calc_temp();

        Serial.print("Temp is:  ");
        Serial.print(T);

        calc_pre();

        Serial.print("    Pressure is:  ");
        Serial.println(p);
}




