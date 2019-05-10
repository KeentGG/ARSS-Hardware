// <DEBUG>
char lowYearBCD;
unsigned int lowYear;

char rawLowYearStr[8];
char lowYearStr[8];
// </DEBUG>

void Zero_Fill(char *value) {    // fill text repesentation
  if (value[1] == 0) {           //      with leading zero
    value[1] = value[0];
    value[0] = 47;
    value[2] = 0;
  }
}//~

//--------------------- Reads time and date information from RTC (DS1307)
void Read_Time(char *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year) {
  INTCON.GIE = 0;
  I2C1_Start();
  I2C1_Wr(0xD0);
//  debug("i2c");
  I2C1_Wr(0);
  I2C1_Repeated_Start();
  I2C1_Wr(0xD1);
  *sec =I2C1_Rd(1);
  *min =I2C1_Rd(1);
  *hr =I2C1_Rd(1);
  *week_day =I2C1_Rd(1);
  *day =I2C1_Rd(1);
  *mn =I2C1_Rd(1);
  *year =I2C1_Rd(0);

  I2C1_Stop();
  INTCON.GIE = 1;
}//~

//-------------------- Formats date and time
void Transform_Time(char  *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year) {
  *sec  =  ((*sec & 0x70) >> 4)*10 + (*sec & 0x0F);
  *min  =  ((*min & 0xF0) >> 4)*10 + (*min & 0x0F);
  *hr   =  ((*hr & 0x30) >> 4)*10 + (*hr & 0x0F);
  *week_day =(*week_day & 0x07);
  *day  =  ((*day & 0xF0) >> 4)*10 + (*day & 0x0F);
  *mn   =  ((*mn & 0x10) >> 4)*10 + (*mn & 0x0F);
  *year =  ((*year & 0xF0)>>4)*10+(*year & 0x0F);
}//~

//-------------------- Output values to LCD


//------------------ Performs project-wide init

void DS107_Write(){
  I2C1_Start();              // issue I2C start signal
  I2C1_Wr(0xD0);             // send byte via I2C  (device address + W)
  I2C_wait();
  I2C1_Wr(0x30);             // second
  I2C_wait();
  I2C1_Wr(0x20);             // minute
  I2C_wait();
  I2C1_Wr(0x10);             // hour
  I2C_wait();
  I2C1_Wr(0x01);             // Weekday
  I2C_wait();
  I2C1_Wr(0x28);             // day
  I2C_wait();
  I2C1_Wr(0x08);             // month
  I2C_wait();
  I2C1_Wr(0x20);             // year
  I2C_wait();
  I2C1_Wr(0x19);
  I2C_wait();
  I2C1_Stop();               // issue I2C stop signal
  Delay_100ms();
}