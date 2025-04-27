#include "NTPClient.h"
#include "ESP8266WiFi.h"
#include "WifiUdp.h"
#include<IRremote.h>
const char *ssid = "****";
const char *pass = "****";
#define AC_ON 0x118008;
#define AC_OFF 0x4500188;
#define HSwing_ON 0x6B46408;
#define Hswing_OFF 0x1F46408;
#define VSwing_ON 0x4946408;
#define VSwing_OFF 0x2D46408;
WiFiUDP ntpUDP;
const long utcOffset = 19800;
NTPClient timeClient(ntpUDP,"pool.ntp.org",utcOffset);
IRrecv irrecv(2);
decode_results results;


int getTemp(int data){
  switch(data){
    case 0x7960808:
        return 18;
        break;
    case 0x110808:
        return 19;
        break;
    case  0x4150808:
        return 20;
        break;
    case  0x2130808:
        return 21;
        break;
    case  0x6170808:
        return 22;
        break;
    case 0x1108808:
         return 23;
         break;
    case 0x5148808:
         return 24;
         break;
    case 0x3128808:
         return 25;
         break;
    case 0x7168808:
         return 26;
         break;
    case 0x918808:
         return 27;
         break;
    case 0x4958808:
         return 28;
         break;
    case 0x2938808:
         return 29;
         break;
    case 0x6978808:
         return 30;
         break;
    default:
         return -1;
         break;
  }
}

int getFunction(int data){
  switch(data){
    case 0x118008:
    case 0x7160008:
         Serial.println("AC is ON");
         return 1;
         break;
    case 0x4500188:
         Serial.println("AC is OFF");
         return 1;
         break;
    case 0x6B46408:
         Serial.println("Hswing is ON");
         return 1;
         break;
    case 0x1F46408:
         Serial.println("Hswing is OFF");
         return 1;
         break;
    case 0x4946408:
         Serial.println("VSwing is On");
         return 1;
         break;
    case 0x2D46408:
         Serial.println("Vswing is OFF");
         return 1;
         break;
    default:
         return -1;
         break;
  }
}

void printTime(){
  Serial.print(timeClient.getHours());
Serial.print(":");
Serial.print(timeClient.getMinutes());
Serial.print(":");
Serial.print(timeClient.getSeconds());
Serial.print("  ");
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
WiFi.begin(ssid,pass);
while(WiFi.status()!=WL_CONNECTED){
  delay(200);
  Serial.print(".");
}
if(WiFi.status()==WL_CONNECTED){
  Serial.println("Connected to WiFi");
}
timeClient.begin();
irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:

timeClient.update();

if(irrecv.decode()){
int data = irrecv.decodedIRData.decodedRawData;
irrecv.printIRResultAsCVariables(&Serial);
int AC_temp = getTemp(data);
if(AC_temp!=-1){
  printTime();
  Serial.print(AC_temp);
  Serial.print(" C");
  Serial.println("");

}
else{
  if(getFunction(data)==1){
    printTime();
  }
}
irrecv.resume(); 

}


}
