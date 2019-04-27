// GENERAL

const char txt1[] = "PIC 2";
const char txt2[] = "INITIALIZING";

const char waiting[] = "WAITING FROM PIC 1";
const char pressed[] = "PRESSED FROM PIC 1";

unsigned int hasTapCard = 0;

char counterStr[4];
char sdaBuffer[64];
unsigned int sdaPtr = 0;
unsigned int dataReceived = 0;
char j;

char unitNumBootMsg[32];

char unitNum[4];

unsigned int hasPrevSession = 0;

// MAIN


// - Unit -

// -- Unit - Logic --

unsigned int hasSession = 0;

// - Code -

// -- Code - Interrupt --



// -- Code - RFID --

