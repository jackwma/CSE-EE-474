#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <stdio.h>
#include <stdlib.h>

#include "tasks.h"
#include "taskFunctions.h"

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int calls = 0;
Bool tempReverse = FALSE;
Bool systolicDone = FALSE;
Bool diastolicDone = FALSE;
Bool pulseReverse = FALSE;

void measureTask(void* measureData){ //
    dataMeasure* data = (dataMeasure*)measureData;
    if(calls%2 == 0){
        if(tempReverse){
            *(data->temperatureRawPtr) -= 2;
        }
        else{
            *(data->temperatureRawPtr) += 2;
        }
        *(data->systolicPressRawPtr) += 3;
	*(data->diastolicPressRawPtr) -= 2;
        if(pulseReverse){
            *(data->pulseRateRawPtr) += 1;
        }
        else{
            *(data->pulseRateRawPtr) -= 1;
        }
    }
    if(calls%2 == 1){
        if(tempReverse){
            *(data->temperatureRawPtr) += 1;
        }
        else{
            *(data->temperatureRawPtr) -= 1;
        }
        *(data->systolicPressRawPtr) -= 1;
	*(data->diastolicPressRawPtr) += 1;
        if(pulseReverse){
            *(data->pulseRateRawPtr) -= 3;
        }
        else{
            *(data->pulseRateRawPtr) += 3;
        }
    }
    if(*(data->temperatureRawPtr) > 50) {
        tempReverse = TRUE;
    }
    else if(*(data->temperatureRawPtr) < 0){
        tempReverse = FALSE;
    }
    if(*(data->pulseRateRawPtr) > 40) {
        pulseReverse = TRUE;
    }
    else if(*(data->pulseRateRawPtr) < 15){
        pulseReverse = FALSE;
    }

    if(*(data->systolicPressRawPtr) > 100){
	systolicDone = TRUE;
    }
    if(*(data->diastolicPressRawPtr) < 40){
	diastolicDone = TRUE;
    }
    if(systolicDone && diastolicDone){
	*(data->systolicPressRawPtr) = 80;
	*(data->diastolicPressRawPtr) = 80;
    }
}

void computeTask(void* computeData){ //
    dataCompute* data = (dataCompute*)computeData;
    *(data->tempCorrectedPtr) = 5+0.75*(*(data->temperatureRawPtr));
    *(data->sysCorrectedPtr) = 9+2*(*(data->systolicPressRawPtr));
    *(data->diasCorrectedPtr) = 6+1.5*(*(data->diastolicPressRawPtr));
    *(data->prCorrectedPtr) = 8+3*(*(data->pulseRateRawPtr));
}

void setup(void) {
  Serial.begin(9600);
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
    Serial.println(F("Found LGDP4535 LCD driver"));
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
}

void displayTask(void* displayData){ //
    dataDisplay* data = (dataDisplay*)displayData;
    tft.fillScreen(0x0000);
    tft.setCursor(0, 0);

    tft.setTextColor(0x07E0);
    tft.setTextSize(2);

    if (*(data->sysCorrectedPtr) != 120){
        tft.setTextColor(0xF800);
    }
    tft.print("Systolic pressure: "); 
    tft.print(*(data->sysCorrectedPtr));
    tft.print("mm Hg");
    tft.setTextColor(0x07E0);
    if (*(data->diasCorrectedPtr) != 120){
            tft.setTextColor(0xF800);
    }
    tft.print("  Diastolic pressure: ");
    tft.print(*(data->diasCorrectedPtr));
    tft.println(" mm Hg");
    tft.setTextColor(0x07E0);
    if (*(data->tempCorrectedPtr) < 36.1 || *(data->tempCorrectedPtr) > 37.8 ){
            tft.setTextColor(0xF800);
    }
    tft.print("Temperature: ");
    tft.print(*(data->tempCorrectedPtr));
    tft.print(" C"); 
    tft.setTextColor(0x07E0);
    if (*(data->prCorrectedPtr) < 60 || *(data->prCorrectedPtr) > 100 ){
            tft.setTextColor(0xF800);
    }
    tft.print("Pulse rate: ");
    tft.print(*(data->prCorrectedPtr));
    tft.print(" BPM"); 
    tft.setTextColor(0x07E0);
    if (*(data->batteryStatePtr) <= 20){
            tft.setTextColor(0xF800);
    }
    tft.print("Battery: ");
    tft.print(*(data->batteryStatePtr));
}

void warningAlarmTask(void* warningAlarmData){ //
    dataWarningAlarm* dataptr = (dataWarningAlarm*)warningAlarmData;
    dataWarningAlarm data = *dataptr;

}

void statusTask(void* statusData){ //
    dataStatus* data = (dataStatus*)statusData;;
    *(data->batteryStatePtr) -= 1;
}

void schedulerTask(void* scheduleData, unsigned long int gs){
    dataScheduler* data = (dataScheduler*)scheduleData;
    data->mTCBPtr->measureTask(data->mTCBPtr->measureDataPtr);
    data->cTCBPtr->computeTask(data->cTCBPtr->computeDataPtr);
    data->dTCBPtr->displayTask(data->dTCBPtr->displayDataPtr);
    data->wTCBPtr->warningAlarmTask(data->wTCBPtr->warningAlarmDataPtr);
    data->sTCBPtr->statusTask(data->wTCBPtr->warningAlarmDataPtr);
}
