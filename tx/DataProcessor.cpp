#include "DataProcessor.h"


CanetteData data;
char capturAudio[125];
char capturVideo[125];

String jsonPayload;
bool serialPrintData =false;
// Remplit la structure CanetteData avec les données actuelles
void fillCanetteData(CanetteData &data) 
{
  
  data.packet_num = Packetnum;
  data.commande = Command;
  
  memcpy(data.packetAudio, capturAudio, strlen(capturAudio));
  memcpy(data.packetVideo, capturVideo, strlen(capturVideo));
  
  Packetnum+=1;
}

void sendToSerial(String payload) 
{
    Serial.println(payload+",");
}

void printData(void) 
{
  //if(!serialPrintData) return;


    Serial.printf("⭐ Packetnum %d  🍆 Commande %3d\n", Packetnum,Command);
    Serial.println("──────────────────────────────────────────");
}
