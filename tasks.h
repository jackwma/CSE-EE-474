#ifndef tasks_h
#define tasks_h
    enum _myBool { FALSE = 0, TRUE = 1 };
    typedef enum _myBool Bool;

    extern unsigned int temperatureRaw;
    extern unsigned int systolicPressRaw;
    extern unsigned int diastolicPressRaw;
    extern unsigned int pulseRateRaw;

    struct measureStruct{
        unsigned int* temperatureRawPtr;
        unsigned int* systolicPressRawPtr;
        unsigned int* diastolicPressRawPtr;
        unsigned int* pulseRateRawPtr;
    };
    typedef struct measureStruct dataMeasure;

    extern double tempCorrected;
    extern double sysCorrected;
    extern double diasCorrected;
    extern double prCorrected;

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


    extern unsigned short batteryState;
    struct displayStruct{
        double* tempCorrectedPtr;
        double* sysCorrectedPtr;
        double* diasCorrectedPtr;
        double* prCorrectedPtr;
        unsigned short* batteryStatePtr;
    };
    typedef struct displayStruct dataDisplay;


    struct warningAlarmStruct{
        double* tempCorrectedPtr;
        double* sysCorrectedPtr;
        double* diasCorrectedPtr;
        double* prCorrectedPtr;
        unsigned short* batteryStatePtr;
    };
    typedef struct warningAlarmStruct dataWarningAlarm;

    struct statusStruct{
        unsigned short* batteryStatePtr;
    };
    typedef struct statusStruct dataStatus;



    extern unsigned char bpOutOfRange;
    extern unsigned char tempOutOfRange;
    extern unsigned char pulseOutOfRange;

    extern Bool bpHigh;
    extern Bool tempHigh;
    extern Bool pulseLow;

    void initialValues();
#endif
