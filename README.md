# Automatic Pill Dispenser

Complete open source project with cheap and easily available parts (listing below).
All 3d printable parts are in STL format (go to makerworld for the 3D Models), Gerber PCB are packed in zip for easy drag-drop in 
your prefered provider (JCLPCB, PCBWay, etc).
Software are available in pre-compiled (bin files) for the ESP32, or all Arduino files are there so you can 
edit them. I've included all the library I used. The full LCD interface is in Squareline Studio.
Just follow the guides in order to assemble it once you have all the parts.

Please check the user manual for the usage of the device.

![Alt text](/Pictures/FinalView.jpg?raw=true "Title")

## Features:
- USB Powered (5V, 500mah)
- Wifi configuration directly on the screen
- NPT automaticaly updated time (Need Wifi for the time to work)
- UTC/DST configurable on the screen
- Time/Date screensaver (can be disabled)
- Full interface on the touch screen
- Multiples users can be defined by colors
- Audio/Visual Alarms for each tray/users (audio alarms are repeated every minute till dispensed)
- Alarms are mp3 files on the SD card (so can be changed by the user)
- Can stack up to 10 trays
- 30 sections (can accomodate multiple/large pills) for each tray
- Manual dispense of each tray
- Visual indication of remaining pills (P-Touch label 30 to E)
- Web interface for easy configuration with browser
- Telegram integration

![Alt text](/Pictures/Screens.png?raw=true "Title")
![Alt text](/Pictures/TraywithPills.jpg?raw=true "Title")
![Alt text](/Pictures/WebPortal.png?raw=true "Title")

## Part listing:
(A## = Printed parts, B# = PCB, B#.# = PCB Parts, P# = Parts purchased, S# = Screws)

### Printed parts [(complete profile in makerworld)](https://makerworld.com/en/models/389626):

- A1 - Base Bottom [1x] (Printed with supports for the top of the lcd, the usb port and the base of the dispenser opening, 15% infill)
    - There's 2 base version, one with a chute and a door, the other one is with a removable cup
- A1.1 - Base Washer Holder [3x optional] (no supports, 15% infill)
- A1.2 - Cup (for the base A1b ONLY) [1x]
- A2 - LCD Holder [1x] (buildplate supports, 50% infill)
- A3 - DFPlayer Shim [1x]
- A4 - Base Top [1x].stl
- A5 - Lock Clip [1x Base + 1x per Tray]
- A6 - Base Dispense Door (for the A1 base only) [1x]
- A7 - Tray Base [1x per Tray]
- A8 - Finger [1x per Tray]
- A9 - Arm Cap [1x per Tray]
- A10 - Arm Lock [1x per Tray]
- A11 - Arm [1x per Tray]
- A12 - SG90 Cam [1x per Tray]
- A13 - CW Rotation Lock [1x per Tray]
- A14 - Tray Top [1x per Tray]
- A15 - Rotating Tray [1x per Tray]
- A16 - Tray Lock [1x per Tray]
- A17 - Top Dust Cap [1x]

### PCB parts:
- B1 - Base PCB [1x]
  - B1.1 - PCA9685 IC (TSSOP28) [1x]
  - B1.2 - SMD Capacitor 1000uf/10V (Ø10mm) [1x]
  - B1.3 - SMD Capacitor 10uf/6.3V (1206) [1x]
  - B1.4 - SMD Resistors 10Kohm (1206) [2x]
  - B1.5 - SMD Resistors 220ohm (1206) [10x]
  - B1.6 - PCB Header 12 pins Female [1x]
- B2 - LED WS2812B PCB [1x]
  - B2.1 - WS2812B 5050 LED [1x]
  - B2.2 - SMD Capacitor 0.1uf/6.3V (1206) [1x]
  - B2.3 - 74AHCT125N (SOIC14) [1x]
- B3 - Tray PCB [1x per tray]
  - There's now 2 version of the board (Straight and shifting). The shifting version (original),
  is for trays that always will be in stacking order (trays 1 at the bottom and 10 at the top).
  The straight version, is to designate a certain tray to be #1 or 2... and can be placed anywhere in the stack.
  ONLY USE ONE MODEL OF THE PCB - DO NOT MIX.
  - B3.1 - PCB Header 12 pins Male [1x per tray]
  - B3.2 - PCB Header 12 pins Female [1x per tray]
 
### Parts purchased:
- P1 - ESP-32 (ESP32-2432S028) WROOM Development Board with LCD 320x240, resistive touch, 2.8 inch (Called CYD "Cheap Yellow Display")  [1x]
- P2 - Ø30mm 2W Speaker (or anything that fit in the case) [1x]
- P3 - USB-C Female connector PCB (I used the 4 pins blue ones but any model that fit in the hole) [1x]
- P4 - DFPlayer Mini board [1x]
- P5 - MicroSD Card (smallest/cheapest you can find, only needed for 2 tiny MP3) [1x]
- P6 - Ø5mm x 1.5mm Neodinum magnet [1x]
- P7 - Ø12mm rubber or foam pads [5x]
- P8 - SG90 Servo 180° PWM Analog (Blue type is fine) [1x per tray]
- P9 - Ball pen springs (0.4x4.5x18mm) [3x per tray]
- P10 - Ø1.5mm x 14mm rod (I used Aluminium TIG rod, you can use anything that fit) [1x per tray]
- P11 - Ø1.5mm x 12mm rod (I used Aluminium TIG rod, you can use anything that fit) [1x per tray]
- P12 - Torsion Spring - McMaster #9271K71 [1x per tray]
- P-Touch Label 12mm
- S1 - Torx Screws #2 x 3/8" - McMaster #99512A159 [8x Base, 10x per tray]
- S2 - Torx Screws #4 x 1/2" - McMaster #99512A219 [8x Base, 6x per tray]

## Assembly/Notes:

![Alt text](/Pictures/BaseAssembly.jpg?raw=true "Title")

### Note #1:
Fill the hole with hot glue after you carefully placed and aligned the usb connector.
You can hold it in place with a USB-C cable plugged in the other end.

### Note #2:
You can add 24 flat washers Ø5/8" and print the A1.1 washers holders, to add weight to the base.

![Alt text](/Pictures/ServoAdjustment.jpg?raw=true "Title")

### Note #3:
Before you install the A12 Cam to the servo, connect the PCB with the servo into the base. And power the base. 
The servo will self align to the resting position and install the cam like in the picture.

![Alt text](/Pictures/TrayMechanism.jpg?raw=true "Title")

### Note #4:
There's a notch and a line printed in the rotating tray (A15), so you can align 
the P-Touch label from the start of the label all around the ring (starting with E, ending with 30).

### Note #5:
When you insert the ring be sure that the hole in the bottom of 
the tray is fully align with a container in the ring. (Not half of 2 containers)

### Note #6:
The top dust cap have a hole to insert the stylus that usually come with the LCD module when you buy it.

## Firmware flashing:
### The first Firmware Installation:
- Download the 5 bin files in this release
- Download the esptool.exe from here https://github.com/espressif/esptool/releases/tag/v4.7.0
- Copy the 5 bin files to the root of the folder (with esptool.exe)
- Connect your device (the ESP32 module with the LCD) to your computer via USB
- Find the Serial COM port number (in device manager)
- open a command line inside your folder and type, change the COM port that match your device (don't forget to change the files version ex: v1.3):

esptool.exe --chip esp32 --port COM4 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 PillDispenser.bootloader.v1_3.bin 0x8000 PillDispenser.partitions.v1_3.bin 0xe000 boot_app0.bin 0x10000 PillDispenser.esp32.v1_3.bin 0x3D0000 PillDispenser.spiffs.v1_3.bin

### In the future if there's an update:
Use the OTA update page in the web portal of the device, only 2 bin files are needed (esp32 and spiff)

## Buying parts kit (and assembled electronic):
[jsondag](https://github.com/jsondag) is selling kits, you can email him at: 09-snakes.timbres@icloud.com for more informations.

Here is his list of price as of 2025-01-04
<p style="margin: 0.0px 0.0px 0.0px 0.0px; font: 12.0px Helvetica; min-height: 13.8px"><span style="font-family: 'Helvetica'; font-weight: normal; font-style: normal; font-size: 12.00px"></span><br></p>

Description | Quantity | Unit Price | Cost
-- | -- | -- | --
Main PCB, with components, smd assembly, loose pin header | 1 | $16.00 | $16.00
USB socket | 1 | $2.00 | $2.00
LED PCB, with components, smd assembly, loose pin header | 1 | $10.00 | $10.00
Tray PCB, with loose pin headers, straight through. | 10 | $1.00 | $10.00
ESP32 2.8” CYD display dev board. | 1 | $14.00 | $14.00
30mm 2W 8ohm Speaker | 1 | $2.00 | $2.00
DFPlayer mini | 1 | $3.00 | $3.00
Servo  SG90 (buy 1 per tray) | 10 | $2.50 | $25.00
P-Touch Number labels, White on Clear (buy 1 per tray) | 10 | $1.00 | $10.00
3mm OD left hand torsion spring (buy 1 per tray) | 10 | $1.50 | $15.00
Ballpoint pen springs x3 (buy 1 per tray) | 10 | $0.50 | $5.00
Tray Screws #2x5/16” (X10) #4x1/2” (x6). (buy 1 per tray) | 10 | $1.50 | $15.00
Base Screws #2x5/16” (X8) #4x1/2” (x8) | 1 | $1.50 | $1.50
Tig Rod (hinges) | 1 | $1.00 | $1.00
128MB micro SD card | 1 | $3.00 | $3.00
  |   |   |  
  |   |   |  
  |   |   |  
  |   | Subtotal | $132.50
  |   | US Shipping | $8.00
  |   | Total | $140.50
<p style="margin: 0.0px 0.0px 0.0px 0.0px; font: 12.0px Helvetica; min-height: 13.8px"><span style="font-family: 'Helvetica'; font-weight: normal; font-style: normal; font-size: 12.00px"></span><br></p>
<br class="Apple-interchange-newline">

## [Buy me a coffee](https://www.buymeacoffee.com/shaztech_info).





