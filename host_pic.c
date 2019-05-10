#define PIC_ADDR 0x40
#define CLK_FREQ 100000

#include <Headers/host/timelib.h>

// <DEBUG>
unsigned int debugLogCtr = 0;
char ctrStr[10];
// </DEBUG>


// <RTC>
unsigned char sec, min1, hr, week_day, day, mn, year;
char *txt, tnum[4];
TimeStruct ts;
unsigned long int epoch;
char epochStr[24];
// </RTC>


// <SESSION>
unsigned long int currEpoch = 1000000000;
unsigned long int userExpEpoch = 1000000060;
unsigned int unitAddrInt;

char userExpEpochStr[24];
char rawCurrEpochStr[24];
char currEpochStr[24];
char unitAddr;

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
#include <Headers/rtc.h>

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
  
  uartRcvBuff[0] = '\0';
  
  Delay_ms(3000);
  
  while(1){
    while(dataReceived == 0){
//      Delay_ms(2500);
      logSessionHead("Time Sync");
      Read_Time(&sec,&min1,&hr,&week_day,&day,&mn,&year);
      Transform_Time(&sec,&min1,&hr,&week_day,&day,&mn,&year); // format date and time
      ts.ss = sec;
      ts.mn = min1;
      ts.hh = hr;
      ts.md = day;
      ts.mo = mn;
      ts.yy = year + 2000;
      currEpoch = Time_dateToEpoch(&ts);
      
      LongToStr(currEpoch, rawCurrEpochStr);
      strcpy(currEpochStr, Ltrim(rawCurrEpochStr));
      
      clearSession();
      strcpy(sessionMode, "TIME");
      strcpy(sessionData[0], Ltrim(currEpochStr));
      strcpy(sessionBlockData, deMapSession(1, 0));

      debug(sessionBlockData);

      i2cSend(0x44, sessionBlockData);
      logSessionFoot("Time Sync");

      Delay_ms(1000);
      if(intFromUart == 1){
        intFromUart = 0;
        logSessionHead("Send Session");
        debug(uartRcvBuff);
        i2cSend(0x44, uartRcvBuff);
        logSessionFoot("Send Session");
      }
      Delay_ms(1000);
     }
   }

}