/**
 * @file QS_PID.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief   PID 算法
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _QS_PID_H_
#define _QS_PID_H_

#include <stdint.h>

typedef struct
{
    float kp;   //P
    float ki;   //I
    float kd;   //D
    float imax; //积分限幅

    float out_p; //KP输出
    float out_i; //KI输出
    float out_d; //KD输出
    float out;   //pid输出

    float integrator;      //< 积分值
    float last_error;      //< 上次误差
    float last_derivative; //< 上次误差与上上次误差之差
    uint32_t last_t;       //< 上次时间
} pid_param_t;

void PidInit(pid_param_t *pid, float kp, float ki, float kd);

float constrain_float(float amt, float low, float high);

float PidLocCtrl(pid_param_t *pid, float error);

float PidIncCtrl(pid_param_t *pid, float error);

int myabs(int a);

#endif /* _QS_PID_H_ */
