#include <SPI.h>
#include <LoRa.h>
#include <Console.h>
#include <Process.h>
#include "ThingSpeak.h"
#include "YunClient.h"

YunClient client;
unsigned long myChannelNumber = 1519237;
const char * myWriteAPIKey = "6K5JAGZMYGJZFCEH";
uint16_t crcdata = 0;
uint16_t recCRCData = 0;
// Set center frequency
uint32_t freq = 868100000;
int SF = 7, Denominator = 5;
long SBW = 125E3;
int number;
char data[50];
char lat[20];
char lon[20];
char chute[2];
long double gps1;
long old_time=millis();
long new_time;
long status_update_interval=30000;  

void show_config()
{
  Console.print("The frequency is ");Console.print(freq);Console.println("Hz");
  Console.print("The spreading factor is ");Console.println(SF);
  Console.print("The coderate is ");Console.println(Denominator);
  Console.print("The single bandwith is ");Console.print(SBW);Console.println("Hz");
}
void setup() {
  Bridge.begin(115200);
  Console.begin();
  ThingSpeak.begin(client);
//  while (!Console);

  Console.println("LoRa Receiver");

  if (!LoRa.begin(freq)) {
    Console.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(SBW);
  LoRa.setCodingRate4(Denominator);
  LoRa.setSyncWord(0x34); 
  LoRa.receive(0);    
  show_config();  
}
void loop() {

  // try to parse packet
 int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Console.print("Received packet '");

    // read packet
    int i = 0;
    char message[256];    
    while (LoRa.available() && i<256 ) {
     
      message[i]=LoRa.read();
      data[i]=message[i];
     Console.print(message[i]);
    
     i++;
    } 
   Console.println();

    delay(500);
     ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    strcpy(chute,strtok(data, ","));
     ThingSpeak.setField(3,chute);

    strcpy(lat,strtok(NULL, ","));
     ThingSpeak.setField(1,lat);
 // ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    strcpy(lon,strtok(NULL, ","));
 ThingSpeak.setField(2,lon);
 //ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    Console.print("chute= ");
    Console.println(chute);
    Console.print("latitude= ");
    Console.println(lat);
    Console.print("longitude=");
    Console.println(lon);
    
   Console.print("Sending packet ... ");
  LoRa.beginPacket();
  LoRa.print(1);
 
  LoRa.endPacket();



  delay(5000);
  }

 
        new_time = millis();

  if( (new_time-old_time) > status_update_interval){
      Console.println("");
      Console.println("not receive overtime");
      old_time = new_time;
  }  
   
}
