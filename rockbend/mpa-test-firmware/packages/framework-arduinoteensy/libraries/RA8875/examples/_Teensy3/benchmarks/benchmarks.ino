/*
A benchmark test - measure the speed of many drawing functions of RA8875 library at any rotation
Open your serial monitor for results
*/

#include <SPI.h>
#include <RA8875.h>

#define DELAY_BETWEEN 500


/*
Teensy3.x and Arduino's
You are using 4 wire SPI here, so:
 MOSI:  11//Teensy3.x
 MISO:  12//Teensy3.x
 SCK:   13//Teensy3.x
 the rest of pin below:
 */
#define RA8875_INT 19//any pin
#define RA8875_CS  10//restriction for Teensy3 and CS
#define RA8875_RST 8//any pin
/*
Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
*/

RA8875 tft = RA8875(RA8875_CS, RA8875_RST);

void setup() {
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  //  begin display: Choose from: RA8875_480x272, RA8875_800x480, RA8875_800x480ALT, Adafruit_480x272, Adafruit_800x480
  tft.begin(Adafruit_800x480);
}

uint8_t rot = 0;
void loop(void) {
  test(rot);
  rot++;
  if (rot > 3) rot = 0;
}
