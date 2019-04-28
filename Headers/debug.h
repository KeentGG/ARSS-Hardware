void debug(char *msg){
  if(debugLogCtr == 99){
    debugLogCtr = 0;
  }

  IntToStr(debugLogCtr, ctrStr);

  debugLogCtr++;
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text(Ltrim(ctrStr));
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text(" - ");
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text(msg);
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text("\r\n");
  while(UART1_Tx_Idle() == 0){};
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