/*
   how fast is the RA8875? here's.
 */

#include <SPI.h>
#include <RA8875.h>

#define RA8875_RESET 9//any pin or nothing!

#if defined(NEEDS_SET_MODULE)//Energia, this case is for stellaris/tiva

RA8875 tft = RA8875(3);//select SPI module 3
/*
for module 3 (stellaris)
 SCLK:  PD_0
 MOSI:  PD_3
 MISO:  PD_2
 SS:    PD_1
 */
#endif


void setup()
{

  tft.begin(RA8875_800x480);

}

void loop() {

  testdrawrects();
  testtriangles(false);
  testtriangles(true);
  randomRect(false);
  randomRect(true);
  randomCircles(false);
  randomCircles(true);
  randomLines();
  randomPoints();
}


void testdrawrects() {
  tft.fillWindow();
  for (int k = 0; k < 64; k++) {
    for (uint16_t x = 1; x < tft.height(); x += 6) {
      uint16_t c1 = random(0x00FF, 0xFFFF);
      tft.drawRect((uint16_t)((tft.width() / 2) - (x / 2)), (uint16_t)((tft.height() / 2) - (x / 2)), x, x, c1);
    }
  }
}

void randomCircles(bool fill) {
  tft.fillWindow();
  uint8_t k, c;
  for (k = 0; k < 32; k++) {
    for (c = 0; c < 32; c++) {
      //  coordinates
      uint16_t x = random(0, tft.width() - 1);
      uint16_t y = random(0, tft.height() - 1);

      uint16_t r = random(1, tft.height() / 2);

      if (x - r <  0) r = x;
      if (x + r > (tft.width() - 1)) r = (tft.width() - 1) - x;
      if (y - r <  0) r = y;
      if (y + r > (tft.height() - 1)) r = (tft.height() - 1) - y;

      if (fill) {
        tft.fillCircle(x, y, r, random(0x0010, 0xFFFF));
      }
      else {
        tft.drawCircle(x, y, r, random(0x00FF, 0xFFFF));
      }
    }
    if (!fill) tft.fillWindow();
  }
}

void randomRect(bool fill) {
  tft.fillWindow();
  uint16_t k, c;
  for (k = 0; k < 128; k++) {
    for (c = 0; c < 32; c++) {
      uint16_t cx, cy, x, y, w, h;
      //  center
      cx = random(0, tft.width() - 1);
      cy = random(0, tft.height() - 1);
      //  size
      w = random(1, tft.width() / 3);
      h = random(1, tft.height() / 3);
      //  upper-left
      x = cx - w / 2;
      y = cy - h / 2;
      if (x < 0) x = 0;
      if (y < 0) y = 0;
      //  adjust size
      if (x + w >= tft.width()) w = tft.width() - 1 - x;
      if (y + h >= tft.height()) h = tft.height() - 1 - y;
      if (fill) {
        tft.fillRect(x, y, w, h, random(0x0010, 0xFFFF));
      }
      else {
        tft.drawRect(x, y, w, h, random(0x0010, 0xFFFF));
      }

    }
    tft.fillWindow();
  }
}


void randomLines() {
  tft.fillWindow();
  uint16_t k, c;
  for (k = 0; k < tft.height(); k++) {
    for (c = 0; c < 32; c++) {
      uint16_t x1 = random(0, tft.width() - 2);
      uint16_t y1 = random(0, tft.height() - 2);
      uint16_t x2 = random(0, tft.width() - 1);
      uint16_t y2 = random(0, tft.height() - 1);
      tft.drawLine(x1, y1, x2, y2, random(0x0010, 0xFFFF));
    }
    tft.fillWindow();
  }
}


void randomPoints() {
  tft.fillWindow();
  uint16_t k, c;
  for (k = 0; k < 62; k++) {
    for (c = 0; c < 1000; c++) {
      uint16_t x = random(0, tft.width() - 1);
      uint16_t y = random(0, tft.height() - 1);
      tft.drawPixel(x, y, random(0x0010, 0xFFFF));
    }
    tft.fillWindow();
  }
}

void testtriangles(bool fill) {
  tft.fillWindow();
  uint16_t p1x, p1y, p2x, p2y, p3x, p3y;
  uint16_t colour;
  for (uint16_t k = 0; k < 128; k++) {
    for (uint16_t t = 0 ; t <= 30; t += 1) {
      p1x = random(0, tft.width() - 1);   //get a random number 0-319
      p1y = random(0, tft.height() - 1);  //get a random number 0-239
      p2x = random(0, tft.width() - 1);   //get a random number 0-319
      p2y = random(0, tft.height() - 1);  //get a random number 0-239
      p3x = random(0, tft.width() - 1);   //get a random number 0-319
      p3y = random(0, tft.height() - 1);  //get a random number 0-239
      colour = random(0, 65536);       //get a random number 0-65535
      //draw the triangle
      if (fill) {
        tft.fillTriangle(p1x, p1y, p2x, p2y, p3x, p3y, colour);
      }
      else {
        tft.drawTriangle(p1x, p1y, p2x, p2y, p3x, p3y, colour);
      }
    }
    tft.clearScreen();
  }
}

uint16_t halveColor(uint16_t rgb) {
  return (((rgb & 0b1111100000000000) >> 12) << 11 | ((rgb & 0b0000011111100000) >>  6) <<  5 | ((rgb & 0b0000000000011111) >>  1));
}

