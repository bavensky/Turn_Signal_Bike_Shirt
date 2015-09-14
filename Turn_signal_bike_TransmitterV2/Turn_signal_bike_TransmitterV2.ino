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
 
#define  BREAK          A0
#define  BUTTON_LEFT    A1
#define  BUTTON_RIGHT   A2
#define  DEBOUNCE       200

void setup()  {
  Serial.begin(9600);  
  
  pinMode(BREAK, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

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
  else if(digitalRead(BUTTON_LEFT) == 0)  {
    delay(DEBOUNCE);
    buf[1] = 2;
    Serial.println("Left");
  } 
  else if(digitalRead(BUTTON_RIGHT) == 0)  {
    delay(DEBOUNCE);
    buf[1] = 1;
    Serial.println("Right");
  }
  else {
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


