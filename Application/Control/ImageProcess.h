/**
 * @file ImageProcess.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief   图像处理, Control 文件夹核心文件
 * @version 0.1
 * @date 2021-05-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __IMAGEPROCESS_H_
#define __IMAGEPROCESS_H_

#include "control_car.h"
#include "Lab_Camera.h"
#include "Lab_12864.h"

void TFTSPI_BinRoadSide(uint8_t imageOut[Use_ROWS][2]);
uint8_t RoadIsStraight(uint8_t imageSide[Use_ROWS][2]);
uint8_t RoadIsZebra(uint8_t image[Use_ROWS][Use_Line], uint8_t *flag);
uint8_t RoadIsCross(uint8_t imageSide[Use_ROWS][2], uint8_t *flag);
uint8_t RoadIsRoundabout(uint8_t image[Use_ROWS][2], uint8_t *flag);
void RoundaboutGetSide(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageSide[Use_ROWS][2], uint8_t status);
uint8_t RoundaboutGetArc(uint8_t imageSide[Use_ROWS][2], uint8_t status, uint8_t *index);
void ImageAddingLine(uint8_t imageSide[Use_ROWS][2], uint8_t status, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
uint8_t ImageGetHop(uint8_t imageSide[Use_ROWS][2], uint8_t state, uint8_t *x, uint8_t *y);
void RoundaboutProcess(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageSide[Use_ROWS][2], uint8_t *state);
void CrossGetSide(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageSide[Use_ROWS][2]);
void CrossProcess(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageSide[Use_ROWS][2], uint8_t *state);
void ZebraProcess(uint8_t imageSide[Use_ROWS][2], uint8_t state, int16_t *speed);
int16_t RoadGetSteeringError(uint8_t imageSide[Use_ROWS][2], uint8_t lineIndex);
uint8_t RoadIsNoSide(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][2], uint8_t lineIndex);
void RoadNoSideProcess(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][2], uint8_t mode, int lineIndex);
uint8_t ImageGetSide(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][2]);
void ImagePortFilter(uint8_t imageInput[Use_ROWS][Use_Line], pixel_t imageOut[Use_ROWS][Use_Line]);
void ImageProcess(void);
uint8_t createPoint(LostLine_Type mode, int line);
#endif
