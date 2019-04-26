#ifndef TCB_H
#define TCB_H

struct measureTCB
{
    void (*measureTask)(void*);
    void* measureDataPtr;
};
typedef struct measureTCB measure;

struct computeTCB
{
    void (*computeTask)(void*);
    void* computeDataPtr;
};
typedef struct computeTCB compute;

struct displayTCB
{
    void (*displayTask)(void*);
    void* displayDataPtr;
};
typedef struct displayTCB display;

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