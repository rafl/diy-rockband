/*
curve and ellipse test
*/

#include <SPI.h>
#include <RA8875.h>



#define RA8875_CS 10 //any digital pin
#define RA8875_RESET 9//any pin or 255 to disable it!

RA8875 tft = RA8875(RA8875_CS, RA8875_RESET);


void setup()
{
  //  Serial.begin(38400);
  //  long unsigned debug_start = millis ();
  //  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  //  Serial.println("RA8875 start");

  //  begin display: Choose from: RA8875_480x272, RA8875_800x480, RA8875_800x480ALT, Adafruit_480x272, Adafruit_800x480
  tft.begin(RA8875_800x480);
}

uint8_t b = 0;
void loop()
{
  tft.setRotation(b);
  tft.drawEllipse(CENTER, CENTER, 100, 60, RA8875_PURPLE);
  tft.fillCurve(CENTER, CENTER, 80, 30, 0, RA8875_CYAN);
  tft.fillCurve(CENTER, CENTER, 80, 30, 1, RA8875_MAGENTA);
  tft.fillCurve(CENTER, CENTER, 80, 30, 2, RA8875_YELLOW);
  tft.fillCurve(CENTER, CENTER, 80, 30, 3, RA8875_RED);

  tft.drawCurve(CENTER, CENTER, 90, 50, 0, RA8875_CYAN);
  tft.drawCurve(CENTER, CENTER, 90, 50, 1, RA8875_MAGENTA);
  tft.drawCurve(CENTER, CENTER, 90, 50, 2, RA8875_YELLOW);
  tft.drawCurve(CENTER, CENTER, 90, 50, 3, RA8875_RED);
  tft.fillCircle(CENTER, CENTER, 30, RA8875_BLUE);
  delay(100);
  if (b > 2) {
    b = 0;
    tft.fillWindow();
  } else {
    b++;
  }
}