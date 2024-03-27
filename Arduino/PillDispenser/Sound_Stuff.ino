
void Playsound(int soundnumber) {
  if (!muteSound && !currentlyplaying) {
    myDFPlayer.volume(spkvolume);
    myDFPlayer.play(soundnumber);  //Play (1-Alert.mp3, 2-PillsReady.mp3)
    currentlyplaying = true;
    lv_timer_t* timer = lv_timer_create(Currently_playing_Timer, 2000, NULL);
  }
}

static void DFPlayer_Alarm_Timer(lv_timer_t * timer) {
  if (alertinprogress) Playsound(1);
}

static void Currently_playing_Timer(lv_timer_t * timer) {
  currentlyplaying = false;
  lv_timer_del(timer);
}
