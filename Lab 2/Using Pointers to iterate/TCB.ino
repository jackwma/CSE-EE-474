#include "tasks.h"
#include "TCB.h"

void TCBMain(){
    unsigned int temperatureRaw = 75;
    unsigned int systolicPressRaw = 80;
    unsigned int diastolicPressRaw = 80;
    unsigned int pulseRateRaw = 50;
    double tempCorrected = 0.0;
    double sysCorrected = 0.0;
    double diasCorrected = 0.0;
    double prCorrected = 0.0;
    unsigned short batteryState = 200;
    unsigned char bpOutOfRange = 0;
    unsigned char tempOutOfRange = 0;
    unsigned char pulseOutOfRange = 0;
    Bool bpHigh = FALSE;
    Bool tempHigh = FALSE;
    Bool pulseLow = FALSE;
    
    measure mTCB;
    (*((dataMeasure*)(mTCB.measureDataPtr))).temperatureRawPtr = &temperatureRaw;
    (*((dataMeasure*)(mTCB.measureDataPtr))).systolicPressRawPtr = &systolicPressRaw;
    (*((dataMeasure*)mTCB.measureDataPtr)).diastolicPressRawPtr = &diastolicPressRaw;
    (*((dataMeasure*)mTCB.measureDataPtr)).pulseRateRawPtr = &pulseRateRaw;

    compute cTCB;
    (*((dataCompute*)cTCB.computeDataPtr)).temperatureRawPtr = &temperatureRaw;
    (*((dataCompute*)cTCB.computeDataPtr)).systolicPressRawPtr = &systolicPressRaw;
    (*((dataCompute*)cTCB.computeDataPtr)).diastolicPressRawPtr = &diastolicPressRaw;
    (*((dataCompute*)cTCB.computeDataPtr)).pulseRateRawPtr = &pulseRateRaw;
    (*((dataCompute*)cTCB.computeDataPtr)).tempCorrectedPtr = &tempCorrected;
    (*((dataCompute*)cTCB.computeDataPtr)).sysCorrectedPtr = &sysCorrected;
    (*((dataCompute*)cTCB.computeDataPtr)).diasCorrectedPtr = &diasCorrected;
    (*((dataCompute*)cTCB.computeDataPtr)).prCorrectedPtr = &prCorrected;

    display dTCB;
    (*((dataDisplay*)dTCB.displayDataPtr)).tempCorrectedPtr = &tempCorrected;
    (*((dataDisplay*)dTCB.displayDataPtr)).sysCorrectedPtr = &sysCorrected;
    (*((dataDisplay*)dTCB.displayDataPtr)).diasCorrectedPtr = &diasCorrected;
    (*((dataDisplay*)dTCB.displayDataPtr)).prCorrectedPtr = &prCorrected;
    (*((dataDisplay*)dTCB.displayDataPtr)).batteryStatePtr = &batteryState;

    warningAlarm wTCB;
    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).tempCorrectedPtr = &tempCorrected;
    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).sysCorrectedPtr = &sysCorrected;
    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).diasCorrectedPtr = &diasCorrected;
    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).prCorrectedPtr = &prCorrected;
    (*((dataWarningAlarm*)wTCB.warningAlarmDataPtr)).batteryStatePtr = &batteryState;

    status sTCB;
    (*((dataStatus*)sTCB.statusDataPtr)).batteryStatePtr = &batteryState;

    scheduler* schTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).mTCBPtr = &mTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).cTCBPtr = &cTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).dTCBPtr = &dTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).wTCBPtr = &wTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).sTCBPtr = &sTCB;
}


