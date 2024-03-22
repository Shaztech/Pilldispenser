# Automated Pill Dispenser

Complete open source project with cheap and easily available parts (listing below).
All 3d printable parts are in STL format, Gerber PCB are packed in zip for easy drag-drop in 
your prefered provider (JCLPCB, PCBWay, etc).
Software are available in pre-compiled (bin files) for the ESP32, or all Arduino files are there so you can 
edit them. I've included all the library I used. The full LCD interface is in Squareline Studio.
Just follow the guides in order to assemble it once you have all the parts.

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
- Telegram integration (near future...)

![Alt text](/Pictures/Screens.png?raw=true "Title")
![Alt text](/Pictures/TraywithPills.jpg?raw=true "Title")

## Part listing:
(A## = Printed parts, B# = PCB, B#.# = PCB Parts, P# = Parts purchased )

### Printed parts (STL Files):
- A1 - Base Bottom [1x] (Printed with supports for the top of the lcd, the usb port and the base of the dispenser opening, 15% infill)
- A1.1 - Base Washer Holder [3x optional] (no supports, 15% infill)
- A2 - LCD Holder [1x] (buildplate supports, 50% infill)
- A3 - DFPlayer Shim [1x]
- A4 - Base Top [1x].stl
- A5 - Lock Clip [1x Base + 1x per Tray]
- A6 - Base Dispense Door [1x]
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
- B1 -
- B2 -
- B3 -

