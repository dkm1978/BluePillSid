
void setup_sei(int hz){
    int speed=20000;
    if (hz==60) {speed=16666;}
    noInterrupts(); 
    Timer2.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
    Timer2.setPeriod(speed); // in microseconds 20000 for 50Hz 16666 for 60Hz
    Timer2.setCompare(TIMER_CH1, 1);      // overflow might be small
    Timer2.attachInterrupt(TIMER_CH1, handler_led); 
    interrupts();    
}

void handler_led(void) { if (!can_play){gosub(play_music,0,0,0);} } 

