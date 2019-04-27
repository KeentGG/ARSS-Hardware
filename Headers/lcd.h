sbit LCD_RS at RA5_bit;
sbit LCD_EN at RA4_bit;
sbit LCD_D4 at RA3_bit;
sbit LCD_D5 at RA2_bit;
sbit LCD_D6 at RA1_bit;
sbit LCD_D7 at RA0_bit;

sbit LCD_RS_Direction at TRISA5_bit;
sbit LCD_EN_Direction at TRISA4_bit;
sbit LCD_D4_Direction at TRISA3_bit;
sbit LCD_D5_Direction at TRISA2_bit;
sbit LCD_D6_Direction  at TRISA1_bit;
sbit LCD_D7_Direction at TRISA0_bit;

void outputFreshLCD(char *line1, char *line2){
  Lcd_Init();
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1,1,line1);
  Lcd_Out(2,1,line2);
  Delay_ms(20);
}