 #ifndef Rx_Can_25_H     // Vérifie si  n'a pas encore été défini
  #define Rx_Can_25_H   // Définit pour éviter une inclusion multiple

  
  #include <M5Stack.h>
  #include <SPI.h>
  #include <Wire.h>
  #include "EspNow.h"
  #include "DataProcessor.h"


  #define CMD_BUFFER_SIZE 15

 void displayData(void);
 void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len); 
 void checkSerialCommand(void);

#endif // Fin de la protection contre l’inclusion multiple