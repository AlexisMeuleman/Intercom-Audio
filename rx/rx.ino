#include "Rx_Can_25.h"

#define NOTE_DH2 661

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
   if(data.commande == 2 )
   {
    M5.Speaker.tone(NOTE_DH2, 200);
   }
   else
   M5.Speaker.end();
}
