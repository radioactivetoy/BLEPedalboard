# BLEPedalboard
Bluethooth BLE Pedalboard

This pedalboard is targeted to work Yamaha ThrII series amps, but can be adapted to work with any Midi Bluetooth device.

The pedalboard has two modes that are be switched pushing the M footswitch.
Mode 0: Changes between the 5 stored pressets
Mode 1: Turns on/ff each of the 5 effects (Compressor, Nosise Gate, Modulation, Echo, Reverb)

The pedalboard needs to talk with the Yamaha THR android App, this is an amp limitation.

* Materials:
  * ESP32 WROOM32 Board https://es.aliexpress.com/item/32348063163.html?spm=a2g0s.9042311.0.0.7f8363c0Pb0CUG
  * 6 SPST Footswitches https://es.aliexpress.com/item/32864722159.html?spm=a2g0s.9042311.0.0.7f8363c0Pb0CUG4
  * 0,96 Inches OLED Display https://es.aliexpress.com/item/32896971385.html?spm=a2g0s.9042311.0.0.7f8363c0Pb0CUG
  * Wires (I used dupond wires)
  * 3D printer for the housing

* Connections:
  * Screen:
    * GPIO 21 (D21)- DISPLAY SDA
    * GPIO 22 (D22)- DISPLAU SCK
    * 3V3 		       DIPLAY  VDD
    * GND			       DISPLAY GND (common grond with all buttons)

  * Buttons:
    * GPIO 13 (D13)		   Button 1
    * GPIO 25	(D25)	    Button 2
    * GPIO 26	(D26)	    Button 3
    * GPIO 27	(D27)	    Button 4
    * GPIO 32	(D32)	    Button 5
    * GPIO 33 (D33)     Button M
    * One side of each button goes to GPIOs and the other one to ground. Wire one common ground, the screen GND and all buttons, to ESP32 GND.

Load the program on arduino IDE. You need to add the needed libraries (adafruit screen libraries and ESP32 https://github.com/espressif/arduino-esp32)

Compile and upload the program, you need keep the Boot button pushed on the ESP32 until it begins uploading.

Once it is uploaded it will wait to the bluetooth connection to be opened, once it is connected, connect the app to the Amp too and you are good to rock. You can power it with a small powerbank.

Pnce you have all tested, use a 3Dprinter to print the housing ( Side has to be printed 2 times).

WIRING:
![Wiring](images/wiring.jpg)
Preset Mode:
![Pedalboard Presset Mode](images/image1.jpg)
Effect Mode:
![Peadlboard Effect Mode](images/image2.jpg)
