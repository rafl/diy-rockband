# MIDI Pro Adapter Documentation 

This directory contains a number of resources on Mad Catz' original MIDI Pro Adapter for Rock Band 3.

* [hardware](Hardware/)
* [firmware](Firmware/)

## Emulation

There's a number of projects that emulate MIDI Pro Adapters with varying
feature sets. Here's a likely imcomplete list:

* [rockbend](../rockbend)
  An open source hardware and software Rock Band interface platform with hardware-support for MIDI Pro Adapter emulation, but no software-support for it yet.

* http://progsoc.org/~curious/rock_band/diy_midi_pro_adapter2.html
  An emulator using Teensy 3.6 hardware, which is also easy to adapt for other similar micro controllers. Source code is available at https://github.com/curiousjp/mpa-firmware and https://github.com/curiousjp/cores-mpa.

* [Building your own PS3/4 midi pro adapter with a Raspberry Pi](https://www.reddit.com/r/Rockband/comments/97roqd/building_your_own_ps34_midi_pro_adapter_with_a/?utm_source=amp&utm_medium=&utm_content=post_body)
  An emulator using small Linux SOCs and the Linux GPIO and USB Gadget subsystems. Source code at https://pastebin.com/KhPfynvs and https://pastebin.com/dPeBDqt5.

* http://rolllimitless.com/
  An emulator using Arduino hardware including standard MIDI and USB Host shields. Custom 8U2 or 16U2 LUFA-based firmware for USB device emulation, and additional firmware for the main MCU, both proprietary.

* [MIDI Rocker LX](https://www.bytearts.com/midi-rocker-lx)
  An emulator using a PIC4550 MCU. Open source hardware at https://github.com/ByteArts/MIDI-Rocker-LX_Hardware. Open source firmware at https://github.com/ByteArts/MIDI-Rocker-LX
