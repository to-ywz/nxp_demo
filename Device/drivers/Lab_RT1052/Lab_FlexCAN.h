/**
 * @file Lab_FlexCAN.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief CAN ��������
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __LabFLEXCAN_H__
#define __LabFLEXCAN_H__

#include "Lab_GPIO_Cfg.h"

/**  @brief    CAN ��ѡ�ܽ�  */
#define FLEX_CAN1_TX   M3         //M3  A4  E8  H13    A4 ���ⲿQSPI FLASH��RT1064 �ڲ���4M FLASH  ���Բ�ʹ���ⲿQSPI FLASH��
#define FLEX_CAN1_RX   B2         //B2  M4  D8  M13    B2 ���ⲿQSPI FLASH��RT1064 �ڲ���4M FLASH  ���Բ�ʹ���ⲿQSPI FLASH��

#define FLEX_CAN2_TX   H14        //H14 C2  M11 A12    C2 ���ⲿQSPI FLASH��RT1064 �ڲ���4M FLASH  ���Բ�ʹ���ⲿQSPI FLASH��
#define FLEX_CAN2_RX   L10        //L10 G1  G11 A13    G1 ���ⲿQSPI FLASH��RT1064 �ڲ���4M FLASH  ���Բ�ʹ���ⲿQSPI FLASH��



/*!
  * @brief    CAN ��ʼ��
  *
  * @param    base     :CANģ�� CAN1 CAN2  
  * @param    baudrate :CAN����
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/21 ������
  */
void CAN_Init(CAN_Type *base, uint32_t baudrate);


/*!
  * @brief    ����CAN��������
  *
  * @param    base     :CANģ�� CAN1 CAN2    
  * @param    RxMb_num :ʹ�õ������ 
  * @param    id       :����֡��ID 
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/21 ������
  */
void CAN_RxConfig(CAN_Type *base, uint8_t RxMb_num, uint32_t id);


/*!
  * @brief    ����CAN��������
  *
  * @param    base     :CANģ�� CAN1 CAN2    
  * @param    TxMb_num :ʹ�õ������  
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/21 ������
  */
void CAN_TxConfig(CAN_Type *base, uint8_t TxMb_num);



/*!
  * @brief    CAN����֡
  *
  * @param    base     :CANģ�� CAN1 CAN2    
  * @param    TxMb_num :ʹ�õ������   
  * @param    id       :����֡ID
  * @param    msg      :��ŷ������ݵ�ַ 
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/21 ������
  */
void CAN_Tx(CAN_Type *base, uint8_t TxMb_num, uint32_t id, uint8_t *msg);



/*!
  * @brief    ����CAN
  *
  * @param    
  *
  * @return   
  *
  * @note     �շ�IDһ�� CAN����յ��Լ����͵�����
  *
  * @see      
  *
  * @date     2019/8/21 ������
  */
void Test_CAN(void);
      
      
#endif 



