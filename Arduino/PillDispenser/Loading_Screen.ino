static void startup_step1_timer(lv_timer_t * timer) { //Startup Step 1 [after 1000ms]
  if (loadWifiCredentials(ssidload, passwordload)) {
    lv_label_set_text(ui_LoadinginfoLBL, "Connecting Wifi...");
    lv_bar_set_value(ui_LoadingBAR, 2, LV_ANIM_ON);
    lv_timer_create(startup_step2_timer, 250, NULL);
  } else {
    lv_label_set_text(ui_LoadinginfoLBL, "Tray 1 Servo Lock...");
    lv_bar_set_value(ui_LoadingBAR, 5, LV_ANIM_ON);
    setServoPulse(0, 70);
    lv_timer_create(startup_step5_timer, 500, NULL);
  }
  lv_timer_del(timer);
}

static void startup_step2_timer(lv_timer_t * timer) { //Startup Step 2 (Connecting Wifi)
  WiFi.disconnect(true);  // Disconnect any existing connections
  WiFi.mode(WIFI_STA);    // Set Wi-Fi to station mode
  WiFi.hostname(HOSTNAME.c_str());
  WiFi.begin(ssidload, passwordload);
  int maxRetries = 10; // Set based on your patience
  while (WiFi.status() != WL_CONNECTED && maxRetries-- > 0) {
    delay(1000);
  }
  if (WiFi.status() == WL_CONNECTED) {
    lv_bar_set_value(ui_LoadingBAR, 3, LV_ANIM_ON);
    lv_obj_add_flag(ui_NoWifiIconIMG, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_WifiIconIMG, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_ClockLBL, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_WifiInfoLBL, LV_OBJ_FLAG_HIDDEN);
    internetstatus = 1;
    String message = "Connected - IP ";
    message += WiFi.localIP().toString(); // Append the IP address to the message
    lv_label_set_text(ui_LoadinginfoLBL, message.c_str());
    lv_timer_create(startup_step3_timer, 2000, NULL);
    lv_timer_del(timer);
    secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  } else {
    lv_bar_set_value(ui_LoadingBAR, 3, LV_ANIM_ON);
    lv_obj_clear_flag(ui_NoWifiIconIMG, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_WifiIconIMG, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_ClockLBL, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_WifiInfoLBL, LV_OBJ_FLAG_HIDDEN);
    internetstatus = 0;
    lv_label_set_text(ui_LoadinginfoLBL, "Connection Error...");
    lv_timer_create(startup_step3_timer, 2000, NULL);
    lv_timer_del(timer);
  }
}

static void startup_step3_timer(lv_timer_t * timer) { //Startup Step 3 (Showing IP Address)

  lv_bar_set_value(ui_LoadingBAR, 4, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Updating Time...");
  lv_timer_create(startup_step4_timer, 250, NULL);
  lv_timer_del(timer);
}

static void startup_step4_timer(lv_timer_t * timer) { //Startup Step 4 (Updating NPT Time) / (Servo Tray 1 Lock)
  if (internetstatus) setupTime(); ///Update NPT Time here
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 1 Servo Lock...");
  lv_bar_set_value(ui_LoadingBAR, 5, LV_ANIM_ON);
  setServoPulse(0, 70);
  lv_timer_create(startup_step5_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step5_timer(lv_timer_t * timer) { //Startup Step 5 (Servo Tray 2 Lock)
  detachServo(0);
  lv_bar_set_value(ui_LoadingBAR, 6, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 2 Servo Lock...");
  setServoPulse(1, 70);
  lv_timer_create(startup_step6_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step6_timer(lv_timer_t * timer) { //Startup Step 6 (Servo Tray 3 Lock)
  detachServo(1);
  lv_bar_set_value(ui_LoadingBAR, 7, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 3 Servo Lock...");
  setServoPulse(2, 70);
  lv_timer_create(startup_step7_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step7_timer(lv_timer_t * timer) { //Startup Step 7 (Servo Tray 4 Lock)
  detachServo(2);
  lv_bar_set_value(ui_LoadingBAR, 8, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 4 Servo Lock...");
  setServoPulse(3, 70);
  lv_timer_create(startup_step8_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step8_timer(lv_timer_t * timer) { //Startup Step 8 (Servo Tray 5 Lock)
  detachServo(3);
  lv_bar_set_value(ui_LoadingBAR, 9, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 5 Servo Lock...");
  setServoPulse(4, 70);
  lv_timer_create(startup_step9_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step9_timer(lv_timer_t * timer) { //Startup Step 9 (Servo Tray 6 Lock)
  detachServo(4);
  lv_bar_set_value(ui_LoadingBAR, 10, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 6 Servo Lock...");
  setServoPulse(5, 70);
  lv_timer_create(startup_step10_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step10_timer(lv_timer_t * timer) { //Startup Step 10 (Servo Tray 7 Lock)
  detachServo(5);
  lv_bar_set_value(ui_LoadingBAR, 11, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 7 Servo Lock...");
  setServoPulse(6, 70);
  lv_timer_create(startup_step11_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step11_timer(lv_timer_t * timer) { //Startup Step 11 (Servo Tray 8 Lock)
  detachServo(6);
  lv_bar_set_value(ui_LoadingBAR, 12, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 8 Servo Lock...");
  setServoPulse(7, 70);
  lv_timer_create(startup_step12_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step12_timer(lv_timer_t * timer) { //Startup Step 12 (Servo Tray 9 Lock)
  detachServo(7);
  lv_bar_set_value(ui_LoadingBAR, 13, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 9 Servo Lock...");
  setServoPulse(8, 70);
  lv_timer_create(startup_step13_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step13_timer(lv_timer_t * timer) { //Startup Step 13 (Servo Tray 10 Lock)
  detachServo(8);
  lv_bar_set_value(ui_LoadingBAR, 14, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Tray 10 Servo Lock...");
  setServoPulse(9, 70);
  lv_timer_create(startup_step14_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step14_timer(lv_timer_t * timer) { //Startup Step 14 (Wait 500ms)
  detachServo(9);
  lv_bar_set_value(ui_LoadingBAR, 15, LV_ANIM_ON);
  lv_label_set_text(ui_LoadinginfoLBL, "Done...");
  lv_timer_create(startup_step15_timer, 500, NULL);
  lv_timer_del(timer);
}

static void startup_step15_timer(lv_timer_t * timer) { //Startup Step 15 (Load Main Screen)
  detachServo(9);
  inactivity_timer = lv_timer_create(timeout_action, 120000, NULL); // Create 120 sec timer for screen inactivity
  alertsound_timer = lv_timer_create(DFPlayer_Alarm_Timer, 60000, NULL); // Create 60 sec timer for alarm sound repeat
  lv_scr_load(ui_MainSCR);

  for (int i = 1; i <= 10; i++) {
    loadTraySettings(i);
  }
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();

  if (internetstatus) {
    webroute();
    MDNS.begin(HOSTNAME);
    AsyncElegantOTA.begin(&server);
    server.begin();
    MDNS.addService("http", "tcp", 80);
    if (BOT_TOKEN != "" && CHAT_ID != "") {
      bot = new UniversalTelegramBot(BOT_TOKEN, secured_client);
    }
  }
  lv_timer_create(check_trays_timer_cb, 15000, NULL); // 15000 ms = 15 sec
  lv_timer_create(flashing_timer, 250, NULL);
  updateTrays();
  systemloaded = true;
  lv_timer_del(timer);
}

static void timeout_action(lv_timer_t* timer) {
  if (clockSS && internetstatus) {
    lv_scr_load(ui_ClockSCR);
  } else {
    lv_scr_load(ui_BlankSCR);
    digitalWrite(21, LOW);
  }

  for (int i = 1; i <= 10; i++) {
    // Clear the checked state for all trays
    trayCheckedState[i] = false;
    lv_obj_clear_state(ui_TrayIMG[i], LV_STATE_CHECKED); // Clear visual indication
  }
  lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
  lv_obj_add_state(ui_TraycfgBTN, LV_STATE_DISABLED); // Disable the button
  showLED(pixels.Color(0, 0, 0));
}

static void reset_timeout(lv_event_t* e) {
  lv_timer_reset(inactivity_timer);
}

void setupTime() {
  // Configure the NTP servers and timezone
  int dsttemp;
  if (dstEnabled) {
    dsttemp = 3600;
  } else {
    dsttemp = 0;
  }
  configTime(utcOffset * 3600, dsttemp, "pool.ntp.org", "time.nist.gov");

  // Wait until time is synchronized
  Serial.println("Synchronizing time");
  struct tm timeinfo;
  unsigned long startTime = millis();  // Record the start time

  while (!getLocalTime(&timeinfo)) {
    if (millis() - startTime > 30000) {  // Timeout after 30000 milliseconds (30 seconds)
      Serial.println("Time synchronization timed out.");
      break;
    }
    Serial.print(".");
    delay(1000);
  }

  if (getLocalTime(&timeinfo)) {
    Serial.println("Time synchronized");
  } else {
    Serial.println("Failed to synchronize time. Restarting device.");
    ESP.restart();
  }

  // You can now use time functions like localtime_r to get current time
  char strftime_buf[64];
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  Serial.print("Current time: ");
  Serial.println(strftime_buf);
  update_time_label(NULL);
  lv_timer_create(update_time_label, 15000, NULL); // Update every 15 Sec
}

static void update_time_label(lv_timer_t * timer) {
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    char timeString[6]; // Enough space for "HH:MM\0"
    strftime(timeString, sizeof(timeString), "%H:%M", &timeinfo);
    lv_label_set_text(ui_ClockLBL, timeString);
    lv_label_set_text(ui_ClockSCRLBL, timeString);

    char formattedDate[11];
    strftime(formattedDate, sizeof(formattedDate), "%Y-%m-%d", &timeinfo);
    lv_label_set_text(ui_DateSCRLBL, formattedDate);
  }
}
