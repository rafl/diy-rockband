# MIDI Pro Adapter Hardware Documentation

This directory contains the information I've been able to gather on the
original Mad Catz MIDI Pro Adapter hardware for PlayStation 3, XBox 360, and
Wii.

## Schematic

This directory contains a KiCad project documenting the schematic of the
device. A PDF rendering is available [here](mpa.pdf).

## Observations

* PlayStation 3, XBox 360, and Wii models of the device are effectively identical, having with just these differences:
  * LEDs have different colours on different models
  * There's two footprints for each of the 4 status LEDs. One for Wii and PS3 at the bottom, and one for XBox around the center,
  * The jumpers JP1 and JP2 are used to configure the device model at the factory.
    * JP2 being open selects the PS3 model
    * If JP2 is closed, JP1 selects between Wii (open) and XBox (closed)
  * U104 and C113 are only populated on the XBox model
* It's easy to convert between PS3 and Wii MIDI Pro Adapters by changing JP1 and JP2
  This is very convenient, as the former are often hard to find, whereas the latter tend to be available quite cheaply.
* It's possible to convert a PS3 or Wii device to an XBox model if you can supply the U104 chip
  * That chip seems to handle XBox-specific authentication functionality
  * What appears to be clones seems easily available from different distributors
  * One can probably harvest the same chip from other original XBox 360 controllers
* The C2CLK and C2D pins are prominently exposed as test points, and might allow firmware extraction and modification if the lock bits aren't set on the MCU
