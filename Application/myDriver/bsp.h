/**
 * @file bsp.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief LQ1052MBVJ_BM 初始化
 * @version 0.1
 * @date 2021-05-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __BL_BSP_H__
#define __BL_BSP_H__

// * ========================== rt1052 驱动 ==========================
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
// * ========================== fsl 库函数 ==========================
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
// * ========================== Lab 库函数 ==========================
#include "Lab_LED.h"
#include "Lab_GPIO.h"
#include "Lab_KEY.h"
#include "Lab_Uart.h"
#include "Lab_PWM.h"
#include "Lab_12864.h"
#include "Lab_Encoder.h"
#include "Lab_Camera.h"
// * ========================== 自定义 函数 ==========================
#include "control_pid.h"
#include "stdio.h"

#define Motor_FREQUENCY     10000

void BL_LQ1052MBVJ_Init(void);

#endif
