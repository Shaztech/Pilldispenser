
// Start -------Connect to wifi from wifi config screen-------
static void keyboard_wifi_event_handler(lv_event_t * e) { // Keyboard keys (Cancel/Accept)
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_READY) {
    lv_label_set_text(ui_WifiScanPANLBL, "Connecting to Wi-Fi...");
    lv_obj_clear_flag(ui_WifiScanPAN, LV_OBJ_FLAG_HIDDEN);
    lv_timer_t* timer = lv_timer_create(connect_wifi_event_cb, 500, NULL);
  }
  if (code ==  LV_EVENT_CANCEL ) {
    lv_scr_load(ui_SettingSCR);
  }
}
static void connect_wifi_event_cb(lv_timer_t * timer) { //Timer for connecting wifi
  connectToWifi();
  lv_timer_del(timer);
}
void connectToWifi() { //called by timer
  uint16_t selectedIdx = lv_dropdown_get_selected(ui_SSIDDropDown);   // Retrieve SSID from the dropdown
  char ssid[32]; // Adjust the size based on your SSID length limits
  lv_dropdown_get_selected_str(ui_SSIDDropDown, ssid, sizeof(ssid));

  const char* password = lv_textarea_get_text(ui_PassTxtBox);  // Retrieve password from the text box

  // Start Wi-Fi connection logic
  WiFi.disconnect(true);  // Disconnect any existing connections
  WiFi.mode(WIFI_STA);    // Set Wi-Fi to station mode
  WiFi.begin(ssid, password);

  int maxRetries = 10; // Set based on your patience
  while (WiFi.status() != WL_CONNECTED && maxRetries-- > 0) {
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    String message = "Connected successfully!\n\nIP Address: ";
    message += WiFi.localIP().toString(); // Append the IP address to the message
    lv_obj_add_flag(ui_NoWifiIconIMG, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_WifiIconIMG, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_ClockLBL, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_WifiInfoLBL, LV_OBJ_FLAG_HIDDEN);
    internetstatus = 1;
    lv_label_set_text(ui_WifiScanPANLBL, message.c_str());
    lv_label_set_text(ui_SkipWifiBTNLBL, "Next");
    saveWifiCredentials(ssid, password);
  } else {
    lv_obj_clear_flag(ui_NoWifiIconIMG, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_WifiIconIMG, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_ClockLBL, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_WifiInfoLBL, LV_OBJ_FLAG_HIDDEN);
    internetstatus = 0;
    lv_label_set_text(ui_WifiScanPANLBL, "Failed to connect.\nClick scan to try again.");
  }
}
// End -------Connect to wifi from wifi config screen-------


// Start -------Scan Wifi Routine and populate dropdown-------
static void scan_wifi_event_handler(lv_event_t * e) { //Wifi screen - Scan button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    lv_label_set_text(ui_WifiScanPANLBL, "Please wait...\n\nScanning wifi networks\nin progress");
    lv_obj_clear_flag(ui_WifiScanPAN, LV_OBJ_FLAG_HIDDEN);
    lv_timer_t* timer = lv_timer_create(scan_wifi_event_cb, 500, NULL);
  }
}
static void scan_wifi_event_cb(lv_timer_t * timer) {
  populateSSIDDropdown();
  lv_timer_del(timer);
}

void populateSSIDDropdown() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  int16_t networkCount = WiFi.scanNetworks();

  for (int i = 0; i < networkCount; ++i) {
    lv_dropdown_add_option(ui_SSIDDropDown, WiFi.SSID(i).c_str(), LV_DROPDOWN_POS_LAST);
  }
  lv_obj_clear_state(ui_Keyboard, LV_STATE_DISABLED);
  lv_obj_clear_state(ui_PassTxtBox, LV_STATE_DISABLED);
  lv_obj_add_flag(ui_WifiScanPAN, LV_OBJ_FLAG_HIDDEN);
}
// End -------Scan Wifi Routine and populate dropdown-------
