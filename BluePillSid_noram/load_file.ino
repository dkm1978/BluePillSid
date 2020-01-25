
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

  

  debu.println("Otwieram plik: "+ filename);
  if (!SD.exists(filename)){debu.println("Nie ma takiego pliku !");return false;}
  File dataFile = SD.open(filename);
  if (dataFile) { dataFile.read(&sid,sizeof(SidFile));  
    
    if  ( ((sid.magic[0]==0x50) && (sid.magic[1]==0x53) &&(sid.magic[2]==0x49) &&(sid.magic[3]==0x44)) || ((sid.magic[0]==0x52) && (sid.magic[1]==0x53) &&(sid.magic[2]==0x49) &&(sid.magic[3]==0x44)))
    
    { 
    size_music=dataFile.size()-(sid.data[0]*256+sid.data[1]);
    init_music=sid.init[0]*256+sid.init[1];
    play_music=sid.play[0]*256+sid.play[1];
    start_music=(sid.start_song[0]*256+sid.start_song[1])-1;
    if (sid.load[0]*256+sid.load[1]==0)
    {
      debu.println("Adres ladowania $0000... szukam nowego.");
      load_music=sid.data[0]*256+sid.data[1];
      dataFile.seek(load_music);
      sid.load[1]=dataFile.read();
      sid.load[0]=dataFile.read();
      load_music=sid.load[0]*256+sid.load[1];
      debu.print("Nowy adres ladowanie $");
      debu.println(load_music,HEX);
    }
    debu.println ("Inicjalizacja CPU 6502...");
    setup6502(load_music,size_music);
    size_music=0;
    while (dataFile.available()) {poke(load_music+size_music,dataFile.read());size_music++;}
    setup6502(load_music,size_music);
    debu.println();debu.println();
    debu.print("Name\t\t: ");debu.println(sid.name);
    debu.print("Autor\t\t: ");debu.println(sid.author);
    debu.print("(C)\t\t: ");debu.println(sid.relase);
    debu.print("Load Adres\t\t: $");debu.println(load_music,HEX);
    debu.print("Init Adres\t\t: $");debu.println(init_music,HEX);
    debu.print("Play Adres\t\t: $");debu.println(play_music,HEX);
    debu.print("RAW size\t\t: ");debu.println(size_music,HEX);
    }
    
    else 
    { 
      dataFile.close(); 
      debu.println("To nie plik SID.");
      return false;
    }

    
  }
  // if the file isn't open, pop up an error:
  else { debu.println("błąd otwarcia pliku : "+filename);return false;  }
  
  debu.println("Plik wczytany...");return true;
}


void ls() 
{
      init_card();
      if (inserted_card) 
      {
      debu.println("Listowanie katalogu.");
      File root;
      root = SD.open("/");
      root.rewindDirectory();
      printDirectory(root, 0,true);
      }
      else
      {
        debu.println("Brak kart lub jest uszkodzona!");
      }
      
}

void printDirectory(File dir, int numTabs,boolean show_names)
{
  while (true)
  {
    File entry = dir.openNextFile();
    if (! entry)
    {
      if (numTabs == 0)
        debu.println("** Done **");
      return;
    }
    for (uint8_t i = 0; i < numTabs; i++)
      debu.print('\t');
    debu.print(entry.name());
    if (entry.isDirectory())
    {
      if (show_names) {debu.println("/");}
      printDirectory(entry, numTabs + 1,show_names);
    }
    else
    {
      if (show_names){debu.print("\t\t");debu.println(entry.size(), DEC);}
    }
    entry.close();
  }
}

void play_file(String filename)
{
   debu.print("Ladowanie pliku:");
   debu.println(filename);
   stop();
   if ( load_sid(filename) )
   {
    debu.println ("Inicjalizacja playera...");
   if ( gosub(init_music,0,0,0)) { debu.println ("Ustawianie przerwan...");setup_sei(speed_music);play(); } else { debu.println("Out of memory ..... :P");}
   }
}

void init_card(){
  debu.print("Inicjalizacja karty SD...");
  if (!SD.begin()) { debu.println("Blad odczytu karty lub jej brak !");inserted_card=true; } else { debu.println("ok."); inserted_card=true;}
}

void losowy() 
{
      file_index=0;
      los=random(max_index);
      debu.println(los);
      init_card();
      if (inserted_card) 
      {
      //debu.println("Listowanie katalogu.");
      File root;
      root = SD.open("/");
      root.rewindDirectory();
      printD(root, 0);
      }
      else
      {
        debu.println("random Brak kart lub jest uszkodzona!");
      }
      debu.print("Liczba plikow :");debu.println(file_index);debu.println(los_name+" :D");
     
      //play_file(los_name);
      
}

void printD(File dir, int numTabs)
{

 while (true)
  {
    File entry = dir.openNextFile();
    if (! entry)
    {
      if (numTabs == 0)
        debu.println("** Done **");
      return;
    }
    for (uint8_t i = 0; i < numTabs; i++)
      debu.print('\t');
    debu.print(entry.name());inc_file();
    if (file_index==los) {get_name(dir.name(),entry.name());} else {los_name="";}
    if (entry.isDirectory())
    {
      {debu.println("/");}
      printD(entry, numTabs + 1);
    }
    else
    {
     {debu.print("\t\t");debu.println(entry.size(), DEC);}
    }
    entry.close();
  }
  
}

void inc_file() { file_index++;}
void inc_max() { max_index++;}

void licz() 
{
      file_index=0;max_index=0;
      init_card();
      if (inserted_card) 
      {
      //debu.println("Listowanie katalogu.");
      File root;
      root = SD.open("/");
      root.rewindDirectory();
      printDd(root, 0);
      }
      else
      {
        debu.println("random Brak kart lub jest uszkodzona!");
      }
      debu.print("Liczba plikow :");debu.println(file_index);
     
      //play_file(get_name(los));
      
}

void get_name(String l1,String l2)
{
  if (l1=="/") {los_name=l1+l2;} else { los_name=l1+"/"+l2;}
  play_file(los_name);
}

void printDd(File dir, int numTabs)
{
debu.println(".");
 while (true)
  {
    File entry = dir.openNextFile();
    if (! entry)
    {
      if (numTabs == 0)
        //debu.println("** Done **");
      return;
    }
    for (uint8_t i = 0; i < numTabs; i++)
     // debu.print('\t');
    //debu.print(entry.name());
    inc_max();
   // if (file_index==los) {get_name(dir.name(),entry.name());} else {los_name="";}
    if (entry.isDirectory())
    {
      //{debu.println("/");}
      printDd(entry, numTabs + 1);
    }
    else
    {
     //{debu.print("\t\t");debu.println(entry.size(), DEC);}
    }
    entry.close();
  }
  
}
