#define PIC_ADDR 0x40
#define CLK_FREQ 100000

// <DEBUG>

unsigned int debugLogCtr = 0;
char ctrStr[10];

// </DEBUG>

#include <Headers/lcd.h>
#include <Headers/connection.h>
#include <Headers/modules.h>

void main(){
  ADCON1 = 0x0F;
  
  UART1_Init(9600);
  
  I2C_Master_Init(CLK_FREQ);

  outputFreshLCD("init", "");
  while(1){
    debug("ADD, 1421615");
    i2cSend(0x44, "ADD, 1421615");
    Delay_ms(400);
    outputFreshLCD("", "");
    Delay_ms(1000);
  }
}