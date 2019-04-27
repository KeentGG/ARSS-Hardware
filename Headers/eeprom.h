// Dependencies: EEPROM MikroC Library

char EODChr = ';';

void getEEPROM(char *to, char *addr);

void clearEEPROM()
{
  Delay_ms(10);
  EEPROM_Write(0x00, 0xFF);
  Delay_ms(10);
}

void setEEPROM(char *str, char *addr){
  unsigned int cursor = 0;

//  clearEEPROM();

  for(cursor = 0; str[cursor] != 0; cursor++){
    Delay_ms(10);
    EEPROM_Write(addr+cursor, str[cursor]);
    Delay_ms(10);
  }

  EEPROM_Write(addr+cursor, 0xFF);
  Delay_ms(10);
}

void getEEPROM(char *to, char *addr){
  unsigned int cursor = 0;
  unsigned int isReadFinished = 0;
  char eepromBit;
  for(cursor = 0; isReadFinished == 0; cursor++){
    Delay_ms(10);
    to[cursor] = EEPROM_Read(addr+cursor);
    eepromBit = to[cursor];
    if(eepromBit == 0xFF){
      isReadFinished = 1;
      to[cursor] = 0;
    }
    Delay_ms(10);
  }
}