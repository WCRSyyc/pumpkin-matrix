/* Matrix Scroll
 *
 * Explore simple ways to scroll an LED matrix display left to right.  Initial 
 * use is intend to scroll a few character, to display a name.  It should work
 * find with any 8 x 8 image data.
 */

// Basic setup to be able to talk to the LED matrix controller
#include "LedControl.h"
int addr = 0;   // which display: 0 for the first display
LedControl lc=LedControl(12,11,10,1);

unsigned long scrollDelay = 100; // milliseconds between scroll steps (1 pixel)

// Data symbol (letters) as 8 x 8 bit patterns
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
};
// put (references to) the letters into an array to make stepping through them easier
const byte* const letters[] = {letterP, letterH, letterI, letterL, letterSP};
unsigned const int rowsInLetter = sizeof(letterP) / sizeof(letterP[0]);
unsigned const int lettersInWord = sizeof(letters) / sizeof(letters[0]);

unsigned int displayMem[rowsInLetter];

void setup() {
  // Setup to be able to access the LED Matrix controller(s)
  lc.shutdown(addr, false);  // Wake up display(s)
  lc.setIntensity(addr, 8);  // Set intensity levels
  lc.clearDisplay(addr);     // Clear LED Matrix display

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Matrix Scrolling tests");
//  Serial.print(rowsInLetter);
//  Serial.println(" rows in one letter");
//  Serial.print(sizeof(displayMem) / sizeof(displayMem[0]));
//  Serial.println(" rows in display area");
}

void loop() {
  // put your main code here, to run repeatedly:
//  testShowLetterP();
//  testShowLetter();
//  testShowWord();
  scrollTest1();
  delay(60000);  // remove for continuous rotation
}

void scrollTest1() {
  // Clear the in memory display
  for(int row = 0; row < rowsInLetter; row++) {
    displayMem[row] = 0;
  }
  showDisplay();  // Display empty display before starting scrolling
  delay(scrollDelay);

  // Scroll the letters across the display one at at time.
  for(int letter = 0; letter < lettersInWord; letter++) {
    // load the next letter to the low bytes of in memory display area
    for(int row = 0; row < rowsInLetter; row++) {
      displayMem[row] |= letters[letter][row];
//      displayMem[row] += letters[letter][row];
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
    // Last row of last letter not displayed yet
  }
  Serial.println();  // Remove for real display
}// end scrollTest1()

// Send the upper byte of the in memory display area to the physical display
void showDisplay() {
  for(int row = 0; row < rowsInLetter; row++) {
    byte imageRow = displayMem[row] >> 8;
    lc.setRow(addr, row, imageRow);
    showImageRow(imageRow);  // Remove for real display
  }
  Serial.println("....");  // Remove for real display
}// end showDisplay()


// Some debug / testing code, to make sure that the tools being used to simulate
// the LED matrix display work as expected.
void testShowLetterP() {
  // Verify that can display a single letter, using the direct letter array reference
  Serial.println("\nLetter P");
  for(int row = 0; row < sizeof(letterP); row++) {
    Serial.println(letterP[row], BIN);
  }
}// end testShowLetter()

void testShowLetter() {
  // Verify that can display a single letter from the array of letters
  Serial.println("\nSecond letter");
  for(int row = 0; row < rowsInLetter; row++) {
    showImageRow(letters[1][row]);
  }
}

void testShowWord() {
  // Verify that can display the whole word, one letter at a time
  Serial.println("\nPHIL");
  for(int letter = 0; letter < lettersInWord; letter++) {
    for(int row = 0; row < rowsInLetter; row++) {
      showImageRow(letters[letter][row]);
    }
    Serial.println();
  }
}

// Display a single byte, with leading "B"
void showImageRow(byte rowData) {
  Serial.print('B');
  print8Bits(rowData);
  Serial.println();
}

// Display a single byte, with leading zeros
void print8Bits(byte bitData) {
  for(byte mask = 0x80; mask; mask >>= 1) {
    if(mask & bitData) {
      Serial.print('1');
    } else {
      Serial.print('0');
    }
  }
}

