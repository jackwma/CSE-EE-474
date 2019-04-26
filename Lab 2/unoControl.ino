#include <stdlib.h>
//#include <tasks.h>
//#include <TCB.h>
/*----------------Global Variables-------------------------*/
//unsigned tempR = 30;
//unsigned sysPreR = 50;
//unsigned diaPreR = 50;
//unsigned pulseR = 70;
//unsigned short battery = 200;
//double tempC = 0;
//double sysPreC = 0;
//double diaPreC = 50;
//double pulseC = 50;
long mCount = 0;
int sysComp = 1;
int measComp = 1;
int pComp = 1;
//unsigned int globalDelay = 0;
//int tempWarning = 0;
//int sysWarning = 0;
//int diasWarning = 0;
//int bpWarning = 0;
//int batteryWarning =0;
/*--------------------------------------------------------------------*/

/*----------------------------Structs------------------------------*/
//struct computeStruct{
//    unsigned int* temperatureRawPtr;
//    unsigned int* systolicPressRawPtr;
//    unsigned int* diastolicPressRawPtr;
//    unsigned int* pulseRateRawPtr;
//    double* tempCorrectedPtr;
//    double* sysCorrectedPtr;
//    double* diasCorrectedPtr;
//    double* prCorrectedPtr;
//};
////struct computeStruct dataCompute = {&tempR, &sysPreR, &diaPreR, &pulseR, &tempC, &sysPreC, &diaPreC, &pulseC};
////struct computeStruct *computePtr = &dataToCompute;
//
//
//struct statusStruct{
//        unsigned short* batteryStatePtr;
// };
//    typedef struct statusStruct dataStatus;
//struct statusStruct statusState = {&battery};
//struct computeStruct *statusPtr = &statusState;
//
//
//
//struct displayStruct{
//    double* tempCorrectedPtr;
//    double* sysCorrectedPtr;
//    double* diasCorrectedPtr;
//    double* prCorrectedPtr;
//    unsigned short* batteryStatePtr;
//};
////struct displayStruct dataToDis = { &tempC, &sysPreC, &diaPreC, &pulseC, &battery};
////struct displayStruct *displayPtr = &dataToDis;
//
//struct warningAlarmStruct{
//    unsigned int* temperatureRawPtr;
//    unsigned int* systolicPressRawPtr;
//    unsigned int* diastolicPressRawPtr;
//    unsigned int* pulseRateRawPtr;
//    int *tempWarningPtr;
//    int *sysWarningPtr;
//    int *diasWarningPtr;
//    int *bpWarningPtr;
//    int *batteryWarningPtr;
//};
////struct warningAlarmStruct warningState = {&tempWarning, &sysWarning, &diasWarning, &bpWarning, &batteryWarning};
////struct warningAlarmStruct *warningPtr = &warningState;
//
//struct measureStruct{
//    unsigned int* temperatureRawPtr;
//    unsigned int* systolicPressRawPtr;
//    unsigned int* diastolicPressRawPtr;
//    unsigned int* pulseRateRawPtr;
//};
////struct measureStruct dataMeasure = {&tempR, &sysPreR, &diaPreR, &pulseR};
////struct measureStruct *measurePtr = &dataMeasure;

/*-----------------------------------------------------------------*/


/*---------------------------------------Measure-------------------------------*/
//int calls = 0;
//bool tempReverse = false;
//bool systolicDone = false;
//bool diastolicDone = false;
//bool pulseReverse = false;
//
//void measureTask(void* measurePtr){ //
//    dataMeasure* data = (dataMeasure*)measurePtr;
//    if(calls%2 == 0){
//        if(tempReverse){
//            *(data->temperatureRawPtr) -= 2;
//        }
//        else{
//            *(data->temperatureRawPtr) += 2;
//        }
//        *(data->systolicPressRawPtr) += 3;
//      *(data->diastolicPressRawPtr) -= 2;
//        if(pulseReverse){
//            *(data->pulseRateRawPtr) += 1;
//        }
//        else{
//            *(data->pulseRateRawPtr) -= 1;
//        }
//    }
//    if(calls%2 == 1) {
//        if(tempReverse) {
//            *(data->temperatureRawPtr) += 1;
//        }
//        else{
//            *(data->temperatureRawPtr) -= 1;
//        }
//        *(data->systolicPressRawPtr) -= 1;
//      *(data->diastolicPressRawPtr) += 1;
//        if(pulseReverse) {
//            *(data->pulseRateRawPtr) -= 3;
//        }
//        else {
//            *(data->pulseRateRawPtr) += 3;
//        }
//    }
//    if(*(data->temperatureRawPtr) > 50) {
//        tempReverse = true;
//    }
//    else if(*(data->temperatureRawPtr) < 0) {
//        tempReverse = false;
//    }
//    if(*(data->pulseRateRawPtr) > 40) {
//        pulseReverse = true;
//    }
//    else if(*(data->pulseRateRawPtr) < 15) {
//        pulseReverse = false;
//    }
//
//    if(*(data->systolicPressRawPtr) > 100) {
//    systolicDone = true;
//    }
//    if(*(data->diastolicPressRawPtr) < 40) {
//    diastolicDone = true;
//    }
//    if(systolicDone && diastolicDone) {
//    *(data->systolicPressRawPtr) = 80;
//    *(data->diastolicPressRawPtr) = 80;
//    }
//}
void measureTask(void* measurePtr){
    measureStruct* data = (measureStruct*) measurePtr;
    if (mCount%2 == 0){
        if (measComp) {
            *(data -> temperatureRawPtr) +=2;
        }else {
            *(data -> temperatureRawPtr) -=2;
        }
    } else {
        if (measComp) {
            *(data -> temperatureRawPtr) +=1;
        }else {
            *(data -> temperatureRawPtr) -=1;
        }
    }
    if (*(data->temperatureRawPtr) > 50) {
        measComp = 0;
    } else if (*(data->temperatureRawPtr) < 15){
        measComp = 1;
    }

    if (!sysComp) {
        if(mCount%2 ==0) {
            *(data -> systolicPressRawPtr) +=3;
        } else {
            *(data -> systolicPressRawPtr) -=1;
        }
        if(*(data->systolicPressRawPtr) > 100) {
            sysComp = 1;
            *(data -> systolicPressRawPtr) = 80;
        }
    } else {
        if(mCount%2 ==0) {
            *(data -> diastolicPressRawPtr) -=2;
        } else {
            *(data -> diastolicPressRawPtr) +=1;
        }
        if(*(data->diastolicPressRawPtr) < 40) {
            sysComp = 0;
            *(data -> diastolicPressRawPtr) = 80;
        }
    }

    if (mCount%2 == 0){
        if (pComp) {
            *(data -> pulseRateRawPtr) -=1;
        }else {
            *(data -> pulseRateRawPtr) +=1;
        }
    } else {
        if (pComp) {
            *(data -> pulseRateRawPtr) +=3;
        }else {
            *(data -> pulseRateRawPtr) -=3;
        }
    }
    if (*(data->pulseRateRawPtr) > 40) {
        pComp = 0;
    } else if ( *(data->pulseRateRawPtr)< 15){
        pComp = 1;
    }
    mCount+=1;
}
/*---------------------------------------------------------------------*/


/*----------------------------------Compute-----------------------*/
void computeTask(void *computePtr){
    computeStruct* data = (computeStruct*)computePtr;
    *(data -> tempCorrectedPtr) = *(data -> temperatureRawPtr) * 0.75 +5;
    *(data -> sysCorrectedPtr) = *(data -> systolicPressRawPtr) * 2 +9;
    *(data -> diasCorrectedPtr) = *(data -> diastolicPressRawPtr) * 1.5 +6;
    *(data -> prCorrectedPtr) = *(data -> pulseRateRawPtr) * 3 +8;
}
/*------------------------------------------------------------------------------------*/


/*---------------------------------------Warning--------------------------------------------------------------------------------*/
void warning(void *warningPtr){
    warningAlarmStruct* data = (warningAlarmStruct*)warningPtr;
    if(tempR>36.1 && tempR<37.8){
        *(data -> tempWarningPtr) = 0;
    }else{
        *(data -> tempWarningPtr) = 1;
    }
    if(sysPreR >= 120){
        *(data ->sysWarningPtr) = 0;
    }else{
        *(data ->sysWarningPtr) = 1;
    }
    if(diaPreR >= 80){
        *(data -> diasWarningPtr) = 0;
    }else{
        *(data -> diasWarningPtr) = 1;
    }
    if(pulseR>=60 && pulseR<=100){
        *(data -> bpWarningPtr) = 0;

    }else{
        *(data -> bpWarningPtr) = 1;
    }
    if(battery <=40){
        *(data -> batteryWarningPtr) = 1;
    }else{
        *(data -> batteryWarningPtr) = 0;
    }
}
/*------------------------------------------------------------------------------------------------*/


/*****************************************TCB****************************************************/
//struct MyStruct 
//{ 
//    void (*myTask)(void*);  
//    void* taskDataPtr; 
//}; 
//typedef struct MyStruct TCB; 
//
//struct measureTCB
//{
//    void (*measureTask)(void*);
//    void* measureDataPtr;
//};
//typedef struct measureTCB measure;
//
//struct computeTCB
//{
//    void (*computeTask)(void*);
//    void* computeDataPtr;
//};
//typedef struct computeTCB compute;
//
//struct displayTCB
//{
//    void (*displayTask)(void*);
//    void* displayDataPtr;
//};
//typedef struct displayTCB display;
//
//struct warningAlarmTCB
//{
//    void (*warningAlarmTask)(void*);
//    void* warningAlarmDataPtr;
//};
//typedef struct warningAlarmTCB warningAlarm;
//
//struct statusTCB
//{
//    void (*statusTask)(void*);
//    void* statusDataPtr;
//};
//typedef struct statusTCB status;
//
//struct schedulerTCB
//{
//    void (*schedulerTask)(void*);
//    void* schedulerDataPtr;
//};
//typedef struct schedulerTCB scheduler;
//
//extern measure mTCB;
//extern compute cTCB;
//extern display dTCB;
//extern warningAlarm wTCB;
//extern status sTCB;
//struct schedulerStruct{
//    measure* mTCBPtr;
//    compute* cTCBPtr;
//    display* dTCBPtr;
//    warningAlarm* wTCBPtr;
//    status* sTCBPtr;
//};
//typedef struct schedulerStruct dataScheduler;
//extern scheduler* schTCB;
///************************************************************************************************/
//measure mTCB;
//    (*((dataMeasure*)(mTCB.measureDataPtr))).temperatureRawPtr = &tempR;
//    (*((dataMeasure*)(mTCB.measureDataPtr))).systolicPressRawPtr = &sysPreR;
//    (*((dataMeasure*)mTCB.measureDataPtr)).diastolicPressRawPtr = &diaPreR;
//    (*((dataMeasure*)mTCB.measureDataPtr)).pulseRateRawPtr = &pulseR;
//
//compute cTCB;
//    (*((dataCompute*)cTCB.computeDataPtr)).temperatureRawPtr = &tempR;
//    (*((dataCompute*)cTCB.computeDataPtr)).systolicPressRawPtr = &sysPreR;
//    (*((dataCompute*)cTCB.computeDataPtr)).diastolicPressRawPtr = &diaPreR;
//    (*((dataCompute*)cTCB.computeDataPtr)).pulseRateRawPtr = &pulseR;
//    (*((dataCompute*)cTCB.computeDataPtr)).tempCorrectedPtr = &tempC;
//    (*((dataCompute*)cTCB.computeDataPtr)).sysCorrectedPtr = &sysPreC;
//    (*((dataCompute*)cTCB.computeDataPtr)).diasCorrectedPtr = &diaPreC;
//    (*((dataCompute*)cTCB.computeDataPtr)).prCorrectedPtr = &pulseC;
//
//display dTCB;
//    (*((dataDisplay*)dTCB.displayDataPtr)).tempCorrectedPtr = &tempC;
//    (*((dataDisplay*)dTCB.displayDataPtr)).sysCorrectedPtr = &sysPreC;
//    (*((dataDisplay*)dTCB.displayDataPtr)).diasCorrectedPtr = &diaPreC;
//    (*((dataDisplay*)dTCB.displayDataPtr)).prCorrectedPtr = &pulseC;
//    (*((dataDisplay*)dTCB.displayDataPtr)).batteryStatePtr = &battery;
//
//warningAlarm wTCB;
//    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).tempWarningPtr = &tempWarning;
//    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).sysWarningPtr = &sysWarning;
//    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).diasWarningPtr = &diaWarning;
//    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).bpWarningPtr = &bpWarning;
//    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).batteryWarningPtr = &batteryWarning;
// 
//status sTCB;
//    *((dataStatus*)sTCB.statusDataPtr)).batteryStatePtr = &battery;
//
////scheduler* schTCB;
////    (*((dataScheduler*)schTCB->schedulerDataPtr)).mTCBPtr = &mTCB;
////    (*((dataScheduler*)schTCB->schedulerDataPtr)).cTCBPtr = &cTCB;
////    (*((dataScheduler*)schTCB->schedulerDataPtr)).dTCBPtr = &dTCB;
////    (*((dataScheduler*)schTCB->schedulerDataPtr)).wTCBPtr = &wTCB;
////    (*((dataScheduler*)schTCB->schedulerDataPtr)).sTCBPtr = &sTCB;

/*********************************************************************************************/

void statusTask(void* statusData){ //
    statusStruct* data = (statusStruct*)statusData;;
    if(battery > 0) {
      *(data->batteryStatePtr) -= 1;
    }
}

void schedulerTask(void* queue1){
  TCB* queue = (TCB*)queue1;
  (*queue[0].myTask)(queue[0].taskDataPtr);
  (*queue[1].myTask)(queue[1].taskDataPtr);
  (*queue[2].myTask)(queue[2].taskDataPtr);
  (*queue[3].myTask)(queue[3].taskDataPtr);
  (*queue[4].myTask)(queue[4].taskDataPtr);
  delay(5000);

//    dataScheduler* data = (dataScheduler*)scheduleData;
//    data->mTCBPtr->measureTask(data->mTCBPtr->measureDataPtr);
//    data->cTCBPtr->computeTask(data->cTCBPtr->computeDataPtr);
//    data->dTCBPtr->displayTask(data->dTCBPtr->displayDataPtr);
//    data->wTCBPtr->warningAlarmTask(data->wTCBPtr->warningAlarmDataPtr);
//    data->sTCBPtr->statusTask(data->wTCBPtr->warningAlarmDataPtr);
}


//void setup()
//{
//  Serial.begin(9600);
//
//}
//
//void loop()
//{
//  //  send some test characters from the mega to the uno
//  Serial.println(12.1);
//  delay(1000);
//  Serial.println(1.1);
//  delay(1000);
//  Serial.println(2.1);
//  delay(1000);
//  
//  while(1) {
//
//    
//  }
//}
