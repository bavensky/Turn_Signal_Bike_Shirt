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

int stoplight[] = {0, 1, 13, 14, 15, 16, 17, 18, 19, 29, 30, 31, 32, 32,
                   6, 7, 8, 9, 10, 20, 21, 22, 23, 24, 25, 26, 38, 39};

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
}

void loop()  {
  uint8_t buf[32];
  uint8_t len = sizeof(buf);
  nrf24.waitAvailable();
  if (nrf24.recv(buf, &len))  {
    Serial.println(buf[1]);
    if(buf[1] == 1) {
        turn_right();
    }
    if(buf[1] == 2) {
      turn_left();
    }
    if(buf[1] == 3) {
      bike_break();
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
    delay(500);
    m++;
    if (m == 5)  m = 1;
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
    delay(500);
    m++;
    if (m == 5)  m = 1;
  }
}

void bike_break()  {
  for(int i=0; i<28; i++) {
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

