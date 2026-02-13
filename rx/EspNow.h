#ifndef EspNow_H     // Vérifie si  n'a pas encore été défini
  #define EspNow_H   // Définit pour éviter une inclusion multiple

  #include <esp_wifi.h>
  #include <esp_now.h>
  #include <WiFi.h>
  #include "DataProcessor.h"

extern  int rssi_value;  

void initEspNow(void);
String getMacAddress(void);
void promiscuous_rx_cb(void *buf, wifi_promiscuous_pkt_type_t type);
void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);  
#endif // Fin de la protection contre l’inclusion multiple
