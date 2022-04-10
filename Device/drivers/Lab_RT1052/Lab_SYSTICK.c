/**
 * @file Lab_SYSTICK.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief SysTick ��ʱ������
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "fsl_common.h"
#include "Lab_LED.h"
#include "Lab_SYSTICK.h"
#define EACH_PER_MS    25   //ÿ�� 25 ms �ж�һ��  systick ��ʱ����24λ���¼����Ķ�ʱ��  ���װ��ֵ16777215 / 600 000 000= 0.2796 ����ʱ27ms

struct time{
	
    uint32_t fac_us;                  //us��Ƶϵ��
	uint32_t fac_ms;                  //ms��Ƶϵ��
	volatile uint32_t millisecond;   //ms
	uint8_t ms_per_tick;              //1ms����systick��������
	
}timer;



/**
  * @brief    systime ��ʼ��
  *
  * @param    
  *
  * @return   
  *
  * @note     Ĭ�����ȼ���� �����޸�
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void systime_init()
{
	timer.fac_us = SystemCoreClock / 1000000;
	timer.fac_ms = SystemCoreClock / 1000;
	timer.ms_per_tick = EACH_PER_MS;
    timer.millisecond = 100;
	SysTick_Config((SystemCoreClock / 1000) * timer.ms_per_tick );   //����systick�ж�
    
//    //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
//    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
}



/**
  * @brief    systime �жϷ�����
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void SysTick_Handler(void)
{
	timer.millisecond += timer.ms_per_tick;
}



/**
  * @brief    ��ȡ��ǰʱ��
  *
  * @param    
  *
  * @return   ��ǰmsֵ
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
static inline uint32_t systime_get_current_time_ms(void)
{
    register uint32_t val, ms;
    do
    {
        ms  = timer.millisecond;
        val = SysTick->VAL; 
    }while(ms != timer.millisecond);
    
	return ms  -  val/timer.fac_ms;
}



/**
  * @brief    ��ȡ��ǰʱ��
  *
  * @param    
  *
  * @return   ��ǰusֵ
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
static inline uint32_t systime_get_current_time_us(void)
{
    register uint32_t val, ms;
    do
    {
        ms  = timer.millisecond;
        val = SysTick->VAL;
    }while(ms != timer.millisecond);
	return (uint32_t)((uint32_t)(ms * 1000) -  val / timer.fac_us);
}




/**
  * @brief    systime ��ʱ����
  *
  * @param    
  *
  * @return   
  *
  * @note     �����ʱ��Ҫ���� 4292s
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void systime_delay_us(uint32_t us)     
{
    uint32_t now = systime.get_time_us();
	uint32_t end_time = now + us - 1;
	while( systime.get_time_us() <= end_time)
    {
        ;
    }
}



/**
  * @brief    ��ʱ����
  *
  * @param    ms :  ��ʱʱ��
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void systime_delay_ms(uint32_t ms) 
{
    while(ms--)
    {
        systime.delay_us(1000);
    }
	
}


systime_t  systime = 
{
	systime_init,
	systime_get_current_time_us,
	systime_get_current_time_ms,
	systime_delay_us,
	systime_delay_ms
};


/**
  * @brief    ����systime ��ʱ��
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
void Test_Systick(void)
{
    LED_Init();                          //LED��ʼ��
    systime.init();                      //����systick��ʱ��
    uint32_t nowtime = 0;
    nowtime = systime.get_time_us();
    while(1)
    {
        
        if(systime.get_time_us() - nowtime >= 1000)
        {
            nowtime = systime.get_time_us();
            
            LED_ColorReverse(red);     //��ת��� ����ָʾ��������
            
        }
    }
    
}


/**
  * @brief    ����systime ��ʱ
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
void Test_SystickDelay(void)
{
    LED_Init();                          //LED��ʼ��
    systime.init();                      //����systick��ʱ��
    while(1)
    {
        systime.delay_ms(1);
        LED_ColorReverse(red);           //��ת��� ����ָʾ��������
        
    }
    
}



