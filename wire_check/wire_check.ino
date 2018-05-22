/* wire_check

Check that one MAX7219 chip and 8 x 8 LED matrix has been correctly wired to an Arduino.

You should see a blinking diagonal line from the upper left-hand corner to the lower
right-hand corner of the LED matrix.

 */

/* Include the library needed to communicate with the MAX7219 driver chip.
 * This chip handles the multiplexing (also called scanning) for the 8x8 matrix and 
 * reduces the number of required Arduino pins.
 */

#include <LedControl.h>

// Define constants required by LedControl.h

/* Note the all caps used to define these constants.  This is a coding convention 
 * used for unchanging constants, as opposed to variables.
 */

/* There are three pins associated with the SPI protocol (Serial Peripheral Interface Bus)
 * which is used to communicate with the MAX7219 chip.
 * The "LC_" prefix for the name is just to show they are going to be used by "LedControl".
 * The MAX72xx chips use the SPI hardware interface for communications.  Arduino boards
 * also have an SPI hardware interface, but the library used here uses software control to
 * emulate the hardware interface.  That means that any digital pins can be used, at the
 * cost of making the Arduino work harder to send the data.
 */

// Define the MISO (master input slave output) interface pin
const unsigned int LC_DATA_IN = 12;

// Define the SCK (serial clock) interface pin
const unsigned int LC_CLK = 11;

// Define the SS (slave select) interface
const unsigned int LC_LOAD = 10;

// Define the number of matrices connected
const unsigned int LC_NUM_DEVICES = 1;

// Have the library create an interface that knows about the pin numbers, and device count
// "lc" is the program interface to the 7219 chip that controls the LED Matrix.

LedControl lc = LedControl(LC_DATA_IN, LC_CLK, LC_LOAD, LC_NUM_DEVICES);

/*
 *  Define a bit array with any to correspond to each of the matrix LED rows.
 *  A 1 turns the LED on and a 0 turns it off.
 */

const static byte testDisplay[] PROGMEM = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
};

// Get the actual number of entries in the array, to use when sequencing through them
unsigned int displaySize = sizeof(testDisplay) / sizeof(byte); // better be 8 for the matrix

/*  Define a wait time between display changes.
 *  Note the use of capitals for a variable. 
 *  The convention is to start with a small letter and use Caps in the middle to make
 *  the name more readable.
 */

int delayTime = 200; // milliseconds

int lcAddress = 0; // the first MAX7219 is address 0, and only one used in this sketch
int lcIntensity = 5; // brightness of the display (LEDS); minimum 0 to maximum 15

void setup() {
  lc.shutdown(lcAddress, false);  // Wake up the display
  lc.setIntensity(lcAddress, lcIntensity);  // Set the intensity level
  lc.clearDisplay(lcAddress);  // Clear the display
}

void loop() {
  
  // Note the use of a for loop here.
  
  for (int lcRow = 0; lcRow < displaySize; lcRow++) {  // for each row of the LED matrix
    lc.setRow(lcAddress, lcRow, testDisplay[lcRow]); // Set the LEDs to be on for a single row
  }
  delay(delayTime); // Full display set: leave it there for awhile
  lc.clearDisplay(lcAddress); // clear the matrix display (all LEDs off)
  delay(delayTime); // Leave it off for awhile
}

