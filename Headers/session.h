// Dependencies: coreSession.h, eeprom.h, output_strings.h
char unitSerialId[11];

void updateSessionData(){
  char expTime[MAX_SESSION_DATA_SIZE];
  char serialID[MAX_SESSION_DATA_SIZE];
  char deMapSessionData[255];

  clearEEPROM();

  setEEPROM(sessionData[2], 0x00);
  setEEPROM(sessionData[3], 0x0C);
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
  if(strcmp(sessionMode, "SESSION") == 0){
    if(strcmp(sessionData[0], UNIT_NUM) == 0){
      if(strcmp(sessionData[1], ADD_MODE) == 0){
        hasSession = 1;
        outputFreshLCD("Renting..", sessionData[2]);
        end_overdue = 0;
        updateSessionData();
      }else if(strcmp(sessionData[1], REMOVE_MODE) == 0){
        hasSession = 0;
        outputFreshLCD("This unit is", "now available");
        Delay_ms(500);
        clearEEPROM();
      }else if(strcmp(sessionData[1], UPDATE_MODE) == 0){
        setEEPROM(sessionData[2], 0x0C);
      }else if(strcmp(sessionData[1], "READ") == 0){
        Delay_ms(500);
        getEEPROM(serialID, 0x00);
        getEEPROM(userExp, 0x0C);
        outputFreshLCD(serialID, userExp);
      }else if(strcmp(sessionData[1], "END_OVERDUE") == 0){
        end_overdue = 1;
        updateSessionData();
      }
    }else {
      Delay_ms(500);
    }
  }else if(strcmp(sessionMode, "TIME") == 0){
    currTime = atol(sessionData[0]);
    LongToStr(currTime, rawCurrTimeStr);
    strcpy(currTimeStr, Ltrim(rawCurrTimeStr));
  }
}