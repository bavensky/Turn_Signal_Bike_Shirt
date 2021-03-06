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
  #include <RCSwitch.h>
  #include "LPD8806.h"
  #include "SPI.h"
  
  RCSwitch mySwitch = RCSwitch();
  
  //  จำนวนของหลอด LED
  int nLEDs = 32;
  
  // หน่วงเวลา
  int wait  =  50;
  
  int _loop;
  int row1;
  int row2;
  int row3;
  int row4;
  
  int one  =  0;
  int two  =  0;
  int three  =  0;
  int four  =  0;
  
  //  ขาข้อมูล(Data) ต่อขา Digital 2
  //  ขาสัญญาณนาฬิกา(Clock) ต่อขา Digital 3
  int dataPin  = 4;
  int clockPin = 3;
  
  LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
  
  void setup() 
  {
    Serial.begin(9600);
    strip.begin();
    mySwitch.enableReceive(0);  //  connect inerrupt0 = pin 2
  }
  
  void loop()  {
    rainbowCycle(1);
    if (mySwitch.available()) {
      int received = 0;
      received = mySwitch.getReceivedValue();
      Serial.print("Received : ");
      Serial.println(received);
      mySwitch.resetAvailable();
    }
    
//     
//    if(received == 1)  {
//      rainbowCycle(1);
//    }
//    if(received == 2)  {
//      turn_right();
//    }
//    if(received == 3)  {
//      turn_left();
//    }
    
//    rainbowCycle(1);
//    delay(1000);
//    turn_right();
//    delay(1000);
//    turn_left();
//    delay(1000);
    
    
  }    //  End loop
    
  void turn_right()
  {
    one    =  0;
    two    =  15;
    three  =  16;
    four   =  31;    
    for(_loop=0; _loop<=8; _loop++)  {
      strip.setPixelColor(one, strip.Color(  127,  0,  0));
      strip.setPixelColor(two, strip.Color(  127,  0,  0));
      strip.setPixelColor(three, strip.Color(  127,  0,  0));
      strip.setPixelColor(four, strip.Color(  127,  0,  0));
      delay(wait);
      
      one += 1;
      two -= 1;
      three += 1;
      four -= 1;
      
      strip.show();
    }
    one    =  0;
    two    =  15;
    three  =  16;
    four   =  31;  
    
    for(_loop=0; _loop<=8; _loop++)  {
      strip.setPixelColor(one, strip.Color(  0,  0,  0));
      strip.setPixelColor(two, strip.Color(  0,  0,  0));
      strip.setPixelColor(three, strip.Color(  0,  0,  0));
      strip.setPixelColor(four, strip.Color(  0,  0,  0));
      delay(wait);
      
      one += 1;
      two -= 1;
      three += 1;
      four -= 1;
      
      strip.show();
    }
  }
  
  void turn_left()  {
    one    =  7;
    two    =  8;
    three  =  23;
    four   =  24;    
    for(_loop=0; _loop<=8; _loop++)  {
      strip.setPixelColor(one, strip.Color(  127,  0,  0));
      strip.setPixelColor(two, strip.Color(  127,  0,  0));
      strip.setPixelColor(three, strip.Color(  127,  0,  0));
      strip.setPixelColor(four, strip.Color(  127,  0,  0));
      delay(wait);
      
      one -= 1;
      two += 1;
      three -= 1;
      four += 1;
      
      strip.show();
    }
    
    one    =  7;
    two    =  8;
    three  =  23;
    four   =  24;   
    for(_loop=0; _loop<=8; _loop++)  {
      strip.setPixelColor(one, strip.Color(  0,  0,  0));
      strip.setPixelColor(two, strip.Color(  0,  0,  0));
      strip.setPixelColor(three, strip.Color(  0,  0,  0));
      strip.setPixelColor(four, strip.Color(  0,  0,  0));
      delay(wait);
      
      one -= 1;
      two += 1;
      three -= 1;
      four += 1;
      
      strip.show();
    }
    
  }
  
  void bike_break()  {
    
  }
  
  void dark_right()  {
    //ดับทุกหลอด
    for(int l=0; l<=32; l++)  {
      strip.setPixelColor(l, 0);
      delay(wait);
    }
    strip.show(); 
  }

 void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g - b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}
