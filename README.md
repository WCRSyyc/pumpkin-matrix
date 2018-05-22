# pumpkin-matrix

Arduino sketches and other information for the WCRS level 3 blinky bot pumpkin project.

This repository contains multiple sketch folders.  It is organized to make it each to clone the repository, then (temporarily) change the Arduino sketchbook folder to the repository folder.  That will allow easy access to any and all of the sketch included here.

Not included in this repository, but the LedControl library (by Eberhadr Fahle) is need by the sketches.  Install it in your Arduino environment using the [standard process](https://www.arduino.cc/en/pmwiki.php?n=Guide/Libraries).  It is available in the the Library Manager for the (recent versions) standalone IDE.  Menu "Sketch" » "Include Library" » "Manage Libraries".

* wire_check
  * A sketch to display a simple pattern, on a single LED matrix.  Use as a simple test that the LED matrix, MAX7219 chip, and Arduino wiring has been done correctly.