// -------------------------------------------------------------
// CANtest for Teensy 3.6 dual CAN bus
// by Collin Kidder, Based on CANTest by Pawelsky (based on CANtest by teachop)
//
// Both buses are left at default 250k speed and the second bus sends frames to the first
// to do this properly you should have the two buses linked together. This sketch
// also assumes that you need to set enable pins active. Comment out if not using
// enable pins or set them to your correct pins.
//
// This sketch tests both buses as well as interrupt driven Rx and Tx. There are only
// two Tx buffers by default so sending 5 at a time forces the interrupt driven system
// to buffer the final three and send them via interrupts. All the while all Rx frames
// are internally saved to a software buffer by the interrupt handler.
//

#include <FlexCAN.h>

#ifndef __MK66FX1M0__
  #error "Teensy 3.6 with dual CAN bus is required to run this example"
#endif

static CAN_message_t msg;
static uint8_t hex[17] = "0123456789abcdef";

// -------------------------------------------------------------
static void hexDump(uint8_t dumpLen, uint8_t *bytePtr)
{
  uint8_t working;
  while( dumpLen-- ) {
    working = *bytePtr++;
    Serial.write( hex[ working>>4 ] );
    Serial.write( hex[ working&15 ] );
  }
  Serial.write('\r');
  Serial.write('\n');
}


// -------------------------------------------------------------
void setup(void)
{
  delay(1000);
  Serial.println(F("Hello Teensy 3.6 dual CAN Test."));

  Can0.begin();  
  Can1.begin(1000000);

  //if using enable pins on a transceiver they need to be set on
  pinMode(13, OUTPUT);
 

  digitalWrite(13, HIGH);


  msg.ext = 0;
  msg.id = 0x02;
  msg.len = 8;
  msg.buf[0] = 0x00;
  msg.buf[1] = 0x00;
  msg.buf[2] = 0x00;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x0f;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0xf0;
  msg.buf[7] = 0x00;
}


// -------------------------------------------------------------
void loop(void)
{
 // CAN_message_t inMsg;
 // while (Can1.available()) 
  //{
   // Can0.read(inMsg);
    //Serial.print("CAN bus 1: "); hexDump(8, inMsg.buf);
  //}
  
  Can1.write(msg);
   //msg.buf[7]= msg.buf[7]+10;

delay(1000);
  

}
