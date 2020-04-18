/*
An example of the internal support for the capacitive touch screen
that use FT5206.
Using FT5206 instead resistive RA8875 one give more precision, don't need any calibration
and you have max 5 concurrent touches plus gesture and more...
*/

#include <SPI.h>
#include <RA8875.h>
#include <Wire.h>


#define RA8875_CS         10 
#define RA8875_RESET      23                 
#define RA8875_INT        2

#define MAXTOUCHLIMIT     5//1...5

RA8875 tft = RA8875(RA8875_CS, RA8875_RESET);


void setup(){
  /*
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  */
  //  begin display: Choose from: RA8875_480x272, RA8875_800x480, RA8875_800x480ALT, Adafruit_480x272, Adafruit_800x480
  tft.begin(RA8875_800x480);
  #if defined(USE_FT5206_TOUCH)
  tft.useCapINT(RA8875_INT);//we use the capacitive chip Interrupt out!
  //the following set the max touches (max 5)
  //it can be placed inside loop but BEFORE touched()
  //to limit dinamically the touches (for example to 1)
  tft.setTouchLimit(MAXTOUCHLIMIT);
  //tft.setRotation(0);//this works in any rotation mode!
  tft.enableCapISR(true);//capacitive touch screen interrupt it's armed
  #else
  tft.print("you should open RA8875UserSettings.h file and uncomment USE_FT5206_TOUCH!");
  #endif
  tft.setTextColor(RA8875_WHITE,RA8875_BLACK);
}

void loop(){
  #if defined(USE_FT5206_TOUCH)
  if (tft.touched()){//if touched(true) detach isr
  //at this point we need to fill the FT5206 registers...
    tft.updateTS();//now we have the data inside library
    tft.setCursor(CENTER,CENTER);
    tft.print("                              ");
    tft.setCursor(CENTER,CENTER);
    tft.print("touches:");
    tft.print(tft.getTouches());
    tft.print(" | gesture:");
    tft.print(tft.getGesture(),HEX);
    tft.print(" | state:");
    tft.print(tft.getTouchState(),HEX);
    //you need to get the coordinates? We need a bidimensional array
    uint16_t coordinates[MAXTOUCHLIMIT][2];//to hold coordinates
    tft.getTScoordinates(coordinates);//done
    //now coordinates has the x,y of all touches
    //now draw something....
    uint16_t tempCol;
    for (uint8_t i=1;i<=tft.getTouches();i++){
      if (i == 1)tempCol = RA8875_RED;
      if (i == 2)tempCol = RA8875_GREEN;
      if (i == 3)tempCol = RA8875_MAGENTA;
      if (i == 4)tempCol = RA8875_CYAN;
      if (i == 5)tempCol = RA8875_YELLOW;
      tft.fillCircle(coordinates[i-1][0],coordinates[i-1][1],10,tempCol);
    }
    tft.enableCapISR();//rearm ISR if needed (touched(true))
    //otherwise it doesn't do nothing...
  }
  #endif
}