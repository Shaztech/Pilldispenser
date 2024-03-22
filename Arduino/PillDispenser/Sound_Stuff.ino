
void Playsound(int soundnumber) {
  myDFPlayer.volume(spkvolume);
  myDFPlayer.play(soundnumber);  //Play (1-Alert.mp3, 2-PillsReady.mp3)
  //myDFPlayer.reset();
  //currentsound = soundnumber;
  //lv_timer_t* timer = lv_timer_create(DFPlayerwake_Timer, 500, NULL);
}

static void DFPlayer_Alarm_Timer(lv_timer_t * timer) {
  if (alertinprogress) Playsound(1);
}
