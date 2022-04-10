/**
 * @file Lab_PIT.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief PIT ����
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_PIT_H_
#define __Lab_PIT_H_
/**
  * @brief    PIT��ʱ����ʼ��
  *
  * @param    channel�� PITͨ�� kPIT_Chnl_0 - kPIT_Chnl_3
  * @param    count  �� ��ʱ��ʱ�� us
  *
  * @return   
  *
  * @note     PIT��GPTʹ�� ͬһʱ��Դ Ĭ��IPG/2ʱ�� 75M
  *
  * @example  Lab_PIT_Init(kPIT_Chnl_0, 5000);  //����ͨ��0��ʱ���жϣ�ÿ5000us�ж�һ��
  *
  * @date     2019/6/4 ���ڶ�
  */
void Lab_PIT_Init(pit_chnl_t channel, uint32_t count);


/**
  * @brief    ����PIT�ж�
  *
  * @param    
  *
  * @return   
  *
  * @note     ��ʾ������ C12 500Hz   A13 100Hz
  *
  * @example  
  *
  * @date     2019/6/4 ���ڶ�
  */
void Test_PIT(void);





#endif  
