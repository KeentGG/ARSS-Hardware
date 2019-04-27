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

void logSessionHead(char *head){
  UART1_Write_Text("\r\n----- ");
  UART1_Write_Text(head);
  UART1_Write_Text(" -----\r\n");
}

void logSessionFoot(char *foot){
  UART1_Write_Text("-----// ");
  UART1_Write_Text(foot);
  UART1_Write_Text(" //-----\r\n");
}