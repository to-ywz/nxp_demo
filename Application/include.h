#ifndef __INCLUDE_H
#define __INCLUDE_H


// #define EnableInterrupts  __asm(" CPSIE i");//开总中断
// #define DisableInterrupts __asm(" CPSID i");//关总中断


#define LabMT9V034    //选择使用神眼摄像头模块

#ifdef LabMT9V034 //LabMT9V034模块
    #define CAMERA_FPS  100
    #define APP_CAMERA_WIDTH  (IMAGEW)
    #define APP_CAMERA_HEIGHT (IMAGEH/2)  //一个uint16_t里面装了两个像素， 一行IMAGEW 里面其实装了两行的像素点，所以高度/2
    #define APP_BPP 2 //像素格式，
    #define  Use_ROWS  60    //使用图像高度
    #define  Use_Line  94    //使用图像宽度
#else            //LabOV7725模块
    //#define LabOV7725RGB   //使用7725RGB   
    #define LabOV7725YUV     //使用7725灰度
    #define CAMERA_FPS  100
    #define APP_CAMERA_WIDTH  320
    #define APP_CAMERA_HEIGHT 240

    #define APP_BPP 2 //像素格式
    #define  Use_ROWS  120    //使用图像高度
    #define  Use_Line  160    //使用图像宽度
#endif

/* 这里主要存放一些全局宏定义 */

/* 显示屏幕 */
#define OLED



/* MPU6050   只能使用 硬件IIC 和软件IIC */
/* ICM20602  能使用 硬件IIC 和软件IIC  硬件SPI 和软件SPI */
/* 龙邱九轴  只能使用 硬件IIC 和软件IIC */
/* 宏定义 使用不同的接线方式 */
#define USE_HAL_SPI  0
#define USE_SOFT_SPI 1
#define USE_SOFT_IIC 2
#define USE_HAL_IIC  3
#define USE_Track    1
#endif

