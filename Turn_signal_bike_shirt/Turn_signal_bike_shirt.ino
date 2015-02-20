   /*******************************************************************************
   * Project  : Turn signal bike shirt                                           *
   * Compiler : Arduino 1.5.5                                                    *
   * Board    : Arduino Duemilanove                                              *
   * Shield   : -                                                                *
   * Module   : LPD8806 RGB LED Strip                                            *
   * Library  : https://github.com/adafruit/LPD8806                              *
   * Author   : Bavensky :3                                                      *
   * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
   * Date     : 20/02/2015 [dd/mm/yyyy]                                          *
   *******************************************************************************/
   
  #include "LPD8806.h"
  #include "SPI.h"
  
  //  จำนวนของหลอด LED
  int nLEDs = 32;
  
  // หน่วงเวลา
  int wait  =  50;
  int _loop;
  int one  =  0;
  int two  =  0;
  int three  =  0;
  int four  =  0;
  
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
    one    =  0;
    two    =  15;
    three  =  16;
    four   =  31;
    
    for(_loop=0; _loop<=8; _loop++)  {
      strip.setPixelColor(one, strip.Color(  127,  0,  0));
      strip.setPixelColor(two, strip.Color(  127,  0,  0));
      strip.setPixelColor(three, strip.Color(  127,  0,  0));
      strip.setPixelColor(one, strip.Color(  127,  0,  0));
      delay(wait);
      
      one += 1;
      two -= 1;
      three += 1;
      four -= 1;
    }
    strip.show();
    
    
//    for(one=7; one>=0; one--)  {
//      strip.setPixelColor(one, strip.Color(  127,  0,  0));
////      strip.show();
//      delay(wait);
//    } 
//    for(two=8; two<=15; two++)  {
//      strip.setPixelColor(two, strip.Color(  127,  0,  0));
//      strip.show();
//      delay(wait);
//    } 
    
//    if(one  <=  0)  {
//      dark_right();
//      one=0;
//    }
//
//    if(one  <=  0 && two  >=  15)  {
//      dark_right();
//      one=0;
//      two=0;
//      delay(2000);
//    }
    
    
    
  }    //  End loop
    
  void turn_right()
  {
//    ---->
    strip.setPixelColor(0, strip.Color(  127,  0,  0));
    strip.setPixelColor(1, strip.Color(  127,  0,  0));
    strip.setPixelColor(2, strip.Color(  127,  0,  0));
    strip.setPixelColor(3, strip.Color(  127,  0,  0));
    strip.setPixelColor(4, strip.Color(  127,  0,  0));
    strip.setPixelColor(5, strip.Color(  127,  0,  0));
    strip.setPixelColor(6, strip.Color(  127,  0,  0));
    strip.setPixelColor(7, strip.Color(  127,  0,  0));

//    <----    
    strip.setPixelColor(8, strip.Color(  127,  0,  0));
    strip.setPixelColor(9, strip.Color(  127,  0,  0));
    strip.setPixelColor(10, strip.Color(  127,  0,  0));
    strip.setPixelColor(11, strip.Color(  127,  0,  0));
    strip.setPixelColor(12, strip.Color(  127,  0,  0));
    strip.setPixelColor(13, strip.Color(  127,  0,  0));
    strip.setPixelColor(14, strip.Color(  127,  0,  0));
    strip.setPixelColor(15, strip.Color(  127,  0,  0));
    
//    ---->    
    strip.setPixelColor(16, strip.Color(  127,  0,  0));
    strip.setPixelColor(17, strip.Color(  127,  0,  0));
    strip.setPixelColor(18, strip.Color(  127,  0,  0));
    strip.setPixelColor(19, strip.Color(  127,  0,  0));
    strip.setPixelColor(20, strip.Color(  127,  0,  0));
    strip.setPixelColor(21, strip.Color(  127,  0,  0));
    strip.setPixelColor(22, strip.Color(  127,  0,  0));
    strip.setPixelColor(23, strip.Color(  127,  0,  0));

//    <----     
    strip.setPixelColor(24, strip.Color(  127,  0,  0));
    strip.setPixelColor(25, strip.Color(  127,  0,  0));
    strip.setPixelColor(26, strip.Color(  127,  0,  0));
    strip.setPixelColor(27, strip.Color(  127,  0,  0));
    strip.setPixelColor(28, strip.Color(  127,  0,  0));
    strip.setPixelColor(29, strip.Color(  127,  0,  0));
    strip.setPixelColor(30, strip.Color(  127,  0,  0));
    strip.setPixelColor(31, strip.Color(  127,  0,  0));
    
    delay(wait);
    strip.show(); 
  }
  
  void dark_right()  {
  //ดับทุกหลอด
  for(int l=7; l>=0; l--)  {
    strip.setPixelColor(l, 0);
    delay(wait);
  }
  for(int o=15; o>=8; o--)  {
    strip.setPixelColor(o, 0);
    delay(wait);
  }
  strip.show(); 
  }

 
