/* Matrix Scroll
 * 
 * Sample program to scroll letters across a single LED matrix
 */

// Basic setup to be able to talk to the LED matrix controller
#include "LedControl.h"
int addr = 0;   // which display: 0 for the first display
LedControl lc=LedControl(12,11,10,1);

unsigned long scrollDelay = 200; // milliseconds between scroll steps (1 pixel)

// Data symbols (letters) as 8 x 8 bit patterns
const byte letterP[] = {
  B11111000,
  B10000100,
  B10000010,
  B11111100,
  B10000000,
  B10000000,
  B10000000,
  B00000001,
};
const byte letterH[] = {
  B10000010,
  B10000010,
  B10000010,
  B11111110,
  B10000010,
  B10000010,
  B10000010,
  B00000001,
};
const byte letterI[] = {
  B11111110,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B11111110,
  B00000001,
};
const byte letterL[] = {
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B11111110,
  B00000001,
};
const byte letterSP[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000001,
};  // Include a space at the end, so that the last letter scrolls off the display

// put (references to) the letters into an array to make stepping through them easier
const byte* const letters[] = {letterP, letterH, letterI, letterL, letterSP};
// "const" is mostly optional, but is REQUIRED for rowsInLetter, to be able to use it
// to specify the size for displayMem
unsigned const int rowsInLetter = sizeof(letterP) / sizeof(letterP[0]);
unsigned const int lettersInWord = sizeof(letters) / sizeof(letters[0]);

unsigned int displayMem[rowsInLetter];

void setup() {
  // Setup to be able to access the LED Matrix controller(s)
  lc.shutdown(addr, false);  // Wake up display(s)
  lc.setIntensity(addr, 8);  // Set intensity levels
  lc.clearDisplay(addr);     // Clear LED Matrix display
}// end setup()

void loop() {
  // Clear the in memory display
  for(int row = 0; row < rowsInLetter; row++) {
    displayMem[row] = 0;
  }
  showDisplay();  // Show empty display before starting scrolling
  delay(scrollDelay);

  // Scroll the letters across the display one at at time.
  for(int letter = 0; letter < lettersInWord; letter++) {
    // load the next letter to the low bytes of in memory display area
    for(int row = 0; row < rowsInLetter; row++) {
      displayMem[row] |= letters[letter][row];  // "|=" is 'or equals'; "+=" works here too
    }

    // scroll (shift) the new letter into the display area one column at a time
    for(int shiftCnt = 0; shiftCnt < 8; shiftCnt++) {
      // shift each row of the display area over one pixel
      for(int row = 0; row < rowsInLetter; row++) {
        displayMem[row] <<= 1;
      }
      showDisplay();  // Display after scrolling
      delay(scrollDelay);
    }
  }
}// end loop()

// Send the upper byte of the in memory display area to the physical display
void showDisplay() {
  for(int row = 0; row < rowsInLetter; row++) {
    byte imageRow = displayMem[row] >> 8;
    lc.setRow(addr, row, imageRow);
  }
}// end showDisplay()

