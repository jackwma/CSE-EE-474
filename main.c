#include <stdio.h>
#include <time.h>
#include <stdlib.h>



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



