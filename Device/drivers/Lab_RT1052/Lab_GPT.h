/**
 * @file Lab_GPT.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief GPT ����
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _Lab_GPT_H_
#define _Lab_GPT_H_

/**
  * @brief    ����GPT ��ʱ��
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
void Test_GPTTimer(void);

/**
  * @brief    ����GPT ��ʱ
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
void Test_GPTDelay(void);

/**
  * @brief    GPT ͨ�ö�ʱ����ʼ��
  *
  * @param    
  *
  * @return   
  *
  * @note     ��ʼ��GPT������  GPT1��������ʱ��  GPT2������ȷ��ʱ
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Lab_GPT_Init(void);

/**
  * @brief    gpt ��ʱ����ȷ��ʱ
  *
  * @param    ms �� ��ʱʱ�� ms
  *
  * @return   
  *
  * @note     GPT ��32Ϊ������ �����ʱ4294967295 / 5 000000 = 868s
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void GPT_DelayMs(uint32_t ms);

/**
  * @brief    gpt ��ʱ����ȷ��ʱ
  *
  * @param    us �� ��ʱʱ�� us
  *
  * @return   
  *
  * @note     GPT ��32Ϊ������ �����ʱ4294967295 / 5 000000 = 868s
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void GPT_DelayUs(uint32_t us);

/**
  * @brief    gpt ��ʱ����ʼ��ʱ
  *
  * @param   
  *
  * @return   
  *
  * @note     GPT ��32Ϊ������ �����ʱ4294967295 / 1 000000 = 4290s 
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void GPT_TimeStart(void);

/**
  * @brief    gpt ��ʱ����ʼ��ʱ
  *
  * @param   
  *
  * @return   
  *
  * @note     GPT ��32Ϊ������ �����ʱ4294967295 / 1 000000 = 4290s 
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
uint32_t GPT_TimeGetUs(void);

#endif
