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
