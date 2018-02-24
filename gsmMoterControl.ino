#include <SoftwareSerial.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
#define Fan 3
#define Light 4
#define TV 5
#define AC 6
int temp=0,i=0;
int led=13;
String fback;
char str[15];
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
   pinMode(Fan, OUTPUT);
    pinMode(Light, OUTPUT);
     pinMode(TV, OUTPUT);
     pinMode(AC, OUTPUT);
     digitalWrite(Fan,HIGH);
  digitalWrite(Light,HIGH);
  digitalWrite(TV,HIGH);
  digitalWrite(AC,HIGH);
      
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
    digitalWrite(Light, HIGH);
      digitalWrite(Fan, HIGH);
      digitalWrite(TV, HIGH);
      digitalWrite(AC, HIGH);
    fback="Rtc turned on";
  SendMessage();
  delay(200);
  }
  else if((now.hour()==20)&&(now.minute()==43)&&(now.second()==20)){
    digitalWrite(Light, LOW);
      digitalWrite(Fan, LOW);
      digitalWrite(TV, LOW);
         digitalWrite(AC, LOW);
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
  
   if(!(strncmp(str,"tv off",6)))
    {
      digitalWrite(TV, HIGH);
      fback="tv is turned off";
      SendMessage();
      delay(200);
    }  
   
   else if(!(strncmp(str,"tv on",5)))
    {
      digitalWrite(TV, LOW);
     fback="tv is turned on";
      SendMessage();
      delay(200);
    }
  else if(!(strncmp(str,"ac off",6)))
    {
      digitalWrite(AC, HIGH);
      fback="ac is turned off";
      SendMessage();
      delay(200);
    }  
   
   else if(!(strncmp(str,"ac on",5)))
    {
      digitalWrite(AC, LOW);
     fback="ac is turned on";
      SendMessage();
      delay(200);
    }
  
    else if(!(strncmp(str,"fan off",7)))
    {
      digitalWrite(Fan, HIGH);
     fback="fan is turned off";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"fan on",6)))
    {
      digitalWrite(Fan, LOW);
      fback="fan is turned on";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"light off",9)))
    {
      digitalWrite(Light, HIGH);
      fback="light is turned off";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"light on",8)))
    {
      digitalWrite(Light, LOW);
     fback="light is turned on";
      SendMessage();
      delay(200);
    } 
    
    else if(!(strncmp(str,"all off",7)))
    {
      digitalWrite(Light, HIGH);
      digitalWrite(Fan, HIGH);
      digitalWrite(TV, HIGH);
      digitalWrite(AC, HIGH);
     fback="all switches off";
      SendMessage();
      delay(200);
    }
 
    else if(!(strncmp(str,"all on",6)))
    {
      digitalWrite(Light, LOW);
      digitalWrite(Fan, LOW);
      digitalWrite(TV, LOW);
         digitalWrite(AC, LOW);
    fback="all switches on";
      SendMessage();
      delay(200);
    }  
      
}
