# PillDispenser - Enhanced Edition

A PlatformIO port of the **Automatic Pill Dispenser** project originally created by [Shaztech](https://github.com/Shaztech), with enhancements by [dgshue](https://github.com/dgshue).

**Original project:** [https://github.com/Shaztech/Pilldispenser](https://github.com/Shaztech/Pilldispenser)

## What's New (Enhancements Branch)

### Discord Integration
- **Discord webhook notifications** — get pill reminders in any Discord channel
- Configurable alert intervals (Instant to 60 min), same as Telegram
- Save & test webhook from the web portal

### 12-Hour Clock Support
- Toggle between 12hr and 24hr format from the settings screen or web portal
- AM/PM displayed on both the main screen and screensaver
- Screensaver uses a separate label with Montserrat 22 font (custom time font only has digits)

### Web Portal Overhaul
- **Crash fix**: Replaced server-side `processor()` template (50+ heap-fragmenting String allocations per page load) with static HTML + `/api/settings` JSON endpoint
- **Modern UI**: Card-based layout, toggle switches, status messages, info grid
- **Discord section** with webhook URL, alert interval, save & test buttons
- **No more device resets** when loading the web page

### Custom OTA Updates
- Dropped ElegantOTA dependency — replaced with built-in `Update` library
- Firmware + SPIFFS upload at `/update` with progress indicator
- Eliminates transitive dependency conflicts that caused dual-library builds

### Dependency Cleanup
- All libraries managed by PlatformIO (no more local copies except TFT_eSPI and SquareLine UI)
- ESPAsyncWebServer 3.10.1, AsyncTCP 3.4.10, ArduinoJson 7.4.3
- LVGL 8.4.0 with Montserrat 12/14/16/20/22 enabled
- Flash usage: **87.2%** | RAM: **36.1%**

### UI Layout Fixes
- Clock label repositioned on main screen
- Settings checkboxes spread out (DST, 12Hr, Screensaver)
- "Time/Date as Screensaver" renamed to "Enable Screensaver"

## Features

- **LVGL touchscreen UI** designed with SquareLine Studio on an ILI9341 TFT + XPT2046 touch
- **Web configuration portal** for tray schedules, system settings, and notifications
- **Telegram bot integration** for remote pill-taking notifications
- **Discord webhook integration** for channel notifications
- **Servo-driven dispensing** via PCA9685 PWM driver
- **NeoPixel LED indicators** for tray status
- **DFPlayer Mini audio alerts**
- **Custom OTA firmware updates** via built-in Update library
- **NVS persistent storage** for all settings
- **12hr/24hr clock** with AM/PM on screensaver

## Prerequisites

- [PlatformIO](https://platformio.org/) (CLI or IDE extension)
- ESP32 Dev Module
- ILI9341 TFT display with XPT2046 touch controller

## Setup

1. Clone this repository
2. Switch to the `enhancements` branch:
   ```bash
   git checkout enhancements
   ```
3. Update `platformio.ini`:
   - `upload_port` — your ESP32's COM port (default: `COM14`)
4. Build and upload:
   ```bash
   cd Arduino/PillDispenser
   pio run -t upload     # Firmware
   pio run -t uploadfs   # Web portal files (SPIFFS)
   ```

## Project Structure

```
Arduino/PillDispenser/
  src/
    PillDispenser.ino      - Main entry, display/touch init, setup() and loop()
    Check_Alerts.ino       - Alert monitoring, Telegram & Discord notifications
    Dispense_Rooutine.ino  - Servo dispensing logic
    Loading_Screen.ino     - Boot screen, WiFi, NTP, screensaver clock
    Lock_Screen.ino        - Passcode lock screen
    LVGL_Buttons.ino       - LVGL UI button/event handlers
    Save_Load_Stuff.ino    - NVS preferences save/load
    Servo_Stuff.ino        - PCA9685 servo control
    Sound_Stuff.ino        - DFPlayer audio control
    TS_TFT_Stuff.ino       - Display flush and touchpad read callbacks
    Trays_Stuff.ino        - Tray management logic
    Web_Stuff.ino          - AsyncWebServer routes, JSON API, OTA handler
    Wifi_Screen.ino        - WiFi configuration AP screen
  data/                    - SPIFFS web files (index.html, saved.html, etc.)

Arduino/libraries/
  TFT_eSPI/               - Local copy with custom User_Setup.h (pin config)
  ui/                      - SquareLine Studio generated LVGL UI library
  lv_conf.h               - LVGL configuration (at libraries root)
```

## Web API

The device exposes a JSON API at `/api/settings` returning all configuration as JSON. Integration settings (Telegram, Discord) have dedicated save/test endpoints:

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/api/settings` | GET | All settings as JSON |
| `/save` | GET | Save main settings (reboots device) |
| `/test` | GET | Save Telegram settings |
| `/telegram_test` | GET | Send Telegram test message |
| `/discord_save` | GET | Save Discord settings |
| `/discord_test` | GET | Send Discord test message |
| `/update` | GET/POST | OTA firmware/SPIFFS update |
| `/reset` | GET | Factory reset |

## Branch Strategy

| Branch | Purpose |
|--------|---------|
| `main` | Upstream mirror of [Shaztech/Pilldispenser](https://github.com/Shaztech/Pilldispenser) |
| `enhancements` | All modifications — Discord, 12hr clock, web fix, UI overhaul |

## Credits

- **Original Author:** [Shaztech](https://github.com/Shaztech) — [Shaztech.Info](https://shaztech.info)
- **Enhancements:** [dgshue](https://github.com/dgshue)
- **UI Design Tool:** [SquareLine Studio](https://squareline.io/)

## License

Please refer to the [original repository](https://github.com/Shaztech/Pilldispenser) for licensing information.
