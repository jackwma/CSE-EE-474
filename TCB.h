#ifndef TCB_H
#define TCB_H

struct warningAlarmTCB
{
    void (*warningAlarmTask)(void*);
    void* warningAlarmDataPtr;
};
typedef struct warningAlarmTCB warningAlarm;

struct statusTCB
{
    void (*statusTask)(void*);
    void* statusDataPtr;
};
typedef struct statusTCB status;

struct schedulerTCB
{
    void (*schedulerTask)(void*);
    void* schedulerDataPtr;
};
typedef struct schedulerTCB scheduler;

extern status sTCB;
struct schedulerStruct{
    measure* mTCBPtr;
    compute* cTCBPtr;
    display* dTCBPtr;
    warningAlarm* wTCBPtr;
    status* sTCBPtr;
};
typedef struct schedulerStruct dataScheduler;
extern scheduler* schTCB;

void TCBMain();



#endif