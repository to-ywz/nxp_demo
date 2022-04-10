#include "LowPassFilter.h"
#include "QS_PID.h"

#define M_2PI 6.283185307179586f

/**
 * @brief                   设置低通滤波的 频率 和 截止频率             
 * 
 * @param filter            滤波器实体
 * @param sample_freq       滤波频率
 * @param cutoff_freq       截止频率
 * 
 * 
 * @date 2021-05-28
 */
void LowPassFilter_Init(lowFilter_t *filter, float sample_freq, float cutoff_freq)
{
    filter->sample_freq = sample_freq;
    filter->cutoff_freq = cutoff_freq;

    if (filter->cutoff_freq <= 0.0f || filter->sample_freq <= 0.0f)
    {
        filter->alpha = 1.0;
    }
    else
    {
        float dt = 1.0f / filter->sample_freq;
        float rc = 1.0f / (M_2PI * filter->cutoff_freq);
        filter->alpha = constrain_float(dt / (dt + rc), 0.0f, 1.0f);
    }
}

/**
 * @brief               滤波
 * 
 * @param filter        滤波器实体
 * @param sample        需要滤波的信号
 *  
 * @retval              上次的输出信号
 * 
 * @date 2021-05-28
 */
float LowPassFilter_apply(lowFilter_t *filter, float sample)
{
    filter->oupt += (sample - filter->oupt) * filter->alpha;
    return filter->oupt;
}

// 实例化
low_filter_t lowPassFilter =
    {
        LowPassFilter_Init,
        LowPassFilter_apply,
};
