#define PIC_ADDR 0x44
#define CLK_FREQ 100000

#include <Built_in.h>
#include <Headers/lcd.h>
#include <Headers/connection.h>
#include <Headers/eeprom.h>
#include <Headers/coreSession.h>
#include <Headers/session.h>

// <INTERRUPT>

char sdaBuffer[64];
unsigned int sdaPtr = 0;
unsigned int dataReceived = 0;
char j;
unsigned int timerCounter = 0;
unsigned int intFromTimer = 0;

// </INTERRUPT>

void interrupt(){
  if (PIR1.SSPIF){
    SSPCON1.CKP = 0;

    if (SSPSTAT.BF == 0){
      j = SSPBUF;
      return;
    }

    if (SSPSTAT.D_A == 1){
      char sdaByte = SSPBUF;
//      dataReceived = 1;
      if(sdaByte == ';'){
        dataReceived = 1;

        sdaBuffer[sdaPtr++] = '\0';
        sdaPtr = 0;
      }else{
        sdaBuffer[sdaPtr++] = sdaByte;
      }
      PIR1.SSPIF = 0;
      SSPCON1.CKP = 1;
      return;
    }
  }
  PIR1.SSPIF = 0;
  SSPCON1.CKP = 1;
  j = SSPBUF;
}

void main(){
  ADCON1 = 0x0F;

  I2C_Slave_Init(0x44);

  outputFreshLCD("init", "");
  
  while(1){
    while(dataReceived == 0){}
    mapSession(sdaBuffer);
    checkSession();
    
    outputFreshLCD("","");
    sdaBuffer[0] = '\0';
    dataReceived = 0;
  }
}