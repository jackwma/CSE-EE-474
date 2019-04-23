#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <stdbool.h>

#define MAJOR_CYCLE 500

typedef struct measureData {
  unsigned int temperatureRaw;
  unsigned int systolicPressRaw;
  unsigned int diastolicPressRaw;
  unsigned int pulseRateRaw;
} measureData;

typedef struct computeData {
  unsigned int temperatureRaw;
  unsigned int systolicPressRaw;
  unsigned int diastolicPressRaw;
  unsigned int pulseRateRaw;
  unsigned char *tempCorrected;
  unsigned char *sysPressCorrected;
  unsigned char *diasCorrected;
  unsigned char *prCorrected;
} computeData;

typedef struct displayData {
  unsigned char *tempCorrected;
  unsigned char *sysPressCorrected;
  unsigned char *diasCorrected;
  unsigned char *prCorrected;
  unsigned short batteryState;
} displayData;

typedef struct warningAlarmData {
  unsigned int temperatureRaw;
  unsigned int systolicPressRaw;
  unsigned int diastolicPressRaw;
  unsigned int pulseRateRaw;
  unsigned short batteryState;

} warningAlarmData;

typedef struct Status {
  unsigned short batteryState;
} statusData;

#endif // DATASTRUCTS_H

