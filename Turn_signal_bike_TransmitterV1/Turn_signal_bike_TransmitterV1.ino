   /******************************************************************************
   * Project  : Turn signal bike shirt Transmitter                               *
   * Compiler : Arduino 1.5.5                                                    *
   * Board    : Arduino Nano                                                     *
   * Shield   : -                                                                *
   * Module   : LPD8806 RGB LED Strip                                            *
   * Library  : https://github.com/adafruit/LPD8806                              *
   * Author   : Bavensky :3                                                      *
   * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
   * Date     : 21/02/2015 [dd/mm/yyyy]                                          *
   *******************************************************************************/
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  
}

void loop() {
  mySwitch.send(1,24);
  delay(10000);
  mySwitch.send(2,24);
  delay(10000);
  mySwitch.send(3,24);
  delay(10000);
}
