/**
 * @file Lab_SYSTICK.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief SysTick 驱动
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_SYSTICK_H
#define __Lab_SYSTICK_H
#include "fsl_common.h"

typedef struct
{	
	void (* init) (void);  
	uint32_t (* get_time_us) (void);
	uint32_t (* get_time_ms) (void);
	void (* delay_us)(uint32_t);
	void (* delay_ms)(uint32_t);
}systime_t;

/* 声明 systime 结构体*/
extern systime_t  systime;

/**
  * @brief    测试systime 延时
  *
  * @param    
  *
  * @return   
  *
  * @note     示波器 A7   500Hz翻转
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void Test_SystickDelay(void);


/**
  * @brief    测试systime 计时器
  *
  * @param    
  *
  * @return   
  *
  * @note     示波器 A7   500Hz翻转
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void Test_Systick(void);


#endif //__Lab_SYSTICK_H




