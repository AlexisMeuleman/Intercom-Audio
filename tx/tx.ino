#include "Tx_Can_25.h"
#include <Adafruit_MCP23X17.h>

#define BUTTON_PIN 1

Adafruit_MCP23X17 mcp;

void setup() 
{
  Time_ms = millis();

  Serial.begin(230400);
  initEspNow();

    if (!mcp.begin_I2C(0x27)) { 
    Serial.println("Error.");
    while (1);
  }

  mcp.pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() 
{

  checkSerialCommand();

  if (millis() >= Time_ms + 1000)  //prends une mesure
  {
    Time_ms = millis();
   

    fillCanetteData(data);                            //rempli la struc avec les data
    
   // sendPayload(ESPNOW, jsonPayload);

    if (!mcp.digitalRead(BUTTON_PIN)) 
    {
     Serial.println("Button Pressed!");
     Command=2;
    }
   else
   Command=0;

    sendToESPNow(data);
    printData();  //Print to Serial port USB
  }
}
