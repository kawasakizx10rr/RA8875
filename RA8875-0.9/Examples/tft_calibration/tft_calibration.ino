#include <SPI.h>
#include <RA8875.h>
#include "Fonts/Akashi_36.h"

namespace pin {
const byte ra8875_int = 2;
const byte ra8875_rst = 33;
const byte ra8875_cs = 34;
const byte ra8875_sdo = 50;
const byte ra8875_sdi = 51;
const byte ra8875_sck = 52;
}

RA8875 tft = RA8875(pin::ra8875_cs, pin::ra8875_rst);

const uint8_t samples = 20;
uint16_t tempData[samples][2];
volatile int count = 0;
uint16_t tx, ty;//used as temp
uint16_t _XLOW_VAR;
uint16_t _YLOW_VAR;
uint16_t _XHIGH_VAR;
uint16_t _YHIGH_VAR;
bool proceed;
int scount = 0;

#if !defined(USE_RA8875_TOUCH) || defined(_AVOID_TOUCHSCREEN)
#error "you need to enable resistive touchscreen by uncommenting USE_RA8875_TOUCH in settings!"
#endif

void setup() {
  Serial.begin(115200);
  Serial.println("RA8875 calibration started...");
  tft.begin(RA8875_800x480); // BuyDisplay
  tft.setFont(&akashi_36px_Regular);
  tft.setFontScale(1);
  tft.setTextColor(RA8875_WHITE, RA8875_BLACK);
  //tft.begin(Adafruit_800x480);
  tft.useINT(pin::ra8875_int);
  tft.touchBegin();
  tft.enableISR(true);
  if (tft.touchCalibrated()) {//already calibrated?
    if (tft.width() > 480)
      tft.setFontScale(1);
    Serial.println("You have old calibration data present!\n");
    Serial.println("\nPlease open RA8875/_utility/RA8875calibration.h and put zero on the following:\n");
    Serial.println("#define TOUCSRCAL_XLOW  0");
    Serial.println("#define TOUCSRCAL_YLOW  0");
    Serial.println("#define TOUCSRCAL_XHIGH 0");
    Serial.println("#define TOUCSRCAL_YHIGH 0\n");
    Serial.println("Then save and try to run this again!");
    tft.setCursor(0, 0);
    tft.println("---> You have old calibration data present! <---");
    tft.println("Please open RA8875/_utility/RA8875calibration.h");
    tft.println("and put zero on the following:");
    tft.println(" ");
    tft.println("   #define TOUCSRCAL_XLOW   0");
    tft.println("   #define TOUCSRCAL_YLOW   0");
    tft.println("   #define TOUCSRCAL_XHIGH  0");
    tft.println("   #define TOUCSRCAL_YHIGH  0");
    tft.println(" ");
    tft.print("Then save and try to run this again!");
    proceed = false;
  }
  else {
    Serial.println("Start calibration, please follow indications...\n");
    Serial.println("\nPlease press FIRMLY the TOP/LEFT angle of your screen now!\n");
    if (tft.width() > 480)
      tft.setFontScale(1);
    tft.setCursor(CENTER, CENTER);
    tft.print("Please press the TOP/LEFT angle now!");
    tft.fillCircle(5, 5, 5, RA8875_RED);
    proceed = true;
    //You can avoid ISR by simple ignore the line above
    //it will use the slower digitalRead(pin) alternative internally
  }
}

void loop() {
  if (proceed) {
    if (tft.touched()) {
      if (count >= samples) {
        tft.touchEnable(false);
        count = 0;//reset counts
        uint32_t valx = 0;
        uint32_t valy = 0;
        if (scount < 1) {
          for (uint8_t i = 0; i < samples; i++) {
            valx += tempData[i][0];
            valy += tempData[i][1];
          }
          valx = valx / samples;
          valy = valy / samples;
          tft.fillWindow();
          if (tft.width() > 480)
            tft.setFontScale(1);
          tft.setCursor(CENTER, CENTER);
          tft.println("Top/Left done. Please do not touch screen...");
          tft.setFontScale(1);
          tft.print("Please do not touch screen!");
          tft.setFontScale(0);
          Serial.print("Top/Left done...");
          Serial.print("Please do not touch screen...");
          _XLOW_VAR = valx;
          _YLOW_VAR = valy;
          delay(3000);
          tft.fillWindow();
          tft.fillCircle(tft.width() - 5, tft.height() - 5, 5, RA8875_RED);
          if (tft.width() > 480)
            tft.setFontScale(1);
          tft.setCursor(CENTER, CENTER);
          tft.print("ok, Now Touch Bottom/Right angle!");
          Serial.println("\n...done, Now Touch Bottom/Right angle!");
          delay(2000);
          tft.touchEnable(true);
          scount++;
        }
        else if (scount >= 1) {
          for (uint8_t i = 0; i < samples; i++) {
            valx += tempData[i][0];
            valy += tempData[i][1];
          }
          valx = valx / samples;
          valy = valy / samples;
          tft.fillWindow();
          tft.setCursor(0, 20);
          tft.println("Calibration done...watch results!");
          Serial.println("\nCalibration done...watch results");
          _XHIGH_VAR = valx;
          _YHIGH_VAR = valy;
          tft.println("Now open file:");
          tft.println("RA8875-0.81\\_settings\\RA8875Calibration.h");
          Serial.println("\nNow open file Documents\\Arduino\\libraries\\RA8875-0.81\\_settings\\RA8875Calibration.h \n");
          Serial.println("Change the following:\n");
          tft.println("Change the following:");
          tft.println(" ");
          tft.print("#define TOUCSRCAL_XLOW   ");
          tft.println(_XLOW_VAR, DEC);
          tft.print("#define TOUCSRCAL_YLOW   ");
          tft.println(_YLOW_VAR, DEC);
          tft.print("#define TOUCSRCAL_XHIGH  ");
          tft.println(_XHIGH_VAR, DEC);
          tft.print("#define TOUCSRCAL_YHIGH  ");
          tft.println(_YHIGH_VAR, DEC);
          tft.println(" ");
          tft.println("...then save file and you are calibrated!");
          Serial.println("#define TOUCSRCAL_XLOW  0");
          Serial.println("#define TOUCSRCAL_YLOW  0");
          Serial.println("#define TOUCSRCAL_XHIGH 0");
          Serial.println("#define TOUCSRCAL_YHIGH 0");
          Serial.println("\nInto:\n");
          Serial.print("#define TOUCSRCAL_XLOW  ");
          Serial.println(_XLOW_VAR, DEC);
          Serial.print("#define TOUCSRCAL_YLOW  ");
          Serial.println(_YLOW_VAR, DEC);
          Serial.print("#define TOUCSRCAL_XHIGH ");
          Serial.println(_XHIGH_VAR, DEC);
          Serial.print("#define TOUCSRCAL_YHIGH ");
          Serial.println(_YHIGH_VAR, DEC);
          Serial.println("\nSave and Have a nice day!");
          proceed = false;
          tft.touchEnable(false);
        }
      }
      else {//continue get samples
        delay(1);
        tft.touchReadAdc(&tx, &ty);//we using 10bit adc data here
        if (count >= 0) {
          tempData[count][0] = tx;
          tempData[count][1] = ty;
        }
        count++;
      }
    }
  }//proceed
}
