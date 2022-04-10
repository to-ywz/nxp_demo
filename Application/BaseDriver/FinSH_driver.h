
/**
 * @file FinSH_driver.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief   RT-Thread 的 FinSH 组件 驱动
 * @version 0.1
 * @date 2021-05-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __FINSH_DRIVER_H__
#define __FINSH_DRIVER_H__

#include "enabledef.h"

// * 在 enable.h 中定义
#if USING_FINSH 

#include <rtthread.h>
#include "fsl_lpuart.h"
#include "ringbuffer.h"
// tShell
#define SHELL_USING_LPUART1 1
#define SHELL_USING_LPUART2 0
#define SHELL_USING_LPUART3 0
#define SHELL_USING_LPUART4 0
#define SHELL_USING_LPUART5 0
#define SHELL_USING_LPUART6 0
#define SHELL_USING_LPUART7 0
#define SHELL_USING_LPUART8 0

#define UART_RX_BUF_LEN 16

#if SHELL_USING_LPUART1
    #define FIN_SHELL_LPUART        LPUART1             // * tShell 串口
    #define FIN_SHELL_IRQn          LPUART1_IRQn        // * tShell 中断号
    #define TSHELL_IRQHandler       LPUART1_IRQHandler  // * tShell 中断服务函数    
#endif
#if SHELL_USING_LPUART2
    #define FIN_SHELL_LPUART        LPUART2             // * tShell 串口
    #define FIN_SHELL_IRQn          LPUART2_IRQn        // * tShell 中断号
    #define TSHELL_IRQHandler       LPUART2_IRQHandler  // * tShell 中断服务函数    
#endif
#if SHELL_USING_LPUART3
    #define FIN_SHELL_LPUART        LPUART3             // * tShell 串口
    #define FIN_SHELL_IRQn          LPUART3_IRQn        // * tShell 中断号
    #define TSHELL_IRQHandler       LPUART3_IRQHandler  // * tShell 中断服务函数    
#endif
#if SHELL_USING_LPUART4
    #define FIN_SHELL_LPUART        LPUART4             // * tShell 串口
    #define FIN_SHELL_IRQn          LPUART4_IRQn        // * tShell 中断号
    #define TSHELL_IRQHandler       LPUART4_IRQHandler  // * tShell 中断服务函数    
#endif
#if SHELL_USING_LPUART5
    #define FIN_SHELL_LPUART        LPUART5             // * tShell 串口
    #define FIN_SHELL_IRQn          LPUART5_IRQn        // * tShell 中断号
    #define TSHELL_IRQHandler       LPUART5_IRQHandler  // * tShell 中断服务函数    
#endif
#if SHELL_USING_LPUART6
    #define FIN_SHELL_LPUART        LPUART6             // * tShell 串口
    #define FIN_SHELL_IRQn          LPUART6_IRQn        // * tShell 中断号
    #define TSHELL_IRQHandler       LPUART6_IRQHandler  // * tShell 中断服务函数    
#endif
#if SHELL_USING_LPUART7
    #define FIN_SHELL_LPUART        LPUART7             // * tShell 串口
    #define FIN_SHELL_IRQn          LPUART7_IRQn        // * tShell 中断号
    #define TSHELL_IRQHandler       LPUART7_IRQHandler  // * tShell 中断服务函数    
#endif
#if SHELL_USING_LPUART8
    #define FIN_SHELL_LPUART        LPUART8             // * tShell 串口
    #define FIN_SHELL_IRQn          LPUART8_IRQn        // * tShell 中断号
    #define TSHELL_IRQHandler       LPUART8_IRQHandler  // * tShell 中断服务函数    
#endif

#define FIN_SHELL_BAUDRATE      115200          // * tShell 波特率

#endif

#endif

