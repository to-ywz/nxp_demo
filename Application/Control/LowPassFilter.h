#ifndef __FILTER_H
#define __FILTER_H

#include "stdint.h"

// 用于 编码器
/* 低通滤波器结构体 */
typedef struct
{
	float sample_freq;     //输入信号频率
    float cutoff_freq;     //截止频率
    float alpha;           //系数
    float oupt;            //低通滤波器输出
}lowFilter_t;


typedef struct
{
    void (* init)(lowFilter_t *filter, float sample_freq, float cutoff_freq);
	float (* apply)(lowFilter_t *filter, float sample) ;
}low_filter_t;


extern low_filter_t lowPassFilter;

#endif //__INERTIAL_H


