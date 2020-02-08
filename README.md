# BLEPedalboard
Bluethooth BLE Pedalboard

How to build a Bluetooth Pedalboard. It is targeted to Yamaha ThrII amps, but can be adapted to work with any Midi Bluetooth devices.

The pedalboard has two modes that chan be changed by on of the buttons
Mode 0: Changes between the 5 stored pressets
Mode 1: Turns on/ff each of the 5 effects (Compressor, Nosise Gate, Modulation, Echo, Reverb)

The pedalboard needs to talk with the android App, this is an amp limitation.

Materials:
ESP32 WROOM32 Board https://es.aliexpress.com/item/32348063163.html?spm=a2g0s.9042311.0.0.7f8363c0Pb0CUG

6 SPST Footswitches https://es.aliexpress.com/item/32864722159.html?spm=a2g0s.9042311.0.0.7f8363c0Pb0CUG4

0,96 Inches OLED Display https://es.aliexpress.com/item/32896971385.html?spm=a2g0s.9042311.0.0.7f8363c0Pb0CUG
 

Connections:
Screen:
GPIO 21 (D21)- DISPLAY SDA
GPIO 22 (D22)- DISPLAU SCK
3V3 		       DIPLAY  VDD
GND			       DISPLAY GND (common grond with all buttons)

Buttons:
GPIO 13 (D13)		  Button 1
GPIO 25	(D25)	    Button 2
GPIO 26	(D26)	    Button 3
GPIO 27	(D27)	    Button 4
GPIO 32	(D32)	    Button 5
GPIO 33 (D33)     Button M

One side of each button goes to GPIO and the other one to ground, wire one common ground, the screen GND and all buttons, to ESP32 GND.

