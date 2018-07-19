#include <SoftwareSerial.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
#define m1 3
#define m2 4
#define m3 5
#define m4 6
int temp=0,i=0;
int led=13;
String fback;
char str[15];
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
   pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
     pinMode(m3, OUTPUT);
     pinMode(m4, OUTPUT);
     digitalWrite(m1,HIGH);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,HIGH);
      
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(1000);
 
}

void loop()
{
  if(temp==1)
  {
    check();
    temp=0;
    i=0;
    delay(1000);
  }
   DateTime now = rtc.now();
   if((now.hour()==20)&&(now.minute()==42)&&(now.second()==20)){
    digitalWrite(m2, HIGH);
      digitalWrite(m1, HIGH);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, HIGH);
    fback="Rtc turned on";
  SendMessage();
  delay(200);
  }
  else if((now.hour()==20)&&(now.minute()==43)&&(now.second()==20)){
    digitalWrite(m2, LOW);
      digitalWrite(m1, LOW);
      digitalWrite(m3, LOW);
         digitalWrite(m4, LOW);
   fback="rtc turned off";
  SendMessage();
  delay(200);
  }
}
void SendMessage()
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919440082570\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println(fback);// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void serialEvent() 
 {
  while(Serial.available()) 
  {
    if(Serial.find("#A."))
    {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      while (Serial.available()) 
      {
      char inChar=Serial.read();
      str[i++]=inChar;
      if(inChar=='*')
      {
        temp=1;
        return;
      } 
      } 
    }
   }
   
 }

void check()
{
  
   if(!(strncmp(str,"m3 off",6)))
    {
      digitalWrite(m3, HIGH);
      fback="m3 is turned off";
      SendMessage();
      delay(200);
    }  
   
   else if(!(strncmp(str,"m3 on",5)))
    {
      digitalWrite(m3, LOW);
     fback="m3 is turned on";
      SendMessage();
      delay(200);
    }
  else if(!(strncmp(str,"m4 off",6)))
    {
      digitalWrite(m4, HIGH);
      fback="m4 is turned off";
      SendMessage();
      delay(200);
    }  
   
   else if(!(strncmp(str,"m4 on",5)))
    {
      digitalWrite(m4, LOW);
     fback="m4 is turned on";
      SendMessage();
      delay(200);
    }
    else if(!(strncmp(str,"m1 off",6)))
    {
      digitalWrite(m1, HIGH);
     fback="m1 is turned off";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"m1 on",5)))
    {
      digitalWrite(m1, LOW);
      fback="m1 is turned on";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"m2 off",6)))
    {
      digitalWrite(m2, HIGH);
      fback="m2 is turned off";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"m2 on",5)))
    {
      digitalWrite(m2, LOW);
     fback="m2 is turned on";
      SendMessage();
      delay(200);
    } 
    
    else if(!(strncmp(str,"all off",7)))
    {
      digitalWrite(m2, HIGH);
      digitalWrite(m1, HIGH);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, HIGH);
     fback="all switches off";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"all on",6)))
    {
      digitalWrite(m2, LOW);
      digitalWrite(m1, LOW);
      digitalWrite(m3, LOW);
         digitalWrite(m4, LOW);
    fback="all switches on";
      SendMessage();
      delay(200);
    }  
      
}
