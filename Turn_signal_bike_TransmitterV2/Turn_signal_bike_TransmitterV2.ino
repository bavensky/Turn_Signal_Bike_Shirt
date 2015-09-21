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
#include <NRF24.h>
#include "SPI.h"

NRF24 nrf24(9, 10);
 
#define  BUTTON_LEFT    A0
#define  BUTTON_RIGHT   A1
#define  BREAK          A2
#define  BLINK          A3
#define  DEBOUNCE       100

void setup()  {
  Serial.begin(9600);  
  
  pinMode(BREAK, INPUT);
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);

  if (!nrf24.init())
    Serial.println("NRF24 init failed");
  if (!nrf24.setChannel(9))
    Serial.println("setChannel failed");
  if (!nrf24.setPayloadSize(32))
    Serial.println("setPayloadSize failed");
  if (!nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm))
    Serial.println("setRF failed");    
  nrf24.spiWriteRegister(NRF24_REG_1D_FEATURE, NRF24_EN_DYN_ACK);

  Serial.println("initialised");
  
}

void loop()  {
  uint8_t buf[32];
  if(digitalRead(BREAK) == 0)  {
    delay(DEBOUNCE);
    buf[1] = 3;
    Serial.println("Break");
  }
  if(digitalRead(BUTTON_LEFT) == 0)  {
    delay(DEBOUNCE);
    buf[1] = 2;
    Serial.println("Left");
  } 
  if(digitalRead(BUTTON_RIGHT) == 0)  {
    delay(DEBOUNCE);
    buf[1] = 1;
    Serial.println("Right");
  }
  if(digitalRead(BLINK) == 0)  {
    delay(DEBOUNCE);
    buf[1] = 4;
    Serial.println("SHOW");
  }
  if(digitalRead(BREAK) == 1 && digitalRead(BUTTON_LEFT) == 1 && digitalRead(BUTTON_RIGHT) == 1 && digitalRead(BLINK) == 1)
  {
    Serial.println("None");
    buf[1] = 0;
  }
    
  if (!nrf24.setTransmitAddress((uint8_t*)"bicycle", 5))
   Serial.println("setTransmitAddress failed");
  if (!nrf24.send(buf, sizeof(buf), true)) 
     Serial.println("send failed");  
  if (!nrf24.waitPacketSent())
     Serial.println("waitPacketSent failed");  

}


