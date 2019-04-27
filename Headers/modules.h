void debug(char *msg){
  char ctrStr[10];

  if(debugLogCtr == 99){
    debugLogCtr = 0;
  }

  IntToStr(debugLogCtr, ctrStr);

  debugLogCtr++;
  UART1_Write_Text(Ltrim(ctrStr));
  UART1_Write_Text(" ");
  UART1_Write_Text(msg);
  UART1_Write_Text("\r\n");
}