#define PIC_ADDR 0x44
#define CLK_FREQ 100000


// <SESSION>

unsigned long int currTime = 0;
unsigned int hasSession = 0;

char rawCurrTimeStr[24];
char currTimeStr[24];

// </SESSION>


// <INTERRUPT>

char sdaBuffer[64];
unsigned int sdaPtr = 0;
unsigned int dataReceived = 0;
char j;
unsigned int timerCounter = 0;
unsigned int intFromTimer = 0;

// </INTERRUPT>

#include <Built_in.h>
#include <Headers/lcd.h>
#include <Headers/connection.h>
#include <Headers/output_strings.h>
#include <Headers/eeprom.h>
#include <Headers/coreSession.h>
#include <Headers/session.h>
#include <Headers/modules.h>

void interrupt(){
  isr();
}

void main(){
  ADCON1 = 0x0F;

  I2C_Slave_Init(0x44);

  outputFreshLCD("init", "");
  
  while(1){
    while(dataReceived == 0){}
    mapSession(sdaBuffer);
    checkSession();

    sdaBuffer[0] = '\0';
    dataReceived = 0;
  }
}