#define _XTAL_FREQ 16000000

void slaveInit(char *ADDR);
void I2C_wait();

void slave_to_master(const unsigned long c)
{
//  while(I2C1_Is_Idle == 0){}
  SSPSTAT = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  SSPCON1 = 0b00001000; //0b00001000;
  SSPCON2 = 0;
  INTCON.GIE = 0;
  INTCON.PEIE = 0;
  PIR1.SSPIF = 0;
  PIE1.SSPIE = 0;
}

void master_to_slave(short address)
{
//  while(I2C1_Is_Idle == 0){}
  SSPSTAT = 0x80;
  SSPADD = address;
  SSPCON1 = 0x16; //E
  SSPCON2 = 0; //0x01
  INTCON.GIE = 1;
  INTCON.PEIE = 1;
  PIR1.SSPIF = 0;
  PIE1.SSPIE = 1;
  SSPCON1.SSPEN = 1;
}

void I2C_Master_Init(const unsigned long c)
{
  SSPCON1 = 0b00001000; //0b00001000; //0b00101000
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  SSPSTAT = 0;
  TRISB.B0 = 1;        //Setting as input as given in datasheet
  TRISB.B1 = 1;        //Setting as input as given in datasheet
  SSPCON1.SSPEN = 1;
}

void I2C_Slave_Init(short address)
{
  SSPSTAT = 0x80;
  SSPADD = address;
  SSPCON1 = 0x16; //E
  SSPCON2 = 0x01; //0x01
  TRISB.B0 = 1;   //Setting as input as given in datasheet
  TRISB.B1 = 1;   //Setting as input as given in datasheet
  INTCON.GIE = 1;
  INTCON.PEIE = 1;
  PIR1.SSPIF = 0;
  PIE1.SSPIE = 1;
  SSPCON1.SSPEN = 1;
}

void i2cWait() {
  while(!SSPIF){}
}

void i2cSend(char slave, char *send_data){
  char n = 0;
  char addrStr[2];
  
  INTCON.GIE = 0;

  while(I2C1_Is_Idle == 0){}
//
  I2C_wait();
  I2C1_Init(100000);
  I2C1_Start();

  I2C_wait();
  I2C1_Wr(slave);

  for(n = 0; send_data[n] != 0; n++){
    I2C_wait();
    I2C1_Wr(send_data[n]);
  }
  I2C_wait();
  I2C1_Wr(';');
  I2C_wait();
  I2C1_Stop();
  I2C_wait();
  INTCON.GIE = 1;
}

void I2C_wait ()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));    // wait for start bit to clear in SSPSTAT and bits 0 to 4 in SSPCON2
}

unsigned short i2cread(char address){
  unsigned short read_data;
  while(I2C1_Is_Idle == 0){}
  I2C_wait();
  I2C1_Init(100000);
  I2C1_Start();
  I2C_wait();
  I2C1_Wr(address + 1);
  I2C_wait();
  read_data = I2C1_Rd(_I2C_NACK);
  I2C_wait();
  I2C1_Stop();
  I2C_wait();
//  I2C_wait();
  return read_data;
}