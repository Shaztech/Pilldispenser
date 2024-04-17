void displace(int whichtray, int steps) {
  displacementinprogress = true;
  displacesteps = steps;
  dispense(whichtray);
}

void dispense(int whichtray) {
  if (!dismissinprogress) {
    lv_timer_t* timer = lv_timer_create(dispense_step1_timer, 500, NULL);
    traytodispense = whichtray;
    if (!displacementinprogress) {
      traytriggered[whichtray] = false;
      trayfastflash[whichtray] = true;
      if (trayAlertEna[whichtray]) {
        traydisptoday[whichtray] = true;
        traydismtoday[whichtray] = false;
        char key[20]; // Key string to use for preferences
        preferences.begin("traySettings", false); // Open Preferences with namespace "traySettings". False for read and write.
        snprintf(key, sizeof(key), "traydisptoday%d", whichtray);
        preferences.putBool(key, traydisptoday[whichtray]);
        snprintf(key, sizeof(key), "traydismtoday%d", whichtray);
        preferences.putBool(key, traydismtoday[whichtray]);
        preferences.end(); // Close the Preferences
      }
    }
  } else {
    lv_timer_t* timer = lv_timer_create(dispense_step5_timer, 25, NULL);
    traytodispense = whichtray;
    traytriggered[whichtray] = false;
    trayfastflash[whichtray] = true;
    if (trayAlertEna[whichtray]) {
      traydisptoday[whichtray] = false;
      traydismtoday[whichtray] = true;
      char key[20]; // Key string to use for preferences
      preferences.begin("traySettings", false); // Open Preferences with namespace "traySettings". False for read and write.
      snprintf(key, sizeof(key), "traydisptoday%d", whichtray);
      preferences.putBool(key, traydisptoday[whichtray]);
      snprintf(key, sizeof(key), "traydismtoday%d", whichtray);
      preferences.putBool(key, traydismtoday[whichtray]);
      preferences.end(); // Close the Preferences
    }
  }
}

static void dispense_step1_timer(lv_timer_t * timer) { //Dispense Step 1
  lv_timer_create(dispense_step2_timer, 300, NULL);
  setServoPulse(traytodispense - 1, 180);
  lv_timer_del(timer);
}

static void dispense_step2_timer(lv_timer_t * timer) { //Dispense Step 2
  if (fixaligment) {
    fixaligment = false;
  } else {
    lv_timer_create(dispense_step3_timer, 500, NULL);
  }
  setServoPulse(traytodispense - 1, 70);
  lv_timer_del(timer);
}

static void dispense_step3_timer(lv_timer_t * timer) {  //Dispense Step 3
  lv_timer_create(dispense_step4_timer, 300, NULL);
  setServoPulse(traytodispense - 1, 180);
  lv_timer_del(timer);
}

static void dispense_step4_timer(lv_timer_t * timer) {  //Dispense Step 4
  if (!displacementinprogress) {
    lv_timer_create(dispense_step5_timer, 500, NULL);
  } else {
    displacesteps = displacesteps - 1;
    if (displacesteps == 0) {
      lv_timer_create(dispense_step5_timer, 500, NULL);
    } else {
      lv_timer_t* timer = lv_timer_create(dispense_step1_timer, 500, NULL);
    }
  }
  setServoPulse(traytodispense - 1, 70);
  lv_timer_del(timer);

}

static void dispense_step5_timer(lv_timer_t * timer) {  //Dispense Step 5
  if (!dismissinprogress) {
    detachServo(traytodispense - 1);
    if (!displacementinprogress) {
      trayfastflash[traytodispense] = false;
      lv_obj_set_style_img_recolor_opa(ui_TrayIMG[traytodispense], LV_OPA_TRANSP, 0); // Disable recoloring
      traytodispense = -1;
      dispensebatch(currentcolordispense);
    } else {
      displacementinprogress = false;
      lv_dropdown_set_selected(ui_DisplaceTrayDROP, 0);
      lv_obj_add_flag(ui_InprogressPAN, LV_OBJ_FLAG_HIDDEN);
    }
  } else {
    trayfastflash[traytodispense] = false;
    lv_obj_set_style_img_recolor_opa(ui_TrayIMG[traytodispense], LV_OPA_TRANSP, 0); // Disable recoloring
    traytodispense = -1;
    dispensebatch(currentcolordispense);
  }
  lv_timer_del(timer);
}

void dispensebatch(int colorindex) {
  for (int i = 1; i <= 11; i++) {
    if (i == 11) {
      dispensebatchinprogress = false;
      if (!dismissinprogress) {
        showLED(currentpixelcolor);
        lv_timer_reset(alertsound_timer); //reset alert sound timer
        Playsound(2);
        solidLED = true;
        lv_scr_load(ui_PickPillsSCR);
        lv_timer_create(dismissPickpillsSCR, 30000, NULL);
        break;
      } else {
        dismissinprogress = false;
        lv_timer_reset(alertsound_timer); //reset alert sound timer
        showLED(pixels.Color(0, 0, 0));
        placethings();
        break;
      }
    }
    if (traytriggered[i] && trayColor[i] == colorindex) {
      dispense(i);
      break;
    }
  }
}

static void dismissPickpillsSCR(lv_timer_t * timer) {
  solidLED = false;
  showLED(pixels.Color(0, 0, 0));
  placethings();
  lv_scr_load(ui_MainSCR);
  lv_timer_del(timer);
}
