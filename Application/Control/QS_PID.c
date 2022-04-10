/**
 * @file QS_PID.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief   PID控制器实现
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "QS_PID.h"

/**
 * @brief           获取绝对值
 * 
 * @param a         int 型数据
 *      
 * @retval          取绝对值后的值
 * 
 * @date 2021-05-19
 */
int myabs(int a) //取绝对值
{
    int temp;
    if (a < 0)
        temp = -a;
    else
        temp = a;
    return temp;
}

/**
 * @brief           限幅函数
 * 
 * @param amt       参数
 * @param low       最低值
 * @param high      最高值
 * 
 * @retval 
 * 
 * @date 2021-05-19
 */
float constrain_float(float amt, float low, float high)
{
    return ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)));
}

/**
 * @brief Construct a new Pid Init object
 * 
 * @param pid   PID 控制器
 * @param kp    kp 值
 * @param ki    ki 值
 * @param kd    kd 值
 * 
 * 
 * @date 2021-05-29
 */
void PidInit(pid_param_t *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->imax = 0;
    pid->out_p = 0;
    pid->out_i = 0;
    pid->out_d = 0;
    pid->out = 0;
    pid->integrator = 0;
    pid->last_error = 0;
    pid->last_derivative = 0;
    pid->last_t = 0;
}

/**
 * @brief           pid位置式控制器输出
 * 
 * @param pid       pid参数
 * @param error     pid输入误差
 * 
 * @retval 
 * 
 * @date 2021-05-19
 */
float PidLocCtrl(pid_param_t *pid, float error)
{
    /* 累积误差 */
    pid->integrator += error;

    /* 误差限幅 */
    constrain_float(pid->integrator, -pid->imax, pid->imax);

    pid->out_p = pid->kp * error;
    pid->out_i = pid->ki * pid->integrator;
    pid->out_d = pid->kd * (error - pid->last_error);

    pid->last_error = error;

    pid->out = pid->out_p + pid->out_i + pid->out_d;

    return pid->out;
}

/**
 * @brief           pid增量式控制器输出
 * 
 * @param pid       pid参数
 * @param error     pid输入误差
 * 
 * @retval          PID输出结果   注意输出结果已经包涵了上次结果
 * 
 * @date 2021-05-19
 */
float PidIncCtrl(pid_param_t *pid, float error)
{

    pid->out_p = pid->kp * (error - pid->last_error);
    pid->out_i = pid->ki * error;
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    pid->out = pid->out_p + pid->out_i + pid->out_d;

    return pid->out;
}
