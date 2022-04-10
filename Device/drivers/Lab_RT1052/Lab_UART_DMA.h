/**
 * @file Lab_UART_DMA.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief ����_DMA����
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_UART_DMA_H
#define __Lab_UART_DMA_H

#include "fsl_lpuart_edma.h"
/* ����+DMA ��־λ */
extern volatile bool rxBufferEmpty;
extern volatile bool txBufferFull;
extern volatile bool txOnGoing;
extern volatile bool rxOnGoing;

/* ���յ���֡���� */
extern volatile uint32_t g_rxLen;

/* ���ڽ��� ������ */
extern uint8_t g_rxBuffer[100];
extern uint8_t g_txBuffer[100];

/* DMA ����ṹ�� */
extern lpuart_transfer_t sendXfer;
extern lpuart_transfer_t receiveXfer;

/* ���� + DMA ���ýṹ�� */
extern lpuart_edma_handle_t g_lpuartEdmaHandle;


/**
  * @brief    ����DMA�����ʼ��
  *
  * @param    base  �� LPUART1 - LPUART8
  * @param    bound �� ���ڲ�����
  * @param    TX_channel  �� DMA TXͨ��
  * @param    RX_channel  �� DMA RXͨ��
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/6 ������
  */
void Lab_UART_DMA_Init(LPUART_Type *base, uint32_t bound, uint8_t TX_channel, uint8_t RX_channel);







/**
  * @brief    ���ڲ��Ժ���
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/6 ������
  */
void Test_UART_DMA(void);


#endif
