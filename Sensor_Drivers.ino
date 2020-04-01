/*
 * Sensor Development Project
 *
 * @file    Sensor_Drivers.h
 * @author  Ilia Sosner - March 27, 2020
 * @description   This file is intended for testing various sensor libraries. It initiaes communcations 
 * on the I2C and serial busses, pulls data from sensors, and displays it in the serial monitor.
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



//Created in quarantine on 25 March 2020
//Ilia Sosner 
#include "LSM303D.h"
#include "L3GD20.h"
#include "BMP180.h"
#include "JoyStick.h"



LSM303D LSM;
L3GD20 L3G;
BMP180 BMP;
JoyStick Joy;

void setup() {

  Wire.begin(); //Join i2c bus
  Serial.begin(9600); //for Debugging monitor
  delay(5000);
  //LSM.config();
  //L3G.config();
  //Serial.println("Calibrating");
  //BMP.cal();
 //Serial.println("Calibration done!");
 Joy.configrr();
  
  }




void loop() {
  Serial.print("X-Axis:   ");
  Serial.print(Joy.X());

  Serial.print("    Y-Axis:   ");
  Serial.print(Joy.Y());

  Serial.print("    Z-Axis:   ");
  Serial.println(Joy.Z());

 /*
Serial.print("X Accel: ");
Serial.print( LSM.Xa());
Serial.print("    Y Accel: ");
Serial.print( LSM.Ya());
Serial.print("    Z Accel: ");
Serial.print( LSM.Za());

Serial.print("   X Mag: ");
Serial.print( LSM.Xm());
Serial.print("    Y Mag: ");
Serial.print( LSM.Ym());
Serial.print("    Z Mag: ");
Serial.print( LSM.Zm());
Serial.print("    Temp: ");
Serial.println(LSM.Temp());
delay(200);


Serial.print("   X Gyro: ");
Serial.print( L3G.Xg());
Serial.print("    Y Gyro: ");
Serial.print( L3G.Yg());
Serial.print("    Z Gyro: ");
Serial.print( L3G.Zg());
Serial.print("    Temp: ");
Serial.println(L3G.Temp());
*/
//Serial.println(BMP.read_byte(0xD0));
 //Serial.println("main loop!");
 //BMP.raw_temp();
 //BMP.raw_pre();
//BMP.get_data(); //prints pressure in pascals and tempreture in 0.1 degree celsius 
delay(10);

}
