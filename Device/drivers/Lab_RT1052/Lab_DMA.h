/**
 * @file Lab_DMA.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief DMA ����
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_DMA_H__
#define __Lab_DMA_H__

#include "fsl_edma.h"
/*!
  * @brief    DMA������
  *
  * @note     
  */ 
extern edma_handle_t g_EDMA_Handle; 


/*!
  * @brief    DMA�������ýṹ��
  *
  * @note     
  */ 
extern edma_transfer_config_t transferConfig;

/*!
  * @brief    DMA�ڴ� TO �ڴ��ʼ��
  *
  * @param    DMA_channel:  DMAͨ����  0-31
  * @param    srcAddr    :  Դ��ַ
  * @param    destAddr   :  Ŀ�ĵ�ַ
  * @param    len        :  ���䳤��
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/26 ����һ
  */
void DMA_MemoryToMemoryInit(uint8_t DMA_channel, uint32_t srcAddr, uint32_t destAddr, uint32_t len);


/*!
  * @brief    ����DMA�ڴ浽�ڴ�
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/26 ����һ
  */
void Test_DMA(void);

#endif 
