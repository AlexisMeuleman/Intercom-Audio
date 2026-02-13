#include "EspNow.h" 


bool printEspnow=true,EspnowFlag=true;
String macAddres_Espnow;

String getMacAddress(void) 
{
  uint8_t mac[6];
  WiFi.macAddress(mac);  // Récupère l'adresse MAC

  char macStr[19];  // Buffer pour stocker l'adresse MAC formatée
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  return String(macStr);  // Retourne l'adresse MAC sous forme de String
}

unsigned int initEspNow(void)
{
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();     // Désactive toute connexion Wi-Fi active

  

  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Forcer le canal 1 (important pour ESP-NOW LR)
  esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR); // Active le mode Long Range
  esp_wifi_set_max_tx_power(78);  // Puissance max (19.5 dBm)
  esp_wifi_config_espnow_rate(WIFI_IF_STA, WIFI_PHY_RATE_1M_L); // Débit 1 Mbps pour meilleure portée

 
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println(F("❌ Erreur lors de l'initialisation de l'ESP-NOW"));
    return 0;
  }
  else 
  {
    // Configuration de l'adresse de broadcast
    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(peerInfo));
    for (uint8_t i = 0; i < 6; ++i) {
      peerInfo.peer_addr[i] = 0xFF;  // Adresse de broadcast
    }
    //peerInfo.channel = 0;
    peerInfo.channel = 1;  // Assurer que les appareils sont sur le même canal
    peerInfo.encrypt = false;

    // Configuration du mode Long Range (sans wake window)
    //esp_now_set_pmk((uint8_t *)"0123456789abcdef");  // Définir la clé PMK (16 octets)

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println(F("❌ Erreur lors de l'ajout du peer broadcast"));
      return 0;
    }
    macAddres_Espnow=getMacAddress() ;
    Serial.println(F("✅ ESP-NOW initialisé avec succès"));

     Serial.println(F("✅ espNOW : Mode Long Range activé sur le récepteur"));

        macAddres_Espnow=getMacAddress() ;


         Serial.println(macAddres_Espnow);

    // ✅ Vérifier que le mode Long Range est bien activé
    uint8_t protocol = 0;
    esp_err_t err = esp_wifi_get_protocol(WIFI_IF_STA, &protocol);
    if (err == ESP_OK && (protocol & WIFI_PROTOCOL_LR)) 
    {
      Serial.println(F("✅ Mode Long Range activé"));
    } 
    else 
    {
      Serial.println(F("❌ Mode Long Range NON activé"));
    }
        return 0;
  }
}


void sendToESPNow(const CanetteData &data) 
{
    uint8_t buffer[sizeof(data)]; // Créer un buffer de la taille de la structure
    memcpy(buffer, &data, sizeof(data)); // Copier la structure dans le buffer

    uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    
     esp_err_t result = esp_now_send(broadcastAddress, buffer, sizeof(buffer));

    if (result == ESP_OK) 
    {  
  
        if(printEspnow)  Serial.printf("✅ Payload %d bytes\n", sizeof(data));
    } else 
    {
        Serial.println("❌ Erreur d'envoi ESP-NOW");
       
    }
}



