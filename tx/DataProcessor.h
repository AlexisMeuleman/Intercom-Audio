#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H


#include <Arduino.h>
#include <ArduinoJson.h>  //7.3.0


extern bool serialPrintData;

  enum Destination 
  {
    SD_CARD,
    SPIFFS_MEMORY,
    SERIAL_OUTPUT,
    LORA,
    ESPNOW
  };

struct CanetteData 
{
uint32_t packet_num;       // Numéro du paquet
uint8_t commande;             // commande
char packetAudio[120];
char packetVideo[120];
//char macAdresseNow[19];    //mac adresse Espnow
    
};


 extern CanetteData data;


 #include "Tx_Can_25.h"

// Déclaration des fonctions
void fillCanetteData(CanetteData &data);  // Remplit la structure CanetteData
void printData(void); 

void processDataForSDAndSerial(CanetteData &data, String &jsonPayload);  // Traite les données pour SD et Serial
void sendPayload(Destination dest, String payload);
void sendToSerial(String payload); 

#endif