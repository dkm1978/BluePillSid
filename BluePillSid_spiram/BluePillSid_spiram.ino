#include <SD.h>
#include <MD5.h>
#include <libmaple/iwdg.h>
#include <RTClock.h>

RTClock rtclock (RTCSEL_LSE);

uint16_t load_music,init_music,play_music,size_music; // Zmiennne globalne
uint16_t speed_music,start_music;
int length_music;
volatile byte migacz,stat=0,sekundy;


boolean inserted_card;
String katalog="/",hash_file;
 long  dog,ile=0;
USBSerial console; // Debug serial :)


#ifdef __cplusplus
extern "C" {
#endif
  
 // uint16_t getpc();
  //uint8_t getop();
  uint32_t gosub(uint16_t adress,uint8_t a,uint8_t x,uint8_t y);
  void exec6502(int32_t tickcount);
  void reset6502();
  void poke(uint16_t addr,uint8_t val);
  void writeSid(uint8_t reg,uint8_t val);
  void printhex(uint16_t val);
  void setup6502(uint16_t loadr,uint16_t sizer);
  void RAMwrite(uint16_t address,uint8_t val);
  uint8_t RAMread(uint16_t address);
#ifdef __cplusplus
}
#endif

//void printhex(uint16_t val) { console.println(val, HEX); }




void setup ()
{

    //while (!Serial.available())
    //    continue;  
     
    pinMode(PC13,OUTPUT);
    digitalWrite(PC13,HIGH);
    pinMode(PB5,INPUT_PULLUP);
    //pinMode(PA0, INPUT_ANALOG);
  // console.println("\t\t       **** Almost like Commodore 64 ****");
   //console.println("\t\t        65536 bytes free for You music .\r\n");
    pin_setup();
    SD.begin();
    StartRAM();
   // console.println("Type RUN to start or LOOP to loop playing \r\n");
    randomSeed(millis());
   // console.println("READY.");
    iwdg_init(iwdg_prescaler::IWDG_PRE_32,8000);
    rtclock.attachSecondsInterrupt(SecondCount);
   // attachInterrupt(PB5, reset_pin, CHANGE);
   
} 


void loop () {
  
  sekundy=0;
  while(!rnd()) {  digitalWrite(PC13,LOW); iwdg_feed();}
  while (sekundy<length_music) { if (!digitalRead(PB5)) {break;}}
 
}

void SecondCount ()
{
  sekundy++;
  digitalWrite(PC13, !digitalRead(PC13));
}

void reset_pin(){nvic_sys_reset();}
   






