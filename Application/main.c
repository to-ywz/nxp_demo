/**
 * @file main.c
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief  DEMO TEST
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <rtthread.h>
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "bsp.h"
#include "include.h"
#include "control_car.h"
#include "MotorCtrl.h"
#include "ServoCtrl.h"
#include "ImageProcess.h"

static rt_thread_t led_Thread;
static rt_thread_t KeyScan_Thread;
static rt_thread_t Camera_Thread;
static rt_thread_t oled_Thread;
static rt_timer_t PID_timer1;
static struct rt_semaphore image_Sem;

static int StartSteer = 0;

extern uint8_t Pixel[Use_ROWS][Use_Line];
uint16_t servoDuty = SERVO_MID;
void LED_entry(void *arg);
void KeyScan_entry(void *arg);
void Motor_entry(void *arg);
void OLED_entry(void *arg);
void Camera_entry(void *arg);
static void timeout1(void *parameter);
extern void delayms(uint16_t ms);
/*!
 * @brief Main function
 */
int main(void)
{
	// Lab_SetMotorDty(1, 2300);
	// Lab_SetMotorDty(2, 2300);
	// delayms(4000);
	// Lab_PWM_SetDuty(PWM2, kPWM_Module_3, kPWM_PwmA, SERVO_RIGHT_LIMIT);
	// delayms(3000);

	/* 创建定时器1  周期定时器 */
	PID_timer1 = rt_timer_create("PID", timeout1,
								 RT_NULL, 10, RT_TIMER_FLAG_PERIODIC);
	if (PID_timer1 != RT_NULL)
		rt_timer_start(PID_timer1);

	// 存活表示线程
	led_Thread =
		rt_thread_create("led_B", &LED_entry, RT_NULL, 128, 6, 20);
	// 按键扫描
	KeyScan_Thread =
		rt_thread_create("keyScan", &KeyScan_entry, RT_NULL, 128, 4, 20);
	// oled 刷新
	oled_Thread =
		rt_thread_create("oled", &OLED_entry, RT_NULL, 300, 5, 20);
	// 摄像头数据采集
	Camera_Thread =
		rt_thread_create("camera", &Camera_entry, RT_NULL, 512, 4, 30);

	// 启动线程
	if (led_Thread)
	{
		rt_thread_startup(led_Thread);
	}
	if (KeyScan_Thread)
	{
		// rt_thread_startup(KeyScan_Thread);
	}
	if (Camera_Thread)
	{
		rt_thread_startup(Camera_Thread);
	}
	if (oled_Thread)
	{
		rt_thread_startup(oled_Thread);
	}
}

/* 定时器 1 超时函数 */
static void timeout1(void *parameter)
{
	static uint8_t cnt = 0;

	SteeringCtrl(-g_sSteeringError);

	if (++cnt >= 5)
	{
		SpeedCtrl(motor.TargetVelocity, g_sDifferentVelocity);
		cnt = 0;
	}
}

//

uint8_t ImageSide[Use_ROWS][2];
uint8_t myPixel[Use_ROWS][Use_Line];

void draw_trackSide(void)
{
	int i = 0;
#if USE_Track
	for (i = 0; i < Use_ROWS; i++)
	{
		Pixel[i][ImageSide[i][0]] = 0xff;
		Pixel[i][ImageSide[i][1]] = 0xff;
		Pixel[i][(ImageSide[i][0] + ImageSide[i][1]) / 2] = 0xff;
	}
	for (i = 0; i < Use_Line; i++)
	{ // * 画出主跑行
		Pixel[ROAD_MAIN_ROW][i] = 0xff;
	}
#else
	rt_memset(myPixel, 0, Use_ROWS * Use_Line);
	for (i = 0; i < Use_ROWS; i++)
	{
		myPixel[i][ImageSide[i][0]] = 0xff;
		myPixel[i][ImageSide[i][1]] = 0xff;
		myPixel[i][ImageSide[i][0] + (ImageSide[i][1] - ImageSide[i][0]) / 2] = 0xff;
	}
	for (i = 0; i < Use_Line; i++)
	{ // * 画出主跑行
		myPixel[ROAD_MAIN_ROW][i] = 0xff;
	}
#endif
}

#ifdef LCD_DEBUG
static void Img_printf(void)
{
	rt_kprintf("AA");
	for (int i = 0; i < Use_ROWS; i++)
	{
		for (int j = 0; j < Use_Line; j++)
		{
			rt_kprintf("%d", Pixel[i][j]);
		}
	}
	rt_kprintf("CCCC");
}
static void Img_sidePrintf(void)
{
	printf("[");
	for (int i = 0; i < Use_ROWS; i++)
	{
		printf("%d,", ImageSide[i][0]);
		printf("%d,", ImageSide[i][1]);
	}
	printf("]");
}
#endif

/**
 * @brief 		Camera 线程
 * 
 * @date 2021-05-26
 */
void Camera_entry(void *arg)
{
	rt_sem_init(&(image_Sem), "image", 0, 0);
	while (1)
	{
		//等待摄像头CSI缓存区满
		while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))
		{
			rt_thread_mdelay(10);
		}
		//获取想要使用的大小
		Get_Use_Image();

		Get_01_Value(2);

		/* 对边沿信息进行滤波处理 去除单一噪点 */
		ImagePortFilter(Pixel, Image_Use);

		/* 提取赛道边线 */
		g_ucIsNoSide = ImageGetSide(Image_Use, ImageSide);

		ZebraProcess(ImageSide, &StartSteer, );

		if (g_ucFlagRoundabout == 0 && g_ucFlagCross == 0 && g_ucFlagZebra == 0)
		{
			/* 检测环岛 */
			RoadIsRoundabout(ImageSide, &g_ucFlagRoundabout);
		}

		if (g_ucFlagRoundabout)
		{
			/* 环岛处理 */
			RoundaboutProcess(Image_Use, ImageSide, &g_ucFlagRoundabout);
		}

		if (g_ucFlagRoundabout == 0 && g_ucFlagCross == 0 && g_ucFlagZebra == 0)
		{
			/* 检测十字 */
			RoadIsCross(ImageSide, &g_ucFlagCross);
		}

		if (g_ucFlagCross)
		{
			/* 十字处理 */
			CrossProcess(Image_Use, ImageSide, &g_ucFlagCross);
		}

		// * 根据主跑行, 求取舵机偏差
		g_sSteeringError = RoadGetSteeringError(ImageSide, ROAD_MAIN_ROW);

		// * OLED 显示 赛道
		draw_trackSide();

		rt_sem_release(&image_Sem);
	}
}

#define PWM_DEBUG 0
void OLED_entry(void *arg)
{
#if PWM_DEBUG
	char txt[24] = {0};
#endif
	while (1)
	{
#if PWM_DEBUG == 1
		sprintf(txt, "PWM_L:%6d", motor.PWM_L);
		LCD_P6x8Str(13, 3, txt);
		printf(txt);
		sprintf(txt, "PWM_R:%6d", motor.PWM_R);
		LCD_P6x8Str(13, 4, txt);
		printf(txt);
#elif PWM_DEBUG == 2
		if (RT_EOK == rt_sem_trytake(&image_Sem))
		{
			printf("[");
			for (int i = 0; i < Use_ROWS; i++)
			{
				for (int j = 0; j < Use_Line; j++)
				{
					printf("%d,", myPixel[i][j]);
				}
			}
			printf("]");
			Draw_Road(myPixel);
		}

#else
		if (RT_EOK == rt_sem_trytake(&image_Sem))
		{
#if USE_Track
			Draw_Road(Pixel);
#else
			Draw_Road(myPixel);
#endif
		}
#endif
		rt_thread_mdelay(20);
	}
}

/**
 * @brief 
 * 
 * @param arg 
 */
void KeyScan_entry(void *arg)
{
	while (1)
	{
		rt_thread_mdelay(50);
	}
}

void LED_entry(void *arg)
{
	while (1)
	{
		LED_ColorReverse(B_blue);
		rt_thread_mdelay(500);
	}
}

/**
  * @brief    不精确延时
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @example  delayms(100);
  *
  * @date     2019/4/22 星期一
*/
void delayms(uint16_t ms)
{
	volatile uint32_t i = 0;
	while (ms--)
	{
		for (i = 0; i < 20000; ++i)
		{
			__asm("NOP"); /* delay */
		}
	}
}
