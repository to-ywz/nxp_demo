/**
 * @file Lab_WDog.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief ���ڿ��Ź�
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __LabWDOG_H__
#define __LabWDOG_H__
/**
  * @brief    ���Կ��Ź�
  *
  * @param    
  *
  * @return   
  *
  * @note     ���Ź��������Ƕ�ʱι������������ܷ�û��ι����ϵͳ��λ
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Test_WDOG(void);


/**
  * @brief    ���Ź���ʼ��
  *
  * @param    base  �� WDOG1��WDOG2
  * @param    time  �� ʵ��ʱ��Ϊ(time+1)*0.5s
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Lab_WDOG_Init(WDOG_Type *base, uint8_t time);




#endif 



