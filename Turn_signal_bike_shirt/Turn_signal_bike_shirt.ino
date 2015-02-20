   /*******************************************************************************
   * Project  : Turn signal bike shirt                                           *
   * Compiler : Arduino 1.5.5                                                    *
   * Board    : Arduino Duemilanove                                              *
   * Shield   : -                                                                *
   * Module   : LPD8806 RGB LED Strip                                            *
   * Library  : https://github.com/adafruit/LPD8806                              *
   * Author   : Bavensky :3                                                      *
   * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
   * Date     : 03/09/2014 [dd/mm/yyyy]                                          *
   *******************************************************************************/
   
  #include "LPD8806.h"
  #include "SPI.h"
  
  //  จำนวนของหลอด LED
  int nLEDs = 32;
  
  // หน่วงเวลา
  int wait = 10;
  int i=0;
  
  //  ขาข้อมูล(Data) ต่อขา Digital 2
  //  ขาสัญญาณนาฬิกา(Clock) ต่อขา Digital 3
  int dataPin  = 2;
  int clockPin = 3;
  
  LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
  
  void setup() 
  {
    Serial.begin(115200);
    strip.begin();
  }
  
  void loop() 
  {
    for(i=0; i<=32; i++)  {
      strip.setPixelColor(i, strip.Color(  127,  0,  0));
      i += 1;
      delay(wait);
      strip.show();
    }
//    for(int i=0; i<=5; i++)
//    {
//      for(int i=0; i<=6; i++)
//      {
//        strip.setPixelColor(i, strip.Color(  127,  0,  0));
//        delay(wait);
//        strip.show(); 
//      }
//      
//      for(int i=7; i<=13; i++)
//      {
//        strip.setPixelColor(i, strip.Color(  127,  127,  127));
//        delay(wait);
//        strip.show(); 
//      }
//      
//      for(int i=14; i<=29; i++)
//      {
//        strip.setPixelColor(i, strip.Color(  0,  127,  0));
//        delay(wait);
//        strip.show(); 
//      }
//      
//      for(int i=30; i<=36; i++)
//      {
//        strip.setPixelColor(i, strip.Color(  127,  127,  127));
//        delay(wait);
//        strip.show(); 
//      }
//      
//      for(int i=37; i<=44; i++)
//      {
//        strip.setPixelColor(i, strip.Color(  127,  0,  0));
//        delay(wait);
//        strip.show(); 
//      }
//      
//      // ดับทุกหลอด
//      for(int i=44; i>0; i--)
//      {
//        strip.setPixelColor(i, 0);
//        delay(wait);
//        strip.show(); 
//      }
//    }
//    flag();
//    delay(3000);
  }
    
  void flag()
  {
    // RED 
    strip.setPixelColor(0, strip.Color(  127,  0,  0));
    strip.setPixelColor(1, strip.Color(  127,  0,  0));
    strip.setPixelColor(2, strip.Color(  127,  0,  0));
    strip.setPixelColor(3, strip.Color(  127,  0,  0));
    strip.setPixelColor(4, strip.Color(  127,  0,  0));
    strip.setPixelColor(5, strip.Color(  127,  0,  0));
    strip.setPixelColor(6, strip.Color(  127,  0,  0));
    
    strip.setPixelColor(37, strip.Color(  127,  0,  0));
    strip.setPixelColor(38, strip.Color(  127,  0,  0));
    strip.setPixelColor(39, strip.Color(  127,  0,  0));
    strip.setPixelColor(40, strip.Color(  127,  0,  0));
    strip.setPixelColor(41, strip.Color(  127,  0,  0));
    strip.setPixelColor(42, strip.Color(  127,  0,  0));
    strip.setPixelColor(43, strip.Color(  127,  0,  0));
  
    
    // White 
    strip.setPixelColor(7, strip.Color(  127,  127,  127));
    strip.setPixelColor(8, strip.Color(  127,  127,  127));
    strip.setPixelColor(9, strip.Color(  127,  127,  127));
    strip.setPixelColor(10, strip.Color(  127,  127,  127));
    strip.setPixelColor(11, strip.Color(  127,  127,  127));
    strip.setPixelColor(12, strip.Color(  127,  127,  127));
    strip.setPixelColor(13, strip.Color(  127,  127,  127));
    
    strip.setPixelColor(30, strip.Color(  127,  127,  127));
    strip.setPixelColor(31, strip.Color(  127,  127,  127));
    strip.setPixelColor(32, strip.Color(  127,  127,  127));
    strip.setPixelColor(33, strip.Color(  127,  127,  127));
    strip.setPixelColor(34, strip.Color(  127,  127,  127));
    strip.setPixelColor(35, strip.Color(  127,  127,  127));
    strip.setPixelColor(36, strip.Color(  127,  127,  127));
     
    
    // Blue
    strip.setPixelColor(14, strip.Color(  0,  127,  0));
    strip.setPixelColor(15, strip.Color(  0,  127,  0));
    strip.setPixelColor(16, strip.Color(  0,  127,  0));
    strip.setPixelColor(17, strip.Color(  0,  127,  0));
    strip.setPixelColor(18, strip.Color(  0,  127,  0));
    strip.setPixelColor(19, strip.Color(  0,  127,  0));
    strip.setPixelColor(20, strip.Color(  0,  127,  0));
    strip.setPixelColor(21, strip.Color(  0,  127,  0));
    
    strip.setPixelColor(22, strip.Color(  0,  127,  0));
    strip.setPixelColor(23, strip.Color(  0,  127,  0));
    strip.setPixelColor(24, strip.Color(  0,  127,  0));
    strip.setPixelColor(25, strip.Color(  0,  127,  0));
    strip.setPixelColor(26, strip.Color(  0,  127,  0));
    strip.setPixelColor(27, strip.Color(  0,  127,  0));
    strip.setPixelColor(28, strip.Color(  0,  127,  0));
    strip.setPixelColor(29, strip.Color(  0,  127,  0));
    strip.show(); 
  }

 
