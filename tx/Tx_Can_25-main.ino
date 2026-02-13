#include "Tx_Can_25.h"


void setup() 
{
  Time_ms = millis();

  Serial.begin(230400);
  initEspNow();
}

void loop() 
{

  checkSerialCommand();

  if (millis() >= Time_ms + 1000)  //prends une mesure
  {
    Time_ms = millis();
   

    fillCanetteData(data);                            //rempli la struc avec les data
    
   // sendPayload(ESPNOW, jsonPayload);

   Command+=2;
    sendToESPNow(data);
    printData();  //Print to Serial port USB
  }
}
