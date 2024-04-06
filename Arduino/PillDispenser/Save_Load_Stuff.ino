bool loadWifiCredentials(String &ssid, String &password) { //Load Wifi from Preferences
  preferences.begin("wifi", true); // true for read-only access.
  if (!preferences.isKey("ssid") || !preferences.isKey("password")) {
    preferences.end();
    return false; // Credentials not found
  }
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");
  preferences.end();
  return true; // Credentials loaded successfully
}

void saveWifiCredentials(const char* ssid, const char* password) { //Save Wifi to Preferences
  preferences.begin("wifi", false); // "wifi" is the namespace. false for read/write access.
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();
}

void saveSettings() {
  preferences.begin("appSettings", false); // Open Preferences with namespace "appSettings". False for read and write.

  // Save dropdown value (int)
  installedTrays = lv_dropdown_get_selected(ui_HowManyTrayDROP) + 1; // Assuming dropdown index starts at 0
  preferences.putInt("installedTrays", installedTrays);

  // Save checkbox values (bool)
  muteSound = lv_obj_has_state(ui_MuteCHK, LV_STATE_CHECKED);
  preferences.putBool("muteSound", muteSound);

  clockSS = lv_obj_has_state(ui_ScreensaverCHK1, LV_STATE_CHECKED);
  preferences.putBool("clockSS", clockSS);

  dstEnabled = lv_obj_has_state(ui_DSTCHK, LV_STATE_CHECKED);
  preferences.putBool("dstEnabled", dstEnabled);

  // Save slider value (int)
  utcOffset = lv_slider_get_value(ui_UTCSlider);
  preferences.putInt("utcOffset", utcOffset);

  // Save volume slider value (int)
  spkvolume = lv_slider_get_value(ui_VolSlider);
  preferences.putInt("spkvolume", spkvolume);

  // Save reset hour
  preferences.putInt("resethours", lv_dropdown_get_selected(ui_DayHourDROP));
  resetHours = lv_dropdown_get_selected(ui_DayHourDROP);

  // Save reset minutes
  preferences.putInt("resetmins", lv_dropdown_get_selected(ui_DayMinutesDROP) * 5); // Assuming dropdown indices correspond to 5-min intervals
  resetMin = lv_dropdown_get_selected(ui_DayMinutesDROP) * 5;

  // Save telegram timer interval
  preferences.putInt("telinterv", telegramalertinterval);

  // Save telegram infos
  preferences.putString("bot_token", BOT_TOKEN);
  preferences.putString("chat_id", CHAT_ID);

  preferences.end(); // Close the Preferences
}

void loadSettings() {
  preferences.begin("appSettings", true); // Open Preferences with namespace "appSettings". True for read-only.

  // Load dropdown value (int)
  installedTrays = preferences.getInt("installedTrays", 1); // Default to 1 if not set
  lv_dropdown_set_selected(ui_HowManyTrayDROP, installedTrays - 1); // Adjust index to start at 0

  // Load checkbox values (bool)
  muteSound = preferences.getBool("muteSound", false); // Default to false if not set
  lv_obj_add_state(ui_MuteCHK, muteSound ? LV_STATE_CHECKED : 0);

  clockSS = preferences.getBool("clockSS", false);
  lv_obj_add_state(ui_ScreensaverCHK1, clockSS ? LV_STATE_CHECKED : 0);

  dstEnabled = preferences.getBool("dstEnabled", false);
  lv_obj_add_state(ui_DSTCHK, dstEnabled ? LV_STATE_CHECKED : 0);

  // Load slider value (int)
  utcOffset = preferences.getInt("utcOffset", 0); // Default to 0 if not set
  lv_slider_set_value(ui_UTCSlider, utcOffset, LV_ANIM_OFF);
  String message = "UTC Offset: ";
  message += utcOffset;
  lv_label_set_text(ui_UTCLBL, message.c_str());

  // Load volume slider value (int)
  spkvolume = preferences.getInt("spkvolume", 10); // Default to 1 if not set
  lv_slider_set_value(ui_VolSlider, spkvolume, LV_ANIM_OFF);

  // Load reset hour
  int hourIndex = preferences.getInt("resethours", 0); // Provide default value
  lv_dropdown_set_selected(ui_DayHourDROP, hourIndex);
  resetHours = hourIndex;

  // Load reset minutes
  int minIndex = preferences.getInt("resetmins", 0) / 5; // Assuming dropdown indices correspond to 5-min intervals
  lv_dropdown_set_selected(ui_DayMinutesDROP, minIndex);
  resetMin = minIndex * 5;

  // load telegram timer interval
  telegramalertinterval = preferences.getInt("telinterv", 0);

  // load telegram infos
  BOT_TOKEN = preferences.getString("bot_token", "");
  CHAT_ID = preferences.getString("chat_id", "");

  preferences.end(); // Close the Preferences
}

void clearWifiPreferences() {
  preferences.begin("wifi", false); // Open the Preferences with the "wifi" namespace in read/write mode
  preferences.clear(); // Clear all data within the "wifi" namespace
  preferences.end(); // Close the Preferences
}

void clearTrayPreferences(int trayIndex) {

  preferences.begin("traySettings", false); // Open the Preferences with the "wifi" namespace in read/write mode
  char key[20]; // Buffer for key names

  snprintf(key, sizeof(key), "trayName%d", trayIndex);
  preferences.remove(key);

  snprintf(key, sizeof(key), "trayHour%d", trayIndex);
  preferences.remove(key);

  snprintf(key, sizeof(key), "trayMin%d", trayIndex);
  preferences.remove(key);

  snprintf(key, sizeof(key), "trayAlertEna%d", trayIndex);
  preferences.remove(key);

  snprintf(key, sizeof(key), "trayColor%d", trayIndex);
  preferences.remove(key);

  snprintf(key, sizeof(key), "trayColor%d", trayIndex);
  preferences.remove(key);

  snprintf(key, sizeof(key), "trayColor%d", trayIndex);
  preferences.remove(key);

  snprintf(key, sizeof(key), "traydisptoday%d", trayIndex);
  preferences.remove(key);

  snprintf(key, sizeof(key), "traydismtoday%d", trayIndex);
  preferences.remove(key);

  preferences.end(); // Close the Preferences
}


void saveTraySettings(int trayIndex) {
  if (trayIndex < 1 || trayIndex > 10) return; // Validate tray index
  char key[20]; // Key string to use for preferences

  preferences.begin("traySettings", false); // Open Preferences with namespace "traySettings". False for read and write.

  // Save tray name
  snprintf(key, sizeof(key), "trayName%d", trayIndex);
  preferences.putString(key, lv_textarea_get_text(ui_TraydescTXT));
  trayNames[trayIndex] = lv_textarea_get_text(ui_TraydescTXT);

  // Save tray hour
  snprintf(key, sizeof(key), "trayHour%d", trayIndex);
  preferences.putInt(key, lv_dropdown_get_selected(ui_TrayHourDROP));
  trayHours[trayIndex] = lv_dropdown_get_selected(ui_TrayHourDROP);

  // Save tray minutes
  snprintf(key, sizeof(key), "trayMin%d", trayIndex);
  preferences.putInt(key, lv_dropdown_get_selected(ui_TrayMinutesDROP) * 5); // Assuming dropdown indices correspond to 5-min intervals
  trayMin[trayIndex] = lv_dropdown_get_selected(ui_TrayMinutesDROP) * 5;

  // Save tray alert enabled status
  snprintf(key, sizeof(key), "trayAlertEna%d", trayIndex);
  preferences.putBool(key, lv_obj_has_state(ui_TrayAlertCHK, LV_STATE_CHECKED) ? true : false);
  trayAlertEna[trayIndex] = lv_obj_has_state(ui_TrayAlertCHK, LV_STATE_CHECKED);

  // Save color value (int)
  snprintf(key, sizeof(key), "trayColor%d", trayIndex);
  uint16_t selectedOption = lv_roller_get_selected(ui_ColorRoller);
  installedTrays = lv_dropdown_get_selected(ui_HowManyTrayDROP) + 1; // Assuming dropdown index starts at 0
  preferences.putInt(key, selectedOption);
  trayColor[trayIndex] = selectedOption;

  preferences.end(); // Close the Preferences
}


void loadTraySettings(int trayIndex) {
  if (trayIndex < 1 || trayIndex > 10) return; // Validate tray index

  // Assuming Preferences is already begun and ready to use
  char key[20]; // Key string to use for preferences

  preferences.begin("traySettings", true); // Open Preferences with namespace "appSettings". True for read-only.

  // Load tray name
  snprintf(key, sizeof(key), "trayName%d", trayIndex);
  String trayName = preferences.getString(key, ""); // Provide default value
  lv_textarea_set_text(ui_TraydescTXT, trayName.c_str());
  trayNames[trayIndex] = trayName;

  // Load tray hour
  snprintf(key, sizeof(key), "trayHour%d", trayIndex);
  int hourIndex = preferences.getInt(key, 0); // Provide default value
  lv_dropdown_set_selected(ui_TrayHourDROP, hourIndex);
  trayHours[trayIndex] = hourIndex;

  // Load tray minutes
  snprintf(key, sizeof(key), "trayMin%d", trayIndex);
  int minIndex = preferences.getInt(key, 0) / 5; // Assuming dropdown indices correspond to 5-min intervals
  lv_dropdown_set_selected(ui_TrayMinutesDROP, minIndex);
  trayMin[trayIndex] = minIndex * 5;

  // Load tray alert enabled status
  snprintf(key, sizeof(key), "trayAlertEna%d", trayIndex);
  bool alertEnabled = preferences.getBool(key, false); // Provide default value
  if (alertEnabled) {
    lv_obj_add_state(ui_TrayAlertCHK, LV_STATE_CHECKED);
    trayAlertEna[trayIndex] = true;
  } else {
    lv_obj_clear_state(ui_TrayAlertCHK, LV_STATE_CHECKED);
    trayAlertEna[trayIndex] = false;
  }

  // Load tray dispensed/dismissed for the day status
  snprintf(key, sizeof(key), "traydisptoday%d", trayIndex);
  traydisptoday[trayIndex] = preferences.getBool(key, false); // Provide default value
  snprintf(key, sizeof(key), "traydismtoday%d", trayIndex);
  traydismtoday[trayIndex] = preferences.getBool(key, false); // Provide default value

  // Load color value (int)
  snprintf(key, sizeof(key), "trayColor%d", trayIndex);
  int colorIndex = preferences.getInt(key, 0); // Provide default value
  lv_roller_set_selected(ui_ColorRoller, colorIndex, LV_ANIM_OFF);
  trayColor[trayIndex] = colorIndex;
  lv_obj_set_style_bg_color(ui_ColorPanel, index_to_color(colorIndex), LV_PART_MAIN);

  preferences.end(); // Close the Preferences
}
