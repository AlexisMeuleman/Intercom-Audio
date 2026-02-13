#ifndef EspNow_H     // Vérifie si  n'a pas encore été défini
  #define EspNow_H   // Définit pour éviter une inclusion multiple

  #include <Arduino.h>  // Toujours inclure Arduino.h en premier dans un projet ESP32 sous Arduino
  #include <esp_wifi.h>
  #include <esp_now.h>
  #include <esp_wifi_types.h>
  #include <esp_mac.h>
  
  
  
  #include <WiFi.h>
 

   #include "Tx_Can_25.h"

  extern bool printEspnow,EspnowFlag;
  extern String macAddres_Espnow;
String getMacAddress(void);
unsigned int initEspNow(void);
//void sendToESPNow(String payload);
void sendToESPNow(const CanetteData &data);
#endif // Fin de la protection contre l’inclusion multiple
