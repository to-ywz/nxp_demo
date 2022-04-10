/**
 * @file Lab_UART.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief ��������
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_UART_H
#define __Lab_UART_H

/**********************************  LP_UART(���Ÿ���) ***************************************/
//     �������ͨ��        �˿�            ��ѡ��Χ              ����
#define LP_UART1_RX L14 //L14
#define LP_UART1_TX K14 //K14

#define LP_UART2_RX M12 //M12  P4             P4��QSPI FLASH
#define LP_UART2_TX L11 //L11  P5             P5��QSPI FLASH

#define LP_UART3_RX C9 //B6  C9  K10         B6��SDRAM
#define LP_UART3_TX B9 //A6  B9  C12         A6��SDRAM

#define LP_UART4_RX B11 //A3  B11 M5          A3��SDRAM
#define LP_UART4_TX A11 //A11 B4  L5          B4��SDRAM

#define LP_UART5_RX D14 //D3  D14             D3��SDRAM
#define LP_UART5_TX D13 //D13 G2              G2��SDRAM

#define LP_UART6_RX G11 //B3  G11             B3��SDRAM
#define LP_UART6_TX M11 //D2  M11             D2��SDRAM

#define LP_UART7_RX N4 //D5  N4              D5��SDRAM  N4��QSPI FLASH
#define LP_UART7_TX P3 //C5  P3              C5��SDRAM  P3��QSPI FLASH

#define LP_UART8_RX J2 //B7  J2  J13         B7��SDRAM
#define LP_UART8_TX H2 //D6  H2  L13         D6��SDRAM

/**
  * @brief    �������Ÿ��ó�ʼ��
  *
  * @param    base�� LPUART1 - LPUART8
  *
  * @return   
  *
  * @note     �ڲ����õģ����������ô��ڹܽŸ��õ�
  *
  * @example  
  *
  * @date     2019/6/6 ������
  */
void UART_PinInit(LPUART_Type *base);

/**
  * @brief    ���ڳ�ʼ��
  *
  * @param    base  �� LPUART1 - LPUART8
  * @param    bound �� ���ڲ�����
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/6 ������
  */
void Lab_UART_Init(LPUART_Type *base, uint32_t bound);

/**
 * @brief ����һ���ֽ�
 * 
 * @param base      �� LPUART1 - LPUART8
 * 
 * @retval uint8_t  : ���յ�������
 * 
 * @note
 * 
 * @example  ch = UART_getChar(LPUART1); 
 * 
 * @date     2021/5/16 
 */
uint8_t UART_getChar(LPUART_Type *base);

/**
  * @brief    ����һ���ַ�
  *
  * @param    base  �� LPUART1 - LPUART8
  * @param    data  �� ���͵��ַ�
  *
  * @return   
  *
  * @note     
  *
  * @example  UART_PutChar(LPUART1, char);  //����1  ����char
  *
  * @date     2019/6/6 ������
  */
void UART_PutChar(LPUART_Type *base, uint8_t data);

/**
  * @brief    ����һ������
  *
  * @param    base  �� LPUART1 - LPUART8
  * @param    data  �� ���͵��ַ�
  * @     length�� ���͵��ַ�����
  *
  * @return   
  *
  * @note     
  *
  * @example  UART_PutBuff(LPUART1, buff, 10);//����1������һ������Ϊ10��ַΪbuff������
  *
  * @date     2019/6/6 ������
  */
void UART_PutBuff(LPUART_Type *base, uint8_t *buff, uint32_t length);

/**
  * @brief    ����һ���ַ���
  *
  * @param    base  �� LPUART1 - LPUART8
  * @param    data  �� ���͵��ַ�
  *
  * @return   
  *
  * @note     
  *
  * @example  UART_PutBuff(LPUART1, buff, 10);//����1������һ������Ϊ10��ַΪbuff������
  *
  * @date     2019/6/6 ������
  */
void UART_PutStr(LPUART_Type *base, uint8_t *str);

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
void Test_UART(void);

#endif
