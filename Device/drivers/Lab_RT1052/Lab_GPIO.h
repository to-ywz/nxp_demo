/**
 * @file Lab_GPIO.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief GPIO ����
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _Lab_GPIO_H_
#define _Lab_GPIO_H_

#include "Lab_GPIO_Cfg.h"


/* GPIO ģʽ */
#define PIN_MODE_OUTPUT         0x00         //�������
#define PIN_MODE_INPUT          0x01         //��������
#define PIN_MODE_INPUT_PULLUP   0x02         //��������
#define PIN_MODE_INPUT_PULLDOWN 0x03         //��������
#define PIN_MODE_OUTPUT_OD      0x04         //��©���

/* GPIO �жϴ���ģʽ */
#define PIN_IRQ_MODE_RISING             0x00 //�����أ������������ж�  
#define PIN_IRQ_MODE_FALLING            0x01 //�½��أ������������ж�
#define PIN_IRQ_MODE_RISING_FALLING     0x02 //˫���أ���©�������ж�
#define PIN_IRQ_MODE_HIGH_LEVEL         0x03 //�ߵ�ƽ�������������ж�
#define PIN_IRQ_MODE_LOW_LEVEL          0x04 //�͵�ƽ�������������ж�



/*!
  * @brief    GPIO��ʼ��
  *
  * @param    pin      �� �ܽű��  Lab_GPIO_Cfg.h�ж���
  * @param    mode     �� GPIO ģʽ   Lab_GPIO.h�еĺ궨����ѡ��
  * @param    output   �� ���ģʽʱ�������ƽ 1���ߵ�ƽ  0���͵�ƽ
  *
  * @return   
  *
  * @note     
  *
  * @example  Lab_PinInit(A7, PIN_MODE_OUTPUT, 1);//���ùܽ�A7Ϊ���ģʽ �ߵ�ƽ
  *
  * @date     2019/8/19 ����һ
  */
void Lab_PinInit(GPIO_Name_t pin, uint8_t mode, uint8_t output);



/*!
  * @brief    ��ȡGPIO״̬
  *
  * @param    pin      �� �ܽű�� Lab_GPIO_Cfg.h�ж���
  *
  * @return   
  *
  * @note     GPIOҪ��ʼ��Ϊ����ģʽ
  *
  * @example  Lab_PinRead(A7); //��ȡA7״̬
  *
  * @date     2019/8/19 ����һ
  */
uint8_t Lab_PinRead(GPIO_Name_t pin);



/*!
  * @brief    ����GPIO���״̬
  *
  * @param    pin      �� �ܽű�� Lab_GPIO_Cfg.h�ж���
  * @param    output   �� 1:�ߵ�ƽ  0���͵�ƽ
  *
  * @return   
  *
  * @note     
  *
  * @example  Lab_PinWrite(A7, 1);//A7��Ϊ�ߵ�ƽ
  *
  * @date     2019/8/19 ����һ
  */
void Lab_PinWrite(GPIO_Name_t pin, uint8_t output);



/*!
  * @brief    GPIO�ⲿ�жϳ�ʼ��
  *
  * @param    pin      �� �ܽű�� Lab_GPIO_Cfg.h�ж���
  * @param    mode     �� GPIO �ж�ģʽ   Lab_GPIO.h�еĺ궨����ѡ��
  *
  * @return   
  *
  * @note     
  *
  * @example  Lab_PinExti(C13, PIN_IRQ_MODE_FALLING);//����C13 �½��ش����ж�
  * @example  ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
  * @example  NVIC_SetPriority(GPIO2_Combined_16_31_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
  * @example  EnableIRQ(GPIO2_Combined_16_31_IRQn);			          //ʹ��GPIO2_16~31IO���ж�  
  *
  * @date     2019/8/19 ����һ
  */
void Lab_PinExti(GPIO_Name_t pin, uint8_t mode);


#endif  
