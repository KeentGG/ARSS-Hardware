#define PIC_ADDR 0x40
#define CLK_FREQ 100000

// <SESSION>

unsigned int currTime = 0;
unsigned int hasSession = 0;

char rawCurrTimeStr[24];
char currTimeStr[24];

// </SESSION>

// <LOCAL>

// </LOCAL>

// <DEBUG>

unsigned int debugLogCtr = 0;

// </DEBUG>

#include <Headers/lcd.h>
#include <Headers/connection.h>
#include <Headers/output_strings.h>
#include <Headers/eeprom.h>
#include <Headers/coreSession.h>
#include <Headers/session.h>
#include <Headers/modules.h>

void main(){
  ADCON1 = 0x0F;
  
  I2C_Master_Init(CLK_FREQ);

  outputFreshLCD("init", "");
  while(1){
    clearSession();
    strcpy(sessionMode, "ADD");
    strcpy(sessionData[0], "KEANU");
    strcpy(sessionBlockData, deMapSession(1, 0));

    debug(Ltrim(sessionBlockData));
    i2cSend(0x42, Ltrim(sessionBlockData));
  
    i2cSend(0x44, "Test");
    Delay_ms(400);
    outputFreshLCD("", "");
    Delay_ms(1000);
  }
}