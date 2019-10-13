//**********Library**********//
 
#include "Gyro.h"

//**********Definitions**********//

#define EEPROM_I2C_ADDRESS 0x50                             // Définit l'adresse I²C de l'EEPROM 

//**********Loops**********//

void writeAddress(int address,byte val){                    // Ecrit une valeur dans une adresse de l'EEPROM
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address>>8));   // MSB
  Wire.write((int)(address&0xFF)); // LSB  
  Wire.write(val);
  Wire.endTransmission();
  delay(5);
}

byte readAddress(int address){                              // Lit une valeur dans une adresse de l'EEPROM
  byte rData=0xFF; 
  Wire.beginTransmission(EEPROM_I2C_ADDRESS); 
  Wire.write((int)(address>>8));   // MSB
  Wire.write((int)(address&0xFF)); // LSB
  Wire.endTransmission();  
  Wire.requestFrom(EEPROM_I2C_ADDRESS,1);  
  rData=Wire.read();
  return rData;
}
