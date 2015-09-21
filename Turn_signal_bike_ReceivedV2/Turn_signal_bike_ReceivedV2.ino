/******************************************************************************
* Project  : Turn signal bike shirt  Received V.2                             *
* Compiler : Arduino 1.5.5                                                    *
* Board    : Arduino Nano                                                     *
* Shield   : -                                                                *
* Module   : LPD8806 RGB LED Strip                                            *
* Library  : https://github.com/adafruit/LPD8806                              *
* Author   : Bavensky :3                                                      *
* E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
* Date     : 13/08/2015 [dd/mm/yyyy]                                          *
*******************************************************************************/
#include <NRF24.h>
#include "LPD8806.h"
#include "SPI.h"

// CE : pin 9 and CSN : pin 10
NRF24 nrf24(9, 10);

//  จำนวนของหลอด LED
int nLEDs = 40;

// หน่วงเวลา
int wait  =  30;
int received = 0;
int _loop;

//  ขาข้อมูล(Data) ต่อขา Digital 4
//  ขาสัญญาณนาฬิกา(Clock) ต่อขา Digital 3
int dataPin  = 4;
int clockPin = 3;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

int row1  = 0;
int row2  = 0;
int row3  = 0;
int row4  = 0;
int row5  = 0;

int stoplight[] = {3, 4, 10, 11, 12, 13, 17, 18, 19, 20, 21, 22, 26, 27, 28, 29, 35, 36};

// เลี้ยวขวา
int realkwastep1[9] = {2, 12, 16, 17, 18, 19, 20, 28, 34};
int realkwastep2[9] = {3, 11, 17, 18, 19, 20, 21, 27, 35};
int realkwastep3[9] = {4, 10, 18, 19, 20, 21, 22, 26, 36};
int realkwastep4[9] = {5, 9, 19, 20, 21, 22, 23, 25, 37};
// เลี้ยวซ้าย
int realsaistep1[9] = {5, 11, 19, 20, 21, 22, 23, 27, 37};
int realsaistep2[9] = {4, 12, 18, 19, 20, 21, 22, 28, 36};
int realsaistep3[9] = {3, 13, 17, 18, 19, 20 , 21, 29, 35};
int realsaistep4[9] = {2, 14, 16, 17, 18, 19, 20, 30, 34};

int* realkwa[5];
int* realsai[5];
int* turn;

int m;

void rainbowCycle(uint8_t wait);
uint32_t Wheel(uint16_t WheelPos);

void setup()
{
  realkwa[1] = realkwastep1;
  realkwa[2] = realkwastep2;
  realkwa[3] = realkwastep3;
  realkwa[4] = realkwastep4;

  realsai[1] = realsaistep1;
  realsai[2] = realsaistep2;
  realsai[3] = realsaistep3;
  realsai[4] = realsaistep4;

  strip.begin();
   
  Serial.begin(9600);
  
  if (!nrf24.init())
    Serial.println("NRF24 init failed");
  if (!nrf24.setChannel(9))
    Serial.println("setChannel failed");
  if (!nrf24.setThisAddress((uint8_t*)"bicycle", 5))
    Serial.println("setThisAddress failed");
  if (!nrf24.setPayloadSize(32))
    Serial.println("setPayloadSize failed");
  if (!nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm))
    Serial.println("setRF failed");    
  if (!nrf24.powerUpRx())
      Serial.println("powerOnRx failed");    
  Serial.println("initialised");
  dark_light();
}

void loop()  {
  uint8_t buf[32];
  uint8_t len = sizeof(buf);
  nrf24.waitAvailable();

  if (nrf24.recv(buf, &len))  {
    if(buf[1] == 1) {
      turn_left();
    }
    if(buf[1] == 2) {
      turn_right();
    }
    if(buf[1] == 3) {
      theaterChase(strip.Color(127, 0, 0), 30);
    }
    if(buf[1] == 4) {
      rainbow(1);
    }
    else if(buf[1] == 0)  {
      dark_light();
    } 
  }
}    //  End loop

void turn_right() {
  m = 1;
  for (int i = 0; i < 4; i++) {
    dark_light();
    turn = realkwa[m];
    
    for (int i = 0; i < 9; i++) {
      strip.setPixelColor(*turn++, strip.Color(  255,  0,  200));
      strip.show();
    }
    delay(300);
    m++;
    if (m == 5)  m = 1;
    
    uint8_t buf[32];
    uint8_t len = sizeof(buf);
    nrf24.waitAvailable();
    if (nrf24.recv(buf, &len))  {
      if(buf[1] == 0) {
        m = 1;
        i = 5;
      } 
    }  
    
  }
}

void turn_left() {
  m = 1;
  for (int i = 0; i < 4; i++) {
    dark_light();
    turn = realsai[m];
    
    for (int i = 0; i < 9; i++) {
      strip.setPixelColor(*turn++, strip.Color(  255,  0,  200));
      strip.show();
    }
    delay(300);
    m++;
    if (m == 5)  m = 1;

    uint8_t buf[32];
    uint8_t len = sizeof(buf);
    nrf24.waitAvailable();
    if (nrf24.recv(buf, &len))  {
      if(buf[1] == 0) {
        m = 1;
        i = 5;
      } 
    }
    
  }
}

void bike_break()  {
  for(int i=0; i<18; i++) { 
     strip.setPixelColor(stoplight[i], strip.Color(  255,  0,  0));
  }
  strip.show();
  delay(wait);
}

void dark_light()  {
  //ดับทุกหลอด
  for (int l = 0; l <= 40; l++)  {
    strip.setPixelColor(l, 0);
  }
  strip.show();
  delay(wait);
}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128; // red down
      g = WheelPos % 128;       // green up
      b = 0;                    // blue off
      break;
    case 1:
      g = 127 - WheelPos % 128; // green down
      b = WheelPos % 128;       // blue up
      r = 0;                    // red off
      break;
    case 2:
      b = 127 - WheelPos % 128; // blue down
      r = WheelPos % 128;       // red up
      g = 0;                    // green off
      break;
  }
  return(strip.Color(r,g,b));
}
