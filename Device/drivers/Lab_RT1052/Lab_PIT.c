/**
 * @file Lab_PIT.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief PIT 驱动
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "fsl_pit.h"
#include "Lab_GPIO_Cfg.h"
#include "Lab_PIT.h"
#include "Lab_LED.h"

/*测试PIT用  volatile易变的，在中断里面会改变的变量定义时最好加上，告诉编译器不要优化，每次读取都从该变量的地址读取*/
volatile uint16_t pitIsrCnt0 = 0;   
volatile uint16_t pitIsrCnt1 = 0;
volatile uint16_t pitIsrCnt2 = 0; 
volatile uint16_t pitIsrCnt3 = 0; 

/**
  * @brief    测试PIT中断
  *
  * @param    
  *
  * @return   
  *
  * @note     用示波器测 C12 500Hz   A13 100Hz
  *
  * @example  
  *
  * @date     2019/6/4 星期二
  */
void Test_PIT(void)
{ 
    LED_Init();                             //初始化LED
    
    Lab_PIT_Init(kPIT_Chnl_0, 1000UL);       //1 000us 一次中断
    Lab_PIT_Init(kPIT_Chnl_1, 5000UL);       //5 000us 一次中断
    Lab_PIT_Init(kPIT_Chnl_2, 1000000UL);    //1000 000us 一次中断
    
    while (true)
    {
        if (pitIsrCnt0)
        {
            PT2_22 = !PT2_22;             //翻转 C12         
            pitIsrCnt0 = 0;
        }
        if (pitIsrCnt1)
        {
            PT2_25 = !PT2_25;             //翻转 A13    
            pitIsrCnt1=0;
        }
        if (pitIsrCnt2)
        {
            LED_ColorReverse(red); 
            pitIsrCnt2=0;
        }
    }
}


/**
  * @brief    PIT定时器初始化
  *
  * @param    channel： PIT通道 kPIT_Chnl_0 - kPIT_Chnl_3
  * @param    count  ： 定时器时间 us
  *
  * @return   
  *
  * @note     PIT和GPT使用 同一时钟源 默认IPG/2时钟 75M
  *
  * @example  Lab_PIT_Init(kPIT_Chnl_0, 5000);  //开启通道0定时器中断，每5000us中断一次
  *
  * @date     2019/6/4 星期二
  */
void Lab_PIT_Init(pit_chnl_t channel, uint32_t count)
{
    static uint8_t pit_count = 0;
    
    /* 防止PIT多次初始化 */
    if(pit_count == 0)
    {
        pit_count++;
        
        /* PIT初始化结构体 */
        pit_config_t pitConfig;                
        
        /*
        * pitConfig.enableRunInDebug = false;  
        */
        PIT_GetDefaultConfig(&pitConfig);   //获取默认参数
        
        pitConfig.enableRunInDebug = false;
        PIT_Init(PIT, &pitConfig);          //初始化PIT
        
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(PIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        
        /* Enable at the NVIC */
        EnableIRQ(PIT_IRQn);                //使能中断
        
    }
    
    /* 设置PIT通道和定时时间 PIT默认使用IPG时钟的二分频 75M时钟 */
    PIT_SetTimerPeriod(PIT, channel, USEC_TO_COUNT(count, CLOCK_GetFreq(kCLOCK_IpgClk)/2)); 
    
    //清除中断标志位
    PIT_ClearStatusFlags(PIT, channel, kPIT_TimerFlag); 
    
    //使能通道中断
    PIT_EnableInterrupts(PIT, channel, kPIT_TimerInterruptEnable);  

    //开启定时器
    PIT_StartTimer(PIT, channel);   
}

