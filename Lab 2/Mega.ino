//#include <tasks.h>
//#include <TCB.h>
// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <stdlib.h>
//#include <tasks.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

/*----------------------------------------Struct-----------------------------------------------*/
struct MyStruct 
{ 
    void (*myTask)(void*);  
    void* taskDataPtr; 
}; 
typedef struct MyStruct TCB;

struct computeStruct{
    unsigned int* temperatureRawPtr;
    unsigned int* systolicPressRawPtr;
    unsigned int* diastolicPressRawPtr;
    unsigned int* pulseRateRawPtr;
    double* tempCorrectedPtr;
    double* sysCorrectedPtr;
    double* diasCorrectedPtr;
    double* prCorrectedPtr;
};
typedef struct computeStruct dataCompute;

//struct computeStruct dataCompute = {&tempR, &sysPreR, &diaPreR, &pulseR, &tempC, &sysPreC, &diaPreC, &pulseC};
//struct computeStruct *computePtr = &dataToCompute;


struct statusStruct{
        unsigned short* batteryStatePtr;
 };
    typedef struct statusStruct dataStatus;
//struct statusStruct statusState = {&battery};
//struct computeStruct *statusPtr = &statusState;



struct displayStruct{
    double* tempCorrectedPtr;
    double* sysCorrectedPtr;
    double* diasCorrectedPtr;
    double* prCorrectedPtr;
    unsigned short* batteryStatePtr;
};
typedef struct displayStruct dataDisplay;
//struct displayStruct dataToDis = { &tempC, &sysPreC, &diaPreC, &pulseC, &battery};
//struct displayStruct *displayPtr = &dataToDis;

struct warningAlarmStruct{
    int *tempWarningPtr;
    int *sysWarningPtr;
    int *diasWarningPtr;
    int *bpWarningPtr;
    int *batteryWarningPtr;
};
typedef struct warningAlarmStruct dataWarningAlarm;
//struct warningAlarmStruct warningState = {&tempWarning, &sysWarning, &diasWarning, &bpWarning, &batteryWarning};
//struct warningAlarmStruct *warningPtr = &warningState;

struct measureStruct{
    unsigned int* temperatureRawPtr;
    unsigned int* systolicPressRawPtr;
    unsigned int* diastolicPressRawPtr;
    unsigned int* pulseRateRawPtr;
};
    typedef struct measureStruct dataMeasure;

//struct measureStruct dataMeasure = {&tempR, &sysPreR, &diaPreR, &pulseR};
//struct measureStruct *measurePtr = &dataMeasure;

//struct displayStruct dataToDis = {&tempC, &sysPreC, &diaPreC, &pulseC, &battery};
//struct displayStruct *displayPtr = &dataToDis;
/*----------------------------------------------------------------------*/


/*-----------------------------------------------Globle Variable---------------*/
unsigned int tempR = 75;
unsigned int sysPreR = 80;
unsigned int diaPreR = 80;
unsigned int pulseR = 50;
unsigned short battery = 200;
double tempC = 0;
double sysPreC = 0;
double diaPreC = 50;
double pulseC = 50;
//long mCount = 0;
//int sysComp = 1;
//int measComp = 1;
//int pComp = 1;
unsigned int globalDelay = 0;
int tempWarning = 0;
int sysWarning = 0;
int diasWarning = 0;
int bpWarning = 0;
int batteryWarning =0;
TCB queue[5];
TCB M;
TCB C;
TCB W;
TCB D;
TCB S;

dataMeasure measureState = {&tempR, &sysPreR, &diaPreR, &pulseR};
dataCompute computeState= {&tempR, &sysPreR, &diaPreR, &pulseR, &tempC, &sysPreC, &diaPreC, &pulseC};
dataStatus statusState = {&battery};
dataWarningAlarm warningState = {&tempWarning, &sysWarning, &diasWarning, &bpWarning, &batteryWarning};
dataDisplay displayState = {&tempC, &sysPreC, &diaPreC, &pulseC, &battery};
dataDisplay *displayPtr = &displayState;

/*---------------------------Dispaly Function----------------------------------  */
void display1(void* displayPtr){
   displayStruct* dataToDis = (displayStruct*) displayPtr;
   tft.fillScreen(BLACK);
   unsigned long start = micros();
   tft.setCursor(0, 0);
   tft.setTextColor(GREEN); 
   tft.setTextSize(2);
   if(tempWarning == 1){
      tft.setTextColor(RED);  
   }else{
      tft.setTextColor(GREEN); 
   }
   tft.print("Temperature:");
   tft.setCursor(0,20);
   tft.print(*(dataToDis->tempCorrectedPtr));
   if(sysWarning == 1){
      tft.setTextColor(RED);  
   }else{
      tft.setTextColor(GREEN); 
   }
   tft.setCursor(0,40);
   tft.print("Systolic Pressure:");
   tft.setCursor(0,60);
   tft.print(*(dataToDis->sysCorrectedPtr));
   if(diasWarning == 1){
      tft.setTextColor(RED);  
   }else{
      tft.setTextColor(GREEN); 
   }
   tft.setCursor(0,80);
   tft.print("Diastolic Pressure:");
   tft.setCursor(0,100);
   tft.print(*(dataToDis->diasCorrectedPtr));
   if(bpWarning == 1){
      tft.setTextColor(RED);  
   }else{
      tft.setTextColor(GREEN); 
   }
   tft.setCursor(0,120);
   tft.print("Pulse rate:");
   tft.setCursor(0,140);
   tft.print(*(dataToDis->prCorrectedPtr));
   if(batteryWarning == 1){
      tft.setTextColor(RED);  
   }else{
      tft.setTextColor(GREEN); 
   }
   tft.setCursor(0,160);
   tft.print("Battery:");
   tft.setCursor(0,180);
   tft.print(*(dataToDis->batteryStatePtr));
}
/*-----------------------------------------------------------------------------------*/

  
void setup(void) {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println(F("TFT LCD test"));


#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

   uint16_t identifier = tft.readID();
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial1.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x1111)
  {     
      identifier=0x9328;
       Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9328;
  
  }
  tft.begin(identifier);

  M = {&measureTask, &measureState};
  C = {&computeTask, &computeState};
  W = {&warning, &warningState};
  S = {&statusTask, &statusState};
  D = {&display1, &displayState};

//  M.myTask = &measureTask;
//  M.taskDataPtr = &dataMeasure;
//  C.myTask = &computeTask;
//  C.taskDataPtr = &dataCompute;
//  W.myTask = &measureTask;
//  W.taskDataPtr = &dataMeasure;
//  S.myTask = &measureTask;
//  S.taskDataPtr = &dataMeasure;
//  D.myTask = &measureTask;
//  D.taskDataPtr = &dataMeasure;
  queue[0] = M;
  queue[1] = C;
  queue[2] = W;
  queue[3] = S;
  queue[4] = D;
}




void loop(void) {
//  tempWarning = Serial1.parseInt();
//  sysWarning = Serial1.parseInt();
//  diaWarning = Serial1.parseInt();
//  pulseWarning = Serial1.parseInt();
//  batteryWarning = Serial1.parseInt();
  unsigned int globalCounter = 0;
 
 
 
 

  
  

 schedulerTask(queue);
}
