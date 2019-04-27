void debug(char *msg){
  if(debugLogCtr == 99){
    debugLogCtr = 0;
  }

  IntToStr(debugLogCtr, ctrStr);

  debugLogCtr++;
  UART1_Write_Text(Ltrim(ctrStr));
  UART1_Write_Text(" - ");
  UART1_Write_Text(msg);
  UART1_Write_Text("\r\n");
}