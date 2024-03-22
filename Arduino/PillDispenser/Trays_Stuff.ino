void updateTrays() {
  lv_color_t disabledColor = lv_color_hex(0x2D2D2D);

  for (int i = 1; i <= 10; i++) {
    lv_style_t style;
    lv_style_init(&style);

    if (i <= installedTrays) {      // Tray is enabled: Set recolor opacity to transparent and label to the tray name
      lv_obj_set_style_img_recolor_opa(ui_TrayIMG[i], LV_OPA_TRANSP, 0); // Disable recoloring
      lv_obj_set_style_img_recolor(ui_TrayIMG[i], index_to_color(trayColor[i]), 0);
      lv_label_set_text(ui_TrayLBL[i], trayNames[i].c_str()); // Set label to the tray name
      trayEnabled[i] = true;
    } else {       // Tray is disabled: Apply disabled color and set opacity
      lv_obj_set_style_img_recolor_opa(ui_TrayIMG[i], 150, 0); // Enable recoloring
      lv_obj_set_style_img_recolor(ui_TrayIMG[i], disabledColor, 0); // Apply disabled color
      lv_label_set_text(ui_TrayLBL[i], "Not Installed"); // Update label text
      trayEnabled[i] = false;
    }
  }
}

static void tray_check_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    if (!alertinprogress) {
      // Determine which tray was clicked
      lv_obj_t* clicked_tray = lv_event_get_target(e);
      int clickedIndex = -1;

      for (int i = 1; i <= 10; i++) {
        if (clicked_tray == ui_TrayIMG[i]) {
          clickedIndex = i;
          break;
        }
      }

      if (clickedIndex != -1) {
        // Toggle the checked state of the clicked tray
        trayCheckedState[clickedIndex] = !trayCheckedState[clickedIndex];

        // If we just unchecked the tray, ensure no tray appears selected
        if (!trayCheckedState[clickedIndex]) {
          for (int i = 1; i <= 10; i++) {
            // Clear the checked state for all trays
            trayCheckedState[i] = false;
            lv_obj_clear_state(ui_TrayIMG[i], LV_STATE_CHECKED); // Clear visual indication
          }
        } else {
          // A tray was selected, unselect all others
          for (int i = 1; i <= 10; i++) {
            if (i != clickedIndex) {
              trayCheckedState[i] = false; // Uncheck all other trays
              lv_obj_clear_state(ui_TrayIMG[i], LV_STATE_CHECKED); // Clear visual indication for others
            }
          }
          // Visually indicate the selected tray
          lv_obj_add_state(ui_TrayIMG[clickedIndex], LV_STATE_CHECKED);
        }
      }

      // Check if any tray is now selected to update button states
      bool any_checked = false;
      bool any_installed_checked = false;
      for (int i = 1; i <= 10; i++) {
        if (trayCheckedState[i]) {
          if (i <= installedTrays) any_installed_checked = true;
          any_checked = true;
          break;
        }
      }

      if (any_checked) {
        lv_obj_clear_state(ui_TraycfgBTN, LV_STATE_DISABLED); // Enable the button
      } else {
        lv_obj_add_state(ui_TraycfgBTN, LV_STATE_DISABLED); // Disable the button
      }
      if (any_installed_checked) {
        lv_obj_clear_state(ui_DispenseBTN, LV_STATE_DISABLED); // Enable the button
        lv_obj_add_flag(ui_TraynotinstalledLBL, LV_OBJ_FLAG_HIDDEN);
      } else {
        lv_obj_add_state(ui_DispenseBTN, LV_STATE_DISABLED); // Disable the button
        lv_obj_clear_flag(ui_TraynotinstalledLBL, LV_OBJ_FLAG_HIDDEN);
      }

    }
  }
}


static void roller_event_handler(lv_event_t * e) {
  //lv_style_t style;
  //lv_style_init(&style);
  lv_obj_t * roller = lv_event_get_target(e);
  uint16_t option = lv_roller_get_selected(roller);
  lv_obj_set_style_bg_color(ui_ColorPanel, index_to_color(option), LV_PART_MAIN);
}

lv_color_t index_to_color(int indexcolor) {
  lv_color_t color;
  switch (indexcolor) {
    case 0: color = lv_color_hex(0xFF0000); break; // RED
    case 1: color = lv_color_hex(0xFF00FF); break; // MAGENTA
    case 2: color = lv_color_hex(0x800080); break; // VIOLET
    case 3: color = lv_color_hex(0x0000FF); break; // BLUE
    case 4: color = lv_color_hex(0x00FFFF); break; // CYAN
    case 5: color = lv_color_hex(0x00FF00); break; // GREEN
    case 6: color = lv_color_hex(0xFFFF00); break; // YELLOW
    case 7: color = lv_color_hex(0xFFA500); break; // ORANGE
    default: color = lv_color_hex(0xFFFFFF); // Default or fallback color
  }
  return color;
}

uint32_t index_to_pixel(int indexcolor) {
  uint32_t color;
  switch (indexcolor) {
    case 0: color = pixels.Color(255, 0, 0); break; // RED
    case 1: color = pixels.Color(255, 0, 255); break; // MAGENTA
    case 2: color = pixels.Color(128, 0, 128); break; // VIOLET
    case 3: color = pixels.Color(0, 0, 255); break; // BLUE
    case 4: color = pixels.Color(0, 255, 255); break; // CYAN
    case 5: color = pixels.Color(0, 255, 0); break; // GREEN
    case 6: color = pixels.Color(255, 255, 0); break; // YELLOW
    case 7: color = pixels.Color(255, 165, 0); break; // ORANGE
    default: color = pixels.Color(0, 0, 0); // Default or fallback color, WHITE
  }
  return color;
}
