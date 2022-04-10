/**
 * @file Lab_UART.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief 串口驱动
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_UART_H
#define __Lab_UART_H

/**********************************  LP_UART(引脚复用) ***************************************/
//     串口输出通道        端口            可选范围              建议
#define LP_UART1_RX L14 //L14
#define LP_UART1_TX K14 //K14

#define LP_UART2_RX M12 //M12  P4             P4接QSPI FLASH
#define LP_UART2_TX L11 //L11  P5             P5接QSPI FLASH

#define LP_UART3_RX C9 //B6  C9  K10         B6接SDRAM
#define LP_UART3_TX B9 //A6  B9  C12         A6接SDRAM

#define LP_UART4_RX B11 //A3  B11 M5          A3接SDRAM
#define LP_UART4_TX A11 //A11 B4  L5          B4接SDRAM

#define LP_UART5_RX D14 //D3  D14             D3接SDRAM
#define LP_UART5_TX D13 //D13 G2              G2接SDRAM

#define LP_UART6_RX G11 //B3  G11             B3接SDRAM
#define LP_UART6_TX M11 //D2  M11             D2接SDRAM

#define LP_UART7_RX N4 //D5  N4              D5接SDRAM  N4接QSPI FLASH
#define LP_UART7_TX P3 //C5  P3              C5接SDRAM  P3接QSPI FLASH

#define LP_UART8_RX J2 //B7  J2  J13         B7接SDRAM
#define LP_UART8_TX H2 //D6  H2  L13         D6接SDRAM

/**
  * @brief    串口引脚复用初始化
  *
  * @param    base： LPUART1 - LPUART8
  *
  * @return   
  *
  * @note     内部调用的，仅用来设置串口管脚复用的
  *
  * @example  
  *
  * @date     2019/6/6 星期四
  */
void UART_PinInit(LPUART_Type *base);

/**
  * @brief    串口初始化
  *
  * @param    base  ： LPUART1 - LPUART8
  * @param    bound ： 串口波特率
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/6 星期四
  */
void Lab_UART_Init(LPUART_Type *base, uint32_t bound);

/**
 * @brief 接收一个字节
 * 
 * @param base      ： LPUART1 - LPUART8
 * 
 * @retval uint8_t  : 接收到的数据
 * 
 * @note
 * 
 * @example  ch = UART_getChar(LPUART1); 
 * 
 * @date     2021/5/16 
 */
uint8_t UART_getChar(LPUART_Type *base);

/**
  * @brief    发送一个字符
  *
  * @param    base  ： LPUART1 - LPUART8
  * @param    data  ： 发送的字符
  *
  * @return   
  *
  * @note     
  *
  * @example  UART_PutChar(LPUART1, char);  //串口1  发送char
  *
  * @date     2019/6/6 星期四
  */
void UART_PutChar(LPUART_Type *base, uint8_t data);

/**
  * @brief    发送一个数组
  *
  * @param    base  ： LPUART1 - LPUART8
  * @param    data  ： 发送的字符
  * @     length： 发送的字符长度
  *
  * @return   
  *
  * @note     
  *
  * @example  UART_PutBuff(LPUART1, buff, 10);//串口1，发送一个长度为10地址为buff的数组
  *
  * @date     2019/6/6 星期四
  */
void UART_PutBuff(LPUART_Type *base, uint8_t *buff, uint32_t length);

/**
  * @brief    发送一个字符串
  *
  * @param    base  ： LPUART1 - LPUART8
  * @param    data  ： 发送的字符
  *
  * @return   
  *
  * @note     
  *
  * @example  UART_PutBuff(LPUART1, buff, 10);//串口1，发送一个长度为10地址为buff的数组
  *
  * @date     2019/6/6 星期四
  */
void UART_PutStr(LPUART_Type *base, uint8_t *str);

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
void Test_UART(void);

#endif
