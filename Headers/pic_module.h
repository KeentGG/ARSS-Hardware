

void isr() {
  if (PIR1.SSPIF){  // I2C Interrupt
    SSPCON1.CKP = 0;

    if (SSPSTAT.BF == 0){ // all done,
      j = SSPBUF;         // Nothing in buffer so exit
      return;
    }
    //recieve data from master
    if (SSPSTAT.D_A == 1){
      char sdaByte = SSPBUF;

      if(sdaByte == ';'){
        dataReceived = 1;

        sdaBuffer[sdaPtr++] = '\0';
        sdaPtr = 0;
      }else{
        sdaBuffer[sdaPtr++] = sdaByte;
      }
      PIR1.SSPIF = 0;
      SSPCON1.CKP = 1;
      return;
    }
  }
  PIR1.SSPIF = 0;
  SSPCON1.CKP = 1;
  j = SSPBUF;
}

void bootMessageInit() {
   outputFreshLCD(unitNumBootMsg, "Starting Up");
}

void setUnitNum(char *num) {
   strcpy(unitNumBootMsg, "Unit #");
   catStr(unitNumBootMsg, num);
}

void bootMessageSuccess() {
   outputFreshLCD("Now Online", unitNumBootMsg);
}

void devMode() {
   outputFreshLCD("Done", "");
   awaitingUnlock = 1;
}

void variableInitialization() {
   unitSerialId[0] = '\0';
   unitNumBootMsg[0] = '\0';
}

void picConfig() {
   ADCON1 = 0x0F;
}

void bootMessage() {
   Delay_ms(120);
   bootMessageInit();
   Delay_ms(1500);
   bootMessageSuccess();
   Delay_ms(960);
}

void startUp(char *num) {
   picConfig();
   variableInitialization();

   setUnitNum(num);

   bootMessage();
}
