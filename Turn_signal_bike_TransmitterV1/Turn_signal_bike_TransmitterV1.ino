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

#define  BREAK          3
#define  BUTTON_LEFT    4
#define  BUTTON_RIGHT   5
#define  DEBOUNCE       200

RCSwitch mySwitch = RCSwitch();

int transmitter  =  0;

void setup()  {
  Serial.begin(9600);  
  pinMode(BREAK, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
}

void loop()  {

  if(digitalRead(BREAK) == 0)  {
    delay(DEBOUNCE);
    transmitter = 1;
  }
  else if(digitalRead(BUTTON_LEFT) == 0)  {
    delay(DEBOUNCE);
    transmitter = 2;
  } 
  else if(digitalRead(BUTTON_RIGHT) == 0)  {
    delay(DEBOUNCE);
    transmitter = 3;
  }
  else {
    transmitter = 0;
  }
    
  mySwitch.send(transmitter,  24);
  Serial.println(transmitter);

}
