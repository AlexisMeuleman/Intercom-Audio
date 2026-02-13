
#include "DataProcessor.h"


CanetteData data;


String lastSource = "";
bool newpacket=0;

int lastRssiEspNow = 0;

bool serialPrintData =false;


void processReceivedData(String source) 
{
}


void printData(void) 
{
 
    
    
    Serial.println(F("──────────────────────────────────────────"));
}
