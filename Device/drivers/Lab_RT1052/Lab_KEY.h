/**
 * @file Lab_KEY.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief  ĸ�水������
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_KEY_H__
#define __Lab_KEY_H__

/**
  * @brief    ��ʼ������ĸ���ϵİ���
  *
  * @param    
  *
  * @return   
  *
  * @note     GPIO3_IO04 ------ �ܽ�P2   ----- >  ĸ�尴��K2
  * @note     GPIO2_IO27 ------ �ܽ�C13  ----- >  ĸ�尴��K0
  * @note     GPIO2_IO30 ------ �ܽ�C14  ----- >  ĸ�尴��k1
  *
  * @example  
  *
  * @date     2019/6/4 ���ڶ�
  */
void KEY_Init(void);


/**
  * @brief    ��ȡ����״̬
  *
  * @param    mode�� 0����֧��������;   1��֧��������;
  *
  * @return   0���ް�������  1��KEY0����  2:KEY1����  3:KEY2����
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/4 ���ڶ�
  */
uint8_t KEY_Read(uint8_t mode);


/**
  * @brief    ���԰���
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/4 ���ڶ�
  */
void Test_KEY(void);



/*!
  * @brief    ����GPIIO�ⲿ�ж�
  *
  * @param    
  *
  * @return   
  *
  * @note     ����ĸ���ϲ�ͬ�İ��� ��ͬ��ɫ�ĵ���˸
  *
  * @example  
  *
  * @date     2019/8/19 ����һ
  */
void Test_ExtiKEY(void);



#endif 
