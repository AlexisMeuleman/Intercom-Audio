#include "esp32-hal-gpio.h"
#include "Tx_Can_25.h"

uint8_t cmdIndex = 0, compteur_donne=0, Canette_Mode=0, SupplySource=0;
unsigned long Time_ms=0,Packetnum=0,Command;
float SystemCurrent=0.0,SystemVoltage=0.0,Tmp36_temperatur=0.0,MCP9808_temperature=21.3;
float Internaltemp;
bool buzzerEnabled = false;

char cmdBuffer[CMD_BUFFER_SIZE];




String millisToTimeString(unsigned long currentMillis) 
{
  unsigned long hours = currentMillis / 3600000UL;
  unsigned long minutes = (currentMillis % 3600000UL) / 60000UL;
  unsigned long seconds = (currentMillis % 60000UL) / 1000UL;
  unsigned long milliseconds = currentMillis % 1000UL;

  char buffer[15]; // "hh:mm:ss.ms" + null terminator
  snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu.%03lu", hours, minutes, seconds, milliseconds);

  return String(buffer);
}



//Définition de la fonction buzzer_toggle
void buzzer_toggle(unsigned int time)
{
  static unsigned long time_buzzer = 0;
  static bool pin = 0;

  if (millis() >= time_buzzer + time)
  {
    time_buzzer = millis();
    pin = !pin;

    // Buzzer ON/OFF
    digitalWrite(BUZZER_Pin, pin);
  }
}


void GetInternalTemp(void)
{
  Internaltemp = temperatureRead();
  #ifdef esp_temp
    Serial.print(F("Internal Temperature: "));
    Serial.print(Internaltemp);
  #endif 
}

void checkSerialCommand(void) 
{

}



float truncateFloat(float value, int decimalPlaces) 
{
    float factor = pow(10, decimalPlaces);
    return floor(value * factor) / factor; // Tronquer sans arrondi
}

void sendPayload(Destination dest, String payload) 
{
    switch (dest) 
    {
       
        case SERIAL_OUTPUT:
            if(Canette_Mode)  sendToSerial(payload);
            break;
        case ESPNOW:
            sendToESPNow(data);
            break;
        default:
            Serial.println("❌ Destination inconnue !");
            break;
    }
}
















