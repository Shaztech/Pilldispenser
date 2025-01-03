static void passkey_event_handler(lv_event_t * e) { // Keyboard keys (Cancel/Accept)
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_READY) {
    String codefromscreen = lv_textarea_get_text(ui_PassTXT);
    if (codefromscreen == passcode) {
      lv_textarea_set_text(ui_PassTXT, "");
      if (nextaction == 1) {
        nextaction = 0;
        Dispense_Action();
        return;
      }
      if (nextaction == 2) {
        nextaction = 0;
        loadTraySettings(selectedtray);
        lv_scr_load(ui_TrayConfigSCR);
        return;
      }
      if (nextaction == 3) {
        nextaction = 0;
        lv_scr_load(ui_SettingSCR);
        return;
      }
    } else {
      lv_textarea_set_text(ui_PassTXT, "");
      nextaction = 0;
      lv_scr_load(ui_MainSCR);
    }
  }
  if (code ==  LV_EVENT_CANCEL ) {
    lv_textarea_set_text(ui_PassTXT, "");
    nextaction = 0;
    lv_scr_load(ui_MainSCR);
  }
}
