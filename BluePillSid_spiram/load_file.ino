
struct SidFile {
  
  byte magic[4];
  byte version[2];
  byte data[2];
  byte load[2];
  byte init[2];
  byte play[2];
  byte songs[2];
  byte start_song[2];
  byte speed[4];
  char name[32];
  char author[32];
  char relase[32];
  byte flags[2];
  byte start_page;
  byte page_lenght;
  byte sec_sid;
  byte thrid_sid;
  
};

SidFile sid;


boolean load_sid(String filename)
{

  
  //console.println("Otwieram plik: "+ filename);
  
  if (!SD.exists(filename)){ /*console.println("Nie ma takiego pliku !"); */return false;}
  File dataFile = SD.open(filename);iwdg_feed();
  if (dataFile) { dataFile.read(&sid,sizeof(SidFile));  
    iwdg_feed();
    if  ( ((sid.magic[0]==0x50) && (sid.magic[1]==0x53) &&(sid.magic[2]==0x49) &&(sid.magic[3]==0x44)) /*|| ((sid.magic[0]==0x52) && (sid.magic[1]==0x53) &&(sid.magic[2]==0x49) &&(sid.magic[3]==0x44))*/ )
    
    { 
    size_music=dataFile.size()-(sid.data[0]*256+sid.data[1]);
    init_music=sid.init[0]*256+sid.init[1];
    play_music=sid.play[0]*256+sid.play[1];
    start_music=(sid.start_song[0]*256+sid.start_song[1])-1;
    if (sid.load[0]*256+sid.load[1]==0)
    {
      //console.println("Adres ladowania $0000... szukam nowego.");
      load_music=sid.data[0]*256+sid.data[1];
      dataFile.seek(load_music);
      sid.load[1]=dataFile.read();
      sid.load[0]=dataFile.read();
      load_music=sid.load[0]*256+sid.load[1];
      start_music=(sid.start_song[0]*256+sid.start_song[1])-1;
      //console.printlm(sid.speed[0]);console.printlm(sid.speed[1]);console.printlm(sid.speed[2]);console.printlm(sid.speed[0]);
      if (sid.speed[3]==1) { dataFile.close(); iwdg_feed(); return false;}
      if (bitRead(sid.flags[1],3)){speed_music=60;} else {speed_music=50;}
      //console.print("Nowy adres ladowanie $");
      //console.println(load_music,HEX);
    }
   // console.println ("Inicjalizacja CPU 6502...");
    //setup6502(load_music,size_music);
    size_music=0;
    while (dataFile.available()) {poke(load_music+size_music,dataFile.read());size_music++;iwdg_feed();}
   // setup6502(load_music,size_music);
    //console.println();
   // console.print("\r\nName\t\t: ");console.println(sid.name);
   // console.print("Autor\t\t: ");console.println(sid.author);
   // console.print("(C)\t\t: ");console.println(sid.relase);
  //  console.print("Load Adres\t: $");console.println(load_music,HEX);
  //  console.print("Init Adres\t: $");console.println(init_music,HEX);
  //  console.print("Play Adres\t: $");console.println(play_music,HEX);
   // console.print("RAW size\t: $");console.println(size_music,HEX);
    }
    
    else 
    { 
      dataFile.close(); iwdg_feed();
      //console.println("To nie plik SID.");
      return false;
    }

    
  }
  // if the file isn't open, pop up an error:
  else {  /* console.println("błąd otwarcia pliku : "+filename); */return false;  }
  
 // console.println("Plik wczytany...");
 return true;
}



boolean play_file(String filename)
{
  // console.print("Ladowanie pliku:");
   //console.println(filename);
   stop();
   if ( load_sid(filename) )   { play() ;return true;  }  else {return false;}
}




boolean rnd(){

  int dir,file;
  String file_name;
  long start_t=0;
  
 // start_t=millis();
  dir=random(0,11);
  if (dir==10) {file=random(0,2372)+1;} else {file=random(0,5000)+1;}
  //dir=0;file=0;
  file_name="/HVSC/"+String(dir)+"/"+String(file)+".SID";

  //console.println(file_name);
  if(play_file(file_name))
  
  {
      iwdg_feed();
  
 // console.println("File loading & setup time :"+String((millis()-start_t))+" msec");
  hash_file="";
      iwdg_feed();

  //start_t=millis();
  md5_file(file_name);    iwdg_feed();

  //console.println("File MD5 time :"+String((millis()-start_t))+" msec");
 // console.println("MD5:\t"+String(hash_file));
 // start_t=millis();
  get_time();
  //console.println("det_time time :"+String((millis()-start_t))+" msec");
  return true;
  }
  
  else 
  
  {
        iwdg_feed();
 length_music=0 ;return false;  
  }

 
  
}

