#define MAX_SESSION_DATA 5
#define MAX_SESSION_DATA_SIZE 32


char sessionMode[MAX_SESSION_DATA_SIZE];
char sessionData[MAX_SESSION_DATA][MAX_SESSION_DATA_SIZE];
char sessionBlockData[MAX_SESSION_DATA*MAX_SESSION_DATA_SIZE];
int hasReceived;
char receive[255];
char delimiter[] = ",";
char EOD[] = ";";
int awaitingUnlock = 0;

char deMapStr[255];

void catStr(char *to, char *str);
char *deMapSession(unsigned int includeMode);

// Clears sessionMode & sessionData variables
void clearSession(){
  unsigned int dataLength;

  dataLength = strlen(sessionData);
  memset(sessionMode, 0, strlen(sessionMode));
  memset(sessionData, 0, MAX_SESSION_DATA * MAX_SESSION_DATA_SIZE);
}

// Maps sessionArray value to its respective variable sessionMode & sessionData
// sessionMode consist of the first block data of the Session Array
// sessionData is an array consisting of one or more block data starting
// from the second block data of the Session Array onwards.
void mapSession(char *sessionArray){
  unsigned int isDone = 0;
  unsigned int dataPtr = 0;

  clearSession();

  strcpy(sessionMode, strtok(sessionArray, delimiter));
  for(dataPtr = 0; isDone == 0; dataPtr++){
    strcpy(sessionData[dataPtr], strtok(0, delimiter));

    if(strlen(sessionData[dataPtr]) == 0){
      isDone = 1;
    }
  }
}

void catByteToStr(char *to, char *byte){
  char byteBuffer[255];
  char bytePartial[3];
  unsigned int i = 0;
  byteBuffer[0]= 0;

  ByteToHex(byte, *byteBuffer);
}

void StrToBcd(char *to, char *str){
   unsigned int strDec;

   strDec = atoi(str);
   to = Dec2Bcd(strDec);
}


// Returns merged sessionMode & sessionData back to its default Session Array format
// sessionMode, ...sessionData;
char *deMapSession(unsigned int includeMode, unsigned int includeEOD){
  char sessionBuffer[255];
  unsigned int dataPtr = 0;
  unsigned int isDone = 0;

  sessionBuffer[0] = '\0';

  if(includeMode == 1){
    catStr(sessionBuffer, sessionMode);
    catStr(sessionBuffer, delimiter);
  }

  for(dataPtr = 0; strlen(sessionData[dataPtr]) != 0; dataPtr++){
    if(dataPtr != 0){
      catStr(sessionBuffer, delimiter);
    }

    catStr(sessionBuffer, sessionData[dataPtr]);
  }

  if(includeEOD == 1){
    catStr(sessionBuffer, EOD);
  }

  return sessionBuffer;
}

// Conctenates two strings together
void catStr(char *to, char *str){
  strcpy(to, strcat(to, str));
}