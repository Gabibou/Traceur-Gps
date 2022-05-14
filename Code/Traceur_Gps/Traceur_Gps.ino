//------------------------------------------ Library import ------------------------------------------
#include <SoftwareSerial.h> 
#include <TinyGPS.h> 

//------------------------------------------ Pin Define ------------------------------------------
#define RXGPS 2 
#define TXGPS 3 
#define RXLORA 0 
#define TXLORA 1 

//------------------------------------------ Object Define ------------------------------------------
SoftwareSerial GPS(RXGPS, TXGPS);
SoftwareSerial lora(RXLORA, TXLORA); 
TinyGPS gps;
//------------------------------------------ Variable Define ------------------------------------------
float latitude = 28.5458;
float longitude = 77.1703;
String DevEui = "ac1f09fffe054355";
String AppEUI = "ac1F09fff8683172";
String AppKey = "ac1f09fffe054355ac1f09fff8683172";
//------------------------------------------ Programable by using command ------------------------------------------
long DelayTwoMesurementMS = 300000;    //Varible use to choose the time beetween two mesurement(it will affect the battery time) Number in mili second

void setup(){
  GPS.begin(9600);
  LoraSetup(AppKey,AppEUI,DevEui); //Choose the right key to acces  
}

void loop(){
  digitalWrite(4,HIGH);
  DataMesurement();
  LoraConnection();
  delay(5000);  //the connection could take some times so we have to wait
  SendMesurement();
  digitalWrite(4,LOW);
  delay(DelayTwoMesurementMS);
}
