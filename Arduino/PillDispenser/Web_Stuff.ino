String getDB() {
  int strength = WiFi.RSSI();
  return String(strength);
}

String getIP() {
  String ipaddress = WiFi.localIP().toString();
  return String(ipaddress);
}

String getAP() {
  return String(ssidload);
}

String getVER() {
  return String(versionnumber);
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String processor(const String& var) {
  if (var == "IP") {
    return getIP();
  }  else if (var == "AP") {
    return getAP();
  }  else if (var == "DB") {
    return getDB();
  }  else if (var == "VER") {
    return getVER();
  } else if (var == "CLOCKSCRENA") {
    String buttons = "";
    String outputStateValue;
    if (clockSS) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"clockSS\" id=\"clockSS\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "DSTENA") {
    String buttons = "";
    String outputStateValue;
    if (dstEnabled) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"dstEnabled\" id=\"dstEnabled\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "MUTEENA") {
    String buttons = "";
    String outputStateValue;
    if (muteSound) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"mutebutton\" id=\"mutebutton\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "UTCOFFSETBOX") {
    String value = String(utcOffset + 12);
    String selectHTML = "<select name=\"utcoffset\" id=\"utcoffset\">";
    String choices[] = {"-12", "-11", "-10", "-9", "-8", "-7", "-6", "-5", "-4", "-3", "-2", "-1", "0", "+1", "+2", "+3", "+4", "+5", "+6", "+7", "+8", "+9", "+10", "+11", "+12"};
    for (int i = 0; i <= 24; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (value == String(i) ? " selected" : "") + ">" + choices[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "SPKVOL") {
    String value = String(spkvolume - 1);
    String selectHTML = "<select name=\"spkvolume\" id=\"spkvolume\">";
    String choices[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"};
    for (int i = 0; i <= 29; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (value == String(i) ? " selected" : "") + ">" + choices[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "ALERTINTERVAL") {
    String value = String(alertinterval - 1);
    String selectHTML = "<select name=\"alertinterval\" id=\"alertinterval\">";
    String choices[] = {"1 min", "2 mins", "3 mins", "4 mins", "5 mins", "6 mins", "7 mins", "8 mins", "9 mins", "10 mins", "15 mins", "20 mins", "25 mins", "30 mins"};
    for (int i = 0; i <= 13; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (value == String(i) ? " selected" : "") + ">" + choices[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "TRAYINSTBOX") {
    String value = String(installedTrays - 1);
    String selectHTML = "<select name=\"trayinst\" id=\"trayinst\">";
    String choices[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    for (int i = 0; i <= 9; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (value == String(i) ? " selected" : "") + ">" + choices[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "RESETTIMEBOX") {
    int hour =  resetHours;
    int minute = resetMin;
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"resettime\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX1") {
    int hour =  trayHours[1];
    int minute = trayMin[1];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time1\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX2") {
    int hour =  trayHours[2];
    int minute = trayMin[2];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time2\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX3") {
    int hour =  trayHours[3];
    int minute = trayMin[3];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time3\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX4") {
    int hour =  trayHours[4];
    int minute = trayMin[4];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time4\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX5") {
    int hour =  trayHours[5];
    int minute = trayMin[5];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time5\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX6") {
    int hour =  trayHours[6];
    int minute = trayMin[6];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time6\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX7") {
    int hour =  trayHours[7];
    int minute = trayMin[7];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time7\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX8") {
    int hour =  trayHours[8];
    int minute = trayMin[8];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time8\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX9") {
    int hour =  trayHours[9];
    int minute = trayMin[9];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time9\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "TIMEBOX10") {
    int hour =  trayHours[10];
    int minute = trayMin[10];
    char timeInput[64];
    snprintf(timeInput, sizeof(timeInput), "<input type=\"time\" name=\"time10\" value=\"%02d:%02d\" step=\"300\">", hour, minute);
    return String(timeInput);
  } else if (var == "COLORBOX1") {
    String lastColor = String(trayColor[1]);
    String selectHTML = "<select name=\"color1\" id=\"color1\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX2") {
    String lastColor = String(trayColor[2]);
    String selectHTML = "<select name=\"color2\" id=\"color2\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX3") {
    String lastColor = String(trayColor[3]);
    String selectHTML = "<select name=\"color3\" id=\"color3\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX4") {
    String lastColor = String(trayColor[4]);
    String selectHTML = "<select name=\"color4\" id=\"color4\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX5") {
    String lastColor = String(trayColor[5]);
    String selectHTML = "<select name=\"color5\" id=\"color5\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX6") {
    String lastColor = String(trayColor[6]);
    String selectHTML = "<select name=\"color6\" id=\"color6\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX7") {
    String lastColor = String(trayColor[7]);
    String selectHTML = "<select name=\"color7\" id=\"color7\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX8") {
    String lastColor = String(trayColor[8]);
    String selectHTML = "<select name=\"color8\" id=\"color8\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX9") {
    String lastColor = String(trayColor[9]);
    String selectHTML = "<select name=\"color9\" id=\"color9\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "COLORBOX10") {
    String lastColor = String(trayColor[10]);
    String selectHTML = "<select name=\"color10\" id=\"color10\">";
    String colors[] = {"Red", "Magenta", "Violet", "Blue", "Cyan", "Green", "Yellow", "Orange"};
    for (int i = 0; i < 8; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (lastColor == String(i) ? " selected" : "") + ">" + colors[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  } else if (var == "BTNENA1") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[1]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna1\" id=\"trayAlertEna1\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA2") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[2]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna2\" id=\"trayAlertEna2\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA3") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[3]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna3\" id=\"trayAlertEna3\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA4") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[4]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna4\" id=\"trayAlertEna4\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA5") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[5]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna5\" id=\"trayAlertEna5\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA6") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[6]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna6\" id=\"trayAlertEna6\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA7") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[7]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna7\" id=\"trayAlertEna7\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA8") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[8]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna8\" id=\"trayAlertEna8\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA9") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[9]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna9\" id=\"trayAlertEna9\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "BTNENA10") {
    String buttons = "";
    String outputStateValue;
    if (trayAlertEna[10]) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"trayAlertEna10\" id=\"trayAlertEna10\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  }  else if (var == "TXTDESC1") {
    String texts = "";
    String value = String(trayNames[1]);
    texts += "<input maxlength=\"15\" name=\"trayNames1\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC2") {
    String texts = "";
    String value = String(trayNames[2]);
    texts += "<input maxlength=\"15\" name=\"trayNames2\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC3") {
    String texts = "";
    String value = String(trayNames[3]);
    texts += "<input maxlength=\"15\" name=\"trayNames3\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC4") {
    String texts = "";
    String value = String(trayNames[4]);
    texts += "<input maxlength=\"15\" name=\"trayNames4\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC5") {
    String texts = "";
    String value = String(trayNames[5]);
    texts += "<input maxlength=\"15\" name=\"trayNames5\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC6") {
    String texts = "";
    String value = String(trayNames[6]);
    texts += "<input maxlength=\"15\" name=\"trayNames6\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC7") {
    String texts = "";
    String value = String(trayNames[7]);
    texts += "<input maxlength=\"15\" name=\"trayNames7\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC8") {
    String texts = "";
    String value = String(trayNames[8]);
    texts += "<input maxlength=\"15\" name=\"trayNames8\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC9") {
    String texts = "";
    String value = String(trayNames[9]);
    texts += "<input maxlength=\"15\" name=\"trayNames9\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "TXTDESC10") {
    String texts = "";
    String value = String(trayNames[10]);
    texts += "<input maxlength=\"15\" name=\"trayNames10\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "BOTTOKENTXT") {
    String texts = "";
    String value = String(BOT_TOKEN);
    texts += "<input maxlength=\"75\" name=\"bottoken\" size=\"40\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "CHATIDTXT") {
    String texts = "";
    String value = String(CHAT_ID);
    texts += "<input maxlength=\"75\" name=\"chatID\" size=\"40\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  } else if (var == "ALERTAFTERBOX") {
    String value = String(telegramalertinterval);
    String selectHTML = "<select name=\"telegramalert\" id=\"telegramalert\">";
    String choices[] = {"Disabled", "Instant", "5 min", "10 min", "15 min", "30 min", "45 min", "60 min"};
    for (int i = 0; i <= 7; i++) {
      selectHTML += "<option value=\"" + String(i) + "\"" + (value == String(i) ? " selected" : "") + ">" + choices[i] + "</option>";
    }
    selectHTML += "</select>";
    return selectHTML;
  }  else if (var == "MDNSTXT") {
    String texts = "";
    String value = String(HOSTNAME);
    texts += "<input maxlength=\"15\" name=\"mdnstext\" size=\"15\" type=\"text\" value=\"" + value + "\"/>";
    return texts;
  }  else if (var == "PASSENA") {
    String buttons = "";
    String outputStateValue;
    if (enabledpasscode) {
      outputStateValue = "checked";
    } else {
      outputStateValue = "";
    }
    buttons += "<label class=\"switch\"><input type=\"checkbox\"  name=\"passcodeEnabled\" id=\"passcodeEnabled\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  } else if (var == "PASSTXT") {
    String texts = "";
    String value = String(passcode);
    texts += "<input maxlength=\"6\" minlength=\"4\" name=\"passcodetext\" size=\"15\" type=\"password\" value=\"" + value + "\"/>";
    return texts;
  } else {
    return String("n/a");
  }
}

// Non-blocking Home Assistant Webhook Push
static void ha_webhook_timer_cb(lv_timer_t * timer) {
  if (haWebhookUrl.length() > 0 && WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.setTimeout(2000);
    http.begin(haWebhookUrl);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> doc;
    doc["event"] = pendingWebhookEvent;
    doc["tray"] = pendingWebhookTray;
    doc["alert_in_progress"] = alertinprogress;
    if (pendingWebhookTray >= 1 && pendingWebhookTray <= 10) {
      doc["triggered"] = traytriggered[pendingWebhookTray];
      doc["dispensed_today"] = traydisptoday[pendingWebhookTray];
      doc["dismissed_today"] = traydismtoday[pendingWebhookTray];
      doc["paused"] = trayPaused[pendingWebhookTray];
    }

    String payload;
    serializeJson(doc, payload);
    http.POST(payload);
    http.end();
  }
  lv_timer_del(timer);
}

void notifyHomeAssistant(const String& eventName, int trayNum) {
  if (haWebhookUrl.length() == 0) return;
  pendingWebhookEvent = eventName;
  pendingWebhookTray = trayNum;
  lv_timer_create(ha_webhook_timer_cb, 150, NULL);
}

// GitHub Release Check & OTA Update
String checkLatestGithubRelease(String &fwAssetUrl, String &spiffsAssetUrl) {
  if (WiFi.status() != WL_CONNECTED) return "";
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;
  http.setUserAgent("PillDispenser-ESP32");
  http.setTimeout(5000);

  if (!http.begin(client, "https://api.github.com/repos/Shaztech/Pilldispenser/releases/latest")) {
    return "";
  }
  int code = http.GET();
  if (code != 200) {
    http.end();
    return "";
  }

  DynamicJsonDocument doc(4096);
  DeserializationError err = deserializeJson(doc, http.getStream());
  http.end();
  if (err) return "";

  String tagName = doc["tag_name"] | "";
  JsonArray assets = doc["assets"].as<JsonArray>();
  for (JsonObject asset : assets) {
    String name = asset["name"] | "";
    String url = asset["browser_download_url"] | "";
    String lowerName = name;
    lowerName.toLowerCase();

    if (lowerName.endsWith(".bin")) {
      if (lowerName.indexOf("bootloader") >= 0 || lowerName.indexOf("partitions") >= 0 || lowerName.indexOf("inv") >= 0) {
        continue;
      }
      if (lowerName.indexOf("spiffs") >= 0) {
        spiffsAssetUrl = url;
      } else {
        fwAssetUrl = url;
      }
    }

  }

  return tagName;
}

void performGithubOtaUpdate() {
  String fwUrl = "";
  String spiffsUrl = "";
  String latest = checkLatestGithubRelease(fwUrl, spiffsUrl);
  if (fwUrl == "") return;

  WiFiClientSecure client;
  client.setInsecure();
  httpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  if (spiffsUrl != "") {
    httpUpdate.updateSpiffs(client, spiffsUrl);
  }
  httpUpdate.update(client, fwUrl);
}


void webroute() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/webcmd.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/webcmd.html", String(), false, processor);
  });

  server.on("/dropout", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("tray")) {
      request->send(400, "text/plain", "Param 'tray' is missing.");
      return;
    }

    int tray = request->getParam("tray")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray.");
      return;
    }

    dispense(tray);
    request->send(200, "text/plain", "Done");

  });

  server.on("/dispense", HTTP_GET, [](AsyncWebServerRequest * request) {

    if (!alertinprogress) { // Normal dispense (only one tray)
      request->send(400, "text/plain", "No alarm in progress. Nothing to dispense.");
      return;
    } else { // Alert dispense (1 tray or more)
      for (int i = 1; i <= 10; i++) {
        if (i == 10) {
          alertinprogress = false;
          //lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
        }
        if (traytriggered[i]) {
          dispensebatchinprogress = true;
          currentpixelcolor = index_to_pixel(trayColor[i]);
          currentcolordispense = trayColor[i];
          dispensebatch(currentcolordispense);
          break;
        }
        lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
        lv_obj_add_state(ui_TraycfgBTN, LV_STATE_DISABLED); // Disable the button
      }
      request->send(200, "text/plain", "Done");
    }
  });

  server.on("/fix", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("tray")) {
      request->send(400, "text/plain", "Param 'tray' is missing.");
      return;
    }

    int tray = request->getParam("tray")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray.");
      return;
    }

    fixaligment = true;
    traytodispense = tray;
    lv_timer_t* timer = lv_timer_create(dispense_step1_timer, 250, NULL);

    request->send(200, "text/plain", "Done");

  });

  server.on("/alarm", HTTP_GET, [](AsyncWebServerRequest * request) {

    int alarmId = 2;
    if (request->hasParam("id")) {
      alarmId = request->getParam("id")->value().toInt();
    }

    Playsound(alarmId); // Play the alarm sound
    lv_timer_reset(alertsound_timer); // Reset alert sound timer

    request->send(200, "text/plain", "Done");
  });


  server.on("/dismiss", HTTP_GET, [](AsyncWebServerRequest * request) {
    for (int i = 1; i <= 10; i++) {
      if (i == 10) {
        alertinprogress = false;
        lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
      }
      if (traytriggered[i]) {
        dispensebatchinprogress = true;
        dismissinprogress = true;
        currentpixelcolor = index_to_pixel(trayColor[i]);
        currentcolordispense = trayColor[i];
        dispensebatch(currentcolordispense);
        break;
      }
    }
  });

  server.on("/test", HTTP_GET, [](AsyncWebServerRequest * request) {

    preferences.begin("appSettings", false); // Open Preferences with namespace "appSettings". False for read and write.
    // Handle Telegram settings
    if (request->hasParam("bottoken")) {
      String valueout = request->getParam("bottoken")->value();
      BOT_TOKEN = valueout;
      preferences.putString("bot_token", BOT_TOKEN.c_str());
    }
    if (request->hasParam("chatID")) {
      String valueout = request->getParam("chatID")->value();
      CHAT_ID = valueout;
      preferences.putString("chat_id", CHAT_ID.c_str());
    }
    if (request->hasParam("telegramalert")) {
      String valueout = request->getParam("telegramalert")->value();
      telegramalertinterval = valueout.toInt();
      preferences.putInt("telinterv", telegramalertinterval);
    }
    preferences.end(); // Close the Preferences


    if (request->hasParam("bottoken")) {
      String valueout = request->getParam("bottoken")->value();
      BOT_TOKEN = valueout;
      preferences.putString("bot_token", BOT_TOKEN.c_str());
    }
    if (request->hasParam("chatID")) {
      String valueout = request->getParam("chatID")->value();
      CHAT_ID = valueout;
      preferences.putString("chat_id", CHAT_ID.c_str());
    }
    if (BOT_TOKEN != "" && CHAT_ID != "") {
      bot = new UniversalTelegramBot(BOT_TOKEN, secured_client);
      String message = "This is a test, if you see this message your Bot Token and Chat ID are correct.";
      bot->sendMessage(CHAT_ID, message, "");
      delete bot;
      bot = nullptr;
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest * request) {

    preferences.begin("wifi", false); // Open the Preferences with the "wifi" namespace in read/write mode
    preferences.clear(); // Clear all data within the "wifi" namespace
    preferences.end(); // Close the Preferences

    preferences.begin("appSettings", false); // Open Preferences with namespace "appSettings". False for read and write.
    preferences.clear(); // Clear all data within the "appSettings" namespace
    preferences.end(); // Close the Preferences

    preferences.begin("traySettings", false); // Open the Preferences with the "wifi" namespace in read/write mode
    preferences.clear(); // Clear all data within the "traySettings" namespace
    preferences.end(); // Close the Preferences

    request->send(SPIFFS, "/reset.html", String(), false, processor);
    lv_timer_t* timer = lv_timer_create(reboot_timer, 2500, NULL);
  });

  server.on("/IP", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getIP().c_str());
  });

  server.on("/AP", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getAP().c_str());
  });

  server.on("/DB", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getDB().c_str());
  });

  server.on("/save", HTTP_GET, [](AsyncWebServerRequest * request) {

    preferences.begin("appSettings", false); // Open Preferences with namespace "appSettings". False for read and write.

    dstEnabled = false;
    clockSS = false;
    muteSound = false;
    enabledpasscode = false;

    if (request->hasParam("passcodetext")) {
      String valueout = request->getParam("passcodetext")->value();
      passcode = valueout;
      preferences.putString("passcode", passcode.c_str());
    }
    if (request->hasParam("passcodeEnabled")) enabledpasscode = true;
    preferences.putBool("enabledpasscode", enabledpasscode);

    if (request->hasParam("mdnstext")) {
      String valueout = request->getParam("mdnstext")->value();
      HOSTNAME = valueout;
      preferences.putString("mdnshostname", HOSTNAME.c_str());
    }
    if (request->hasParam("trayinst")) {
      String valueout = request->getParam("trayinst")->value();
      installedTrays = valueout.toInt() + 1;
      preferences.putInt("installedTrays", installedTrays);
    }
    if (request->hasParam("utcoffset")) {
      String valueout = request->getParam("utcoffset")->value();
      utcOffset = valueout.toInt() - 12;
      preferences.putInt("utcOffset", utcOffset);
    }
    if (request->hasParam("spkvolume")) {
      String valueout = request->getParam("spkvolume")->value();
      spkvolume = valueout.toInt() + 1;
      preferences.putInt("spkvolume", spkvolume);
    }
    if (request->hasParam("alertinterval")) {
      String valueout = request->getParam("alertinterval")->value();
      alertinterval = valueout.toInt() + 1;
      preferences.putInt("alertinterval", alertinterval);
    }
    if (request->hasParam("dstEnabled")) dstEnabled = true;
    if (request->hasParam("clockSS")) clockSS = true;
    if (request->hasParam("mutebutton")) muteSound = true;

    preferences.putBool("dstEnabled", dstEnabled);
    preferences.putBool("clockSS", clockSS);
    preferences.putBool("muteSound", muteSound);

    // Handle time settings
    if (request->hasParam("resettime")) {
      String timeValue = request->getParam("resettime")->value();
      int hour, minute;
      sscanf(timeValue.c_str(), "%d:%d", &hour, &minute);
      // Assuming trayHours and trayMin are int arrays
      resetHours = hour;
      resetMin = minute;
      preferences.putInt("resethours", resetHours);
      preferences.putInt("resetmins", resetMin);
    }


    preferences.end(); // Close the Preferences
    preferences.begin("traySettings", false); // False for read and write.

    for (int i = 1; i <= 10; i++) {
      // Handle trayNames
      if (request->hasParam(("trayNames" + String(i)).c_str())) {
        String valueout = request->getParam(("trayNames" + String(i)).c_str())->value();
        // Assuming trayNames is a String array
        trayNames[i] = valueout;
        preferences.putString(("trayName" + String(i)).c_str(), trayNames[i]);
      }

      // Initialize trayAlertEna to false and set to true if present
      trayAlertEna[i] = false;
      if (request->hasParam(("trayAlertEna" + String(i)).c_str())) {
        trayAlertEna[i] = true;
      }
      preferences.putBool(("trayAlertEna" + String(i)).c_str(), trayAlertEna[i]);

      // Handle colors
      if (request->hasParam(("color" + String(i)).c_str())) {
        String valueout = request->getParam(("color" + String(i)).c_str())->value();
        // Assuming trayColor is an int array
        trayColor[i] = valueout.toInt();
        preferences.putInt(("trayColor" + String(i)).c_str(), trayColor[i]);
      }

      // Handle time settings
      if (request->hasParam(("time" + String(i)).c_str())) {
        String timeValue = request->getParam(("time" + String(i)).c_str())->value();
        int hour, minute;
        sscanf(timeValue.c_str(), "%d:%d", &hour, &minute);
        // Assuming trayHours and trayMin are int arrays
        trayHours[i] = hour;
        trayMin[i] = minute;
        preferences.putInt(("trayHour" + String(i)).c_str(), trayHours[i]);
        preferences.putInt(("trayMin" + String(i)).c_str(), trayMin[i]);
      }
    }

    preferences.end(); // Close the Preferences


    request->send(SPIFFS, "/saved.html", String(), false, processor);
    lv_timer_t* timer = lv_timer_create(reboot_timer, 1000, NULL);
  });

  ////----------------------------------------------------------------Home Integration informations

  server.on("/tr_name", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("id")) {
      request->send(400, "text/plain", "Param 'id' is missing.");
      return;
    }

    int tray = request->getParam("id")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray or tray not installed.");
      return;
    }

    request->send(200, "text/plain", trayNames[tray].c_str());
  });

  server.on("/tr_color", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("id")) {
      request->send(400, "text/plain", "Param 'id' is missing.");
      return;
    }

    int tray = request->getParam("id")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray or tray not installed.");
      return;
    }

    request->send(200, "text/plain", String(trayColor[tray]));
  });

  server.on("/tr_inst", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("id")) {
      request->send(400, "text/plain", "Param 'id' is missing.");
      return;
    }

    int tray = request->getParam("id")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray or tray not installed.");
      return;
    }

    request->send(200, "text/plain", String(trayEnabled[tray]));
  });

  server.on("/tr_enab", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("id")) {
      request->send(400, "text/plain", "Param 'id' is missing.");
      return;
    }

    int tray = request->getParam("id")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray or tray not installed.");
      return;
    }

    request->send(200, "text/plain", String(trayAlertEna[tray]));
  });

  server.on("/tr_trig", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("id")) {
      request->send(400, "text/plain", "Param 'id' is missing.");
      return;
    }

    int tray = request->getParam("id")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray or tray not installed.");
      return;
    }

    request->send(200, "text/plain", String(traytriggered[tray]));
  });

  server.on("/tr_disp", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("id")) {
      request->send(400, "text/plain", "Param 'id' is missing.");
      return;
    }

    int tray = request->getParam("id")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray or tray not installed.");
      return;
    }

    request->send(200, "text/plain", String(traydisptoday[tray]));
  });

  server.on("/tr_dism", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("id")) {
      request->send(400, "text/plain", "Param 'id' is missing.");
      return;
    }

    int tray = request->getParam("id")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray or tray not installed.");
      return;
    }

    request->send(200, "text/plain", String(traydismtoday[tray]));
  });

  server.on("/tr_time", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("id")) {
      request->send(400, "text/plain", "Param 'id' is missing.");
      return;
    }

    int tray = request->getParam("id")->value().toInt();

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Wrong value for tray or tray not installed.");
      return;
    }

    if (!trayAlertEna[tray]) {
      request->send(400, "text/plain", "This tray is not enabled for daily alerts");
      return;
    } else {
      String timeString = String(trayHours[tray]) + ":" + String(trayMin[tray]);
      request->send(200, "text/plain", timeString);
      return;
    }
  });
  ////----------------------------------------------------------------Home Assistant Enhanced API

  // 1. Single-request JSON status endpoint (replaces 80+ individual polling requests)
  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonDocument doc(3072);

    doc["version"] = versionnumber;
    doc["hostname"] = HOSTNAME;
    doc["ip"] = getIP();
    doc["rssi"] = WiFi.RSSI();
    doc["free_heap"] = ESP.getFreeHeap();
    doc["uptime_sec"] = millis() / 1000;
    doc["installed_trays"] = installedTrays;
    doc["alert_in_progress"] = alertinprogress;
    doc["displacement_in_progress"] = displacementinprogress;
    doc["mute_sound"] = muteSound;
    doc["ha_webhook_configured"] = (haWebhookUrl.length() > 0);

    JsonArray trays = doc.createNestedArray("trays");
    for (int i = 1; i <= installedTrays; i++) {
      JsonObject t = trays.createNestedObject();
      t["id"] = i;
      t["name"] = trayNames[i];
      t["color"] = trayColor[i];
      t["installed"] = trayEnabled[i];
      t["alert_enabled"] = trayAlertEna[i];
      t["paused"] = trayPaused[i];
      t["triggered"] = traytriggered[i];
      t["dispensed_today"] = traydisptoday[i];
      t["dismissed_today"] = traydismtoday[i];
      char timeBuf[6];
      snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d", trayHours[i], trayMin[i]);
      t["time"] = String(timeBuf);
    }

    serializeJson(doc, *response);
    request->send(response);
  });

  // 2. Register Home Assistant webhook URL for instant push notifications
  server.on("/api/ha_webhook", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("url", true) && !request->hasParam("url")) {
      request->send(400, "text/plain", "Param 'url' is missing.");
      return;
    }
    String newUrl = request->hasParam("url", true) ? request->getParam("url", true)->value() : request->getParam("url")->value();
    haWebhookUrl = newUrl;

    preferences.begin("appSettings", false);
    preferences.putString("ha_webhook", haWebhookUrl);
    preferences.end();

    request->send(200, "application/json", "{\"status\":\"ok\"}");
  });

  // 3. Holiday / Pause mode per tray
  server.on("/tray_pause", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("tray") || !request->hasParam("paused")) {
      request->send(400, "text/plain", "Params 'tray' and 'paused' (0 or 1) are required.");
      return;
    }
    int tray = request->getParam("tray")->value().toInt();
    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Invalid tray number.");
      return;
    }
    bool paused = (request->getParam("paused")->value().toInt() == 1);
    trayPaused[tray] = paused;

    char key[20];
    snprintf(key, sizeof(key), "trayPaused%d", tray);
    preferences.begin("traySettings", false);
    preferences.putBool(key, paused);
    preferences.end();

    notifyHomeAssistant("tray_paused", tray);
    request->send(200, "text/plain", "Done");
  });

  // 4. Advance tray by X steps (for refilling / resetting)
  server.on("/displace", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->hasParam("tray")) {
      request->send(400, "text/plain", "Param 'tray' is missing.");
      return;
    }
    int tray = request->getParam("tray")->value().toInt();
    int steps = request->hasParam("steps") ? request->getParam("steps")->value().toInt() : 1;

    if (tray < 1 || tray > installedTrays) {
      request->send(400, "text/plain", "Invalid tray number.");
      return;
    }
    if (steps < 1 || steps > 30) {
      request->send(400, "text/plain", "Param 'steps' must be between 1 and 30.");
      return;
    }
    if (alertinprogress || displacementinprogress || dispensebatchinprogress) {
      request->send(409, "text/plain", "Dispenser is currently busy.");
      return;
    }

    displace(tray, steps);
    request->send(200, "text/plain", "Done");
  });

  // 5. Check latest GitHub release version
  server.on("/api/update_check", HTTP_GET, [](AsyncWebServerRequest * request) {
    String fwUrl = "";
    String spiffsUrl = "";
    String latestTag = checkLatestGithubRelease(fwUrl, spiffsUrl);

    StaticJsonDocument<512> doc;
    doc["current_version"] = versionnumber;
    doc["latest_version"] = latestTag;
    String cleanCurrent = versionnumber;
    cleanCurrent.replace("v.", "v");
    String cleanLatest = latestTag;
    cleanLatest.replace("v.", "v");

    doc["update_available"] = (cleanLatest.length() > 0 && cleanLatest != cleanCurrent);
    doc["firmware_url"] = fwUrl;


    String out;
    serializeJson(doc, out);
    request->send(200, "application/json", out);
  });

  // 6. Trigger one-click OTA update from GitHub latest release
  server.on("/api/ota_github", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (alertinprogress || displacementinprogress || dispensebatchinprogress) {
      request->send(409, "text/plain", "Cannot update while dispensing or alert is active.");
      return;
    }
    triggerGithubOta = true;
    request->send(200, "application/json", "{\"status\":\"updating\"}");
  });

}
