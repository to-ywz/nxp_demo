/**
 * @file Lab_Camera.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief 摄像头驱动
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_SGP18TEST_H
#define __Lab_SGP18TEST_H

#include "Lab_CSI.h"
/* 用于存放需要使用数据 */
extern pixel_t Image_Use[Use_ROWS][Use_Line];

/* 用于储存当前帧的地址 */
extern uint32_t fullCameraBufferAddr;
/**
  * @brief    获取需要使用的图像数组
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/25 星期二
  */
void Get_Use_Image(void);

/**
  * @brief    TFT1.8 显示图像
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/24 星期一
  */
void Test_SGP18_Camera(void);

/**
  * @brief    OLED 显示图像
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/24 星期一
  */
void Test_OLED_Camera(void);

/**
  * @brief    OLED 显示图像
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/25 星期二
  */
void Draw_Road(uint8_t img[Use_ROWS][Use_Line]);

/**
  * @brief    二值化
  *
  * @param    mode  ：  0：使用大津法阈值    1：使用平均阈值
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/25 星期二
  */
void Get_01_Value(uint8_t mode);

int GetOSTU(pixel_t tmImage[Use_ROWS][Use_Line]);

void QS_sobel(pixel_t imageIn[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][Use_Line], uint8_t Threshold);

void QS_sobelAutoThreshold(pixel_t imageIn[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][Use_Line]);

void Draw_RoadMiddleLine(void);

#endif
