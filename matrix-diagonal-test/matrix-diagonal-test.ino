// Get the matrix to display a diagonal line and refresh

/* 
 *  The purpose of this program is make sure you have correctly wired one 8 x 8 matrix 
 *  to a 7219 chip and an accompanying Arduino.  You should see a blinking diagonal line
 *  from the upper left-hand corner to the lower right-hand corner of the matrix.
 */

/* Include the library needed to communicate with the 7219 driver chip.
 * This chip handles the multiplexing (also called scanning) for the 8x8 matrix and 
 * reduces the number of required Arduino pins.
 */

#include <LedControl.h>

// Define constants requried by LedControl.h

/* Note the all caps used to define these constants.  This is a coding convention 
 * used for unchanging constants, as opposed to a variable.
 */

/* There are three pins associated with the SPI protocol (Serial Peripheral Interface Bus)
 * which is used to communicate with the 7919 chip.
 */

// Define the MISO (master input slave output) interface
const unsigned int LC_DATA_IN = 12;

// Define the SCK (serial clock) interface
const unsigned int LC_CLK = 11;

// Define the SS (slave select) interface
const unsigned int LC_LOAD = 10;

// Define the number of matrices connected
const unsigned int LC_NUM_DEVICES = 1;

// Pass this data to the LedControl library and save it in memory as lc

// Is there a better way to explain this -- simply?

LedControl lc = LedControl(LC_DATA_IN, LC_CLK, LC_LOAD, LC_NUM_DEVICES);

/* 
 *  Define a bit array to correspond to the matrix LEDs.
 *  A 1 turns the LED on and a 0 turns it off.
 */

byte matrix[8] = {
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
};

/*  Define a delay time between loops.
 *  Note the use of capitals for a variable. 
 *  The convention is to start with a small letter and use Caps in the middle to make
 *  the name more readable.
 */

int delayTime = 200;

void setup() {
  lc.shutdown(0,false);  // Wake up the display
  lc.setIntensity(0,5);  // Set the intensity level
  lc.clearDisplay(0);  // Clear the display
}

void loop() {
  
  // Note the use of a for loop here.
  
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,matrix[i]);
  }
  delay (delayTime);
  lc.clearDisplay(0);
  delay (delayTime);
}

