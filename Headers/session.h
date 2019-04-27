// Dependencies: coreSession.h, eeprom.h, output_strings.h
char unitSerialId[11];

char eepromTest[] = "1556283018";

void updateSessionData(){
  char expTime[MAX_SESSION_DATA_SIZE];
  char serialID[MAX_SESSION_DATA_SIZE];
  char deMapSessionData[255];

  clearEEPROM();

  setEEPROM(sessionData[0], 0x00);
  setEEPROM(sessionData[1], 0x0C);
}

void unlockUnit(){
  LATD.f0 = 1;
  Delay_ms(2000);
  LATD.f0 = 0;
}

// Requires for the sessionMode & sessionData to be mapped first. Check coreSession.h
// Checks sessionMode & sessionData values to perform their corresponding actions.
void checkSession(){
  char serialID[24];
  char userExp[24];

  if(strcmp(sessionMode, ADD_MODE) == 0){
    hasSession = 1;
    outputFreshLCD("Adding..", sessionData[1]);
    updateSessionData();
  }else if(strcmp(sessionMode, REMOVE_MODE) == 0){
    hasSession = 0;
    outputFreshLCD("Removing..", "");
    clearEEPROM();
  }else if(strcmp(sessionMode, UPDATE_MODE) == 0){
    outputFreshLCD("Updating..", "");
    setEEPROM(sessionData[0], 0x0C);
  }else if(strcmp(sessionMode, "READ") == 0){
    outputFreshLCD("Reading..", "");
    Delay_ms(500);
    getEEPROM(serialID, 0x00);
    getEEPROM(userExp, 0x0C);
    outputFreshLCD(serialID, userExp);
  }else if(strcmp(sessionMode, "TIME") == 0){
    currTime = atol(sessionData[0]);
    LongToStr(currTime, rawCurrTimeStr);
    strcpy(currTimeStr, Ltrim(rawCurrTimeStr));
    Lcd_Out(2,1, currTimeStr);
  }
  Delay_ms(1500);
  outputFreshLCD("","");
}