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
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text("\r\n----- ");
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text(head);
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text(" -----\r\n");
  while(UART1_Tx_Idle() == 0){};
}

void logSessionFoot(char *foot){
while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text("-----// ");
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text(foot);
  while(UART1_Tx_Idle() == 0){};
  UART1_Write_Text(" //-----\r\n");
  while(UART1_Tx_Idle() == 0){};
}