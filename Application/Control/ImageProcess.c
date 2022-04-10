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
#include "control_car.h"
#include "Lab_Camera.h"
#include "Lab_12864.h"
#include "ImageProcess.h"

// * 环岛标志位
uint8_t g_ucFlagRoundabout = 0;

// * 十字标志位
uint8_t g_ucFlagCross = 0;

// * 斑马线标志位
uint8_t g_ucFlagZebra = 0;

// *小车期望速度
int16_t g_sTargetVelocity = 200;

// *转向误差
int16_t g_sSteeringError = 0;

// *两轮差速
int16_t g_sDifferentVelocity = 0;

// *丢线标志位
uint8_t g_ucIsNoSide = 0;
uint8_t g_ucIsNoSide;
volatile uint8_t Field_Over_Flag;

extern uint8_t Pixel[Use_ROWS][Use_Line];

/*!
  * @brief    判断是否是斑马线
  *
  * @param    image ： 二值图像信息
  *
  * @return   0：不是， 1：是
  *
  * @note     思路：
  *
  * @see      
  *
  * @date     2021/6/23 星期二
  */
uint8_t RoadIsZebra(uint8_t image[Use_ROWS][Use_Line], uint8_t *flag)
{
    int i = 0, j = 0;
    int count = 0;

    for (i = ROAD_MAIN_ROW - 5; i > ROAD_MAIN_ROW + 5; i++)
    {
        for (j = 1; j < Use_Line; j++)
        {
            if (image[i][j] == 1 && image[i][j - 1] == 0)
            {
                count++;
            }
        }
        if (count > 4)
        {
            *flag = 1;
            return 1;
        }
    }

    return 0;
}

/*!
  * @brief    判断是否是十字
  *
  * @param    imageSide ： 图像边线信息
  * @param    flag      ： 十字状态信息
  *
  * @return   0：不是， 1：是
  *
  * @note     思路：两条边线距离车头近的行丢线 -- 然后一部分行不丢线  --  接着又丢线 则证明有十字
  *
  * @see      
  *
  * @date     2021/6/23 星期二
  */
uint8_t RoadIsCross(uint8_t imageSide[Use_ROWS][2], uint8_t *flag)
{
    int i = 0;
    uint8_t rightState = 0;
    int start[5] = {0, 0, 0, 0, 0}, end[5] = {0, 0, 0, 0, 0};
    uint8_t count = 0;
    uint8_t index = 0;

    /* 检测右侧边线距离车头近的行丢线 -- 然后一部分行不丢线  --  接着又丢线 */
    for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
    {
        if (imageSide[i][1] == 159)
        {
            count++;
        }
        else
        {
            if (count > 5 && index < 5)
            {
                start[index] = i + count;
                end[index] = i;
                index++;
            }
            count = 0;
        }
    }

    if (index > 1)
    {
        if (end[0] - start[1] > 5)
        {
            rightState = 1;
        }
    }

    index = 0;

    /* 检测左侧边线距离车头近的行丢线 -- 然后一部分行不丢线  --  接着又丢线 */
    if (rightState == 1)
    {
        for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
        {
            if (imageSide[i][0] == 0)
            {
                count++;
            }
            else
            {
                if (count > 5 && index < 5)
                {
                    start[index] = i + count;
                    end[index] = i;
                    index++;
                }
                count = 0;
            }
        }

        if (index > 1)
        {
            if (end[0] - start[1] > 5)
            {
                *flag = 1;
                return 1;
            }
        }
    }

    return 0;
}

/*!
  * @brief    获取十字边线
  *
  * @param    imageInput ： 二值图像信息
  * @param    imageOut   ： 边线数组
  *
  * @return   
  *
  * @note     思路：从中间向两边搜线
  *
  * @see      
  *
  * @date     2021/6/23 星期二
  */
void CrossGetSide(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageSide[Use_ROWS][2])
{
    int i = 0, j = 0;

    for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
    {
        for (j = (Use_Line - 4) / 2; j > 1; j--)
        {
            if (imageInput[i][j].gray[0])
            {
                imageSide[i][0] = j;
                break;
            }
        }

        for (j = (Use_Line - 4) / 2; j < Use_Line-1; j++)
        {
            if (imageInput[i][j].gray[0])
            {
                imageSide[i][1] = j;
                break;
            }
        }
    }
}

/*!
  * @brief    十字补线处理
  *
  * @param    imageInput ： 二值图像信息
  * @param    imageSide  ： 边线数组
  * @param    status     ：十字标志位   1：发现十字    2：进入十字   3：出十字
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2021/6/24 星期三
  */
void CrossProcess(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageSide[Use_ROWS][2], uint8_t *state)
{

    uint8_t pointX = 0, pointY = 0;
    uint8_t leftIndex = 0;
    static uint8_t count = 0;
    switch (*state)
    {
    case 1:
    {
        /* 重新获取边线 */
        CrossGetSide(imageInput, imageSide);

        /* 寻找跳变点 */
        if (ImageGetHop(imageSide, 1, &pointX, &pointY))
        {
            /* 补线 */
            ImageAddingLine(imageSide, 1, pointX, pointY, 0, ROAD_START_ROW);
        }

        leftIndex = pointY;
        pointX = 0;
        pointY = 0;

        /* 寻找跳变点 */
        if (ImageGetHop(imageSide, 2, &pointX, &pointY))
        {
            /* 补线 */
            ImageAddingLine(imageSide, 2, pointX, pointY, (Use_Line - 1), ROAD_START_ROW);
        }

        if (leftIndex != 0 && pointY != 0 && leftIndex >= ROAD_MAIN_ROW && pointY >= ROAD_MAIN_ROW)
        {
            *state = 2;
            count = 0;
        }

        if (count++ > 20)
        {
            *state = 2;
            count = 0;
        }

        break;
    }

    case 2:
    {

        /* 检查弧线 */
        if (RoundaboutGetArc(imageSide, 1, &leftIndex))
        {
            /* 重新确定左边界 */
            RoundaboutGetSide(imageInput, imageSide, 1);

            if (ImageGetHop(imageSide, 1, &pointX, &pointY))
            {
                /* 补线 */
                ImageAddingLine(imageSide, 1, pointX, pointY, imageSide[leftIndex][0], leftIndex);

                *state = 3;

                count = 0;
            }
            else
            {
                imageSide[ROAD_MAIN_ROW][0] = Use_Line / 2;
                imageSide[ROAD_MAIN_ROW][1] = Use_Line - 1;
            }
        }

        break;
    }

    case 3:
    {

        /* 重新确定左边界 */
        RoundaboutGetSide(imageInput, imageSide, 1);

        if (ImageGetHop(imageSide, 1, &pointX, &pointY))
        {
            /* 检查弧线 */
            if (RoundaboutGetArc(imageSide, 1, &leftIndex))
            {
                /* 补线 */
                ImageAddingLine(imageSide, 1, pointX, pointY, imageSide[leftIndex][0], leftIndex);
            }
            else
            {
                /* 补线 */
                ImageAddingLine(imageSide, 1, pointX, pointY, 0, ROAD_START_ROW);
            }

            if (pointY >= ROAD_MAIN_ROW)
            {
                *state = 0;
                count = 0;
            }
        }
        else
        {
            imageSide[ROAD_MAIN_ROW][0] = 120;
            imageSide[ROAD_MAIN_ROW][1] = Use_Line - 1;
        }

        if (count++ > 10)
        {
            *state = 0;
            count = 0;
        }

        break;
    }
    }
}

/*!
  * @brief    停车线处理
  *
  * @param    imageSide  ： 边线数组
  * @param    state      ： 停车状态  1：车库在左侧   2：车库在右侧
  * @param    speed      ： 速度
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2021/6/24 星期四
  */
void ZebraProcess(uint8_t imageSide[Use_ROWS][2], uint8_t state, int16_t *speed)
{
    static uint16_t count = 0;

    count++;

    if (state == 1)
    {
        imageSide[ROAD_MAIN_ROW][0] = 0;
        imageSide[ROAD_MAIN_ROW][1] = Use_Line / 2;
    }
    else
    {
        imageSide[ROAD_MAIN_ROW][0] = Use_Line / 2;
        imageSide[ROAD_MAIN_ROW][1] = Use_Line - 1;
    }

    if (count > 50)
    {
        *speed = 0;
        while (1)
            ;
    }
}

/**
 * @brief               判断是否是直道
 * 
 * @param imageSide     二值图像信息
 * 
 * @retval               0：不是直道
 *                       1：直道
 * 
 * @date 2021-05-28
 */
uint8_t RoadIsStraight(uint8_t imageSide[Use_ROWS][2])
{
    uint8_t i = 0;
    uint8_t leftState = 0, rightState = 0;

    /* 左边线是否单调 */
    for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
    {
        if (imageSide[i][0] + 3 < imageSide[i + 1][0])
        {
            leftState = 1;
            break;
        }
    }

    /* 右边线是否单调 */
    for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
    {
        if (imageSide[i][1] - 3 > imageSide[i + 1][1])
        {
            rightState = 1;
            break;
        }
    }

    if (leftState == 1 && rightState == 1)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief           环岛检测
 * 
 * @param image     边线信息
 * @param flag      环岛状态信息
 * 
 * @retval          0：不是
 *                  1：左环岛  
 *                  2：右环岛 
 * 
 * @note            一条边线严格单调
 *                  另一条边线距离车头近的行丢线
 *                  然后一部分行不丢线
 *                  接着又丢线 
 *                  则证明有环岛
 * 
 * @date 2021-05-28
 */
uint8_t RoadIsRoundabout(uint8_t image[Use_ROWS][2], uint8_t *flag)
{
    int i = 0;
    uint8_t leftState = 0, rightState = 0;
    int start[5] = {0, 0, 0, 0, 0}, end[5] = {0, 0, 0, 0, 0};
    uint8_t count = 0;
    uint8_t index = 0;

    /* 左边线是否单调 */
    for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
    {
        if (image[i][0] + 3 < image[i + 1][0])
        {
            leftState = 1;
            break;
        }
    }

    /* 右边线是否单调 */
    for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
    {
        if (image[i][1] - 3 > image[i + 1][1])
        {
            rightState = 1;
            break;
        }
    }

    /* 左边单调,  检测右侧是否是环岛 */
    if (leftState == 0)
    {
        for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
        {
            if (image[i][1] == Use_Line - 1)
            {
                count++;
            }
            else
            {
                if (count > 5 && index < 3)
                {
                    start[index] = i + count;
                    end[index] = i;
                    index++;
                }
                count = 0;
            }
        }

        if (index > 1)
        {
            if (end[0] - start[1] > 5)
            {
                *flag = 2;
                return 2;
            }
        }
    }

    /* 右边单调,  检测左侧是否是环岛 */
    if (rightState == 0)
    {
        for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
        {
            if (image[i][0] == 0)
            {
                count++;
            }
            else
            {
                if (count > 5 && index < 3)
                {
                    start[index] = i + count;
                    end[index] = i;
                    index++;
                }
                count = 0;
            }
        }

        if (index > 1)
        {
            if (end[0] - start[1] > 5)
            {
                *flag = 1;
                return 1;
            }
        }
    }

    return 0;
}

/**
 * @brief               获取环岛边线
 * 
 * @param imageInput    二值图像信息
 * @param imageSide     边线数组
 * @param status        1：左环岛  
 *                      2：右环岛
 * 
 * @note     环岛一边边线严格单调, 根据一边边线, 获取另一边线
 * 
 * @date 2021-05-28
 */

void RoundaboutGetSide(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageSide[Use_ROWS][2], uint8_t status)
{
    int i = 0, j = 0;

    switch (status)
    {

        /* 左环岛 */
    case 1:
    {
        /* 重新确定左边界 */
        for (i = ROAD_START_ROW; i > ROAD_END_ROW; i--)
        {
            for (j = Use_Line / 2; j > 0; j--)
            {
                if (imageInput[i][j].gray[0])
                {
                    imageSide[i][0] = j;
                    break;
                }
            }
        }
        break;
    }

    case 2:
    {
        /* 重新确定右边界 */
        for (i = ROAD_START_ROW; i > ROAD_END_ROW; i--)
        {
            for (j = Use_Line / 2; j < Use_Line; j++)
            {
                if (imageInput[i][j].gray[0])
                {
                    imageSide[i][1] = j;
                    break;
                }
            }
        }
        break;
    }
    }
}

/**
 * @brief               判断环岛边线是否存在弧形
 *  
 * @param imageSide     二值图像信息
 * @param status        边线数组
 * @param index         1：左环岛  
 *                      2：右环岛
 * 
 * @retval 
 * 
 * @date 2021-05-28
 */
uint8_t RoundaboutGetArc(uint8_t imageSide[Use_ROWS][2], uint8_t status, uint8_t *index)
{
    int i = 0;
    uint8_t inc = 0, dec = 0;
    switch (status)
    {
    case 1:
        for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
        {
            if (imageSide[i][0] != 0 && imageSide[i + 1][0] != 0)
            {
                if (imageSide[i][0] >= imageSide[i + 1][0])
                {
                    inc++;
                }
                else
                {
                    dec++;
                }

                /* 有弧线 */
                if (inc > 5 && dec > 5)
                {
                    *index = i + 5;
                    return 1;
                }
            }
            else
            {
                inc = 0;
                dec = 0;
            }
        }

        break;

    case 2:
        for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
        {
            if (imageSide[i][1] != Use_Line - 1 && imageSide[i + 1][1] != Use_Line - 1)
            {
                if (imageSide[i][1] > imageSide[i + 1][1])
                {
                    inc++;
                }
                else
                {
                    dec++;
                }

                /* 有弧线 */
                if (inc > 5 && dec > 5)
                {
                    *index = i + 5;
                    return 1;
                }
            }
            else
            {
                inc = 0;
                dec = 0;
            }
        }

        break;
    }

    return 0;
}

/**
 * @brief               补线处理
 * 
 * @param imageSide     边线
 * @param status        1：左边线补线   
 *                      2：右边线补线
 * @param startX        起始点 列数
 * @param startY        起始点 行数
 * @param endX          结束点 列数
 * @param endY          结束点 行数
 * 
 * @note                endY 一定要大于 startY
 * 
 * @date 2021-05-28
 */
void ImageAddingLine(uint8_t imageSide[Use_ROWS][2], uint8_t status, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
    int i = 0;

    /* 直线 x = ky + b*/
    double k = 0.0f, b = 0.0f;
    switch (status)
    {
    case 1:
    {
        k = (double)((double)endX - (double)startX) / (double)((double)endY - (double)startY);
        b = (double)startX - (double)startY * k;

        for (i = startY; i < endY; i++)
        {
            imageSide[i][0] = (uint8_t)(k * i + b);
        }
        break;
    }

    case 2:
    {
        k = (double)((double)endX - (double)startX) / (double)((double)endY - (double)startY);
        b = (double)startX - (double)startY * k;

        for (i = startY; i < endY; i++)
        {
            imageSide[i][1] = (uint8_t)(k * i + b);
        }
        break;
    }
    }
}

/**
 * @brief               寻找跳变点
 * 
 * @param imageSide     边线数组
 * @param state         1：左边界   
 *                      2：右边界
 * @param x             跳变点的 x
 * @param y             跳变点的 y  
 *  
 * @retval 
 * 
 * @date 2021-05-28
 */
#define ROUND_Diff 20
uint8_t ImageGetHop(uint8_t imageSide[Use_ROWS][2], uint8_t state, uint8_t *x, uint8_t *y)
{
    int i = 0;
    uint8_t px = 0, py = 0;
    uint8_t count = 0;
    switch (state)
    {
    case 1:
        /* 寻找跳变点 */
        for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
        {
            if (imageSide[i][0] == 0 && i > (ROAD_END_ROW + 5))
            {
                count++;

                if (count > 5)
                {
                    if (imageSide[i - 1][0] > (imageSide[i][0] + ROUND_Diff))
                    {
                        py = i - 1;
                        px = imageSide[py][0];
                        break;
                    }
                    if (imageSide[i - 2][0] > (imageSide[i - 1][0] + ROUND_Diff))
                    {
                        py = i - 2;
                        px = imageSide[py][0];
                        break;
                    }
                    if (imageSide[i - 3][0] > (imageSide[i - 2][0] + ROUND_Diff))
                    {
                        py = i - 3;
                        px = imageSide[py][0];
                        break;
                    }
                    if (imageSide[i - 4][0] > (imageSide[i - 3][0] + ROUND_Diff))
                    {
                        py = i - 4;
                        px = imageSide[py][0];
                        break;
                    }
                }
            }
            else
            {
                count = 0;
            }
        }

        if (py != 0)
        {
            *x = px;
            *y = py;
            return 1;
        }

        break;

    case 2:
        /* 寻找跳变点 */
        for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
        {
            if (imageSide[i][1] == Use_Line - 1 && i > (ROAD_END_ROW + 5))
            {
                count++;

                if (count > 5)
                {
                    if (imageSide[i - 1][1] < (imageSide[i][1] - ROUND_Diff))
                    {
                        py = i - 1;
                        px = imageSide[py][1];
                        break;
                    }
                    if (imageSide[i - 2][1] < (imageSide[i - 1][1] - ROUND_Diff))
                    {
                        py = i - 2;
                        px = imageSide[py][1];
                        break;
                    }
                    if (imageSide[i - 3][1] < (imageSide[i - 2][1] - ROUND_Diff))
                    {
                        py = i - 3;
                        px = imageSide[py][1];
                        break;
                    }
                    if (imageSide[i - 4][1] < (imageSide[i - 3][1] - ROUND_Diff))
                    {
                        py = i - 4;
                        px = imageSide[py][1];
                        break;
                    }
                }
            }
            else
            {
                count = 0;
            }
        }

        if (py != 0)
        {
            *x = px;
            *y = py;
            return 1;
        }

        break;
    }

    return 0;
}

/**
 * @brief                   环岛补线处理
 * 
 * @param imageInput        二值图像信息
 * @param imageSide         边线数组
 * @param state             环岛标志位   
 *                              1：发现左环岛   
 *                              2：发现右环岛   
 *                              3：左环岛即将入环  
 *                              4：右环岛即将入环  
 *                              5：左环岛即将出环  
 *                              6：右环岛即将出环
 * 
 * @note                    目前场地只有左环岛,右环岛加入赛道再编写代码
 * 
 * @date 2021-05-28
 */
void RoundaboutProcess(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageSide[Use_ROWS][2], uint8_t *state)
{
    int i = 0;
    uint8_t pointX = 0, pointY = 0;
    uint8_t err = 0;
    static uint8_t cnt = 0;
    switch (*state)
    {
        /* 发现左环岛 环岛出口处补线 */
    case 1:

        /* 重新确定左边界 */
        RoundaboutGetSide(imageInput, imageSide, 1);

        /* 检查弧线 */
        err = RoundaboutGetArc(imageSide, 1, &pointY);

        /* 有弧线 进行补线 连接弧线最右点 和 图像左下角 */
        if (err)
        {
            pointX = imageSide[pointY][0];

            /* 准备入环岛 */
            if ((pointY + 5) > ROAD_MAIN_ROW)
            {
                *state = 3;
            }
        }
        else
        {
            pointY = ROAD_START_ROW - 1;

            /* 没有弧线 进行补线 连接边线最右点 和 图像左下角 */
            for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
            {
                if (imageSide[i][0] > imageSide[pointY][0])
                {
                    pointY = i;
                }
            }

            pointX = imageSide[pointY][0];
        }

        /* 补线 */
        ImageAddingLine(imageSide, 1, pointX, pointY, 0, ROAD_START_ROW);

        break;

        /* 发现右环岛 环岛出口处补线 */
    case 2:
        /* 重新确定左边界 */
        RoundaboutGetSide(imageInput, imageSide, 2);

        /* 检查弧线 */
        err = RoundaboutGetArc(imageSide, 2, &pointY);

        /* 有弧线 进行补线 连接弧线最右点 和 图像左下角 */
        if (err)
        {
            pointX = imageSide[pointY][0];

            /* 准备入环岛 */
            if ((pointY - 5) > ROAD_MAIN_ROW)
            {
                *state = 4;
            }
        }
        else
        {
            pointY = ROAD_START_ROW - 1;

            /* 没有弧线 进行补线 连接边线最右点 和 图像左下角 */
            for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
            {
                if (imageSide[i][0] < imageSide[pointY][0])
                {
                    pointY = i;
                }
            }

            pointX = imageSide[pointY][0];
        }

        /* 补线 */
        ImageAddingLine(imageSide, 2, pointX, pointY, 0, ROAD_START_ROW);

        *state = 0;
        break;

        /* 准备进入环岛,  直道部分补线 */
    case 3:
        pointY = ROAD_START_ROW - 1;

        /* 重新确定左边界 */
        RoundaboutGetSide(imageInput, imageSide, 1);

        /* 检查弧线 */
        err = RoundaboutGetArc(imageSide, 1, &pointY);

        /* 有弧线 进行补线 连接弧线最右点 和 图像左下角 */
        if (err)
        {
            pointX = imageSide[pointY][0];

            if ((pointY + 5) > ROAD_MAIN_ROW)
            {
                /* 环岛出口补线 */
                ImageAddingLine(imageSide, 1, pointX, pointY, 0, ROAD_START_ROW);
            }
        }

        /* 环岛入口补线 */
        pointX = Use_Line / 3;
        pointY = ROAD_START_ROW - 1;

        /* 寻找跳变点 */
        ImageGetHop(imageSide, 1, &pointX, &pointY);

        if (pointY >= ROAD_MAIN_ROW && pointY != ROAD_START_ROW - 1)
        {
            imageSide[ROAD_MAIN_ROW][0] = 0;
            *state = 5;
        }

        /* 补线 */ // * 30?
        ImageAddingLine(imageSide, 2, pointX + 15, pointY, (Use_Line - 1), ROAD_START_ROW);

        break;

    case 4:

        break;

        /* 出环岛,  直道处补线 */
    case 5:

        /* 检查弧线 */
        err = RoundaboutGetArc(imageSide, 2, &pointY);

        if (err || cnt)
        {
            cnt++;

            imageSide[ROAD_MAIN_ROW][0] = 0;
            imageSide[ROAD_MAIN_ROW][1] = Use_Line / 3;
        }

        // * 20% ?
        if (cnt > 35)
        {
            cnt = 0;
            *state = 0;
        }

        break;

        /* 出环岛,  直道处补线 */
    case 6:

        break;
    }
}

/**
 * @brief               根据主跑行, 求取舵机偏差
 * 
 * @param imageSide     边线数组
 * @param lineIndex     主跑行
 * 
 * @retval 
 * 
 * @date 2021-05-28
 */
int16_t RoadGetSteeringError(uint8_t imageSide[Use_ROWS][2], uint8_t lineIndex)
{
    return imageSide[lineIndex][0] + imageSide[lineIndex][1] - Use_Line - 1;
}

/**
 * @brief               丢线检测
 * 
 * @param imageInput    二值图像信息
 * @param imageOut      边线数组
 * @param lineIndex     行
 * 
 * @retval              0：没有丢线   
 *                      1: 左边丢线  
 *                      2：右边丢线  
 *                      3：左右都丢线   
 *                      4：奇奇怪怪的状态(基本时错误了)
 * 
 * @date 2021-05-28
 */
uint8_t RoadIsNoSide(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][2], uint8_t lineIndex)
{
    uint8_t state = 0;
    int i = 0;
    // 45
    static uint8_t last = (Use_Line - 4) / 2;

    imageOut[lineIndex][0] = 0;
    imageOut[lineIndex][1] = Use_Line - 1;

    /* 用距离小车比较近的行,  判断是否丢线 */
    for (i = last; i > 1; i--)
    { // * 2~45 检测左边是否丢失
        if (imageInput[lineIndex][i].gray[0])
        {
            imageOut[lineIndex][0] = i;
            break;
        }
    }

    if (i == 1)
    {
        /* 左边界丢线 */
        state = 1;
    }

    for (i = last; i < Use_Line - 1; i++)
    { // * 45 ~ 90 检测右边界是否丢失
        if (imageInput[lineIndex][i].gray[0])
        {
            imageOut[lineIndex][1] = i;
            break;
        }
    }

    if (i == Use_Line - 1)
    {
        /* 左右边界丢线 */
        if (state == 1)
        {
            state = 3;
        }

        /* 右边界丢线 */
        else
        {
            state = 2;
        }
    }

    if (imageOut[lineIndex][1] <= imageOut[lineIndex][0])
    {
        state = 4;
    }
    return state;
}

/**
 * @brief               丢线处理
 * 
 * @param imageInput    二值图像信息
 * @param imageOut      边线数组
 * @param mode          丢线的边
 *                          1：左边丢线  
 *                          2：右边丢线  
 * @param lineIndex     丢线的行
 * 
 * 
 * @date 2021-05-28
 */
void RoadNoSideProcess(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][2], uint8_t mode, int lineIndex)
{
    int i = 0, j = 0, count = 0;

    switch (mode)
    {
    case 1:
        for (i = imageOut[lineIndex][1]; i > 1; i--)
        {
            count++;
            for (j = lineIndex; j > ROAD_END_ROW && lineIndex > count; j--)
            {
                if (imageInput[j][i].gray[0])
                {
                    imageOut[lineIndex - count][0] = 0;
                    imageOut[lineIndex - count][1] = i;
                    break;
                }
            }
        }
        break;

    case 2:
        for (i = imageOut[lineIndex][0]; i < Use_Line - 1; i++)
        {
            count++;
            for (j = lineIndex; j > ROAD_END_ROW && lineIndex > count; j--)
            {
                if (imageInput[j][i].gray[0])
                {
                    imageOut[lineIndex - count][0] = i;
                    imageOut[lineIndex - count][1] = Use_Line - 1;
                    break;
                }
            }
        }
        break;
    }
}

/**
  * @brief              获取边线
  * 
  * @param imageInput   二值图像信息
  * @param imageOut     边线数组
  * 
  * @retval             是否丢线
  *                         1: 右边丢线
  *                         2. 左边丢线
  * 
  * @note               从距离车头较近的行开始从中间向两边搜线
  *                     ( )
  * 
  * @date 2021-05-28
  */
uint8_t ImageGetSide(pixel_t imageInput[Use_ROWS][Use_Line], uint8_t imageOut[Use_ROWS][2])
{
    int i = 0, j = 0;

    // * 丢线检测
    RoadIsNoSide(imageInput, imageOut, ROAD_START_ROW);

    /* 离车头近的40行, 寻找边线 */
    for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
    {
        imageOut[i][0] = 0;
        imageOut[i][1] = Use_Line - 1;

        /* 根据边界连续特性 寻找边界 */
        for (j = imageOut[i + 1][0] + 5; j > 0; j--)
        { // * 左边线
            if (imageInput[i][j].gray[0])
            {
                imageOut[i][0] = j;
                break;
            }
        }

        for (j = imageOut[i + 1][1] - 5; j < Use_Line; j++)
        { // * 右边线
            if (imageInput[i][j].gray[0])
            {
                imageOut[i][1] = j;
                break;
            }
        }

        // * 此处采用的是图片中线,为了有更好的 效果我觉得可以赛道为边生成一个数组
        // * 产生一个缓冲效果,让中线更具有惯性
        /* 如果左边界 即将超出中线,  则检查是否右丢线 */
        if (imageOut[i][0] > (Use_Line / 2 - 5) /* 这里就是图像的中线 */ && imageOut[i][1] > (Use_Line - 3))
        { // * 42
#if BINARY
            /* 右丢线处理 */
            imageOut[i][1] = createPoint(RIGHT_LOSS, i);
#else
            RoadNoSideProcess(imageInput, imageOut, 2, i);

            if (i > 42)
            {
                imageOut[i][0] += 30;
            }
#endif
            return 1;
        }

        /* 如果右边界 即将超出中线,  则检查是否左丢线 */
        if (imageOut[i][1] < (Use_Line / 2 + 5) && imageOut[i][0] < (3))
        {
#if BINARY
            /* 左丢线处理 */
            imageOut[i][1] = createPoint(LEFT_LOSS, i);
#else
            RoadNoSideProcess(imageInput, imageOut, 1, i);

            if (i > 42)
            {
                imageOut[i][1] -= 30;
            }
#endif
            return 2;
        }
    }

    return 0;
}

/**
 * @brief               除单一的噪点
 * 
 * @param imageInput    滤波前图像
 * @param imageOut      滤波后图像
 * 
 * @note                检查边沿邻域内的9个点, 如果大于设置值, 则保留该点
 * 
 * @date 2021-05-28
 */
void ImagePortFilter(uint8_t imageInput[Use_ROWS][Use_Line], pixel_t imageOut[Use_ROWS][Use_Line])
{
    uint8_t temp = 0;

    for (int i = 1; i < Use_ROWS - 1; i++)
    {
        for (int j = 1; j < Use_Line - 1; j++)
        {
            temp = imageInput[i - 1][j - 1] + imageInput[i - 1][j] + imageInput[i - 1][j + 1] +
                   imageInput[i][j - 1] + imageInput[i][j] + imageInput[i][j + 1] +
                   imageInput[i + 1][j - 1] + imageInput[i + 1][j] + imageInput[i + 1][j + 1];

            /* 邻域内5个点是边沿 则保留该点 可以调节这里优化滤波效果 */
            if (temp > 4)
            {
                imageOut[i][j].gray[0] = 1;
            }
            else
            {
                imageOut[i][j].gray[0] = 0;
            }
        }
    }
}

// * 边线数组
extern uint8_t ImageSide[Use_ROWS][2];

uint8_t MiddleLine[Use_ROWS];

/**
 * @brief           滤波
 * 
 * @param mode      丢线:   1,2,3
 *                          LEFT_LOSS   : 左边线丢失
 *                          RIGHT_LOSS  : 右边线丢失
 *                          MIDDLE_LOSS : 中线丢失
 * @param line      丢失行
 * 
 * @retval          最小二乘法补充的点
 * 
 * @date 2021-06-18
 */
uint8_t createPoint(LostLine_Type mode, int line)
{
    uint8_t pose = 0;
    int8_t tmp = 0;
    double sumX = 0;
    double sumY = 0;
    double averageX = 0;
    double averageY = 0;
    double sumUp = 0;
    double sumDown = 0;
    double parameterA;
    double parameterB;
    switch (mode)
    {
    case LEFT_LOSS:
        /* 左边线丢失 */
        {
            pose = 0;
        }
        break;
    case RIGHT_LOSS:
        /* 右边线丢失 */
        {
            pose = 1;
        }
        break;
    case MIDDLE_LOSS:
        /* 中线丢失 */
        {
            pose = 0;
        }
        break;
    }

    // 取邻近的 POINT_COUNT 个点进行拟合
    while (++tmp <= POINT_SCAN_RANGE)
    {
        sumX += (line + tmp);
        sumY += ImageSide[line + tmp][pose];
    }
    --tmp;
    averageX = sumX / tmp;
    averageY = sumY / tmp;

    do
    {
        sumUp += (ImageSide[line + tmp][pose] - averageY) * (line + tmp - averageX);
        sumDown += (line + tmp - averageX) * (line + tmp - averageX);
    } while (--tmp > 0);

    if (sumDown == 0)
        parameterB = 0;
    else
        parameterB = sumUp / sumDown;

    parameterA = averageY - parameterB * averageX;
    return (uint8_t)(parameterA + parameterB * line + 0.5);
}
