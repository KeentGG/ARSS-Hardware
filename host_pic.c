#define PIC_ADDR 0x40
#define CLK_FREQ 100000

#include <Headers/lcd.h>
#include <Headers/connection.h>

void main(){
  ADCON1 = 0x0F;
  
  I2C_Master_Init(CLK_FREQ);

  outputFreshLCD("init", "");
  while(1){

     i2cSend(0x44, "Test");
     Delay_ms(400);
     outputFreshLCD("", "");
     Delay_ms(1000);
  }
}