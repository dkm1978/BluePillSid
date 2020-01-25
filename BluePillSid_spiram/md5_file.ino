#include "MD5.h"

MD5_CTX ctx;
byte md5sum [16];
byte mem;




boolean md5_file(String file_name)
{
  File plik;
  if (!SD.exists(file_name)) {
    //console.println("Nie ma takiego pliku !");
    return false;
  }
  plik = SD.open(file_name);
  MD5::MD5Init(&ctx);
  while (plik.available())
  {
    iwdg_feed();
    if (!digitalRead(PB5)) {plik.close();return false;}
    mem = plik.read();
    MD5::MD5Update(&ctx, &mem, 1);
  }

  MD5::MD5Final(md5sum, &ctx);

  for ( int i = 0; i <= 15; i++)
  {
    //console.print(md5sum[i], HEX);
    if (md5sum[i] <= 15) {
      hash_file += "0";
    }
    hash_file += String(md5sum[i], HEX);
    //console.print(md5sum[i],HEX);
  }

  plik.close();return true;
}





boolean get_time()
{
  File plik;
  int st;
  String temp = "";
  char tt = 0;
  String file_name = "/HVSC/" + hash_file.substring(0, 1) + ".MD5";

  if (!SD.exists(file_name)) {
   // console.println("Nie ma  pliku MD5!");
    return 0;
  }
  plik = SD.open(file_name);


  while ( plik.available())
  {

    iwdg_feed();
    if (!digitalRead(PB5)) {plik.close();return false;}
    tt = plik.read();
    temp = temp + tt;
    // console.println(temp);
    if (tt == 0x0A)
    {
      tt = 0;
      //console.println("****************************************************");
      if (temp.substring(0, 32) == hash_file)  {
        find_time(temp);
        plik.close();
        return st;
      }
      temp = "";
    }
  }



  plik.close(); return true;
}

void find_time(String lin) {
  String ts, tm;

  lin = lin.substring(33);
  //console.println(lin);
  for (int i = 0; i <= lin.length(); i++) {
    if (lin.charAt(i) == 32) break;
    if (lin.charAt(i) == 58) {
      tm = ts;
      ts = "";
    }
    else {
      ts += lin.charAt(i);
    }
  }
  length_music=(tm.toInt()*60)+ts.toInt();
 // console.println("Duration\t: " + tm + ":" + ts);
  //console.println("Time ins sec " +String(length_music));


}

