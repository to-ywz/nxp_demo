#ifndef __SERVOCTRL_H__
#define __SERVOCTRL_H__


void ServoInit(void);
void ServoCtrl(int16_t servoPWM);
void SteeringCtrl(int16_t error);

#endif
