/**
 * @file Lab_Rtwdog.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_RTWDOG_H
#define __Lab_RTWDOG_H

#include "fsl_common.h"
/**
  * @brief    ���ڿ��Ź�
  *
  * @param   toval: ���Ź�������������ֵ(cnt������ֵ��������λ).��Χ:0~65535 
  *           win : ���Ź�����������ֵ.��Χ:0~65535,0��ʾ��ʹ�ô���ģʽ.
  * @return   
  *
  * @note     ι��Ҫ�� win - toval ֮��
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void MYRTWDOG_Init(uint16_t toval,uint16_t win);


/**
  * @brief    ���Դ��ڿ��Ź�
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Test_Rtwdog(void);




#endif

