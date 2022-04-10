/**
 * @file MotorCtrl.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief 电机控制
 * @version 0.1
 * @date 2021-05-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "control_car.h"
#include "Lab_Encoder.h"
#include "MotorCtrl.h"

#define MOTOR_R 1
#define MOTOR_L 2

// * 电机频率
#define MOTOR_FREQUENCY 10000
#define MOTOR_MAX 6000

// * 限幅
#define CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

/*
 * 电机pid参数        对应电机如下
 *
 *     
 *
 *     1(左后)   2(右后)
 */
pid_param_t gL_tMotorPid, gR_tMotorPid;

/*
 * 编码器低通滤波参数        对应电机如下
 *
 *     
 *
 *     1(左后)   2(右后)
 */
lowFilter_t gL_tEnc, gR_tEnc;

/*
 * 电机相关数据
 *  TargetVelocity: 车辆期望速度
 *  PWM_R:          右轮输出的PWM
 *  PWM_L:          左轮输出的PWM
 *  ENC_R:          右编码器值
 *  ENC_L:          左编码器值
 */
Motor_t motor = {Motor_Speed, 0, 0};
/**
 * @brief           电机初始化
 * 
 * @date 2021-05-28
 */
void MotorInit(void)
{

    /* 初始化电机PWM接口 */
    Lab_PWM_Init(PWM2, kPWM_Module_0, kPWM_PwmA_B, MOTOR_FREQUENCY); //  A8 A9
    Lab_PWM_Init(PWM1, kPWM_Module_3, kPWM_PwmA_B, MOTOR_FREQUENCY); //  L5 M5

    PidInit(&gL_tMotorPid, 7.0, 0.5, 0.14);
    PidInit(&gR_tMotorPid, 7.0, 0.5, 0.14);

    /* 编码器低通滤波器初始化 */
    lowPassFilter.init(&gL_tEnc, 200, 100);
    lowPassFilter.init(&gR_tEnc, 200, 100);
}

/**
 * @brief           编码器初始化
 * 
 * @date 2021-05-28
 */
void EncInit(void)
{
    Lab_ENC_Init(ENC1, false);
    Lab_ENC_Init(ENC3, true);
}

/**
 * @brief               电机控制函数
 * 
 * @param _ucDuty_L     左电机占空比
 * @param _ucDuty_R     右电机占空比
 * 
 * 
 * @date 2021-05-28
 */
void MotorCtrl(short _ucDuty_L, short _ucDuty_R)
{

    /* 限幅  防止电机转速反差过大  */
    static short L_motorLast = 0, R_motorLast = 0;
    _ucDuty_L = L_motorLast + CONSTRAIN(_ucDuty_L - L_motorLast, -1000, 1000);
    _ucDuty_R = R_motorLast + CONSTRAIN(_ucDuty_R - R_motorLast, -1000, 1000);

    /* 限幅  */
    _ucDuty_L = CONSTRAIN(_ucDuty_L, -MOTOR_MAX, MOTOR_MAX);
    _ucDuty_R = CONSTRAIN(_ucDuty_R, -MOTOR_MAX, MOTOR_MAX);

    // 同步数据到电机状态结构体
    motor.PWM_L = _ucDuty_L;
    motor.PWM_R = _ucDuty_R;

    L_motorLast = _ucDuty_L;
    R_motorLast = _ucDuty_R;

    Lab_SetMotorDty(MOTOR_L, _ucDuty_L);
    Lab_SetMotorDty(MOTOR_R, _ucDuty_R);
}

/**
 * @brief           速度控制函数
 * 
 * @param x         速度期望值
 * @param error     偏差值,是否差速转弯
 * 
 * 
 * @date 2021-05-28
 */
void SpeedCtrl(int16_t x, int16_t error)
{
    /* 两个轮子的期望速度  */
    int16_t R_targetSpeed = 0, L_targetSpeed = 0;

    /* 根据小车速度大小和方向  计算每个轮子的期望转速  */
    R_targetSpeed = x;

    /* 大弯使用差速 */
    if (error > 30)
    {
        L_targetSpeed = x - error / 30;
    }
    else
    {
        L_targetSpeed = x;
    }

    /* 获取编码器值 */
    motor.ENC_R = (int16_t)ENC_GetPositionDifferenceValue(ENC1); //得到编码器微分值;
    motor.ENC_L = (int16_t)ENC_GetPositionDifferenceValue(ENC3); //得到编码器微分值;

    /* 滤波 */
    motor.ENC_R = (int16_t)lowPassFilter.apply(&gR_tEnc, motor.ENC_R);
    motor.ENC_L = (int16_t)lowPassFilter.apply(&gL_tEnc, motor.ENC_L);

    /* PID处理 */
    motor.PWM_R += PidIncCtrl(&gL_tMotorPid, R_targetSpeed - motor.ENC_R);
    motor.PWM_L += PidIncCtrl(&gR_tMotorPid, L_targetSpeed - motor.ENC_L);

    /* 电机控制 */
    MotorCtrl(motor.PWM_L, motor.PWM_R);
}
