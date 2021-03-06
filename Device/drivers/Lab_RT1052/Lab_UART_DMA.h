/**
 * @file Lab_UART_DMA.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief 串口_DMA驱动
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_UART_DMA_H
#define __Lab_UART_DMA_H

#include "fsl_lpuart_edma.h"
/* 串口+DMA 标志位 */
extern volatile bool rxBufferEmpty;
extern volatile bool txBufferFull;
extern volatile bool txOnGoing;
extern volatile bool rxOnGoing;

/* 接收到的帧长度 */
extern volatile uint32_t g_rxLen;

/* 串口接收 缓冲区 */
extern uint8_t g_rxBuffer[100];
extern uint8_t g_txBuffer[100];

/* DMA 传输结构体 */
extern lpuart_transfer_t sendXfer;
extern lpuart_transfer_t receiveXfer;

/* 串口 + DMA 配置结构体 */
extern lpuart_edma_handle_t g_lpuartEdmaHandle;


/**
  * @brief    串口DMA传输初始化
  *
  * @param    base  ： LPUART1 - LPUART8
  * @param    bound ： 串口波特率
  * @param    TX_channel  ： DMA TX通道
  * @param    RX_channel  ： DMA RX通道
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/6 星期四
  */
void Lab_UART_DMA_Init(LPUART_Type *base, uint32_t bound, uint8_t TX_channel, uint8_t RX_channel);







/**
  * @brief    串口测试函数
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/6 星期四
  */
void Test_UART_DMA(void);


#endif
