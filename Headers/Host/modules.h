void host_isr(){
  SSPCON1.CKP = 0;
  
  if (PIR1.RCIF) {
    uartRcv = RCREG;
    
    if(uartRcv == ':'){
      sessionReceivedValid = 1;
      uartCount = 0;
    }

    if(sessionReceivedValid){
      if(RCREG == ';') {
        uartRcvBuff[uartCount] = '\0';
        uartCount = 0;
        intFromUart = 1;
        sessionReceivedValid = 0;
      }else {
        uartRcvBuff[uartCount] = RCREG;
        uartCount++;
      }
    }
  }
  
  PIR1.SSPIF = 0;
  PIR1.RCIF = 0;
  SSPCON1.CKP = 1;
  j = SSPBUF;
  return;
}