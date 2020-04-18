/*
	--------------------------------------------------
	RA8875 LCD/TFT Graphic Controller Driver Library
	--------------------------------------------------
	Version:0.70b11p11
	++++++++++++++++++++++++++++++++++++++++++++++++++
	Written by: Max MC Costa for s.u.m.o.t.o.y
	++++++++++++++++++++++++++++++++++++++++++++++++++
An attemp to create a full featured library support for RA8875 chip from RAiO.
Works with many SPI drived RA8875 Boards included Adafruit, Eastrising(buydisplay).
NOT work if you have a I2C or Parallel based display!

-------------------------------------------------------------------------------------
					>>>>>>>>>>>> About Copyrights <<<<<<<<<<<<<<<
-------------------------------------------------------------------------------------
License:GNU General Public License v3.0

    RA8875 fast SPI library for RAiO SPI RA8875 drived TFT
    Copyright (C) 2014  egidio massimo costa sumotoy (a t) gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------------------
					     >>>>>>>>>>>> Thanks to <<<<<<<<<<<<<<<
-------------------------------------------------------------------------------------
Teensy 3.1, a tiny MCU but monster of performances at tiny price, Arduino should learn...
Paul Stoffregen, the 'guru' behind many arduino magic, the father of Teensy
Bill Greyman, another 'maestro', greatly inspired many coders
Jnmattern & Marek Buriak for drawArc
Last but not less important the contributors and beta tester of this library:
M.Sandercrock, the experimentalist, MrTom and many others
-------------------------------------------------------------------------------------
				>>>>>>>>>>>> Current version notes <<<<<<<<<<<<<<<
-------------------------------------------------------------------------------------
	0.70b11p8 changes: Fixed some small error (thanks Mr TOM) that affects drawLine
	and drawLineAngle. Initial support for SPARK devices (very early development)
	Fixed a couple of examples.
	0.70b11p9 changes: Now compile with particle spark! But spark development toolchain it's a nightmare so 
	use https://github.com/sumotoy/spark_ra8875
	0.70b11p10: Some changes proposed by MrTom to fix the triangle hardware bug of RA8875
	0.70b11p11: Minor changes on triangles helper (MrTom)
-------------------------------------------------------------------------------------
				>>>>>>>>>>>>>>>>>>>>> Wiring <<<<<<<<<<<<<<<<<<<<<<<<<
-------------------------------------------------------------------------------------
TFT side	Teensy/Uno
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
CLK:		pin 13 UNO
MOSI:		pin 11 UNO
MISO:		pin 12 UNO
CS:			pin 10 (selectable but note 1*!)
INT:		pin 2  (selectable 2*)
RESET:		pin 9  (selectable and optional 0*)
*(0) In some modules you can leave unconnected but check if it's needed!
*(1) On Teensy3.x not all pin are usable for CS! Read the printed paper
that come with your Teensy3.x for more informations!
*(2) Arduino cannot use any pin for interrupts! In my examples I don't use
interrupts but just reading pin state so you can use any pin :)
-------------------------------------------------------------------------------------
TFT side	Stellaris (LM4F120XL) module=0 (still not checked)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
CLK:		xxx
MOSI:		xxx
MISO:		xxx
CS:			xxx  (selectable)
INT:		xxx  (selectable)
RESET:		xxx  (selectable and optional)

*if you use an [optional] SD card here's connections...
-------------------------------------------------------------------------------------
TFT side	Teensy2/Teensy3/Uno
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
SD CLK:		pin 13 [shared with RA]
SD MOSI:	pin 11 [shared with RA]
SD MISO:	pin 12 [shared with RA]
SD CS:		pin 4  (selectable 3*)
SD CARD ID: pin xx (selectable and optional)
*(3) On Teensy3.x not all pin are usable for CS! 
can be used: 2,6,9,10,15,20,21,22,23
-------------------------------------------------------------------------------------
TFT side	Stellaris (LM4F120XL) module=0 (still not checked)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
SD CLK:		xxx shared
SD MOSI:	xxx shared
SD MISO:	xxx shared
SD CS:		xxx  (selectable)
SD CARD ID: pin xx (selectable and optional)
-------------------------------------------------------------------------------------
TFT side	Teensy3 alternative setup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
There are special cases on Teensy 3.x since it can be used for audio shield that remap
some pin. Using SPI in that situation will be impossible but you can use the alternative
pins definition feature of Teensy 3!
SD CLK:		pin 13(normal),pin 14(alt)  [shared with RA]
SD MOSI:	pin 11(normal),pin 7(alt) 	[shared with RA]
SD MISO:	pin 12(normal),pin 8(alt) 	[shared with RA]
SD CS:		pin 2  (selectable 3*)
SD CARD ID: pin xx (selectable and optional)
*(3) On Teensy3.x not all pin are usable for CS's! 
can be used: 2,6,9,10,15,20,21,22,23
-------------------------------------------------------------------------------------
TFT side	Particle Spark  (caution, never tested!)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
CLK:		 	A3
MOSI:			A5
MISO:			A4
CS:				A2
INT:		
SDA:			D0
SCL:			D1

Benchmark results for reference --------------------------------------
Screen fill              16635		16585		16561		8326
Test Pixel               60			77			63			53
Test Pixels              39780		52085		41885		35412
Text                     4500		4389		4634		3409
Lines                    96705		101951		97943		55986
Horiz/Vert Lines         66656		72470		67732		42703
Rectangles (outline)     269786		271251		269987		137691
Rectangles (filled)      269498		271415		270002		137858
Circles (filled)         110285		195011		181003		117279
Circles (outline)        109604		191746		177459		115584
Triangles (outline)      24521		26320		24886		14728
Triangles (filled)       64947		66801		65367		35226
Rounded rects (outline)  146391		167477		151142		103027
Rounded rects (filled)   935691		953280		940016		493179


PIN     UNO		MEGA       CD4050     RA8875
SCK      13		52           YES       SCK
MOSI     11		51           YES       MOSI
MISO     12		50            NO       MISO
RST      9		 5           YES       RST
CS       10		53           YES       CS
*/

#ifndef _RA8875MC_H_
#define _RA8875MC_H_

#include <inttypes.h>


#if !defined(swapvals)
	#if defined(ESP8266)
		#define swapvals(a, b) { int16_t t = a; a = b; b = t; }
		//#define swapvals(a, b) { typeid(a) t = a; a = b; b = t; }
	#else
		#define swapvals(a, b) { typeof(a) t = a; a = b; b = t; }
	#endif
#endif

enum RA8875sizes { 			RA8875_480x272, RA8875_800x480, RA8875_800x480ALT, Adafruit_480x272, Adafruit_800x480 };
enum RA8875tcursor { 		NOCURSOR=0,IBEAM,UNDER,BLOCK };//0,1,2,3
enum RA8875tsize { 			X16=0,X24,X32 };//0,1,2
enum RA8875fontSource { 	INTFONT=0, EXTFONT };//0,1
enum RA8875fontCoding { 	ISO_IEC_8859_1, ISO_IEC_8859_2, ISO_IEC_8859_3, ISO_IEC_8859_4 };
enum RA8875extRomType { 	GT21L16T1W, GT21H16T1W, GT23L16U2W, GT30L16U2W, GT30H24T3Y, GT23L24T3Y, GT23L24M1Z, GT23L32S4W, GT30H32S4W, GT30L32S4W, ER3303_1, ER3304_1, ER3301_1 };
enum RA8875extRomCoding { 	GB2312, GB12345, BIG5, UNICODE, ASCII, UNIJIS, JIS0208, LATIN };
enum RA8875extRomFamily { 	STANDARD, ARIAL, ROMAN, BOLD };
enum RA8875boolean { 		LAYER1, LAYER2, TRANSPARENT, LIGHTEN, OR, AND, FLOATING };
enum RA8875writes { 		L1=0, L2, CGRAM, PATTERN, CURSOR };
enum RA8875scrollMode{ 		SIMULTANEOUS, LAYER1ONLY, LAYER2ONLY, BUFFERED };
enum RA8875pattern{ 		P8X8, P16X16 };
enum RA8875btedatam{ 		CONT, RECT };
enum RA8875btelayer{ 		SOURCE, DEST };
enum RA8875intlist{ 		BTE=1,TOUCH=2, DMA=3,KEY=4 };

/*
-------------- UNICODE decode (2 byte char) ---------------------
Latin:      \u0000 -> \u007F	/u00
Greek:		\u0370 -> \u03FF	/u03
Cyrillic:   \u0400 -> \u04FF	/u04
Hebrew:     \u0590 -> \u05FF	/u05
Arabic: 	\u0600 -> \u06FF	/u06
Hiragana:	\u3040 -> \u309F	/u30
Katakana:   \u30A0 -> \u30FF	/u30
CJK-Uni:	\u4E00 -> \u9FD5	/u4E ... /u9F
*/
/* ----------------------------DO NOT TOUCH ANITHING FROM HERE ------------------------*/


// Documentation on the ILI9488_t3 font data format:
// https://forum.pjrc.com/threads/54316-ILI9488_t-font-structure-format
/*
typedef struct {
	const unsigned char *index;
	const unsigned char *unicode;
	const unsigned char *data;
	unsigned char version;
	unsigned char reserved;
	unsigned char index1_first;
	unsigned char index1_last;
	unsigned char index2_first;
	unsigned char index2_last;
	unsigned char bits_index;
	unsigned char bits_width;
	unsigned char bits_height;
	unsigned char bits_xoffset;
	unsigned char bits_yoffset;
	unsigned char bits_delta;
	unsigned char line_space;
	unsigned char cap_height;
} ILI9341_t3_font_t;
*/
#include "ILI9341_fonts.h"


// Lets see about supporting Adafruit fonts as well?
#ifndef _GFXFONT_H_
#define _GFXFONT_H_

/// Font data stored PER GLYPH
typedef struct {
	uint16_t bitmapOffset;     ///< Pointer into GFXfont->bitmap
	uint8_t  width;            ///< Bitmap dimensions in pixels
    uint8_t  height;           ///< Bitmap dimensions in pixels
	uint8_t  xAdvance;         ///< Distance to advance cursor (x axis)
	int8_t   xOffset;          ///< X dist from cursor pos to UL corner
    int8_t   yOffset;          ///< Y dist from cursor pos to UL corner
} GFXglyph;

/// Data stored for FONT AS A WHOLE
typedef struct { 
	uint8_t  *bitmap;      ///< Glyph bitmaps, concatenated
	GFXglyph *glyph;       ///< Glyph array
	uint8_t   first;       ///< ASCII extents (first char)
    uint8_t   last;        ///< ASCII extents (last char)
	uint8_t   yAdvance;    ///< Newline distance (y axis)
} GFXfont;

#endif // _GFXFONT_H_

#ifdef __cplusplus
#include "_includes/RA8875_CPU_commons.h"

#include "_includes/font.h"
#include "_includes/RA8875Registers.h"
#include "_includes/RA8875ColorPresets.h"
#include "_settings/RA8875UserSettings.h"

#if !defined(_AVOID_TOUCHSCREEN) &&  defined(USE_FT5206_TOUCH)
#include <Wire.h>
#endif

#if defined(_FORCE_PROGMEM__) && !defined(ESP8266)
template <typename T> T PROGMEM_read (const T * sce)
  {
  static T temp;
  memcpy_P (&temp, sce, sizeof (T));
  return temp;
  }
#endif

#if defined(ESP8266) && defined(_FASTSSPORT)
	#include <eagle_soc.h>
#endif

class RA8875 : public Print
{
 public:
	// void 		debugData(uint16_t data,uint8_t len=8);
	// void 		showLineBuffer(uint8_t data[],int len);
//------------- INSTANCE -------------------------------------------------------------------
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		RA8875(const uint8_t CSp,const uint8_t RSTp=255,const uint8_t mosi_pin=11,const uint8_t sclk_pin=13,const uint8_t miso_pin=12);
	#elif defined(__MKL26Z64__)//TeensyLC
		RA8875(const uint8_t CSp,const uint8_t RSTp=255,const uint8_t mosi_pin=11,const uint8_t sclk_pin=13,const uint8_t miso_pin=12);
	#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)  || defined(__IMXRT1062__)	
		RA8875(const uint8_t CSp,const uint8_t RSTp=255,const uint8_t mosi_pin=11,const uint8_t sclk_pin=13,const uint8_t miso_pin=12);
	#elif defined(___DUESTUFF)//DUE
		RA8875(const uint8_t CSp, const uint8_t RSTp=255);
	#elif defined(SPARK)//SPARK
		RA8875(const uint8_t CSp, const uint8_t RSTp=255);
	#elif defined(NEEDS_SET_MODULE)//ENERGIA
		RA8875::RA8875(const uint8_t module, const uint8_t RSTp=255);
	#else//8 BIT ARDUINO's
		RA8875(const uint8_t CSp, const uint8_t RSTp=255);
	#endif
//------------- SETUP -----------------------------------------------------------------------
	void 		begin(const enum RA8875sizes s,uint8_t colors=16, uint32_t SPIMaxSpeed = (uint32_t)-1, uint32_t SPIMaxReadSpeed = (uint32_t)-1 );
	//(RA8875_480x272, RA8875_800x480, Adafruit_480x272, Adafruit_800x480) , (8/16 bit)
//------------- HARDWARE ------------------------------------------------------------
	void 		backlight(boolean on);
	void    	displayOn(boolean on);//turn diplay on/off
	void    	sleep(boolean sleep);//put display in sleep or not
	void 		brightness(uint8_t val);//ok
	uint8_t 	readStatus(void);//used to verify when an operation has concluded
	void 		clearMemory(bool stop=false);
	void 		clearWidthColor(bool bte);
	//void		clearMemory(boolean full);//clear the RA8875 internal buffer (fully or current layer)
	uint8_t		errorCode(void);//0: no error,
	/*
	format: 1byte 0b00000000;, bit described below:
	nan,nan,nan,nan,nan,CS(out-of-range),MOSI/MISO/SCLK(out-of-range),display(not-recognized)
	*/
//------------ Low Level functions ---------------------------------------------------------
	void    	writeCommand(const uint8_t d);
	void  		writeData16(uint16_t data);
//Hack fonts
	// setOrigin sets an offset in display pixels where drawing to (0,0) will appear
	// for example: setOrigin(10,10); drawPixel(5,5); will cause a pixel to be drawn at hardware pixel (15,15)
	void setOrigin(int16_t x = 0, int16_t y = 0) { 
		_originx = x; _originy = y; 
		//if (Serial) Serial.printf("Set Origin %d %d\n", x, y);
		updateDisplayClip();
	}
	void getOrigin(int16_t* x, int16_t* y) { *x = _originx; *y = _originy; }

	// setClipRect() sets a clipping rectangle (relative to any set origin) for drawing to be limited to.
	// Drawing is also restricted to the bounds of the display

	void setClipRect(int16_t x1, int16_t y1, int16_t w, int16_t h) 
		{ _clipx1 = x1; _clipy1 = y1; _clipx2 = x1+w; _clipy2 = y1+h; 
			//if (Serial) Serial.printf("Set clip Rect %d %d %d %d\n", x1, y1, w, h);
			updateDisplayClip();
		}
	void setClipRect() {
			 _clipx1 = 0; _clipy1 = 0; _clipx2 = _width; _clipy2 = _height; 
			//if (Serial) Serial.printf("clear clip Rect\n");
			 updateDisplayClip(); 
		}
		
	bool _invisible = false; 
	bool _standard = true; // no bounding rectangle or origin set. 

	inline void updateDisplayClip() {
		_displayclipx1 = max(0,min(_clipx1+_originx,width()));
		_displayclipx2 = max(0,min(_clipx2+_originx,width()));

		_displayclipy1 = max(0,min(_clipy1+_originy,height()));
		_displayclipy2 = max(0,min(_clipy2+_originy,height()));
		_invisible = (_displayclipx1 == _displayclipx2 || _displayclipy1 == _displayclipy2);
		_standard =  (_displayclipx1 == 0) && (_displayclipx2 == _width) && (_displayclipy1 == 0) && (_displayclipy2 == _height);
		if (Serial) {
			//Serial.printf("UDC (%d %d)-(%d %d) %d %d\n", _displayclipx1, _displayclipy1, _displayclipx2, 
			//	_displayclipy2, _invisible, _standard);

		}
	}
	
	inline void setFontDefault() { 
		_use_default = 1; 
		if(_portrait && (!_use_gfx_font || !_use_ili_font)) {
			_cursorX += _cursorY;
			_cursorY -= _cursorX;
		}
		_use_ili_font=0; 
		_use_gfx_font=0;
		setActiveWindow();
		_textPosition(_cursorX, _cursorY, false);
		};
	void setFont(const ILI9341_t3_font_t &f);
    void setFont(const GFXfont *f = NULL);
	void setFontAdafruit(void) { setFont(); }
	void drawFontChar(unsigned int c);
	void drawGFXFontChar(unsigned int c);
	
    void setTextSize(uint8_t sx, uint8_t sy);
	void inline setTextSize(uint8_t s) { setTextSize(s,s); }
	
	void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);
	void inline drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) 
	    { drawChar(x, y, c, color, bg, size);}
	void drawFontBits(bool opaque, uint32_t bits, uint32_t numbits, int32_t x, int32_t y, uint32_t repeat);
	void Pixel(int16_t x, int16_t y, uint16_t color);
	
	void charBounds(char c, int16_t *x, int16_t *y,
		int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);
    void getTextBounds(const uint8_t *buffer, uint16_t len, int16_t x, int16_t y,
      int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
    void getTextBounds(const char *string, int16_t x, int16_t y,
      int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
    void getTextBounds(const String &str, int16_t x, int16_t y,
      int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
	int16_t strPixelLen(const char * str);

	void drawFontPixel( uint8_t alpha, uint32_t x, uint32_t y );

	void write16BitColor(uint16_t color, bool last_pixel=false);

	// Hack to see about combining outputs for speed.
	int16_t _combine_x_start = 0;
	int16_t _combine_y = 0;
	int16_t _combine_count = 0;
	uint16_t _combine_color = 0;

	inline void combineAndDrawPixel(int16_t x, int16_t y, uint16_t color) {
		if (_combine_count && (color == _combine_color)) _combine_count++;
		else {
			if (_combine_count)drawLine(_combine_x_start, _combine_y, _combine_x_start+_combine_count-1, _combine_y, _combine_color);
			_combine_x_start = x;
			_combine_y = y;
			_combine_count = 1;
			_combine_color = color;
		}
	}

	inline void forceCombinedPixelsOut() {
		if (_combine_count)fillRect(_combine_x_start, _combine_y, _combine_count, 1, _combine_color);
		_combine_count = 0;
	}


//-------------- AREA ----------------------------------------------------------------------
	void		setActiveWindow(int16_t XL,int16_t XR,int16_t YT,int16_t YB);//The working area where to draw on
	void		setActiveWindow(void);
	void 		getActiveWindow(int16_t &XL,int16_t &XR ,int16_t &YT ,int16_t &YB);
	void		clearActiveWindow(bool full=false);//it clears the active window
	uint16_t 	width(bool absolute=false) const;//the phisical display width
	uint16_t 	height(bool absolute=false) const;//the phisical display height
	void		setRotation(uint8_t rotation); //rotate text and graphics
	uint8_t		getRotation(); //return the current rotation 0-3
	boolean		isPortrait(void);
//-------------- COLOR ----------------------------------------------------------------------
	void		setForegroundColor(uint16_t color);//color of objects in 16bit
	void		setForegroundColor(uint8_t R,uint8_t G,uint8_t B);//color of objects in 8+8+8bit
	void		setBackgroundColor(uint16_t color);//color of objects background in 16bit
	void		setBackgroundColor(uint8_t R,uint8_t G,uint8_t B);//color of objects background in 8+8+8bit
	void 		setTransparentColor(uint16_t color);//the current transparent color in 16bit
	void 		setTransparentColor(uint8_t R,uint8_t G,uint8_t B);//the current transparent color in 8+8+8bit
	void 		setColor(uint16_t fcolor,uint16_t bcolor,bool bcolorTraspFlag=false);
	void 		setColorBpp(uint8_t colors);//set the display color space 8 or 16!
	uint8_t 	getColorBpp(void);//get the current display color space (return 8 or 16)
	uint16_t	grandient(uint8_t val);
	uint16_t 	colorInterpolation(uint16_t color1,uint16_t color2,uint16_t pos,uint16_t div=100);
	uint16_t 	colorInterpolation(uint8_t r1,uint8_t g1,uint8_t b1,uint8_t r2,uint8_t g2,uint8_t b2,uint16_t pos,uint16_t div=100);
//-------------- COLOR CONVERSION -----------------------------------------------------------
	inline uint16_t Color565(uint8_t r,uint8_t g,uint8_t b) { return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); }
	inline uint16_t Color24To565(int32_t color_) { return ((((color_ >> 16) & 0xFF) / 8) << 11) | ((((color_ >> 8) & 0xFF) / 4) << 5) | (((color_) &  0xFF) / 8);}
	inline uint16_t htmlTo565(int32_t color_) { return (uint16_t)(((color_ & 0xF80000) >> 8) | ((color_ & 0x00FC00) >> 5) | ((color_ & 0x0000F8) >> 3));}
	inline void 	Color565ToRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b){r = (((color & 0xF800) >> 11) * 527 + 23) >> 6; g = (((color & 0x07E0) >> 5) * 259 + 33) >> 6; b = ((color & 0x001F) * 527 + 23) >> 6;}
//-------------- CURSOR ----------------------------------------------------------------------
	void 		cursorIncrement(bool on);
	void 		setCursorBlinkRate(uint8_t rate);//set blink rate of the cursor 0...255 0:faster
	void 		showCursor(enum RA8875tcursor c,bool blink);//show cursor(NOCURSOR,IBEAM,UNDER,BLOCK), default blinking
	void    	setCursor(int16_t x, int16_t y,bool autocenter=false);//set cursor position to write text(pixels or CENTER)
	void 		getCursor(int16_t &x, int16_t &y);//from the RA8875 registers
	void 		getCursorFast(int16_t &x, int16_t &y);//from library (faster)
	int16_t		getCursorX(void);
	int16_t		getCursorY(void);
	void 		setGraphicCursor(uint8_t cur);//0...7 Select a custom graphic cursor (you should upload first)
	void 		showGraphicCursor(boolean cur);//show graphic cursor
//-------------- TEXT -----------------------------------------------------------------------
	void 		uploadUserChar(const uint8_t symbol[],uint8_t address);//upload user defined char as array at the address 0..255
	void		showUserChar(uint8_t symbolAddrs,uint8_t wide=0);//show user uploaded char at the adrs 0...255
	void    	setTextColor(uint16_t fcolor, uint16_t bcolor);//set text color + text background color
	void 		setTextColor(uint16_t fcolor);//set text color (backgroud will be transparent)
	void 		setTextGrandient(uint16_t fcolor1,uint16_t fcolor2);
	void    	setFontScale(uint8_t scale);//global font scale (w+h)
	void    	setFontScale(uint8_t xscale,uint8_t yscale);//font scale separated by w and h
	void    	setFontSize(enum RA8875tsize ts);//X16,X24,X32
	void 		setFontSpacing(uint8_t spc);//0:disabled ... 63:pix max
	void 		setFontInterline(uint8_t pix);//0...63 pix
	void 		setFontFullAlign(boolean align);//mmmm... doesn't do nothing! Have to investigate
	uint8_t 	getFontWidth(boolean inColums=false);
	uint8_t 	getFontHeight(boolean inRows=false);
	
	//----------FONT -------------------------------------------------------------------------
	void		setExternalFontRom(enum RA8875extRomType ert, enum RA8875extRomCoding erc,enum RA8875extRomFamily erf=STANDARD);
	void 		setFont(enum RA8875fontSource s);//INTFONT,EXTFONT (if you have a chip installed)
	//void 		setFont(const struct FONT_DEF *	fnt);
	void		setFont(const tFont *font);
	void 		setIntFontCoding(enum RA8875fontCoding f);
	void		setExtFontFamily(enum RA8875extRomFamily erf,boolean setReg=true);
	
//-------------- GRAPHIC POSITION --------------------------------------------------------------
	void    	setXY(int16_t x, int16_t y);//graphic set location
	void 		setX(int16_t x);
	void 		setY(int16_t y) ;
	//--------------- DRAW ---------------------------------------------------------------------
	void    	drawPixel(int16_t x, int16_t y, uint16_t color);
	void 		drawPixels(uint16_t p[], uint16_t count, int16_t x, int16_t y);
	uint16_t 	getPixel(int16_t x, int16_t y);
	//void 		getPixels(uint16_t * p, uint32_t count, int16_t x, int16_t y);
	void    	drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void    	drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
	void    	fillWindow(uint16_t color=_RA8875_DEFAULTBACKLIGHT);//fill the ActiveWindow with a color(default black)
	void		clearScreen(uint16_t color=_RA8875_DEFAULTBACKLIGHT);//fill the entire screen (regardless ActiveWindow) with a color(default black)
	void    	drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	void 		drawLineAngle(int16_t x, int16_t y, int16_t angle, uint16_t length, uint16_t color,int offset = -90);
	void 		drawLineAngle(int16_t x, int16_t y, int16_t angle, uint16_t start, uint16_t length, uint16_t color,int offset = -90);
	void    	drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void    	fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void 		writeRect(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *pcolors);
	void    	drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void    	fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void    	drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void    	fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void    	drawEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint16_t color);
	void    	fillEllipse(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint16_t color);
	void    	drawCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint8_t curvePart, uint16_t color);
	void    	fillCurve(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis, uint8_t curvePart, uint16_t color);
	void 		drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);//ok
	void 		fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
	void 		drawQuad(int16_t x0, int16_t y0,int16_t x1, int16_t y1,int16_t x2, int16_t y2,int16_t x3, int16_t y3, uint16_t color);
	void 		fillQuad(int16_t x0, int16_t y0,int16_t x1, int16_t y1,int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color, bool triangled=true);
	void 		drawPolygon(int16_t cx, int16_t cy, uint8_t sides, int16_t diameter, float rot, uint16_t color);
	void 		drawMesh(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t spacing,uint16_t color);
	void 		setArcParams(float arcAngleMax, int arcAngleOffset);
	void 		setAngleOffset(int16_t angleOffset);
	inline __attribute__((always_inline)) void drawArc(uint16_t cx, uint16_t cy, uint16_t radius, uint16_t thickness, float start, float end, uint16_t color) {
		if (start == 0 && end == _arcAngle_max) {
			_drawArc_helper(cx, cy, radius, thickness, 0, _arcAngle_max, color);
		} else {
			_drawArc_helper(cx, cy, radius, thickness, start + (_arcAngle_offset / (float)360)*_arcAngle_max, end + (_arcAngle_offset / (float)360)*_arcAngle_max, color);
		}	
	}
//-------------- GAUGES ---------------------------------------------------------------------------
	void 		ringMeter(int val, int minV, int maxV, int16_t x, int16_t y, uint16_t r, const char* units="none", uint16_t colorScheme=4,uint16_t backSegColor=RA8875_BLACK,int16_t angle=150,uint8_t inc=10);
	void		roundGaugeTicker(uint16_t x, uint16_t y, uint16_t r, int from, int to, float dev,uint16_t color);
//-------------- LAYERS --------------------------------------------------------------------------
	void 		useLayers(boolean on);//mainly used to turn of layers!
	void		writeTo(enum RA8875writes d);//L1, L2, CGRAM, PATTERN, CURSOR
	void 		layerEffect(enum RA8875boolean efx);//LAYER1, LAYER2, TRANSPARENT, LIGHTEN, OR, AND, FLOATING
	void 		layerTransparency(uint8_t layer1,uint8_t layer2);
	uint8_t		getCurrentLayer(void); //return the current drawing layer. If layers are OFF, return 255
//--------------- SCROLL --------------------------------------------------------------------------
	void        setScrollMode(enum RA8875scrollMode mode); // The experimentalist
	void 		setScrollWindow(int16_t XL,int16_t XR ,int16_t YT ,int16_t YB);
	void 		scroll(int16_t x,int16_t y);
//-------------- DMA ------------------------------------------------------------------------------
	void 		DMA_blockModeSize(int16_t BWR,int16_t BHR,int16_t SPWR);
	void 		DMA_startAddress(unsigned long adrs);
	void 		DMA_enable(void);
	void 		drawFlashImage(int16_t x,int16_t y,int16_t w,int16_t h,uint8_t picnum);
//-------------- BTE -------------------------------------------------------------------------------
	void 		BTE_size(int16_t w, int16_t h);
	void	 	BTE_moveFrom(int16_t SX,int16_t SY);
	void	 	BTE_moveTo(int16_t DX,int16_t DY);
	//void 		BTE_source_destination(uint16_t SX,uint16_t DX ,uint16_t SY ,uint16_t DY);
	void		BTE_ropcode(unsigned char setx);//
	void 		BTE_enable(bool on);//
	void 		BTE_dataMode(enum RA8875btedatam m);//CONT,RECT
	void 		BTE_layer(enum RA8875btelayer sd,uint8_t l);//SOURCE,DEST - 1 or 2
	void		BTE_move(int16_t SourceX, int16_t SourceY, int16_t Width, int16_t Height, int16_t DestX, int16_t DestY, uint8_t SourceLayer=0, uint8_t DestLayer=0, bool Transparent = false, uint8_t ROP=RA8875_BTEROP_SOURCE, bool Monochrome=false, bool ReverseDir = false);
	//---------- PATTERN --------------------------------------------------------------------------
	void 		setPattern(uint8_t num, enum RA8875pattern p=P8X8);
	void 		writePattern(int16_t x,int16_t y,const uint8_t *data,uint8_t size,bool setAW=true);
//-------------- GPIO & PWM -------------------------
	void    	GPIOX(boolean on);
	void    	PWMout(uint8_t pw,uint8_t p);//1:backlight, 2:free
//-------------- ISR ------------------------------------------------------------------------------
	void		useINT(const uint8_t INTpin=2,const uint8_t INTnum=0);
	void 		enableISR(bool force = false); 
	void 		setInternalInt(enum RA8875intlist b);//   BTE,TOUCH,DMA,KEY
	void 		clearInternalInt(enum RA8875intlist b);// BTE,TOUCH,DMA,KEY
//-------------- TOUCH SCREEN ---------------------------------------------------------------------
#if !defined(_AVOID_TOUCHSCREEN)
	bool 		touched(bool safe=false);
	void 		setTouchLimit(uint8_t limit);//5 for FT5206, 1 for  RA8875
	uint8_t 	getTouchLimit(void);

#	if defined(USE_RA8875_TOUCH)
		//void		useINT(const uint8_t INTpin=2,const uint8_t INTnum=0);
		//void 		enableISR(bool force = false); 
		void 		touchBegin(void);//prepare Touch Screen driver
		void    	touchEnable(boolean enabled);//enable/disable Touch Polling (disable INT)
		void 		touchReadAdc(uint16_t *x, uint16_t *y);//returns 10bit ADC data (0...1024)
		void 		touchReadPixel(uint16_t *x, uint16_t *y);//return pixels (0...width, 0...height)
		boolean		touchCalibrated(void);//true if screen calibration it's present
		void		setTouchCalibrationData(uint16_t minX, uint16_t maxX, uint16_t minY, uint16_t maxY);
	#elif defined (USE_FT5206_TOUCH)
		void		setWireObject(TwoWire *wire) {_wire = wire; }
		void		useCapINT(const uint8_t INTpin=2,const uint8_t INTnum=0);
		void 		enableCapISR(bool force = false); 
		void	 	updateTS(void);
		uint8_t 	getGesture(void);
		uint8_t 	getTouches(void);
		uint8_t 	getTouchState(void);
		uint8_t 	getTScoordinates(uint16_t (*touch_coordinates)[2]);
	#endif
#endif

//--------------Text Write -------------------------
//virtual size_t write(uint8_t b) {
//	if (_FNTgrandient) _FNTgrandient = false;//cannot use this with write
//	_textWrite((const char *)&b, 1);
//	return 1;
//}

virtual size_t write(uint8_t c) {
	_fontWrite(&c, 1);
	return 1;
}

virtual size_t write(const uint8_t *buffer, size_t size){
	if(_use_default) {
		_textWrite((const char *)buffer, size);
	} else {
		_fontWrite(buffer, size);
	}
	return size;
}


using Print::write;

 protected:
 	uint32_t textcolorPrexpanded, textbgcolorPrexpanded;
	boolean wrap; // If set, 'wrap' text at right edge of display
	const ILI9341_t3_font_t *font;
	
	int16_t  _clipx1, _clipy1, _clipx2, _clipy2;
	int16_t  _originx, _originy;
	int16_t  _displayclipx1, _displayclipy1, _displayclipx2, _displayclipy2;
	
 	// GFX Font support
	const GFXfont *gfxFont = nullptr;
	int8_t _gfxFont_min_yOffset = 0;
	
	// Opaque font chracter overlap?
	unsigned int _gfx_c_last;
	int16_t   _gfx_last__cursorX, _gfx_last__cursorY;
	int16_t	 _gfx_last_char_x_write = 0;
	uint16_t _gfx_last_char_textcolor;
	uint16_t _gfx_last_char_textbgcolor;
	bool gfxFontLastCharPosFG(int16_t x, int16_t y);
 
 //=====================
	volatile bool 				  _textMode;
	volatile uint8_t 			  _MWCR0_Reg; //keep track of the register 		  [0x40]
	int16_t 		 			   RA8875_WIDTH, 	   RA8875_HEIGHT;//absolute
	int16_t 		 			  _width, 			  _height;
	int16_t						  _cursorX, 		  _cursorY;
	uint8_t						  _scaleX,			  _scaleY;
	bool						  _scaling;
	uint8_t						  _FNTwidth, 		  _FNTheight;
	uint8_t						  _FNTbaselineLow, 	  _FNTbaselineTop;
	volatile uint8_t			  _TXTparameters;
	/* It contains several parameters in one byte
	bit			 parameter
	0	->		_extFontRom 		i's using an ext rom font
	1	->		_autoAdvance		after a char the pointer move ahead
	2	->		_textWrap
	3	->		_fontFullAlig		
	4	->		_fontRotation       (actually not used)
	5	->		_alignXToCenter;
	6	->		_alignYToCenter;
	7	->		_renderFont active;
	*/
	bool						  _FNTgrandient;
	uint16_t					  _FNTgrandientColor1;
	uint16_t					  _FNTgrandientColor2;
	bool						  _FNTcompression;
	int							  _spaceCharWidth;
	volatile bool				  _needISRrearm;
	volatile uint8_t			  _enabledInterrups;
	// Allow up to three displays to have touch?
	static void 		 		  _isr(void);
	static void 		 		  _isr1(void);
	static void 		 		  _isr2(void);
	static RA8875 				 *_active_touch_objects[3]; 
	volatile uint8_t 			 _RA8875_INTS = 0b00000000;//container for INT states

	#if !defined(_AVOID_TOUCHSCREEN)
		volatile bool			  _touchEnabled;
		volatile bool			  _clearTInt;
	#endif

	#if defined(USE_FT5206_TOUCH)
		volatile bool			  _needCTS_ISRrearm;
		static void 		 	  cts_isr(void);
		#if defined(___DUESTUFF) && defined(USE_DUE_WIRE1_INTERFACE)
		TwoWire 				 *_wire=&Wire1;
		#else
		TwoWire 				 *_wire=&Wire;
		#endif
	#elif defined(USE_RA8875_TOUCH)
		//volatile bool			  _touchEnabled;
		//volatile bool			  _clearTInt;
	#endif

	
	#ifdef SPI_HAS_TRANSACTION
	volatile uint32_t 			_SPITransactionSpeed; //holder for SPI speed
	uint32_t					_SPIMaxSpeed;         // Max Speed defined in either begin or presets...
	uint32_t					_SPIMaxReadSpeed;	  // Max Read speed defined in either begin or presets.
	#endif
	#if defined(TEENSYDUINO)//all of them (32 bit only)
		uint8_t 				  _cs;
		uint8_t 				  _miso, _mosi, _sclk;
	  #if defined(__MK64FX512__) || defined(__MK66FX1M0__)  || defined(__IMXRT1062__) || defined(__MKL26Z64__)
		SPIClass				*_pspi;	// which SPI are we using...
      #endif
	#elif defined(ENERGIA)
		uint8_t _cs;
	#else
		#if defined(___DUESTUFF)
			#if defined(_FASTSSPORT)
				uint32_t 		  _cs, cspinmask;
			#else
				uint8_t 		  _cs;
			#endif
		#elif defined(ESP8266)	
			#if defined(_FASTSSPORT)
				uint32_t 		  _cs;
			#else
				uint8_t 		  _cs;
			#endif
		#elif defined(SPARK)
			#if defined(_FASTSSPORT)
				uint32_t 		  _cs;
			#else
				uint8_t 		  _cs;
			#endif
		#else
			#if defined(_FASTSSPORT)
				uint8_t 		  _cs, cspinmask;
			#else
				uint8_t 		  _cs;
			#endif
		#endif
	#endif
 private:
 //HACK
	uint8_t _use_gfx_font = 0;
	uint8_t  _use_ili_font = 0;
	uint8_t _use_default = 1;
	uint8_t textsize, textsize_x, textsize_y;
	uint16_t textcolor, textbgcolor; 
	//anti-alias font
	uint8_t fontbpp = 1;
	uint8_t fontbppindex = 0;
	uint8_t fontbppmask = 1;
	uint8_t fontppb = 8;
	uint8_t* fontalphalut;
	float fontalphamx = 1;
	
	uint8_t							_rst;
	uint8_t							_intPin;
	uint8_t						 	_intNum;
	bool							_useISR;
	const tFont 			  	 *  _currentFont;
	bool 						 	_checkInterrupt(uint8_t _bit,bool _clear=true);
	void 						    _disableISR(void);
	
	uint32_t fetchbit(const uint8_t *p, uint32_t index);
	uint32_t fetchbits_unsigned(const uint8_t *p, uint32_t index, uint32_t required);
	uint32_t fetchbits_signed(const uint8_t *p, uint32_t index, uint32_t required);
	void 	 _fontWrite(const uint8_t* buffer, uint16_t len);
	
	/**
	 * Found in a pull request for the Adafruit framebuffer library. Clever!
	 * https://github.com/tricorderproject/arducordermini/pull/1/files#diff-d22a481ade4dbb4e41acc4d7c77f683d
	 * Converts  0000000000000000rrrrrggggggbbbbb
	 *     into  00000gggggg00000rrrrr000000bbbbb
	 * with mask 00000111111000001111100000011111
	 * This is useful because it makes space for a parallel fixed-point multiply
	 * This implements the linear interpolation formula: result = bg * (1.0 - alpha) + fg * alpha
	 * This can be factorized into: result = bg + (fg - bg) * alpha
	 * alpha is in Q1.5 format, so 0.0 is represented by 0, and 1.0 is represented by 32
	 * @param	fg		Color to draw in RGB565 (16bit)
	 * @param	bg		Color to draw over in RGB565 (16bit)
	 * @param	alpha	Alpha in range 0-255
	 **/
	uint16_t alphaBlendRGB565( uint32_t fg, uint32_t bg, uint8_t alpha )
	 __attribute__((always_inline)) {
	 	alpha = ( alpha + 4 ) >> 3; // from 0-255 to 0-31
		bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
		fg = (fg | (fg << 16)) & 0b00000111111000001111100000011111;
		uint32_t result = ((((fg - bg) * alpha) >> 5) + bg) & 0b00000111111000001111100000011111;
		return (uint16_t)((result >> 16) | result); // contract result
	}
	
	/**
	 * Same as above, but fg and bg are premultiplied, and alpah is already in range 0-31
	 */
	uint16_t alphaBlendRGB565Premultiplied( uint32_t fg, uint32_t bg, uint8_t alpha )
	 __attribute__((always_inline)) {
		uint32_t result = ((((fg - bg) * alpha) >> 5) + bg) & 0b00000111111000001111100000011111;
		return (uint16_t)((result >> 16) | result); // contract result
	}
	
	uint32_t fetchpixel(const uint8_t *p, uint32_t index, uint32_t x);

	// Touch Screen vars ---------------------
	#if !defined(_AVOID_TOUCHSCREEN)
	uint8_t						    _maxTouch;//5 on FT5206, 1 on resistive
		#if defined(USE_FT5206_TOUCH)// FT5206 specifics
			uint8_t					_intCTSNum;
			uint8_t					_intCTSPin;
			uint8_t 				_cptRegisters[31];
			uint8_t					_gesture;
			uint8_t					_currentTouches;//0...5
			uint8_t					_currentTouchState;//0,1,2
			void 					_initializeFT5206(void);
			void 					_sendRegFT5206(uint8_t reg,const uint8_t val);
			void 					_disableCapISR(void);
		#elif defined(USE_RA8875_TOUCH)//RA8875 internal resistive specifics
			uint16_t 				_tsAdcMinX,_tsAdcMinY,_tsAdcMaxX,_tsAdcMaxY;
			uint16_t 				_touchrcal_xlow,_touchrcal_ylow,_touchrcal_xhigh,_touchrcal_yhigh;
			void					readTouchADC(uint16_t *x, uint16_t *y);
			bool					_calibrated;
			boolean					_isCalibrated(void);//true if screen calibration it's present
		#endif
	#endif
	#if defined(USE_RA8875_KEYMATRIX)
		bool						_keyMatrixEnabled;
	#endif
	//system vars -------------------------------------------
	bool							_inited;//true when init has been ended
	bool							_sleep;
	enum RA8875sizes 				_displaySize;//Adafruit_480x272, etc
	bool							_portrait;
	uint8_t							_rotation;
	uint8_t							_initIndex;
	int16_t							_activeWindowXL,_activeWindowXR,_activeWindowYT,_activeWindowYB;
	uint8_t							_errorCode;
	//color vars ----------------------------------------------
	uint16_t						_foreColor;
	uint16_t						_backColor;
	bool							_backTransparent;
	uint8_t							_colorIndex;
	#if defined(USE_RA8875_SEPARATE_TEXT_COLOR)
		uint16_t					_TXTForeColor;
		uint16_t					_TXTBackColor;
		bool						_TXTrecoverColor;
	#endif
	//text vars-------------------------------------------------		
	uint8_t							_FNTspacing;
	uint8_t							_FNTinterline;
	enum RA8875extRomFamily 		_EXTFNTfamily;
	enum RA8875extRomType 			_EXTFNTrom;
	enum RA8875extRomCoding 		_EXTFNTcoding;
	enum RA8875tsize				_EXTFNTsize;//X16,X24,X32
	enum RA8875fontSource 			_FNTsource;
	enum RA8875tcursor				_FNTcursorType;
	//centering -------------------------------
	bool							_relativeCenter;
	bool							_absoluteCenter;
	//layer vars -----------------------------
	uint8_t							_maxLayers;
	bool							_useMultiLayers;
	uint8_t							_currentLayer;
	bool 							_hasLayerLimits;//helper
	//scroll vars ----------------------------
	int16_t							_scrollXL,_scrollXR,_scrollYT,_scrollYB;
	//color space-----------------------------
	uint8_t							_color_bpp;//8=256, 16=64K colors
	uint8_t							_brightness;
	//various
	float 							_arcAngle_max;
	int 							_arcAngle_offset;
	int								_angle_offset;
	// Register containers -----------------------------------------
	// this needed to  prevent readRegister from chip that it's slow.
	
	uint8_t			 _DPCR_Reg;  ////Display Configuration		  	  [0x20]
	uint8_t			 _FNCR0_Reg; //Font Control Register 0 		  	  [0x21]
	uint8_t			 _FNCR1_Reg; //Font Control Register1 			  [0x22]
	uint8_t			 _FWTSET_Reg; //Font Write Type Setting Register   [0x2E]
	uint8_t			 _SFRSET_Reg; //Serial Font ROM Setting 		  	  [0x2F]
	uint8_t			 _INTC1_Reg; //Interrupt Control Register1		  [0xF0]
	//		functions --------------------------------------------------
	void 		_initialize();
	void 		_setSysClock(uint8_t pll1,uint8_t pll2,uint8_t pixclk);
	//      TEXT writing stuff-------------------------------------------
	void    	_textWrite(const char* buffer, uint16_t len=0);//thanks to Paul Stoffregen for the initial version of this one
	void 		_charWrite(const char c,uint8_t offset);
	void 		_charWriteR(const char c,uint8_t offset,uint16_t fcolor,uint16_t bcolor);
	int 		_getCharCode(uint8_t ch);
	#if defined(_RA8875_TXTRNDOPTIMIZER)
		void 		_drawChar_unc(int16_t x,int16_t y,int charW,int index,uint16_t fcolor);
	#else
		void 		_drawChar_unc(int16_t x,int16_t y,int16_t w,const uint8_t *data,uint16_t fcolor,uint16_t bcolor);
	#endif
	
	//void 		_drawChar_com(int16_t x,int16_t y,int16_t w,const uint8_t *data);
	void 		_textPosition(int16_t x, int16_t y,bool update);
	void 		_setFNTdimensions(uint8_t index);
	int16_t 	_STRlen_helper(const char* buffer,uint16_t len=0);
	void 		fontRomSpeed(uint8_t sp);
	//--------------------------------------------------------------------
	void 		PWMsetup(uint8_t pw,boolean on, uint8_t clock);
	void 		_updateActiveWindow(bool full);
	void 		_setTextMode(bool m);
	void 		_scanDirection(boolean invertH,boolean invertV);
	// 		helpers-----------------------------
	
	void 		_circle_helper(int16_t x0, int16_t y0, int16_t r, uint16_t color, bool filled);
	void 		_rect_helper(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, bool filled);
	void 		_roundRect_helper(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color, bool filled);
	float		_check_area(int16_t Ax, int16_t Ay, int16_t Bx, int16_t By, int16_t Cx, int16_t Cy);
	void 		_triangle_helper(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color, bool filled);
	void 		_ellipseCurve_helper(int16_t xCenter, int16_t yCenter, int16_t longAxis, int16_t shortAxis,uint8_t curvePart, uint16_t color, bool filled);
	void 		_drawArc_helper(uint16_t cx, uint16_t cy, uint16_t radius, uint16_t thickness, float startAngle, float endAngle, uint16_t color);
	void 		_line_addressing(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
	void 		_curve_addressing(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
	float 		_cosDeg_helper(float angle);
	float 		_sinDeg_helper(float angle);
	#if defined(_RA8875_TXTRNDOPTIMIZER)
	void 		_charLineRender(bool lineBuffer[],int charW,int16_t x,int16_t y,int16_t currentYposition,uint16_t fcolor);
	#endif
	
	
	//convert a 16bit color(565) into 8bit color(332) as requested by RA8875 datasheet
	//inline __attribute__((always_inline))
	uint8_t _color16To8bpp(uint16_t color) 
		__attribute__((always_inline)) {
 		return ((color & 0xe000) >> 8) | ((color & 0x700) >> 6) | ((color & 0x18) >> 3);
//		return (map((color & 0xF800) >> 11, 0,28, 0,7)<<5 | map((color & 0x07E0) >> 5, 0,56, 0,7)<<2 | map(color & 0x001F, 0,24, 0,3));
	}
		
	//inline __attribute__((always_inline)) 
	void _checkLimits_helper(int16_t &x,int16_t &y)
		__attribute__((always_inline)) {
			if (x < 0) x = 0;
			if (y < 0) y = 0;
			if (x >= RA8875_WIDTH) x = RA8875_WIDTH - 1;
			if (y >= RA8875_HEIGHT) y = RA8875_HEIGHT -1;
			x = x;
			y = y;
	}
		
	//inline __attribute__((always_inline)) 	
	void _center_helper(int16_t &x, int16_t &y)
		__attribute__((always_inline)) {
			if (x == CENTER) x = _width/2;
			if (y == CENTER) y = _height/2;
	}
	#if defined(TEENSYDUINO)//all of them (32 bit only)
		// nothing, already done
	#elif defined(ENERGIA)
		// TODO
	#else
		#if defined(___DUESTUFF) // DUE
			#if defined(_FASTSSPORT)
				volatile uint32_t *csport;
			#endif
		#elif defined(ESP8266) // ESP8266
				uint32_t _pinRegister(uint8_t pin)
				__attribute__((always_inline)) {
					return _BV(pin);
				}
		#elif defined(SPARK)
			// Mmmm, dunno... put nothing for now
		#else// AVR,ARM (not DUE),STM,CHIPKIT
	    //TODO:must check if all processor are compatible
			#if defined(_FASTSSPORT)
				volatile uint8_t *csport;
			#endif
		#endif
	#endif
    // Low level access  commands ----------------------
	
	//inline __attribute__((always_inline)) 
	void _startSend()
		__attribute__((always_inline)) {
		#if defined(SPI_HAS_TRANSACTION)
			#if defined(__MK64FX512__) || defined(__MK66FX1M0__)  || defined(__IMXRT1062__) || defined(__MKL26Z64__)
				_pspi->beginTransaction(SPISettings(_SPITransactionSpeed, MSBFIRST, SPI_MODE3));
			#elif defined(ESP8266)	
				SPI.beginTransaction(SPISettings(_SPITransactionSpeed, MSBFIRST, SPI_MODE3));//it works, anyway ESP doesn't work in MODE3!
			#elif defined(SPARK)	
				SPI.beginTransaction(SPISettings(_SPITransactionSpeed, MSBFIRST, SPI_MODE0));//TODO !
			#else
				SPI.beginTransaction(SPISettings(_SPITransactionSpeed, MSBFIRST, SPI_MODE3));
			#endif
		#elif !defined(ENERGIA) && !defined(_SPITransactionSpeed) && !defined(___STM32STUFF) && !defined(ESP8266) && !defined(SPARK)
			cli();//protect from interrupts
		#endif//end has transaction
		
		#if defined(TEENSYDUINO)//all of them (32 bit only)
			digitalWriteFast(_cs, LOW);
		#elif !defined(ENERGIA)//UNO,DUE,ETC.
			#if defined(___DUESTUFF) && defined(SPI_DUE_MODE_EXTENDED)//DUE extended SPI
				//nothing
			#else//DUE (normal),UNO,ETC.
				#if defined(ESP8266)	
					#if defined(_FASTSSPORT)
						GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, _pinRegister(_cs));//L
					#else
						digitalWrite(_cs, LOW);// for now
					#endif
				#elif defined(SPARK)
					pinResetFast(_cs);
				#elif !defined(ESP8266) && defined(_FASTSSPORT)
					*csport &= ~cspinmask;
				#else
					digitalWrite(_cs, LOW);
				#endif
			#endif
		#else//ENERGIA
			digitalWrite(_cs, LOW);
		#endif
	}
	
	//inline __attribute__((always_inline)) 
	void _endSend()
		__attribute__((always_inline)) {
	#if defined(TEENSYDUINO)//all of them (32 bit only)
		digitalWriteFast(_cs, HIGH);
	#elif !defined(ENERGIA)
		#if defined(___DUESTUFF) && defined(SPI_DUE_MODE_EXTENDED)//DUE extended SPI
			//nothing
		#else//DUE (normal),UNO,ETC.
			#if defined(ESP8266)	
				#if defined(_FASTSSPORT)
					GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, _pinRegister(_cs));//H
				#else
					digitalWrite(_cs, HIGH);
				#endif
			#elif defined(SPARK)
				pinSetFast(_cs);
			#elif !defined(ESP8266) && defined(_FASTSSPORT)
				*csport |= cspinmask;
			#else
				digitalWrite(_cs, HIGH);
			#endif
		#endif
	#else//ENERGIA
		digitalWrite(_cs, HIGH);
	#endif
	
	#if defined(SPI_HAS_TRANSACTION)
		#if defined(__MK64FX512__) || defined(__MK66FX1M0__)  || defined(__IMXRT1062__) || defined(__MKL26Z64__)
			_pspi->endTransaction();
		#else
			SPI.endTransaction();
		#endif
	#elif !defined(ENERGIA) && !defined(SPI_HAS_TRANSACTION) && !defined(___STM32STUFF) && !defined(ESP8266) && !defined(SPARK)
		sei();//enable interrupts
	#endif
} 
	void    	_writeRegister(const uint8_t reg, uint8_t val);
	uint8_t 	_readRegister(const uint8_t reg);
	void    	_writeData(uint8_t data);
	uint8_t 	_readData(bool stat=false);
	boolean 	_waitPoll(uint8_t r, uint8_t f, uint8_t timeout=15);//from adafruit add settable timeout
	void 		_waitBusy(uint8_t res=0x80);//0x80, 0x40(BTE busy), 0x01(DMA busy)

	#if defined(NEEDS_SET_MODULE)//for Energia
		void 		selectCS(uint8_t module);
	#endif

#if defined(_FASTCPU)
//inline __attribute__((always_inline)) 
void _slowDownSPI(bool slow,uint32_t slowSpeed=10000000UL)
	__attribute__((always_inline)) {
	#if defined(SPI_HAS_TRANSACTION)
		if (slow){
			_SPITransactionSpeed = slowSpeed;
		} else {
			_SPITransactionSpeed = _SPIMaxSpeed;
		}
	#else
		if (slow){
			#if defined(___DUESTUFF) && defined(SPI_DUE_MODE_EXTENDED)
				SPI.setClockDivider(_cs,SPI_SPEED_SAFE);
			#else
				SPI.setClockDivider(SPI_SPEED_SAFE);
			#endif
		} else {
			#if defined(___DUESTUFF) && defined(SPI_DUE_MODE_EXTENDED)
				SPI.setClockDivider(_cs,SPI_SPEED_WRITE);
			#else
				SPI.setClockDivider(SPI_SPEED_WRITE);
			#endif
		}
	#endif
}
#endif

#if defined(__AVR__)
	//inline __attribute__((always_inline))
		void _spiwrite16(uint16_t d) 
			__attribute__((always_inline)) {
			SPDR = highByte(d);
			while (!(SPSR & _BV(SPIF)));
			SPDR = lowByte(d);
			while (!(SPSR & _BV(SPIF)));
		}

	//inline __attribute__((always_inline))
		void _spiwrite(uint8_t c) 
			__attribute__((always_inline)) {
			SPDR = c;
			//asm volatile("nop");
			while (!(SPSR & _BV(SPIF)));
		}
		
	//inline __attribute__((always_inline))
		uint8_t _spiread(void) 
			__attribute__((always_inline)) {
			uint8_t r = 0;
			SPDR = 0x00;
			//asm volatile("nop");
			while(!(SPSR & _BV(SPIF)));
			r = SPDR;
			return r;
		}
#elif defined(SPARK)
		void _spiwrite16(uint16_t d) 
			__attribute__((always_inline)) {
			SPI.transfer(d >> 8);
			SPI.transfer(d & 0xFF);
		}

		void _spiwrite(uint8_t c) 
			__attribute__((always_inline)) {
			SPI.transfer(c);
		}
		
		uint8_t _spiread(void) 
			__attribute__((always_inline)) {
			uint8_t r = SPI.transfer(0x00);
			return r;
		}
		
#endif
};
#endif // __cplusplus

#endif
