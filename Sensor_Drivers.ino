//Created in quarantine on 25 March 2020

//Ilia Sosner 
//Addr: 0x1D ACK LSM303D 3-Axis Accelerometer and Magnetometer
//Addr: 0x6B ACK L3GD20 3-axis Gyroscope
//Addr: 0x77 ACK

#include <Wire.h>

#define LSM303D 0x1D

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


//set up variables
int X0=0;
int X1=0;
int16_t X2=0;
int16_t X4=0;
float X3=0;






float mapf(int16_t x, float in_min, float in_max, float out_min, float out_max){

            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



int LSM303D_config(){
///This function sets all the configuration registers of the LSM303D IC to a working baseline.

//////////////////Write Control Register 0
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(CTRL0));
Wire.write(byte(B01000000)); // 
Wire.endTransmission();// End transmission
delay(25);

//////////////////Write Control Register 1
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(CTRL1));
Wire.write(byte(B01100111)); // 
Wire.endTransmission();// End transmission
delay(25);

//////////////////Write Control Register 2
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(CTRL2));
Wire.write(byte(B00001000)); // 
Wire.endTransmission();// End transmission
delay(25);

//////////////////Write Control Register 3
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(CTRL3));
Wire.write(byte(B00000000)); // 
Wire.endTransmission();// End transmission
delay(25);

//////////////////Write Control Register 4
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(CTRL4));
Wire.write(byte(B00000000)); // 
Wire.endTransmission();// End transmission
delay(25);

//////////////////Write Control Register 5
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(CTRL5));
Wire.write(byte(B11110000)); // 
Wire.endTransmission();// End transmission
delay(25);

//////////////////Write Control Register 6
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(CTRL6));
Wire.write(byte(B00100000)); // 
Wire.endTransmission();// End transmission
delay(25);

//////////////////Write Control Register 7
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(CTRL7));
Wire.write(byte(B00000000)); // 
Wire.endTransmission();// End transmission
delay(25);

//////////////////Write FIFO Control register
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(FIFO_CTRL));
Wire.write(byte(B01000000)); // 
Wire.endTransmission();// End transmission
delay(25);

}


float Xa_data(){
///////////////////Read X Accel data Low
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Xal)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xal Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Xah)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
       X1=Wire.read();
       //Serial.print("Xah Register:  ");
       //Serial.println(X1,BIN);
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
//Serial.println(X2);     // prints the signed int

X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}


float Ya_data(){
///////////////////Read X Accel data Low
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Yal)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Yal Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Yah)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
       X1=Wire.read();
       //Serial.print("Yah Register:  ");
       //Serial.println(X1,BIN);
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
//Serial.println(X2);     // prints the signed int

X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}

float Za_data(){
///////////////////Read X Accel data Low
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Zal)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Yal Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Zah)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
       X1=Wire.read();
       //Serial.print("Yah Register:  ");
       //Serial.println(X1,BIN);
      }

X2=X0|(X1<<8);          //combines 2 bytes into a 16-bit signed int
//Serial.println(X2);     // prints the signed int

X3=mapf(X2,-32768, 32768,-4.0,4.0); ///scale the signed int to +-4g's (current accel range)
return X3;

}

float Xm_data(){
///////////////////Read X Accel data Low
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Xml)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xml Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Xmh)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
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

float Ym_data(){
///////////////////Read X Accel data Low
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Yml)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xml Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Ymh)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
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

float Zm_data(){
///////////////////Read X Accel data Low
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Zml)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xml Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Zmh)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
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


float Temp(){

int16_t mask1=0x0800; ///b0000100000000000
int16_t mask2=0x0FFF; ///b0000111111111111


///////////////////Read X Accel data Low
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Temp_l)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
  if(Wire.available()){
     X0=Wire.read();
    // Serial.print("Xml Register:  ");
     //Serial.println(X0,BIN);
    }

///////////////////Read X Accel data High
Wire.beginTransmission(LSM303D); //begin transmission with LSM303D
Wire.write(byte(Temp_h)); // 
Wire.endTransmission();// End transmission
Wire.requestFrom(LSM303D,1);
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




void setup() {
 
  Wire.begin(); //Join i2c bus
  Serial.begin(9600); //for Debugging monitor
  LSM303D_config();
}




void loop() {
 
Serial.print("X Accel: ");
Serial.print( Xa_data());
Serial.print("    Y Accel: ");
Serial.print( Ya_data());
Serial.print("    Z Accel: ");
Serial.print( Za_data());

Serial.print("   X Mag: ");
Serial.print( Xa_data());
Serial.print("    Y Mag: ");
Serial.print( Ya_data());
Serial.print("    Z Mag: ");
Serial.print( Za_data());
Serial.print("    Temp: ");
Serial.println( Temp());
delay(200);



}
