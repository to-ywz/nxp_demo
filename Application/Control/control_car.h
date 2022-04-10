/**
 * @file control_car.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief   车辆基本控制头文件
 * @version 0.1
 * @date 2021-05-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __CONTROL_CAR_H__
#define __CONTROL_CAR_H__

#include <stdint.h>
#include "include.h"
#include "QS_PID.h"
#include "Lab_PWM.h"
#include "LowPassFilter.h"

typedef struct MotorDevice
{
    int16_t TargetVelocity;
    short PWM_R;
    short PWM_L;
    short ENC_R;
    short ENC_L;
} Motor_t;

extern Motor_t motor;

// * 舵机 数据需要自己测定
#define SERVO_RIGHT_LIMIT 360 // * 极限值 370 建议边缘值控制在 350 ~ 340
#define SERVO_MID 292
#define SERVO_LEFT_LIMIT 230 // * 极限值 215 建议边缘值控制在 220 ~ 230

// * 电机参数
#define Motor_Speed 320

// * 编码器最大转速
#define CAR_MAX_SPEED 1000

// * 主跑行
#define ROAD_MAIN_ROW 50

// * 使用起始行
#define ROAD_START_ROW 55

// * 使用结束行
#define ROAD_END_ROW 5

// @param pwm:  当前 PWM
// @param max:  最大 PWM
// @param min:  最小 PWM
#define LIMITSPEED(pwm, max, min) ((pwm) < (min) ? (min) : ((pwm) > (max) ? (max) : (pwm)));

// * ================================== 绘图 =================================
// * 中线扫描
#define POINT_SCAN_RANGE 6
// * 补线
typedef enum LOSS_POINT_TYPE
{
    LEFT_LOSS = 1,  /*!< 左线丢失 >*/
    RIGHT_LOSS = 2, /*!< 右线丢失 >*/
    MIDDLE_LOSS = 3 /*!< 中线丢失 >*/
} LostLine_Type;

// * ============================= 车辆行进相关参数 ======================================
// * 环岛标志位
extern uint8_t g_ucFlagRoundabout;

// * 十字标志位
extern uint8_t g_ucFlagCross;

// * 斑马线标志位
extern uint8_t g_ucFlagZebra;

// * 小车期望速度
extern int16_t g_sTargetVelocity;

// * 舵机期望打角
extern int16_t g_sSteeringError;

// * 两轮差速
extern int16_t g_sDifferentVelocity;

// * 丢线标志位
extern uint8_t g_ucIsNoSide;

extern volatile uint8_t Field_Over_Flag;

void Draw_RoadMiddleLine(void);

// * 补线算法测试 是否 使用最小二乘法回归
#define BINARY 0

#endif
