#define PIC_ADDR 0x44
#define CLK_FREQ 100000


// <SESSION>
unsigned long int currTime = 0;
unsigned int hasSession = 0;
unsigned int userExpEpoch = 0;

char rawCurrTimeStr[24];
char currTimeStr[24];
char userExpEpochStr[24];
// </SESSION>


// <INTERRUPT>
char sdaBuffer[64];
unsigned int sdaPtr = 0;
unsigned int dataReceived = 0;
char j;
unsigned int timerCounter = 0;
unsigned int intFromTimer = 0;
// </INTERRUPT>

// <RFID>
char msg[12];
char UID[6];
unsigned TagType;
char size;
char i;
char blockfour[255];
char serialId[24];
char storedSerialId[24];
// </RFID>

#include <Built_in.h>
#include <Headers/lcd.h>
#include <Headers/connection.h>
#include <Headers/output_strings.h>
#include <Headers/eeprom.h>
#include <Headers/coreSession.h>
#include <Headers/session.h>
#include <Headers/modules.h>
#include <Headers/mfrc522.h>

void interrupt(){
  isr();
}

void main(){
  ADCON1 = 0x0F;

  Soft_SPI_Init();
  MFRC522_Init();
  I2C_Slave_Init(0x44);

  outputFreshLCD("init", "");
  
  while(1){
    while(dataReceived == 0){
      if( MFRC522_isCard( &TagType ) ){
        serialId[0] = '\0';
        if( MFRC522_ReadCardSerial( &UID ) ) {
          for( i=0; i < 5; i++) {
            ByteToHex( UID[i], msg );
            catStr(serialId, msg);
          }
          MFRC522_Halt();
          getEEPROM(storedSerialId, 0x00);
          if(strcmp(storedSerialId, serialId) == 0){
            getEEPROM(userExpEpochStr, 0x0C);
            userExpEpoch = atol(userExpEpochStr);
            if(currTime > userExpEpoch){
              outputFreshLCD("Expired session", "Please settle overdue");
            }else{
              outputFreshLCD("Unlocking unit", "");
            }
          }else{
            outputFreshLCD("Serial not match", "");
          }
        }
      }
    }
    mapSession(sdaBuffer);
    checkSession();
    sdaBuffer[0] = '\0';
    dataReceived = 0;
  }
}