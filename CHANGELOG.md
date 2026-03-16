# Changelog

All notable changes to this project will be documented in this file.

---

## [v2.0.0] — 2026-03-16

### 🐛 Bug Fixes

#### Web Page Crash (Critical)
- **Root cause**: Loading the web portal caused the ESP32 to hard reset. Serial backtrace showed `EXCVADDR: 0xbaad5680` (use-after-free) in `AsyncWebServer::_rewriteRequest()` at `WebServer.cpp:141`
- **Contributing factors**:
  1. Three conflicting AsyncTCP/ESPAsyncWebServer versions loaded simultaneously (local AsyncTCP 1.1.4 + PlatformIO AsyncTCP 3.3.2 + ESPAsyncWebServer's bundled AsyncTCP 3.4.10)
  2. Server-side `processor()` template callback performing 50+ `String` heap allocations per page load, fragmenting memory on the ESP32's constrained heap
- **Fix**: Replaced `processor()` template system with static HTML served from SPIFFS + a `/api/settings` JSON endpoint using `AsyncResponseStream`. Removed `processor` parameter from all `server.on()` routes. Consolidated to single library versions via PlatformIO dependency management.

#### `ui_Clock12hrCHK` Null Pointer Crash
- **Root cause**: `Save_Load_Stuff.ino` lines 34 and 88 called `lv_obj_has_state(ui_Clock12hrCHK, ...)` and `lv_obj_add/clear_state(ui_Clock12hrCHK, ...)`, but `ui_Clock12hrCHK` was never declared, defined, or created anywhere in the UI library — it was a dangling null pointer
- **Fix**: Added `extern lv_obj_t * ui_Clock12hrCHK` declaration in `ui.h`, definition in `ui.c`, and full checkbox creation with blue indicator styling in `ui_SettingSCR.c`
- **Impact**: This was likely the root cause of the "Save & Restart" crash reported by users, since `saveSettings()` called `lv_obj_has_state()` on an undefined pointer every time

---

### ✨ New Features

#### Discord Webhook Integration
- New global variables: `DISCORD_WEBHOOK`, `discordalertinterval`, `discord_alertonce`
- `sendDiscordMessage()` function: HTTPS POST to Discord webhook URL via `WiFiClientSecure` (no additional library needed)
- Alert trigger fires alongside Telegram with identical interval options (Disabled, Instant, 5/10/15/30/45/60 min)
- Web routes: `/discord_save` (persist webhook URL + interval) and `/discord_test` (send test message)
- Settings saved to NVS as `discord_wh` and `discinterv` in the `appSettings` namespace
- **Files**: `Check_Alerts.ino`, `Save_Load_Stuff.ino`, `Web_Stuff.ino`, `PillDispenser.ino`, `index.html`

#### 12-Hour Clock Support
- Toggle between 12hr/24hr format from:
  - **Device**: New checkbox on the Settings screen (`ui_Clock12hrCHK`)
  - **Web portal**: Toggle switch in System Settings section
- Main screen clock label shows full `%I:%M %p` format (e.g., "05:15 PM")
- Screensaver clock shows `%I:%M` (digits only, using custom `ui_font_Timefont` which only contains ASCII 48-58) with a **separate AM/PM label** (`ui_ClockSCRAMPM`) using `lv_font_montserrat_22` positioned beside the time
- AM/PM label is hidden automatically in 24hr mode
- Persisted via NVS `clock12hr` boolean
- **Files**: `Loading_Screen.ino`, `Save_Load_Stuff.ino`, `ui_ClockSCR.c`, `ui_SettingSCR.c`, `ui.h`, `ui.c`

#### Custom OTA Updates
- Removed `AsyncElegantOTA` library entirely (was the source of transitive dependency conflicts pulling in duplicate ESPAsyncWebServer versions)
- Replaced with `setupOTA()` function using ESP32's built-in `Update` library + existing `AsyncWebServer`
- HTML upload page at `/update` (GET) with firmware and filesystem upload forms
- Upload handler at `/update` (POST) supporting both `U_FLASH` and `U_SPIFFS` update types
- Progress reporting and automatic reboot after successful update
- **Files**: `Web_Stuff.ino`, `Loading_Screen.ino`, `PillDispenser.ino`

---

### 🎨 UI Changes

#### Web Portal Overhaul (`index.html`)
- Complete rewrite from server-side templates to client-side JavaScript (AJAX)
- `loadSettings()` fetches JSON from `/api/settings` and populates all form fields dynamically
- Modern card-based layout with shadows and rounded corners
- CSS toggle switches replacing raw checkboxes
- Status messages with ✓/✗ feedback for Telegram and Discord save/test actions
- Device info grid (IP, AP, Signal, Firmware)
- Factory reset with confirmation dialog
- Discord section with webhook URL, alert interval dropdown, save & test buttons
- OTA Update and API Docs buttons in Device Info card

#### LVGL Settings Screen
- Checkbox row spread across screen: DST (x=15), 12Hr (x=80), Enable Screensaver (x=145) at y=181
- Label renamed: "Time/Date as Screensaver" → "Enable Screensaver"
- 12Hr checkbox styled with blue indicator (`lv_color_hex(0x2196F3)`)

#### Main Screen
- Clock label repositioned: x changed from 100 → 92

#### Screensaver
- New `ui_ClockSCRAMPM` label using `lv_font_montserrat_22` for AM/PM display beside the time
- Time and date label positions adjust dynamically based on 12hr/24hr mode

---

### 📦 Dependency Changes

#### Removed (local bundled copies → PlatformIO managed)
| Library | Old Local Version | New PlatformIO Version |
|---------|------------------|----------------------|
| AsyncTCP | 1.1.4 | 3.4.10 |
| ESPAsyncWebServer | 1.2.3 (me-no-dev) | 3.10.1 (esp32async) |
| ArduinoJson | 7.0.4 | 7.4.3 |
| Adafruit NeoPixel | 1.1.2 | 1.15.4 |
| Adafruit PWM Servo Driver | 3.0.1 | 3.0.3 |
| Adafruit BusIO | 1.14.1 | 1.17.4 |
| XPT2046_Touchscreen | local copy | PlatformIO managed |
| DFRobotDFPlayerMini | local copy | 1.0.6 |
| UniversalTelegramBot | local copy | 1.3.0 |
| LVGL | 8.3.11 (local) | 8.4.0 (PlatformIO) |
| AsyncElegantOTA | 2.2.7 | **Removed** |

#### Kept Local (require custom configuration)
| Library | Reason |
|---------|--------|
| `TFT_eSPI` | Custom `User_Setup.h` with pin definitions for CYD display |
| `ui` | SquareLine Studio generated LVGL UI library |
| `lv_conf.h` | LVGL configuration at `Arduino/libraries/` root |

#### LVGL Font Changes (`lv_conf.h`)
- Enabled `LV_FONT_MONTSERRAT_20` and `LV_FONT_MONTSERRAT_22` (for screensaver AM/PM label)
- Previously enabled: 12, 14, 16

---

### 🏗️ Architecture Changes

#### PlatformIO Migration
- Full PlatformIO project structure at `Arduino/PillDispenser/`
- `platformio.ini` targeting `esp32dev` on COM14 with `min_spiffs.csv` partitions
- `lib_extra_dirs = ../libraries` for local TFT_eSPI, ui, and lv_conf.h
- Build flags: `-DLV_CONF_INCLUDE_SIMPLE -I../libraries`
- SPIFFS data served from `data/` at project root

#### Web Server Architecture
- **Before**: `server.on("/", ..., processor)` with inline `%PLACEHOLDER%` replacement causing 50+ String allocations per request
- **After**: `server.on("/", ...)` serves static `index.html` from SPIFFS; JavaScript fetches `/api/settings` JSON endpoint; form submits go to `/save` with query parameters
- Deprecated `send_P()` calls replaced with `send()` throughout `Web_Stuff.ino`

---

### 📊 Build Stats

| Metric | Before (v1.9) | After (v2.0.0) |
|--------|---------------|----------------|
| Flash | ~88% | **87.2%** (1,713,497 / 1,966,080 bytes) |
| RAM | ~36% | **36.1%** (118,240 / 327,680 bytes) |
| Bundled libraries | 11 local copies | 3 local + 9 PlatformIO-managed |
| ESPAsyncWebServer versions | 3 conflicting | 1 (3.10.1) |

---

### 📁 Key Files Modified

| File | Changes |
|------|---------|
| `PillDispenser.ino` | Version bumped to v2.0.0, added `#include <Update.h>`, Discord globals, removed ElegantOTA include |
| `Check_Alerts.ino` | Added `sendDiscordMessage()`, `discord_timer()`, `discord_resetalert()`, Discord alert trigger alongside Telegram |
| `Save_Load_Stuff.ino` | Added Discord webhook/interval save & load to NVS |
| `Web_Stuff.ino` | New `/api/settings` JSON endpoint, `/discord_save`, `/discord_test` routes, `setupOTA()` function, removed `processor` from all routes, `send_P` → `send` |
| `Loading_Screen.ino` | 12hr/24hr screensaver format, AM/PM label updates, `setupOTA()` call |
| `index.html` | Complete rewrite — AJAX-based, card layout, Discord section, toggle switches |
| `ui_SettingSCR.c` | Added `ui_Clock12hrCHK` creation, checkbox row layout, label rename |
| `ui_ClockSCR.c` | Added `ui_ClockSCRAMPM` label with montserrat_22 |
| `ui_MainSCR.c` | Clock label x position: 100 → 92 |
| `ui.h` / `ui.c` | Added declarations/definitions for `ui_Clock12hrCHK`, `ui_ClockSCRAMPM` |
| `lv_conf.h` | Enabled `LV_FONT_MONTSERRAT_20`, `LV_FONT_MONTSERRAT_22` |
| `platformio.ini` | New PlatformIO project config |

---

### Web API Reference

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
| `/IP` | GET | Device IP address |
| `/AP` | GET | Connected access point name |
| `/DB` | GET | WiFi signal strength (dBm) |
| `/dispense?tray=N` | GET | Dispense tray N |
| `/dropout?tray=N` | GET | Drop out tray N |
| `/alarm?tray=N` | GET | Trigger alarm for tray N |
| `/dismiss` | GET | Dismiss active alert |
| `/tr_name?tray=N` | GET | Get tray N name |
