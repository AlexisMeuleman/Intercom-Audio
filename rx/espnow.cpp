 #include "EspNow.h"
 #include "Rx_Can_25.h"
  
int rssi_value = 0; 
String macAddres_Espnow; 

void initEspNow(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(); // Éviter les conflits Wi-Fi

    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Forcer le canal 1
    esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR); // Activer le mode Long Range
    esp_wifi_set_max_tx_power(78); // Maximiser la puissance TX
    esp_wifi_config_espnow_rate(WIFI_IF_STA, WIFI_PHY_RATE_1M_L); // Optimiser pour longue portée

    esp_wifi_set_promiscuous(true); // Activer le mode promiscuous pour récupérer le RSSI
    esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx_cb);

    if (esp_now_init() != ESP_OK) 
    {
        Serial.println("❌ ESP-NOW Init Failed");
        return;
    }

    esp_now_register_recv_cb(onDataRecv); //callBack reception espnow
  
    // ✅ Vérification du mode Long Range activé
    uint8_t protocol = 0;
    esp_err_t err = esp_wifi_get_protocol(WIFI_IF_STA, &protocol);
    if (err == ESP_OK && (protocol & WIFI_PROTOCOL_LR)) 
    {
        Serial.println(F("✅ espNOW : Mode Long Range activé sur le récepteur"));

        macAddres_Espnow=getMacAddress() ;


         Serial.println(macAddres_Espnow);
       
    } 
    else 
    {
        Serial.println(F("❌ espNOW :  Mode Long Range NON activé sur le récepteur"));
    }   
}

// Callback promiscuous pour capturer le RSSI
void promiscuous_rx_cb(void *buf, wifi_promiscuous_pkt_type_t type) 
{
    if (type != WIFI_PKT_MGMT) return;
    const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buf;
    rssi_value= ppkt->rx_ctrl.rssi; 
}

void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
   if (len == sizeof(CanetteData)) 
   {
        memcpy(&data, incomingData, sizeof(CanetteData));

        lastRssiEspNow = rssi_value;  // 🔄 Stocker le RSSI ESP-NOW
        
        processReceivedData("ESP-NOW");  
        newpacket=1;
    } 
    else 
    {
        Serial.println("❌ Erreur : Taille de paquet incorrecte en ESP-NOW");
    } 
}

String getMacAddress(void) 
{
  uint8_t mac[6];
  WiFi.macAddress(mac);  // Récupère l'adresse MAC

  char macStr[19];  // Buffer pour stocker l'adresse MAC formatée
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  return String(macStr);  // Retourne l'adresse MAC sous forme de String
}
