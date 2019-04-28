#define PIC_ADDR 0x40
#define CLK_FREQ 100000

// <DEBUG>
unsigned int debugLogCtr = 0;
char ctrStr[10];
// </DEBUG>


// <SESSION>
unsigned long int currEpoch = 1000000000;
unsigned long int userExpEpoch = 1000000060;

char userExpEpochStr[24];
char currEpochStr[24];
// </SESSION>


// <INTERRUPT>
char j;
char uartRcv;
char uartRcvBuff[64];

unsigned int uartCount = 0;
unsigned int intFromUart = 0;
unsigned int dataReceived = 0;
unsigned int intFromTimer = 0;
unsigned int timerCounter = 0;
unsigned int timerThirtySecCounter = 0;
// </INTERRUPT>

// <TEMPORARY>
char intFromUartStr[7];
// </TEMPORARY>


#include <Headers/lcd.h>
#include <Headers/connection.h>
#include <Headers/output_strings.h>
#include <Headers/coreSession.h>
#include <Headers/debug.h>
#include <Headers/host/modules.h>

void interrupt(){
  host_isr();
}

void main(){
  ADCON1 = 0x0F;
  
  PIE1.SSPIE = 1;
  PIE1.RCIE = 1;
  PIR1.RCIF = 0;
  
  UART1_Init(9600);
  
  I2C_Master_Init(CLK_FREQ);
  
  INTCON.GIE = 1;
  INTCON.PEIE = 1;
  
  while(1){
    while(dataReceived == 0){
    }
    if(intFromUart == 1){
       debug(uartRcvBuff);
    }
    if(intFromTimer){
      intFromTimer = 0;

      logSessionHead("Time Sync");
      LongToStr(currEpoch, currEpochStr);
      debug(currEpochStr);
      clearSession();
      strcpy(sessionMode, "TIME");
      debug(sessionMode);
      strcpy(sessionData[0], Ltrim(currEpochStr));
      strcpy(sessionBlockData, deMapSession(1, 0));
      debug(sessionBlockData);

      i2cSend(0x44, Ltrim(sessionBlockData));

      logSessionFoot("Time Sync");
    }

    dataReceived = 0;
  }
}