/**
 * @file Lab_SYSTICK.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief SysTick ����
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

/* ���� systime �ṹ��*/
extern systime_t  systime;

/**
  * @brief    ����systime ��ʱ
  *
  * @param    
  *
  * @return   
  *
  * @note     ʾ���� A7   500Hz��ת
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Test_SystickDelay(void);


/**
  * @brief    ����systime ��ʱ��
  *
  * @param    
  *
  * @return   
  *
  * @note     ʾ���� A7   500Hz��ת
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Test_Systick(void);


#endif //__Lab_SYSTICK_H




