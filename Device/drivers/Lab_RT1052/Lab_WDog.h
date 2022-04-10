/**
 * @file Lab_WDog.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief 窗口看门狗
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __LabWDOG_H__
#define __LabWDOG_H__
/**
  * @brief    测试看门狗
  *
  * @param    
  *
  * @return   
  *
  * @note     看门狗的作用是定时喂狗，如果程序跑飞没有喂狗，系统复位
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void Test_WDOG(void);


/**
  * @brief    看门狗初始化
  *
  * @param    base  ： WDOG1、WDOG2
  * @param    time  ： 实际时间为(time+1)*0.5s
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void Lab_WDOG_Init(WDOG_Type *base, uint8_t time);




#endif 



