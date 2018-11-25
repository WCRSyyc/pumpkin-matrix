// also see https://www.brainy-bits.com/how-to-control-max7219-led-matrix/
// also see https://playground.arduino.cc/Main/LedControl
// initial test for led matrix testing.

#include "LedControl.h"

int addr = 0;   // which display: 0 for the first display

/*
 * The pin numbers in the LEDCONTROL function must match your wiring
 * LedControl(int dataPin, int clkPin, int csPin, int numDevices) {
 *  SPI_MOSI=dataPin
 *  SPI_CLK=clkPin
 *  SPI_CS=csPin
 *  numDevices
 */

LedControl lc=LedControl(12,11,10,1);  // Pins: DIN,CLK,CS, # of Display connected

const unsigned long eyebase[] = {
  0b111111111111111111111111,   // 0
  0b111111111111111111111111,   // 1
  0b111111111111111111111111,   // 2
  0b111111111111111111111111,   // 3
  0b111111111111111111111111,   // 4
  0b111111111111111111111111,   // 5
  0b111111111111111111111111,   // 6
  0b111111111111111111111111,   // 7
  0b111111111111111111111111,   // 8
  0b111111111111111111111111,   // 9
  0b111111111111111111111111,   // 10
  0b111111111111111111111111,   // 11
  0b111111111110011111111111,   // 12
  0b111111111110011111111111,   // 13
  0b111111111111111111111111,   // 14
  0b111111111111111111111111,   // 15
  0b111111111111111111111111,   // 16
  0b111111111111111111111111,   // 17
  0b111111111111111111111111,   // 18
  0b111111111111111111111111,   // 19
  0b111111111111111111111111,   // 20
  0b111111111111111111111111,   // 21
  0b111111111111111111111111,   // 22
  0b111111111111111111111111,   // 23
};
const byte roundEye[] = {
  0b11000011,   // 0
  0b10000001,   // 1
  0b00000000,   // 2
  0b00000000,   // 3
  0b00000000,   // 4
  0b00000000,   // 5
  0b10000001,   // 6
  0b11000011,   // 7
};

void setup()
{
  lc.shutdown(addr,false);  // Wake up displays
  lc.setIntensity(addr,8);  // Set intensity levels
  lc.clearDisplay(addr);  // Clear Displays
}

void loop() {
  displayAt0(0,0);
  delay(1000);
  displayAt0(8,8);
  delay(100000);
}

void displayAt0(const int x, const int y) {
  for(int row = y; row < y + 8; row ++) {
    lc.setRow(addr, row - y, eyebase[row] >> x);
  }
}

void displayAt1(const int x, const int y) {
  byte eyeball[8];
  for(int row = y; row < y + 8; row ++) {
    eyeball[row - y] = roundEye[row - y] & eyebase[row] >> x;
  }
  for(int row = 0; row < 8; row ++) {
    lc.setRow(addr, row, eyeball[row]);
  }
}

void displayAt2(const int x, const int y) {
  byte eyeball[8];
  for(int row = y; row < y + 8; row ++) {
    eyeball[row - y] = eyebase[row] >> x;
  }
  for(int row = 0; row < 8; row ++) {
    lc.setRow(addr, row, roundEye[row] & eyeball[row]);
  }
}
