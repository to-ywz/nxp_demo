/**
 * @file Lab_Camera.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief ����ͷ����
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_SGP18TEST_H
#define __Lab_SGP18TEST_H

#include "Lab_CSI.h"
/* ���ڴ����Ҫʹ������ */
extern pixel_t Image_Use[Use_ROWS][Use_Line];

/* ���ڴ��浱ǰ֡�ĵ�ַ */
extern uint32_t fullCameraBufferAddr;
/**
  * @brief    ��ȡ��Ҫʹ�õ�ͼ������
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/25 ���ڶ�
  */
void Get_Use_Image(void);

/**
  * @brief    TFT1.8 ��ʾͼ��
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/24 ����һ
  */
void Test_SGP18_Camera(void);

/**
  * @brief    OLED ��ʾͼ��
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/24 ����һ
  */
void Test_OLED_Camera(void);

/**
  * @brief    OLED ��ʾͼ��
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/25 ���ڶ�
  */
void Draw_Road(uint8_t img[Use_ROWS][Use_Line]);

/**
  * @brief    ��ֵ��
  *
  * @param    mode  ��  0��ʹ�ô����ֵ    1��ʹ��ƽ����ֵ
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/25 ���ڶ�
  */
void Get_01_Value(uint8_t mode);

int GetOSTU(pixel_t tmImage[Use_ROWS][Use_Line]);

void QS_sobel(pixel_t imageIn[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][Use_Line], uint8_t Threshold);

void QS_sobelAutoThreshold(pixel_t imageIn[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][Use_Line]);

void Draw_RoadMiddleLine(void);

#endif
