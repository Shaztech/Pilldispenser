#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <XPT2046_Touchscreen.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <AsyncElegantOTA.h>
#include <Preferences.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "time.h"
#include <Adafruit_NeoPixel.h>
#include "DFRobotDFPlayerMini.h"

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_NUM 0
#define SDA_PIN 22
#define SCL_PIN 27
#define SAMPLE_RATE 16000 // Adjust based on your WAV file
#define DAC_CHANNEL 26 // GPIO 26
#define LED_PIN    16  // Use GPIO16
#define NUM_LEDS   2  // Number of LEDs in your strip

//TX2 POUR AUDIO = PIN17


// declaration
String newHostname  = "PillsDisp";
lv_timer_t* inactivity_timer = NULL; // Declare the timer pointer globally
lv_timer_t* alertsound_timer = NULL; // Declare the timer pointer globally
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];
uint16_t touchScreenMinimumX = 300, touchScreenMaximumX = 3800, touchScreenMinimumY = 220, touchScreenMaximumY = 3800;
String ssidload, passwordload;
bool systemloaded = false;
String trayNames[11] = {"", "", "", "", "", "", "", "", "", "", ""};
bool trayAlertEna[11] = {false, false, false, false, false, false, false, false, false, false, false};
bool traytriggered[11] = {false, false, false, false, false, false, false, false, false, false, false};
bool trayEnabled[11] = {false, false, false, false, false, false, false, false, false, false, false};
bool trayfastflash[11];
int trayHours[11];
int trayMin[11];
int trayColor[11];
bool alreadyTriggered[11] = {false};
bool trayCheckedState[11] = {false}; // Initialize all as unchecked
bool alertinprogress = false;
bool dispensebatchinprogress;
bool displacementinprogress;
int currentcolordispense;
int flashing;
uint32_t currentpixelcolor;
lv_obj_t* ui_TrayIMG[11];
lv_obj_t* ui_TrayLBL[11];

bool internetstatus;
bool clockSS;
bool muteSound;
int installedTrays;
bool dstEnabled;
int utcOffset;
int traytodispense;
int displacesteps;
int selectedtray;
int spkvolume;

// register stuff
SPIClass mySpi = SPIClass(VSPI);
AsyncWebServer server(80);
Preferences preferences;
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
DFRobotDFPlayerMini myDFPlayer;


void setup() {
  Serial.begin( 115200 );
  Serial2.begin(9600, SERIAL_8N1, -1, 17);

  if (!SPIFFS.begin()) {
    return;
  }

  String showversion = "LVGL v";
  showversion += String('.') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  showversion += " - SOFT v.1.0"; // SOFTWARE VERSION DEFINITION

  Wire.begin(SDA_PIN, SCL_PIN);
  pwm.begin();
  pwm.setPWMFreq(60);

  myDFPlayer.begin(Serial2);
  myDFPlayer.volume(1);  //Set volume value. From 0 to 30

  pixels.begin();

  /*Initialize the display*/
  lv_init();
#if LV_USE_LOG != 0
  lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif
  mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  ts.begin(mySpi);
  ts.setRotation(3);
  tft.begin();
  tft.setRotation(3);
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_t * my_indev = lv_indev_drv_register( &indev_drv );

  ui_init(); //// BEFORE ANYTHING RELATED TO LVGL !!!!!

  ui_TrayIMG[1] = ui_TrayIMG1;
  ui_TrayIMG[2] = ui_TrayIMG2;
  ui_TrayIMG[3] = ui_TrayIMG3;
  ui_TrayIMG[4] = ui_TrayIMG4;
  ui_TrayIMG[5] = ui_TrayIMG5;
  ui_TrayIMG[6] = ui_TrayIMG6;
  ui_TrayIMG[7] = ui_TrayIMG7;
  ui_TrayIMG[8] = ui_TrayIMG8;
  ui_TrayIMG[9] = ui_TrayIMG9;
  ui_TrayIMG[10] = ui_TrayIMG10;

  ui_TrayLBL[1] = ui_TrayLBL1;
  ui_TrayLBL[2] = ui_TrayLBL2;
  ui_TrayLBL[3] = ui_TrayLBL3;
  ui_TrayLBL[4] = ui_TrayLBL4;
  ui_TrayLBL[5] = ui_TrayLBL5;
  ui_TrayLBL[6] = ui_TrayLBL6;
  ui_TrayLBL[7] = ui_TrayLBL7;
  ui_TrayLBL[8] = ui_TrayLBL8;
  ui_TrayLBL[9] = ui_TrayLBL9;
  ui_TrayLBL[10] = ui_TrayLBL10;

  lv_obj_add_event_cb(ui_ScanWifiBTN, scan_wifi_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_Keyboard, keyboard_wifi_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_SettingBackBTN, SettingBackBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_WifiClearBTN, WifiClearBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_DispenseBTN, DispenseBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_UpIMGBTN, UpIMGBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_DownIMGBTN, DownIMGBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_TraycfgBTN, TraycfgBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_TrayCfgSaveBTN, TrayCfgSaveBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_TrayCfgClearBTN, TrayCfgClearBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_VolTestBTN, VolTestBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_DisplaceBTN, DisplaceBTN_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_ColorRoller, roller_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(ui_PickPillsSCR, pick_pills_screen_event_handler, LV_EVENT_CLICKED, NULL);

  for (int i = 1; i <= 10; i++) {
    lv_obj_add_event_cb(ui_TrayIMG[i], tray_check_event_handler, LV_EVENT_ALL, NULL);
  }

  lv_obj_add_state(ui_Keyboard, LV_STATE_DISABLED);
  lv_obj_add_state(ui_PassTxtBox, LV_STATE_DISABLED);
  lv_obj_add_flag(ui_WifiScanPAN, LV_OBJ_FLAG_HIDDEN);

  lv_label_set_text(ui_VersionLBL, showversion.c_str());

  lv_timer_t* timer = lv_timer_create(startup_step1_timer, 1000, NULL);
  pixels.setPixelColor(1, pixels.Color(213, 230, 255));
  pixels.setBrightness(50);
  pixels.show();
  loadSettings();

}


void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  lv_task_handler();
}
