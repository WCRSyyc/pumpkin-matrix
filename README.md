# pumpkin-matrix

Arduino sketches and other information for the WCRS level 3 blinky bot pumpkin project.

This repository contains multiple sketch folders.  It is organized to make it easy to clone the repository, then (temporarily) change the Arduino sketchbook folder to the repository folder.  That will allow easy access to any and all of the sketches included here.

Not included in this repository, but the LedControl library (by Eberhadr Fahle) is need by the sketches.  Install it in your Arduino environment using the [standard process](https://www.arduino.cc/en/pmwiki.php?n=Guide/Libraries).  It is available in the the Library Manager for the (recent versions) standalone IDE.  Menu "Sketch" » "Include Library" » "Manage Libraries".

* wire_check
  * A sketch to display a simple pattern, on a single LED matrix.  Use as a simple test that the LED matrix, MAX7219 chip, and Arduino wiring has been done correctly.
* masinf
  * A sketch to demonstrate using a masks to display eyeball and pupil animations
* scroll_explore
  * A sketch to demonstrate various ways to scroll content on an LED matrix
* matrix_with_72xx
  * demonstrate frame based animation, using a struct to control sequence and timing for 2 LED Matricies
* matrix-diagonal-test
  * wiring check. Display a blinking diagonal line on a single LED matrix.
* matrix-scroll
  * scroll letters across a single LED matrix from a small set of character images
* matrix-scroll-testing
  * testing shift/scroll logic with serial print debug
* matrix-scroll-test-reduced
  * cleaned up version of matrix-scroll-testing after debug output verified
