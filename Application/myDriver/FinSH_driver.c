/**
 * @file FinSH_driver.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief RT-Thread FinSH 组件 驱动
 * @version 0.1
 * @date 2021-05-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "FinSH_driver.h"
#include "Lab_UART.h"

// * 在 enable.h 中定义
#if USING_FINSH 

static rt_uint8_t uart_rx_buf[UART_RX_BUF_LEN] = {0};
struct ringbuffer uart_rxcb;             /* 定义一个 ringbuffer cb */
static struct rt_semaphore shell_rx_sem; /* 定义一个静态信号量 */

/**
 * @brief 初始化 FInSH 串口
 * 
 * @retval 
 * 
 * @date 2021-05-16
 */
static int FinSH_Init(void)
{
    /* 初始化串口接收 ringbuffer  */
    ringbuffer_init(&uart_rxcb, uart_rx_buf, UART_RX_BUF_LEN);

    /* 初始化串口接收数据的信号量 */
    rt_sem_init(&(shell_rx_sem), "shell_rx", 0, 0);

    Lab_UART_Init(FIN_SHELL_LPUART, 115200); 
    NVIC_SetPriority(FIN_SHELL_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 3, 3));
    EnableIRQ(FIN_SHELL_IRQn); //使能LPUART1中断

    return 0;
}
INIT_BOARD_EXPORT(FinSH_Init);

/**
 * @brief       FinSH 组件 接收字节 实现
 * 
 * @retval      收到的字节数据
 * 
 * @date 2021-05-16
 */
char rt_hw_console_getchar(void)
{
    char ch = 0;

    /* 从 ringbuffer 中拿出数据 */
    while (ringbuffer_getchar(&uart_rxcb, (rt_uint8_t *)&ch) != 1)
    {
        rt_sem_take(&shell_rx_sem, RT_WAITING_FOREVER);
    }
    return ch;
}

/**
 * @brief       shell 发送数据
 * 
 * @param str   要发送的字符串
 * 
 * 
 * @date 2021-05-16
 */
void rt_hw_console_output(const char *str)
{
    size_t i = 0, length = 0;
    char ch = '\r';

    length = rt_strlen(str);
    for (i = 0; i < length; i++)
    {
        /* 等待base->STAT为空 */
        while (!(FIN_SHELL_LPUART->STAT & LPUART_STAT_TDRE_MASK))
            ;
        if (*(str + i) == '\n')
        {
            FIN_SHELL_LPUART->DATA = (uint8_t)ch;
        }
        FIN_SHELL_LPUART->DATA = *(str + i);
    }
}

/**
 * @brief FINSH 中断服务函数
 * 
 * @date 2021-05-17
 */
void TSHELL_IRQHandler(void)
{
    int ch = -1;
    /* enter interrupt */
    rt_interrupt_enter(); //在中断中一定要调用这对函数，进入中断

    while (1)
    {
        ch = -1;
        if ((FIN_SHELL_LPUART->STAT) & kLPUART_RxDataRegFullFlag) //接收中断
        {
            ch = LPUART_ReadByte(FIN_SHELL_LPUART);
        }
        if (ch == -1)
        {
            break;
        }
        /* 读取到数据，将数据存入 ringbuffer */
        ringbuffer_putchar(&uart_rxcb, ch);
    }
    rt_sem_release(&shell_rx_sem);
    /* leave interrupt */
    rt_interrupt_leave(); //在中断中一定要调用这对函数，离开中断

    __DSB(); //数据同步屏蔽指令
}

#endif
