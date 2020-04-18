# A DIY Rock Band MIDI Controller/Adapter

## Features:

* Ability to freely map MIDI events to controller inputs
* USB MIDI input, including support for high speed devices
* DIN 41524 MIDI input, allowing it to replace MIDI Pro adapters
* MIDI output via DIN and USB
* Native controller support, not requiring additional controllers to join and
  allowing system menus to be navigated
* Wireless support, eliminating the need for extremely long USB or MIDI cables

## Requirements:

* A native Rock Band drum controller for your platform
* A Teensy 4.0 (porting to other Teensy models or other micro controllers would be easy)
* An external DIN MIDI and/or USB MIDI Host I/O circuit
  * You can build one yourself based on the provided schematic, or use the provided PCB
* An optional enclosure
  * You can build one yourself, or use the provided 3d-printed one

## Firmware

The firmware uses the platformio.org ecosystem. You can build and upload it
using `pio run -t upload`.

There's real no configuration currently, and most behaviour is just hardcoded
in [main.cpp](firmware/src/main.cpp). You can change your MIDI mapping and
pinout by making changes there.

## Hardware

The [schematic](hardware/rbdrums.pdf) includes DIN MIDI input, DIN MIDI output,
and USB Host MIDI input. You can omit the ones you don't need as you see fit.

### Connecting to controller PCB

I've only used this with a PlayStation 4 drum wireless drum controller that
shipped with Rock Band 4.

The same approach will also work for other drum controllers, but might need
some software tweaks. You might however lose some features, such as being able
to natively navigate system menus on PS4 when using a PS3 drum controller.

Similarly, the same approach will also work with other platforms, such as Xbox
One, Xbox 360, and Wii, as long as you have an appropriate native drum kit for
that platform.

#### Drum Pads

The inputs for the drum pads are easily accessible on the controller PCB and
labeled with the corresponding color on the silk screen. I've re-used the JST
connectors that the piezo elements were connected to in the original drum
controller, but you can also solder to the test points next to the JST
connectors. Note that the polarity is flipped between the connectors on the
left and right side of the controller. Be sure to not accidentally flip signal
and ground.

#### Kick

This is accessible using a JST connector at the bottom of the controller PCB,
similar to the drum pad inputs.

#### Cymbals

These inputs are accessible via 5-pin JST connector at the top of the
controller PCB. The signals for the three cymbals are on the 3 center pins,
surrounded by GND and V+ on either side.

#### Buttons

These are optional and not required to just be able to play Rock Band drums,
but can be connected to the micro controller to allow the firmware to trigger
them, for example to be able to pause the game with a spare cymbal.
Additionally, triggering the 4 drum pads using these buttons as opposed to the
piezo sensor inputs seems to cause less latency within the original controller
firmware.

The inputs aren't broken out in an easily accessible way. I've connected the
signals to the "far" end of the current limiting resistors on each of the input
pins on the controller PCB.

#### Power

This is accessible as a JST header on the top right of the controller PCB.
Supplying 3.3V works fine, even though that's slightly higher than the
controller's original supply voltage. The 250mA provided by the Teensy's 3.3V
regulator are plenty to power the controller PCB.

You can use the Ground pin on the power connector or any of the signal
connectors or a combination thereof to reference to the Teensy's Ground.

### PCB

The provided [PCB](hardware/rbdrums.kicad_pcb) provides an easy way to connect
the Teensy to MIDI inputs and outputs as well as the appropriate places on the
controller PCB.

Please note that:

* You don't need to connect all the Ground pads provided. Any one will do. More
  than one won't hurt.

* Ground and Signal pads are swapped for two of the drum pad outputs to
  accommodate for the flipped polarity on two of the original JST connectors.

* Some mounting holes shouldn't be used, as they're too close to traces. Metal
  screws will damage those traces. Nylon screws might be OK to use for them,
  but you really don't need all of them.

* The 15kΩ pull-down resistance for USB D+ and D- is split into 2 resistors in
  series each, as I didn't have 15kΩ resistors handy. If you do, just use one
  resistor each accross the two footprints.

* There should probably be some input protection for the DIN MIDI output. Don't
  accidentally plug your instrument's MIDI output into the controller's MIDI
  output.

### Enclosure

The provided 3d-printed [enclosure](enclosure/) isn't great, but works well
enough. You'll need some M3 nuts and bolts for assembly. There's embedded
cutouts for M3 hex nuts to attach the front panel to the rest of the box.
You'll need to pause the print at the appropriate layer to insert these hex
nuts before continuing.

The design is available at
https://cad.onshape.com/documents/a9620f856c6ff58f2b23ec93/w/108910e108c10d455aeabe6d/e/1614ddb50d750c8a54a42bdd
