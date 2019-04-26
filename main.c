#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <task.h>

unsigned int temperatureRaw = 75;
unsigned int systolicPressRaw = 80;
unsigned int diastolicPressRaw = 80;
unsigned int pulseRateRaw = 50;
long mCount = 0;
int sysComp = 1;
int measComp = 1;
int pComp = 1;


void measureTask(void* measureData) {
    struct measureStruct dataMeasure = {&temperatureRaw, &systolicPressRaw, &diastolicPressRaw, &pulseRateRaw};
    struct measureStruct *measurePtr = &dataMeasure;
    if (mCount%2 == 0){
        if (measComp) {
            *(dataMeasure.temperatureRawPtr) +=2;
        }else {
            *(dataMeasure.temperatureRawPtr) -= 2;
        }
    } else {
        if (measComp) {
            *(dataMeasure.temperatureRawPtr) +=1;
        }else {
            *(dataMeasure.temperatureRawPtr) -=1;
        }
    }
    if (temperatureRaw > 50) {
        measComp = 0;
    } else if (temperatureRaw < 15){
        measComp = 1;
    }

    if (!sysComp) {
        if(mCount%2 ==0) {
            *(dataMeasure.systolicPressRaw) +=3;
        } else {
            *(dataMeasure.systolicPressRaw) -=1;
        }
        if(systolicPressRaw > 100) {
            sysComp = 1;
            *(dataMeasure.systolicPressRaw) = 80;
        }
    } else {
        if(mCount%2 ==0) {
            *(dataMeasure.diastolicPressRaw) +=2;
        } else {
            *(dataMeasure.diastolicPressRaw) -=1;
        }
        if(diastolicPressRaw < 40) {
            sysComp = 1;
            *(dataMeasure.diastolicPressRaw) = 80;
        }
    }

    if (mCount%2 == 0){
        if (pComp) {
            *(dataMeasure.pulseRateRawPtr) -=1;
        }else {
            *(dataMeasure.pulseRateRawPtr) +=1;
        }
    } else {
        if (pComp) {
            *(dataMeasure.pulseRateRawPtr) +=3;
        }else {
            *(dataMeasure.pulseRateRawPtr) -=3;
        }
    }
    if (pulseRateRaw > 40) {
        measComp = 0;
    } else if (temperatureRaw < 15){
        measComp = 1;
    }
    mCount+=1;
}


        
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

void compute(struct computeStruct *ComputePtr){
    *(ComputePtr -> tempCorrectedPtr) = *(ComputePtr -> temperatureRawPtr) * 0.75 +5;
    *(ComputePtr -> sysCorrectedPtr) = *(ComputePtr -> systolicPressRawPtr) * 9 +2;
    *(ComputePtr -> diasCorrectedPtr) = *(ComputePtr -> diastolicPressRawPtr) * 1.5 +6;
    *(ComputePtr -> prCorrectedPtr) = *(ComputePtr -> pulseRateRawPtr) * 3 +8;
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
    struct computeStruct dataCompute = {&tempR, &sysPreR, &diaPreR, &pulseR, &tempC, &sysPreC, &diaPreC, &pulseC};
    struct computeStruct *computePtr = &dataCompute;
    compute(computePtr);
    printf("corrected temperature：%f\n", *(dataCompute.tempCorrectedPtr));
    printf("corrected sPressure：%f\n", *(dataCompute.sysCorrectedPtr));
    printf("corrected dPressure：%f\n", *(dataCompute.diasCorrectedPtr));
    printf("corrected pulse：%f\n", *(dataCompute.prCorrectedPtr));
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

