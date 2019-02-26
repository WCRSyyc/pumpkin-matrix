#include <LedControl.h>

const unsigned int LC_DATA_IN = 12;
const unsigned int LC_CLK = 11;
const unsigned int LC_LOAD = 10;
const unsigned int LC_NUM_DEVICES = 2;
const int LEFT_ADDR = 0;
const int RIGHT_ADDR = 1;
const int MAT_BRIGHTNESS = 7; // 0 .. 15 = min .. max

LedControl lc1 = LedControl(LC_DATA_IN, LC_CLK, LC_LOAD, LC_NUM_DEVICES);
byte frame0[] = {B11111111, B10000001, B10000001, B10000001, B10000001, B10000001, B10000001, B11111111};
byte frame1[] = {B00000000, B01111110, B01000010, B01000010, B01000010, B01000010, B01111110, B00000000};
byte frame2[] = {B00000000, B00000000, B00111100, B01000010, B01000010, B00111100, B00000000, B00000000};
byte frame3[] = {B00000000, B00000000, B00000000, B00011000, B00011000, B00011000, B00000000, B00000000};

byte frame4[] = {B11000000, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};
byte frame5[] = {B00000000, B01100000, B01100000, B00000000, B00000000, B00000000, B00000000, B00000000};
byte frame6[] = {B00000000, B00000000, B00110000, B00110000, B00000000, B00000000, B00000000, B00000000};
byte frame7[] = {B00000000, B00000000, B00000000, B00011000, B00011000, B00000000, B00000000, B00000000};
byte frame8[] = {B00000000, B00000000, B00000000, B00000000, B00001100, B00001100, B00000000, B00000000};
byte frame9[] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000110, B00000110, B00000000};
byte framea[] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B00000011};

struct Frame {
  byte * pattern; // 8 byte array
  unsigned long ms; // milliseconds to display
};
Frame leftEye[] = {{frame0, 400}, {frame1, 200}, {frame2, 200}, {frame3, 400}, {frame2, 200}, {frame1, 200}};
Frame rightEye[] = {{frame4, 240}, {frame5, 120}, {frame6, 120}, {frame7, 120}, {frame8, 120}, {frame9, 120},
  {framea, 120}, {frame9, 120}, {frame8, 120}, {frame7, 120}, {frame6, 120}, {frame5, 120}};
unsigned int leftSteps = sizeof(leftEye) / sizeof(Frame);
unsigned int rightSteps = sizeof(rightEye) / sizeof(Frame);
unsigned int curLeft, curRight;
unsigned long lastLeft, lastRight;

void setup() {
  lc1.shutdown(LEFT_ADDR, false); // wake up from power saving mode
  lc1.shutdown(RIGHT_ADDR, false);
  lc1.setIntensity(LEFT_ADDR, MAT_BRIGHTNESS);
  lc1.setIntensity(RIGHT_ADDR, MAT_BRIGHTNESS);
  curLeft = curRight = 0;
  lastLeft = lastRight = millis();
  showFrame(lc1, LEFT_ADDR, leftEye[curLeft].pattern);
  showFrame(lc1, RIGHT_ADDR, rightEye[curRight].pattern);
}

void loop() {
  unsigned long animTime = millis();

  if (animTime - lastLeft >= leftEye[curLeft].ms) {
    curLeft++;
    if (curLeft >= leftSteps) {
      curLeft = 0;
    }
    showFrame(lc1, LEFT_ADDR, leftEye[curLeft].pattern);
    lastLeft = animTime;
  }

  if (animTime - lastRight >= rightEye[curRight].ms) {
    curRight++;
    if (curRight >= rightSteps) {
      curRight = 0;
    }
    showFrame(lc1, RIGHT_ADDR, rightEye[curRight].pattern);
    lastRight = animTime;
  }
}

/**
 Show a frame (image) that controls every LED of an 8 by 8 LED matrix
 
 @oaram lc LedControl instance
 @param addr address of the 72xx chip
 @param frame array of 8 bit patterns, one for each row
 */
void showFrame(LedControl lc, const int addr, const byte * frame) {
  for(int row = 0; row < 8; row++) {
    lc.setRow(addr, row, frame[row]);
  }
}
