#include <SD.h>

uint16_t load_music,init_music,play_music,size_music; // Zmiennne globalne
uint16_t speed_music,start_music;
int file_index,max_index;
int los=0;
String los_name="";
volatile boolean can_play;
boolean inserted_card;
USBSerial debu; // Debug serial :)

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
  void out_ram();
#ifdef __cplusplus
}
#endif

void printhex(uint16_t val) { debu.println(val, HEX); }
void out_ram() { debu.println("Out of memoty :)");}



void setup ()
{

    debu.begin();delay(5000);
    randomSeed(analogRead(0));
    debu.println ("Inicjalizacja sprzetowa SID'a...");
    pin_setup();
    init_card();
    licz();
     debu.print("plikow :"); debu.print(file_index);
    help();
    debu.print(">>> ");
} 


void loop () 
{
String command="";

if (debu.available()>0)
  {
    
    command=debu.readString();
    debu.println(command);
  
    if (command=="ls\r\n") { ls(); }
    if (command=="help\r\n") { help(); }
    if (command=="play\r\n") { play(); }
    if (command=="stop\r\n") { stop(); }
     if (command=="random\r\n") { losowy(); }
    if (command=="init\r\n") { init_card(); }
    if (command.substring(0,1)=="@")
    {
      debu.print("Wczytywanie : ");
      debu.println(command.substring(1));
      command=command.substring(1,command.length()-2);
      command.toUpperCase();
      play_file(command);
      
    }
  debu.print(">>> ");
 }
  
}

void help(){
  debu.println ();
    debu.println ("Dostepne komendy :");
    debu.println ("ls - wyswietla zawartosc karty"); 
    debu.println ("@<filename> - wczytuje plik");
    debu.println ("stop - zatrzymuje playera");
    debu.println ("play - wczytuje plik");
    debu.println ("help - pomoc :)");
     debu.println ();
   
  
}



