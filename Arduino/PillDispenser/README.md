# PillDispenser - PlatformIO Edition

A PlatformIO port of the **Automatic Pill Dispenser** project originally created by [Shaztech](https://github.com/Shaztech).

**Original project:** [https://github.com/Shaztech/Pilldispenser](https://github.com/Shaztech/Pilldispenser)

## About

An ESP32-based automatic pill dispenser featuring:

- **LVGL touchscreen UI** designed with SquareLine Studio on an ILI9341 TFT + XPT2046 touch controller
- **Web configuration portal** for managing tray schedules, system settings, and Telegram alerts
- **Telegram bot integration** for remote pill-taking notifications
- **Servo-driven dispensing** via PCA9685 PWM driver
- **NeoPixel LED indicators** for tray status
- **DFPlayer Mini audio alerts**
- **OTA firmware updates** via AsyncElegantOTA
- **NVS persistent storage** for all settings

## Prerequisites

- [PlatformIO](https://platformio.org/) (CLI or IDE extension)
- ESP32 Dev Module
- The Arduino libraries from the original project placed at a known path (see `lib_extra_dirs` in `platformio.ini`)

## Setup

1. Clone this repository
2. Update `platformio.ini` paths to match your local library locations:
   - `lib_extra_dirs` — path to the Arduino libraries folder from the [original project](https://github.com/Shaztech/Pilldispenser)
   - `upload_port` — your ESP32's COM port
3. Build and upload:
   ```bash
   pio run -t upload
   ```
4. Upload the SPIFFS filesystem (web portal HTML files):
   ```bash
   pio run -t uploadfs
   ```

## Project Structure

```
src/
  PillDispenser.ino    - Main entry point, setup() and loop()
  Check_Alerts.ino     - Alert monitoring and Telegram notifications
  Dispense_Rooutine.ino - Servo dispensing logic
  Loading_Screen.ino   - Boot/loading screen and WiFi connection
  Lock_Screen.ino      - Passcode lock screen
  LVGL_Buttons.ino     - LVGL UI button handlers
  Save_Load_Stuff.ino  - NVS preferences save/load
  Servo_Stuff.ino      - PCA9685 servo control
  Sound_Stuff.ino      - DFPlayer audio control
  TS_TFT_Stuff.ino     - Touchscreen and TFT display setup
  Trays_Stuff.ino      - Tray management logic
  Web_Stuff.ino        - AsyncWebServer routes and handlers
  Wifi_Screen.ino      - WiFi configuration screen
data/
  index.html           - Main configuration portal
  saved.html           - Settings saved confirmation page
  reset.html           - Factory reset confirmation page
  webcmd.html          - Home integration API reference
```

## Credits

- **Original Author:** [Shaztech](https://github.com/Shaztech) — [Shaztech.Info](https://shaztech.info)
- **Original Repository:** [https://github.com/Shaztech/Pilldispenser](https://github.com/Shaztech/Pilldispenser)
- **UI Design Tool:** [SquareLine Studio](https://squareline.io/)

## License

Please refer to the [original repository](https://github.com/Shaztech/Pilldispenser) for licensing information.
