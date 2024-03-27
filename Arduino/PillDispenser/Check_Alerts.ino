static void check_trays_timer_cb(lv_timer_t * timer) {
  time_t now;
  struct tm timeinfo;
  time(&now);
  localtime_r(&now, &timeinfo);

  for (int i = 1; i <= 10; i++) {
    if (trayAlertEna[i] && !alreadyTriggered[i] && trayEnabled[i] && !traydisptoday[i] && !traydismtoday[i]) {
      if (trayHours[i] == timeinfo.tm_hour && trayMin[i] == timeinfo.tm_min) {
        // Trigger the visual alert for this tray
        traytriggered[i] = true;
        alreadyTriggered[i] = true; // Mark as triggered (wait for 2 min)

        for (int i = 1; i <= 10; i++) { // Clear the checked state for all trays
          trayCheckedState[i] = false;
          lv_obj_clear_state(ui_TrayIMG[i], LV_STATE_CHECKED); // Clear visual indication
        }
        lv_timer_create(reset_triggered_timer, 120000, NULL);
        lv_timer_reset(alertsound_timer); //reset alert sound timer
        Playsound(1);

        alertinprogress = true;

        lv_obj_add_state(ui_TraycfgBTN, LV_STATE_DISABLED); // Disable the tray config button
        lv_obj_clear_state(ui_DispenseBTN, LV_STATE_DISABLED); // Enable the dispense button
        lv_obj_clear_flag(ui_DismissBTN, LV_OBJ_FLAG_HIDDEN); // Show the dismiss button
        lv_label_set_text(ui_DispenseBTNLBL, "Dispense\nFlashing\nTray(s)\n(By color)");
        placethings();
        lv_scr_load(ui_MainSCR);
      }
    }
    if (resetHours == timeinfo.tm_hour && resetMin == timeinfo.tm_min) {
      traydisptoday[i] = false;
      traydismtoday[i] = false;
      lv_obj_add_flag(ui_TrayCheckIMG[i], LV_OBJ_FLAG_HIDDEN);

      char key[20]; // Key string to use for preferences
      preferences.begin("traySettings", false); // Open Preferences with namespace "traySettings". False for read and write.

      // Save tray alert enabled status
      snprintf(key, sizeof(key), "traydisptoday%d", i);
      preferences.putBool(key, traydisptoday[i]);
      snprintf(key, sizeof(key), "traydismtoday%d", i);
      preferences.putBool(key, traydismtoday[i]);

      preferences.end(); // Close the Preferences
    }
  }
}

static void reset_triggered_timer(lv_timer_t * timer) { // Reset the alreadyTriggered flag after 120 sec
  for (int i = 1; i <= 10; i++) {
    alreadyTriggered[i] = false;
  }
  lv_timer_del(timer);
}

static void flashing_timer(lv_timer_t * timer) {
  static uint8_t ledState = 0; // Manage LED flashing state independently

  for (int i = 1; i <= 10; i++) {
    if (traytriggered[i]) {
      // Handle tray recoloring based on flashing state and tray-specific conditions
      lv_obj_set_style_img_recolor(ui_DownIMGBTN, lv_color_hex(0x3175DE), 0);
      lv_obj_set_style_img_recolor(ui_UpIMGBTN, lv_color_hex(0x3175DE), 0);

      if (flashing == 1 || flashing == 2) { // Slow flash
        if (i <= 5) lv_obj_set_style_img_recolor_opa(ui_DownIMGBTN, LV_OPA_TRANSP, 0); // Disable recoloring
        if (i >= 6) lv_obj_set_style_img_recolor_opa(ui_UpIMGBTN, LV_OPA_TRANSP, 0); // Disable recoloring
        if (!trayfastflash[i]) lv_obj_set_style_img_recolor_opa(ui_TrayIMG[i], LV_OPA_TRANSP, 0); // Disable recoloring
      } else { // Normal or fast flash state
        if (i <= 5) lv_obj_set_style_img_recolor_opa(ui_DownIMGBTN, 255, 0); // Enable recoloring
        if (i >= 6) lv_obj_set_style_img_recolor_opa(ui_UpIMGBTN, 255, 0); // Enable recoloring
        if (!trayfastflash[i]) lv_obj_set_style_img_recolor_opa(ui_TrayIMG[i], 150, 0); // Enable recoloring
      }

      if (systemloaded) {
        lv_timer_reset(inactivity_timer); // Reset screensaver timer
        digitalWrite(21, HIGH); // Assuming this is a signal to indicate activity
      }
    }
    if (flashing == 1 || flashing == 3) { //fast flash
      if (trayfastflash[i]) lv_obj_set_style_img_recolor_opa(ui_TrayIMG[i], LV_OPA_TRANSP, 0); // Disable recoloring
    } else {
      if (trayfastflash[i]) lv_obj_set_style_img_recolor_opa(ui_TrayIMG[i], 150, 0); // Enable recoloring
    }
  }

  for (int i = 1; i <= 10; i++) {
    if (!solidLED) {
      if (trayfastflash[i]) {
        if (flashing == 1 || flashing == 3) { //fast flash
          showLED(pixels.Color(0, 0, 0));
        } else {
          showLED(currentpixelcolor);
        }
        break;
      } else {
        if (traytriggered[i] && !trayfastflash[i]) {
          if (flashing == 1 || flashing == 2) { //slow flash
            if (!trayfastflash[i]) showLED(pixels.Color(0, 0, 0));
          } else {
            if (!trayfastflash[i]) showLED(currentpixelcolor);
          }
        }
      }
    } else {
      showLED(currentpixelcolor);
    }
  }

  // Update flashing state
  flashing++;
  if (flashing > 3) flashing = 0;
}

void placethings() {
  bool anytriggered = false;
  int under6triggered = 0;

  for (int i = 10; i >= 1; i--) {
    if (traytriggered[i]) {
      anytriggered = true;
      under6triggered = i;
      currentpixelcolor = index_to_pixel(trayColor[i]);
    }
  }
  checkmark();
  if (!anytriggered) {
    alertinprogress = false;
    lv_label_set_text(ui_DispenseBTNLBL, "Dispense\nSelected\nTray");
    lv_obj_add_flag(ui_DismissBTN, LV_OBJ_FLAG_HIDDEN); // Hide the dismiss button
    lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the dispense config button
    lv_obj_add_flag(ui_PAGE2CON, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_PAGE1CON, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_bg_color(ui_DispenseBTN, lv_color_hex(0x3175DE), LV_PART_MAIN);
    lv_obj_set_style_img_recolor_opa(ui_DownIMGBTN, 255, 0); // Enable recoloring
    lv_obj_set_style_img_recolor_opa(ui_UpIMGBTN, 255, 0); // Enable recoloring
  } else {
    for (int i = 1; i <= 10; i++) {
      if (traytriggered[i]) {
        lv_obj_set_style_bg_color(ui_DispenseBTN, index_to_color(trayColor[i]), LV_PART_MAIN);
        break;
      }
    }
    if (under6triggered >= 6) {
      lv_obj_add_flag(ui_PAGE1CON, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_PAGE2CON, LV_OBJ_FLAG_HIDDEN);
    }
  }
}

void showLED(uint32_t color) {
  pixels.setPixelColor(0, color);
  pixels.setPixelColor(1, color);
  pixels.setBrightness(50);
  pixels.show();
}
