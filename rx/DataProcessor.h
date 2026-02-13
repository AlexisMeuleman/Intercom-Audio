#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <Arduino.h>



extern int lastRssiEspNow;

extern uint8_t temp_sf;
extern uint16_t temp_sbw;
extern uint8_t temp_cr;
extern bool newpacket;


  extern String jsonPayload;
  extern String lastSource;


struct CanetteData 
{
uint32_t packet_num;       // Numéro du paquet
char commande;             // commande
char packetAudio[120];
char packetVideo[120];
//char macAdresseNow[19];    //mac adresse Espnow
    
};

   

extern CanetteData data;

#include "Rx_Can_25.h"

// Déclaration des fonctions
void printData(void); 

void processDataForSDAndSerial(CanetteData &data, String &jsonPayload);  // Traite les données pour SD et Serial
void processReceivedData(String source); 
#endif