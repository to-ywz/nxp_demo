#ifndef __MOTORCTRL_H__
#define __MOTORCTRL_H__

#include <stdint.h>
#include "QS_PID.h"

extern pid_param_t gL_tMotorPid, gR_tMotorPid;

void MotorInit(void);
void EncInit(void);
void MotorCtrl(short motor1, short motor2);
void SpeedCtrl(int16_t x, int16_t error);

#endif //__MOTORCTRL_H__
