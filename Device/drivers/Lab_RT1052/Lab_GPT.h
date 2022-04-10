/**
 * @file Lab_GPT.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief GPT 驱动
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _Lab_GPT_H_
#define _Lab_GPT_H_

/**
  * @brief    测试GPT 计时器
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
void Test_GPTTimer(void);

/**
  * @brief    测试GPT 延时
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
void Test_GPTDelay(void);

/**
  * @brief    GPT 通用定时器初始化
  *
  * @param    
  *
  * @return   
  *
  * @note     初始化GPT计数器  GPT1用与程序计时器  GPT2用作精确延时
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void Lab_GPT_Init(void);

/**
  * @brief    gpt 定时器精确延时
  *
  * @param    ms ： 延时时间 ms
  *
  * @return   
  *
  * @note     GPT 是32为计数器 最大延时4294967295 / 5 000000 = 868s
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void GPT_DelayMs(uint32_t ms);

/**
  * @brief    gpt 定时器精确延时
  *
  * @param    us ： 延时时间 us
  *
  * @return   
  *
  * @note     GPT 是32为计数器 最大延时4294967295 / 5 000000 = 868s
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void GPT_DelayUs(uint32_t us);

/**
  * @brief    gpt 计时器开始计时
  *
  * @param   
  *
  * @return   
  *
  * @note     GPT 是32为计数器 最大延时4294967295 / 1 000000 = 4290s 
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void GPT_TimeStart(void);

/**
  * @brief    gpt 计时器开始计时
  *
  * @param   
  *
  * @return   
  *
  * @note     GPT 是32为计数器 最大延时4294967295 / 1 000000 = 4290s 
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
uint32_t GPT_TimeGetUs(void);

#endif
