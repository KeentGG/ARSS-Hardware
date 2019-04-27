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
  
  INTCON.GIE = 1;
  INTCON.PEIE = 1;
  
  UART1_Init(9600);
  
  I2C_Master_Init(CLK_FREQ);
  
  PIE1.TMR1IE = 1;
  PIR1.TMR1IF = 0;

  T1CON = 0x80;
  TMR1H = 0x63;
  TMR1L = 0xC0;

  LongToStr(userExpEpoch, userExpEpochStr);
  clearSession();
  strcpy(sessionMode, "ADD");
  strcpy(sessionData[0], "D287131B5D");
  strcpy(sessionData[1], Ltrim(userExpEpochStr));
  strcpy(sessionBlockData, deMapSession(1, 0));

  outputFreshLCD(Ltrim(sessionBlockData), "");
  i2cSend(0x44, Ltrim(sessionBlockData));
  
  Delay_ms(100);
  
  T1CON.TMR1ON = 1;
  
  while(1){
    while(dataReceived == 0){}
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