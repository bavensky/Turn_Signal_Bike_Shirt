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
#include "LPD8806.h"
#include "SPI.h"

#define  BREAK          A0
#define  BUTTON_LEFT    A1
#define  BUTTON_RIGHT   A2
#define  DEBOUNCE       200

RCSwitch mySwitch = RCSwitch();
int transmitter  =  0;

int nLEDs = 12;
int dataPin  = 4;
int clockPin = 3;
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

int wait  =  30;
int _loop = 0;

void setup()  {
  Serial.begin(9600);  
  
  strip.begin();
  
  pinMode(BREAK, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
}

void loop()  {

  if(digitalRead(BREAK) == 0)  {
    delay(DEBOUNCE);
    bike_break();
    transmitter = 1;
    Serial.println("Break");
  }
  else if(digitalRead(BUTTON_LEFT) == 0)  {
    delay(DEBOUNCE);
    turn_left();
    transmitter = 2;
    Serial.println("Left");
  } 
  else if(digitalRead(BUTTON_RIGHT) == 0)  {
    delay(DEBOUNCE);
    turn_right();
    transmitter = 3;
    Serial.println("Right");
  }
  else {
    Serial.println("None");
    flash(); 
    transmitter = 0;
  }
    
  mySwitch.send(transmitter,  24);
  Serial.println(transmitter);

}

void flash()  {
  for(_loop=0; _loop<=11; _loop++)  {
    strip.setPixelColor(_loop, strip.Color(  255,  255,  255));
  }
  strip.show();
  delay(wait);
}

void bike_break()  {
  for(_loop=0; _loop<=11; _loop++)  {
    strip.setPixelColor(_loop, strip.Color(  255,  0,  0));
  }
  strip.show();
  delay(wait);
}

void turn_right()  {
  for(_loop=0; _loop<=5; _loop++)  {
    strip.setPixelColor(_loop, strip.Color(  0,  0,  0));    
    delay(wait);
  }
  strip.show();
  
  for(_loop=6; _loop<=11; _loop++)  {
    strip.setPixelColor(_loop, strip.Color(  200,  0,  200));
    strip.show();
    delay(wait);
  }
  for(_loop=6; _loop<=11; _loop++)  {
    strip.setPixelColor(_loop, strip.Color(  0,  0,  0));
    strip.show();
    delay(wait);
  } 
}

void turn_left()  { 
  for(_loop=6; _loop<=11; _loop++)  {
    strip.setPixelColor(_loop, strip.Color(  0,  0,  0));    
    delay(wait);
  }
  strip.show();
  
  for(_loop=0; _loop<=5; _loop++)  {
    strip.setPixelColor(_loop, strip.Color(  200,  0,  200));
    strip.show();
    delay(wait);
  }
  for(_loop=0; _loop<=5; _loop++)  {
    strip.setPixelColor(_loop, strip.Color(  0,  0,  0));
    strip.show();
    delay(wait);
  }
  
}

