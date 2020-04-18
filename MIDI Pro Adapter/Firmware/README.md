# MIDI Pro Adapter Firmware documentation

## Observations

* The device slightly changes how it presents itself over USB based on the model selection with JP1 and JP2, as well as based on the SW101 setting
  * Seems to just affect USB PID+VID and descriptor strings
  * See the [lsusb](lsusb/) folder for details
* The HID-level communication is identical between models
* When configured as the XBox model, the firmware will attempt to communicate with the U104 IC to retrieve its serial number
  * U104 might be used for other purposes as well
* The firmware runs on a standard 8051 MCU
* It might be possible to extract the code using the C2 protocol
* There appears to be a mechanism commonly referred to as "roll limit", which limits how quickly events can be triggered in succession
  * This seems to happen in the controller firmware only, and not on the console
* The device is a mostly-standard HID joystick
  * It's easy to emulate a compatible device
  * The console only relies on a few things such as USB VID+PID and HID endpoints
    * At least PS3, but potentially also PS4, will request the USB Manufacturer ID string (0x0301) with the non-standard LANGID 0x0048, so any emulated devices will need to present a compatible descriptor
  * The device can act as drums, keys, or guitar within the game, so it's easy to emulate any one of those input device
* The device supports full-speed mode only, making it fairly easy to emulate
