#include "Rx_Can_25.h"


void setup() 
{   

    M5.begin();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Init ESPNow... \n");

    initEspNow();   
   
    
}

void loop() 
{ 
    M5.update();


    if(newpacket)
    {
      newpacket=false;
    
      Serial.printf("🍆 commande #%3d 📦 Packet #%5d \n",data.commande, data.packet_num);
      
    }
}
