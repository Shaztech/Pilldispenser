static void SettingBackBTN_event_handler(lv_event_t * e) { // Setting Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    saveSettings();
    lv_timer_t* timer = lv_timer_create(reboot_timer, 1000, NULL);
  }
}

static void reboot_timer(lv_timer_t * timer) { //Reboot [after 1000ms]
  ESP.restart();
  lv_timer_del(timer);
}

static void WifiClearBTN_event_handler(lv_event_t * e) { // Setting Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    clearWifiPreferences();
  }
}

static void VolTestBTN_event_handler(lv_event_t * e) { // Test Volume Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    spkvolume = lv_slider_get_value(ui_VolSlider);
    Playsound(2);
  }
}

static void DisplaceBTN_event_handler(lv_event_t * e) { // Displace Go Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    displacementinprogress = true;
    displace(selectedtray, lv_dropdown_get_selected(ui_DisplaceTrayDROP) + 1);
  }
}

static void DispenseBTN_event_handler(lv_event_t * e) { // Dispense Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    if (!alertinprogress) { // Normal dispense
      for (int i = 1; i <= 10; i++) {
        if (trayCheckedState[i]) {
          currentpixelcolor = index_to_pixel(trayColor[i]);
          dispense(i);
          trayCheckedState[i] = false;
          lv_obj_clear_state(ui_TrayIMG[i], LV_STATE_CHECKED);
        }
        lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
        lv_obj_add_state(ui_TraycfgBTN, LV_STATE_DISABLED); // Disable the button
      }
    } else { // Alert dispense
      for (int i = 1; i <= 10; i++) {
        if (i == 10) {
          alertinprogress = false;
          lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
        }
        if (traytriggered[i]) {
          dispensebatchinprogress = true;
          currentpixelcolor = index_to_pixel(trayColor[i]);
          currentcolordispense = trayColor[i];
          dispensebatch(currentcolordispense);
          break;
        }
      }
    }

  }
}

static void UpIMGBTN_event_handler(lv_event_t * e) { // Up Arrow Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    if (!alertinprogress) {
      for (int i = 1; i <= 10; i++) {
        // Clear the checked state for all trays
        trayCheckedState[i] = false;
        lv_obj_clear_state(ui_TrayIMG[i], LV_STATE_CHECKED); // Clear visual indication
      }
      lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
      lv_obj_add_state(ui_TraycfgBTN, LV_STATE_DISABLED); // Disable the button
    }
  }
}

static void DownIMGBTN_event_handler(lv_event_t * e) { // Down Arrow Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    if (!alertinprogress) {
      for (int i = 1; i <= 10; i++) {
        // Clear the checked state for all trays
        trayCheckedState[i] = false;
        lv_obj_clear_state(ui_TrayIMG[i], LV_STATE_CHECKED); // Clear visual indication
      }
      lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
      lv_obj_add_state(ui_TraycfgBTN, LV_STATE_DISABLED); // Disable the button
    }
  }
}

static void TraycfgBTN_event_handler(lv_event_t * e) { // Tray config Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    for (int i = 1; i <= 10; i++) {
      if (trayCheckedState[i]) selectedtray = i;
    }
    loadTraySettings(selectedtray);
  }
}


static void TrayCfgClearBTN_event_handler(lv_event_t * e) { // Tray config Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    clearTrayPreferences(selectedtray);
    loadTraySettings(selectedtray);
    updateTrays();
  }
}

static void TrayCfgSaveBTN_event_handler(lv_event_t * e) { // Tray Save Button
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    saveTraySettings(selectedtray);
    updateTrays();
  }
}
