#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "stdint.h"

// * 舵机 数据需要自己测定
#define SERVO_MAX 360 // * 极限值 370 建议边缘值控制在 350 ~ 340
#define SERVO_MID 292
#define SERVO_MIN 230 // * 极限值 215 建议边缘值控制在 220 ~ 230

#define MOTOR_R_MAX 6000
#define MOTOR_R_MIN -MOTOR_R_MAX

#define MOTOR_L_MAX 6000
#define MOTOR_L_MIN -MOTOR_L_MAX

#define CAR_MAX_SPEED 1000

// * 电机状态结构体
// typedef struct Motor_State
// {
//     int32_t pwmDuty;
//     // * 编码器
//     int32_t expectedSpeed;
//     int32_t currentSpeed;

//     int32_t diff;
// } Motor_t;

// * 摄像头结构体

// extern Motor_t MotorR;
// extern Motor_t MotorL;

void Motor_Init(int32_t _ucDutyL, int32_t _ucdutyR);

// @param pwm:  当前 PWM 
// @param max:  最大 PWM 
// @param min:  最小 PWM
#define LIMITSPEED(pwm, max, min) ((pwm) < (min) ? (min) : ((pwm) > (max) ? (max) : (pwm)));

#endif
