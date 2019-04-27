void host_isr(){
  SSPCON1.CKP = 0;
  
  if(PIR1.TMR1IF){
    TMR1H = 0x63;
    TMR1L = 0xC0;
    timerCounter++;
    if(timerCounter == 100){
      currEpoch++;
      timerCounter = 0;
      timerThirtySecCounter++;
      if(timerThirtySecCounter == 10){
        timerThirtySecCounter = 0;
      }
    }
    PIR1.TMR1IF = 0;
    intFromTimer = 1;
    dataReceived  = 1;
  }
  
  PIR1.SSPIF = 0;
  PIR1.RCIF = 0;
  SSPCON1.CKP = 1;
  j = SSPBUF;
  return;
}