/**
 * @file bsp.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief   初始化 RT1052MB-VJ 
 * @version 0.1
 * @date 2021-05-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "bsp.h"
#include "stdint.h"
#include "MotorCtrl.h"
#include "ServoCtrl.h"
#include "control_car.h"

/**
 * @brief   摄像头初始化
 * 
 * @date 2021-05-28
 */
static void Camera_Init(void)
{
  LCD_Show_Frame94();
  Lab_Camera_Init();
}

/**
  * @brief    母板基本初始化
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @example  
  *
  * @date     2021/5/15
*/
void BL_LQ1052MBVJ_Init(void)
{
  // RT 1052 初始化
  BOARD_ConfigMPU();    /* 初始化内存保护单元 */
  BOARD_BootClockRUN(); /* 初始化开发板时钟 */

  LCD_Init(); // OLED 初始化
  LCD_CLS();  //LCD清屏
  // UART 初始化
  Lab_UART_Init(LPUART1, 115200);

  LED_Init();  // LED 初始化
  KEY_Init();  // 按键 初始化
  ServoInit(); // 舵机 初始化
  MotorInit(); // 电机初始化
  EncInit();   // 编码器 初始化

  // 摄像头 初始化
  Camera_Init();
}
