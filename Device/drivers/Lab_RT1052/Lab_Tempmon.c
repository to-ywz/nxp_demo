/**
 * @file Lab_Tempmon.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief 温度检测
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "fsl_debug_console.h"
#include "fsl_tempmon.h"
                      
/* 声明外部延时函数 */
extern void delayms(uint16_t ms);

/**
  * @brief    测试读取温度
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/11 星期二
  */
void Test_Tempmon(void)
{
    float temperature = 0U; 
    tempmon_config_t config;
    

    PRINTF("芯片温度测试例程. \r\n");
    

    /* 默认的测量频率 
    config->frequency = 0x03U;
     默认高报警温度
    config->highAlarmTemp = 40U;
     默认紧急报警温度 
    config->panicAlarmTemp = 90U;
     默认低报警温度 
    config->lowAlarmTemp = 20U;*/
    TEMPMON_GetDefaultConfig(&config);

    config.frequency = 0x03U;
    config.highAlarmTemp = 40U;
    config.lowAlarmTemp = 20;
    config.panicAlarmTemp = 80U;
    
    TEMPMON_Init(TEMPMON, &config);
    TEMPMON_StartMeasure(TEMPMON);

    /* 得到温度 */
    temperature = TEMPMON_GetCurrentTemperature(TEMPMON);

    PRINTF("芯片当前温度： %.1f ℃. \r\n", temperature);

    while (1)
    {
   
        delayms(10000);

        temperature = TEMPMON_GetCurrentTemperature(TEMPMON);
        PRINTF("芯片当前温度： %.1f ℃. \r\n", temperature);
    }
    

}




