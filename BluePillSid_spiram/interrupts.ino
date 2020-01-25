

void start_int(int hz) {
  int speed;
  
  if (hz == 90) {return;}
  RAMwrite(0xDC04, 0);
  RAMwrite(0xDC05, 0);
  //console.println("init :(");
  gosub(init_music, start_music, 0, 0);
  //console.println("init ok");
  if (hz == 60) {
    speed = 16666 ;
   // console.println("Clock at\t: 60 Hz");
    if (((RAMread(0xDC04) + RAMread(0xdc05) * 256)) != 0) {
     // console.println("Clock at\t: CIA INT :(");
      sekundy = length_music;
      return;
    }
  } else {
   
    speed = 20000 ;//0x4FB2 ;
  }

  noInterrupts();
  Timer2.setPrescaleFactor(1);
  Timer2.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
  Timer2.setPeriod(speed);
  Timer2.setCompare(TIMER_CH1, 1);
  Timer2.attachInterrupt(TIMER_CH1, handler);
  sekundy = 0;
  interrupts();

}

void handler(void) {

  
  iwdg_feed();
  gosub(play_music, 0, 0, 0);

}

void stop_int() {
  //console.println("Stop");
  noInterrupts();
  digitalWrite(PC13, HIGH);
  Timer2.detachInterrupt(TIMER_CH1);
  interrupts();
   //console.println("Stop ok");
}


