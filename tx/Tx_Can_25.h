 #ifndef Tx_Can_25_H     // Vérifie si  n'a pas encore été défini
  #define Tx_Can_25_H   // Définit pour éviter une inclusion multiple
  
 
  #include "Arduino.h"
  #include <sys/_stdint.h>

  #include "DataProcessor.h"
  #include "EspNow.h" 

  
  #define BUZZER_Pin 1
  #define CMD_BUFFER_SIZE 30
  #define debug_mode 1







  extern unsigned long Time_ms,Packetnum,Command;
  extern float Internaltemp,SystemCurrent,Tmp36_temperatur,MCP9808_temperature,SystemVoltage;





 
  String millisToTimeString(unsigned long currentMillis); 
  void GetInternalTemp(void);

  String createJsonPacket(void);
  void sendToSerial(String payload);
  void checkSerialCommand(void); 
  float truncateFloat(float value, int decimalPlaces);


#endif // Fin de la protection contre l’inclusion multiple