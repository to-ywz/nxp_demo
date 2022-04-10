/**
 * @file ServoCtrl.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief   舵机控制
 * @version 0.1
 * @date 2021-05-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "control_car.h"

/**  @brief    限幅  */
#define CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

/*
 * 舵机pid参数        
 */
pid_param_t g_tServoPid;

/**
 * @brief 舵机初始化
 * 
 * @date 2021-05-28
 */
void ServoInit(void)
{
  Lab_PWM_Init(PWM2, kPWM_Module_3, kPWM_PwmA, 50); //M3
  // Lab_PWM_Init(PWM2, kPWM_Module_3, kPWM_PwmB, 125); //M3
  Lab_PWM_SetDuty(PWM2, kPWM_Module_3, kPWM_PwmA, SERVO_MID);
  // Lab_PWM_SetDuty(PWM2, kPWM_Module_3, kPWM_PwmB, 65);

  PidInit(&g_tServoPid, 2.0, 0, 0.2);
}

/**
 * @brief             舵机打角控制
 * 
 * @param servoPWM    舵机打角PWM值
 * 
 * 
 * @date 2021-05-28
 */
void ServoCtrl(int16_t servoPWM)
{
  /* 限幅  防止舵机打角反差过大  */
  static int16_t servoPWMLast = SERVO_MID;

  servoPWM = servoPWMLast + CONSTRAIN(servoPWM - servoPWMLast, -30, 30);

  /* 舵机打角限幅  需要根据自己的小车舵机舵盘安装情况，自行调试 */
  servoPWM = CONSTRAIN(servoPWM, SERVO_LEFT_LIMIT, SERVO_RIGHT_LIMIT);

  servoPWMLast = servoPWM;

  Lab_PWM_SetDuty(PWM2, kPWM_Module_3, kPWM_PwmA, servoPWM);
}

/**
 * @brief         舵机控制器
 * 
 * @param error  与中线的偏差
 * 
 * @note        10ms 调用一次
 * 
 * @date 2021-05-28
 */
void SteeringCtrl(int16_t error)
{
  PidLocCtrl(&g_tServoPid, error);

  ServoCtrl((int16_t)g_tServoPid.out + SERVO_MID);
}
