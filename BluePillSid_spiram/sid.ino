
#define cs_pin PB11
#define reset_pin PA13

#define A0_pin PB12
#define A1_pin PB10 // PB13//pb10
#define A2_pin PA9  //PB14 //
#define A3_pin PA14 //PB15 //PA14
#define A4_pin PA8

#define D0_pin PB9
#define D1_pin PB8
#define D2_pin PB7
#define D3_pin PB6
#define D4_pin PB4 //pb 10
#define D5_pin PB3 //a9
#define D6_pin PA15
#define D7_pin PA10




void writeSid(uint8_t reg,uint8_t val)
{ 
 

  digitalWrite(cs_pin,HIGH);

  if (bitRead(reg,0)) {digitalWrite(A0_pin,HIGH);} else {digitalWrite(A0_pin,LOW);}
  if (bitRead(reg,1)) {digitalWrite(A1_pin,HIGH);} else {digitalWrite(A1_pin,LOW);}
  if (bitRead(reg,2)) {digitalWrite(A2_pin,HIGH);} else {digitalWrite(A2_pin,LOW);}
  if (bitRead(reg,3)) {digitalWrite(A3_pin,HIGH);} else {digitalWrite(A3_pin,LOW);}
  if (bitRead(reg,4)) {digitalWrite(A4_pin,HIGH);} else {digitalWrite(A4_pin,LOW);}

   if (bitRead(val,0)) {digitalWrite(D0_pin,HIGH);} else {digitalWrite(D0_pin,LOW);}
   if (bitRead(val,1)) {digitalWrite(D1_pin,HIGH);} else {digitalWrite(D1_pin,LOW);}
   if (bitRead(val,2)) {digitalWrite(D2_pin,HIGH);} else {digitalWrite(D2_pin,LOW);}
   if (bitRead(val,3)) {digitalWrite(D3_pin,HIGH);} else {digitalWrite(D3_pin,LOW);}
   if (bitRead(val,4)) {digitalWrite(D4_pin,HIGH);} else {digitalWrite(D4_pin,LOW);}
   if (bitRead(val,5)) {digitalWrite(D5_pin,HIGH);} else {digitalWrite(D5_pin,LOW);}
   if (bitRead(val,6)) {digitalWrite(D6_pin,HIGH);} else {digitalWrite(D6_pin,LOW);}
   if (bitRead(val,7)) {digitalWrite(D7_pin,HIGH);} else {digitalWrite(D7_pin,LOW);}
   
  
  digitalWrite(cs_pin,LOW);digitalWrite(cs_pin,HIGH);
}




void pin_setup(){
  
  // SID !CS pin // 
  pinMode(cs_pin,OUTPUT);digitalWrite(cs_pin,HIGH);
  //pinMode(reset_pin,OUTPUT);digitalWrite(reset_pin,LOW);delay(100);digitalWrite(reset_pin,HIGH);

  // SID address line A0-A4 //
  pinMode(A0_pin,OUTPUT);digitalWrite(A0_pin,LOW);
  pinMode(A1_pin,OUTPUT);digitalWrite(A1_pin,LOW);
  pinMode(A2_pin,OUTPUT);digitalWrite(A2_pin,LOW);
  pinMode(A3_pin,OUTPUT);digitalWrite(A3_pin,LOW);
  pinMode(A4_pin,OUTPUT);digitalWrite(A4_pin,LOW);

   pinMode(D0_pin,OUTPUT);digitalWrite(D0_pin,LOW);
   pinMode(D1_pin,OUTPUT);digitalWrite(D1_pin,LOW);
   pinMode(D2_pin,OUTPUT);digitalWrite(D2_pin,LOW);
   pinMode(D3_pin,OUTPUT);digitalWrite(D3_pin,LOW);
   pinMode(D4_pin,OUTPUT);digitalWrite(D4_pin,LOW);
   pinMode(D5_pin,OUTPUT);digitalWrite(D5_pin,LOW);
   pinMode(D6_pin,OUTPUT);digitalWrite(D6_pin,LOW);
   pinMode(D7_pin,OUTPUT);digitalWrite(D7_pin,LOW);
   
}

void play()
{
   //console.println("Play"); 
   start_int(speed_music);
   //console.println("Stop");  
}
void stop()
{
    poke(0xD418,0);
    stop_int();  
    
}

