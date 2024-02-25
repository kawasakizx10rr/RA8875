/*
autocenter example:
setCursor has an optional parameter that let you precisely center
text regardless text lenght.
The autocenter flag, automatically reset after each use!!!
*/

#include <SPI.h>
#include <RA8875.h>
#include "Fonts/Akashi_36.h"
#include "Fonts/Hallfetica_42_Nums.h"

/*
Arduino's
 You are using 4 wire SPI here, so:
 MOSI:  11//Arduino UNO
 MISO:  12//Arduino UNO
 SCK:   13//Arduino UNO
 the rest of pin below:
*/

#define RA8875_CS 10 //see below...
/* Arduino's 8 bit: any pin will be ok*/
#define RA8875_RESET 9//any pin or nothing!


RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);//arduino's


void setup()
{
	tft.begin(RA8875_800x480);//or whatever you have
	tft.fillWindow(RA8875_BLACK);
	tft.setFont(&akashi_36px_Regular);
	tft.setFontScale(1);
	tft.setTextColor(RA8875_WHITE, RA8875_BLACK);
	tft.print(100,100, F("RA8875 text test"));
	tft.setCursor(110, 140);
	tft.print(F("Hello ")); tft.print(F(" you are you?")); 
	tft.print(110, 180, F("This i another line  ")); tft.print(tft.getFontX(), 180, F(" of text"));
	delay(2000);
	tft.fillWindow(RA8875_BLACK);
	tft.setFont(&HallfeticaLargenum_42px_Regular);
}

void loop()
{
  static float previousValue = 0;
  static int16_t startX = 0, endX = 0;
  static float value = 0;
  tft.fillRect(startX, 248, endX - startX, 90, RA8875_BLACK);
  startX = (tft.width() / 2) - tft.getStringWidth(value, 2) / 2;
  tft.print(startX, 250, value, 2);
  endX = tft.getFontX();
  value += 0.1;
}