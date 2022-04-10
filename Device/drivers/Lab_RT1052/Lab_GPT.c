/**
 * @file Lab_GPT.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief GPT ����
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_clock.h"
#include "fsl_gpt.h"
#include "Lab_GPT.h"
#include "Lab_LED.h"
/**
  * @brief    GPT ͨ�ö�ʱ����ʼ��
  *
  * @param    
  *
  * @return   
  *
  * @note     ��ʼ��GPT������  GPT1��������ʱ��  GPT2������ȷ��ʱ
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Lab_GPT_Init(void)
{
    gpt_config_t gptConfig;
    
    GPT_GetDefaultConfig(&gptConfig);
    
    GPT_Init(GPT1, &gptConfig);          //��ʼ��GPT1
    GPT_Init(GPT2, &gptConfig);          //��ʼ��GPT2
    
    /* GPT �� PIT ʹ��ͬһʱ��ԴIGP��2��Ƶ Ĭ��75M */
    GPT_SetClockDivider(GPT1, 75);       // GPT1 ʱ�� 75M / 75 = 1M
    GPT_SetClockDivider(GPT2, 15);       // GPT2 ʱ�� 75M /  5 = 5M
    
    GPT_SetOutputCompareValue(GPT1, kGPT_OutputCompare_Channel1, 0XFFFFFFFF);   //GPT ��32Ϊ������ ����������ֵ 0xFFFF FFFF 
    GPT_SetOutputCompareValue(GPT2, kGPT_OutputCompare_Channel1, 0XFFFFFFFF);   //GPT ��32Ϊ������ ����������ֵ 0xFFFF FFFF 

}




/**
  * @brief    gpt ��ʱ����ȷ��ʱ
  *
  * @param    ms �� ��ʱʱ�� ms
  *
  * @return   
  *
  * @note     GPT ��32Ϊ������ �����ʱ4294967295 / 5 000000 = 868s
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void GPT_DelayMs(uint32_t ms)
{
    GPT_DelayUs(ms * 1000);
}



/**
  * @brief    gpt ��ʱ����ȷ��ʱ
  *
  * @param    us �� ��ʱʱ�� us
  *
  * @return   
  *
  * @note     GPT ��32Ϊ������ �����ʱ4294967295 / 5 000000 = 868s
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
inline void GPT_DelayUs(uint32_t us)
{
    /* Start Timer */
    GPT_StartTimer(GPT2);
    uint32_t time = us * 5 - 4;
    while(GPT_GetCurrentTimerCount(GPT2) <= time);
    
    GPT_StopTimer(GPT2);
}



/**
  * @brief    gpt ��ʱ����ʼ��ʱ
  *
  * @param   
  *
  * @return   
  *
  * @note     GPT ��32Ϊ������ �����ʱ4294967295 / 1 000000 = 4290s 
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void GPT_TimeStart(void)
{
    GPT_StopTimer(GPT1);
    GPT_StartTimer(GPT1); 
}



/**
  * @brief    gpt ��ʱ����ʼ��ʱ
  *
  * @param   
  *
  * @return   
  *
  * @note     GPT ��32Ϊ������ �����ʱ4294967295 / 1 000000 = 4290s 
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
uint32_t GPT_TimeGetUs(void)
{
    if(GPT_GetStatusFlags(GPT1, kGPT_RollOverFlag))   //���
    {
#ifdef DEBUG
        PRINTF("\n GPT ��ʱ�������\n");
#endif
        return 0;
    }
        
    else
        return GPT_GetCurrentTimerCount(GPT1) - 1;
}



/**
  * @brief    ����GPT ��ʱ
  *
  * @param    
  *
  * @return   
  *
  * @note     ʾ���� A7   500Hz��ת
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Test_GPTDelay(void)
{
    Lab_GPT_Init();                       //��ʼ��GPT������  GPT1��������ʱ��  GPT2������ȷ��ʱ            
    
    LED_Init();                          //LED��ʼ��
    GPT_DelayMs(100);

    while(1)
    {
        GPT_DelayMs(1);  
        LED_ColorReverse(red);           //��ת��� ����ָʾ��������
    }
}


/**
  * @brief    ����GPT ��ʱ��
  *
  * @param    
  *
  * @return   
  *
  * @note     ʾ���� A7   500Hz��ת
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Test_GPTTimer(void)
{
    Lab_GPT_Init();                       //��ʼ��GPT������  GPT1��������ʱ��  GPT2������ȷ��ʱ            
    
    LED_Init();                          //LED��ʼ��
    GPT_DelayMs(100);

    uint32_t now_time = 0;
    GPT_TimeStart();
    while(1)
    {
        if(GPT_TimeGetUs() - now_time >= 1000) 
        {
            now_time = GPT_TimeGetUs();
            
            LED_ColorReverse(red);       //��ת��� ����ָʾ��������
        }  
    }
}
