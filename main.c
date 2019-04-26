#include <stdio.h>
#include <time.h>
#include <stdlib.h>

unsigned tempR = 30;
unsigned sysPreR = 50;
unsigned diaPreR = 50;
unsigned pulseR = 70;
unsigned short battery = 200;
double tempC = 0;
double sysPreC = 0;
double diaPreC = 50;
double pulseC = 50;
long mCount = 0;
int sysComp = 1;
int measComp = 1;
int pComp = 1;


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
struct computeStruct dataToCompute = {&tempR, &sysPreR, &diaPreR, &pulseR, &tempC, &sysPreC, &diaPreC, &pulseC};
struct computeStruct *computePtr = &dataToCompute;


struct displayStruct{
    double* tempCorrectedPtr;
    double* sysCorrectedPtr;
    double* diasCorrectedPtr;
    double* prCorrectedPtr;
    unsigned short* batteryStatePtr;
};
struct displayStruct dataToDis = { &tempC, &sysPreC, &diaPreC, &pulseC, &battery};
struct displayStruct *displayPtr = &dataToDis;



void compute(){
    *(computePtr -> tempCorrectedPtr) = *(computePtr -> temperatureRawPtr) * 0.75 +5;
    *(computePtr -> sysCorrectedPtr) = *(computePtr -> systolicPressRawPtr) * 9 +2;
    *(computePtr -> diasCorrectedPtr) = *(computePtr -> diastolicPressRawPtr) * 1.5 +6;
    *(computePtr -> prCorrectedPtr) = *(computePtr -> pulseRateRawPtr) * 3 +8;
}


void display(){
    printf("Temperature:");
    tft.print(*(dataToDis.tempCorrectedPtr));
    printf("Systolic Pressure:");
    ftf.print(*(dataToDis.sysCorrectedPtr));
    printf("Diastolic Pressure:");
    tft.print(*(dataToDis.diasCorrectedPtr));
    printf("Pulse rate:");
    tft.print(*(dataToDis.prCorrectedPtr));
    printf("Battery:");
    tft.print(*(dataToDis.batteryStatePtr));
}


int tempWarning = 0;
int  sysWarning = 0;
int  diasWarning = 0;
int  bpWarning = 0;
int  batteryWarning =0;

struct warningAlarmStruct{
    int *tempWarningPtr;
    int *sysWarningPtr;
    int *diasWarningPtr;
    int *bpWarningPtr;
    int *batteryWarningPtr;
};
struct warningAlarmStruct warningState = {&tempWarning, &sysWarning, &diasWarning, &bpWarning, &batteryWarning};
struct warningAlarmStruct *warningPtr = &warningState;

struct measureStruct{
    unsigned int* temperatureRawPtr;
    unsigned int* systolicPressRawPtr;
    unsigned int* diastolicPressRawPtr;
    unsigned int* pulseRateRawPtr;
};

struct measureStruct dataMeasure = {&tempR, &sysPreR, &diaPreR, &pulseR};
struct measureStruct *measurePtr = &dataMeasure;



void warning(){
    if(*(dataMeasure.temperatureRawPtr)>=36.1 && *(dataMeasure.temperatureRawPtr)<=37.8){
        *(warningPtr -> tempWarningPtr) = 0;
    }else{
        *(warningPtr -> tempWarningPtr) = 1;
    }
    if(*(dataMeasure.systolicPressRawPtr) >= 120){
        *(warningPtr ->sysWarningPtr) = 0;
    }else{
        *(warningPtr ->sysWarningPtr) = 1;
    }
    if(*(dataMeasure.diastolicPressRawPtr) >= 80){
        *(warningPtr -> diasWarningPtr) = 0;
    }else{
        *(warningPtr -> diasWarningPtr) = 1;
    }
    if(*(dataMeasure.pulseRateRawPtr)>=60 && *(dataMeasure.pulseRateRawPtr)<=100){
        *(warningPtr -> bpWarningPtr) = 0;

    }else{
        *(warningPtr -> bpWarningPtr) = 1;
    }
    if(battery>= 0.2*200){
        *(warningPtr -> batteryWarningPtr) = 0;
    }else{
        *(warningPtr -> batteryWarningPtr) = 1;
    }
}










void measureTask() {

    if (mCount%2 == 0){
        if (measComp) {
            *(measurePtr -> temperatureRawPtr) +=2;
        }else {
            *(measurePtr -> temperatureRawPtr) -=2;
        }
    } else {
        if (measComp) {
            *(measurePtr -> temperatureRawPtr) +=1;
        }else {
            *(measurePtr -> temperatureRawPtr) -=1;
        }
    }
    if (*(dataMeasure.temperatureRawPtr) > 50) {
        measComp = 0;
    } else if (*(dataMeasure.temperatureRawPtr) < 15){
        measComp = 1;
    }

    if (!sysComp) {
        if(mCount%2 ==0) {
            *(measurePtr -> systolicPressRawPtr) +=3;
        } else {
            *(measurePtr -> systolicPressRawPtr) -=1;
        }
        if(*(dataMeasure.systolicPressRawPtr) > 100) {
            sysComp = 1;
            *(measurePtr -> systolicPressRawPtr) = 80;
        }
    } else {
        if(mCount%2 ==0) {
            *(measurePtr -> diastolicPressRawPtr) +=2;
        } else {
            *(measurePtr -> diastolicPressRawPtr) -=1;
        }
        if(*(dataMeasure.diastolicPressRawPtr) < 40) {
            sysComp = 1;
            *(measurePtr -> diastolicPressRawPtr) = 80;
        }
    }

    if (mCount%2 == 0){
        if (pComp) {
            *(measurePtr -> pulseRateRawPtr) -=1;
        }else {
            *(measurePtr -> pulseRateRawPtr) +=1;
        }
    } else {
        if (pComp) {
            *(measurePtr -> pulseRateRawPtr) +=3;
        }else {
            *(measurePtr -> pulseRateRawPtr) -=3;
        }
    }
    if (*(dataMeasure.pulseRateRawPtr) > 40) {
        measComp = 0;
    } else if ( *(dataMeasure.pulseRateRawPtr)< 15){
        measComp = 1;
    }
    mCount+=1;
}

int main() {
    unsigned tempR = 30;
    unsigned sysPreR = 50;
    unsigned diaPreR = 50;
    unsigned pulseR = 70;
    double tempC = 0;
    double sysPreC = 0;
    double diaPreC = 50;
    double pulseC = 50;
    struct computeStruct *computePtr = &dataCompute;
    compute(computePtr);
    printf("corrected temperature：%f\n", *(dataCompute.tempCorrectedPtr));
    printf("corrected sPressure：%f\n", *(dataCompute.sysCorrectedPtr));
    printf("corrected dPressure：%f\n", *(dataCompute.diasCorrectedPtr));
    printf("corrected pulse：%f\n", *(dataCompute.prCorrectedPtr));
}



