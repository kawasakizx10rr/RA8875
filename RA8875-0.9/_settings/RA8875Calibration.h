#ifndef _RA8875CAL_H_
#define _RA8875CAL_H_


/* Calibration Data --------------------------------*/
/* ------------- TOUCH SCREEN CALIBRATION (how to) -----------
Touch Screen are not all the same and needs a calibration, you will see
yourself by load touchPaint.ino example, try to paint all over the screen!
If you have space on one or more side you prolly need to calibrate values  
    ---- perform calibration ----
To perform the touch screen calibration, load libTouchSCalibration.ino and open serial terminal:
(you have to put data inside RA8875/_utility/RA8875Calibration.h)
1) the lowest value of x by touch the top/left angle of your tft, put value in TOUCSRCAL_XLOW
2) you can get the lowest value of y in the same time, put value in TOUCSRCAL_YLOW
3) the highest value of x by touching the lower/bottom corner of your tft, put the value in TOUCSRCAL_XHIGH
4) in the same manner you get the max value of y, put that value in TOUCSRCAL_XHIGH
*/

// BuyDisplay 5" preset
#define TOUCSRCAL_XLOW  63
#define TOUCSRCAL_YLOW  109
#define TOUCSRCAL_XHIGH 924
#define TOUCSRCAL_YHIGH 902

// Adafruit 5" preset
//#define TOUCSRCAL_XLOW  952
//#define TOUCSRCAL_YLOW  900
//#define TOUCSRCAL_XHIGH 62
//#define TOUCSRCAL_YHIGH 123

// Randys 7" preset 
//#define TOUCSRCAL_XLOW   925
//#define TOUCSRCAL_YLOW   900
//#define TOUCSRCAL_XHIGH  62
//#define TOUCSRCAL_YHIGH  123

// New 5" preset 
//#define TOUCSRCAL_XLOW   0
//#define TOUCSRCAL_YLOW   0
//#define TOUCSRCAL_XHIGH  0
//#define TOUCSRCAL_YHIGH  0

#endif