void isr(){
 if(PIR1.SSPIF){
    SSPCON1.CKP = 0;

    if (SSPSTAT.BF == 0){
      j = SSPBUF;
      return;
    }

    if (SSPSTAT.D_A == 1){
      char sdaByte = SSPBUF;
      dataReceived = 1;

      if(sessionReceivedValid){
        if(sdaByte == ';'){
          dataReceived = 1;
          sdaBuffer[sdaPtr++] = '\0';
          sessionReceivedValid = 0;
          sdaPtr = 0;
        } else{
          sdaBuffer[sdaPtr++] = sdaByte;
        }
      }else {
        if(sdaByte == ':'){
          sessionReceivedValid = 1;
        }
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