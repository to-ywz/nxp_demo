/**
 * @file Lab_RDA5807.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief RDA5807 ����
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __Lab_RDA5807_H
#define __Lab_RDA5807_H

#include "Lab_GPIO_Cfg.h"
#include "fsl_common.h"
#include "Lab_GPIO.h"
#include "stdint.h"


//RDA �ļĴ�����ַ
#define RDA_R00		0x00  //����16��λ��ID =0x5800
#define RDA_R02		0x02  //DHIZ[15],DMUTE[14]����,MONO[13]����,BASS[12]�ص���,SEEKUP[9],SEEK[8],SKMODE[7],CLK_MODE[6:4]ʱ��Դѡ��,SOFTRESET[1]��λ,ENABLE[0]��Դʹ��
#define RDA_R03		0x03  //CHAN[15:6],TUNE[4],BAND[3:2],SPACE[1:0] ����Ƶ�� ���� ����
#define RDA_R04		0x04  //STCIEN[14],DE[11],I2Senable[6],
#define RDA_R05		0x05  //INT_MODE[15],SEEKTH[14:8](�趨�Զ������ź�ǿ�ȷ�ֵ),LNA_PORT_SEL[7:6]=0b10,LNA_ICSEL_BIT[5:4],VOLUME[3:0]����;
#define RDA_R0A		0x0A  //STC[14]seek complete SF[13]seek fail readchan[9:0]��ǰƵ��
#define RDA_R0B		0x0B  //RSSI[15:9],FM TRUE[8]��ǰƵ����һ����Ŀ̨

//IIC������ַ0010000B�����϶�д��־����0x22��д����0x23�����������ַ�ʽ���Ե�������Ӧ�ļĴ������������ҿ���ֱ�Ӷ�дÿһ���Ĵ�����
#define RDA_READ       0x23  //��RDA5807M��0x23
#define RDA_WRITE	   0x22  //дRDA5807M��0x22

#define SOFT_FMI2C_SCL_PIN   A13   /*!< A13  ��Ϊ SCL */
#define SOFT_FMI2C_SDA_PIN   A12   /*!< A12  ��Ϊ SDA */

#define FMSDA_OUT        DIR2_24 = 1
#define FMSDA_IN         DIR2_24 = 0

#define FMI2C_SCL_INIT   Lab_PinInit(SOFT_FMI2C_SCL_PIN, PIN_MODE_OUTPUT, 1)
#define FMI2C_SDA_INIT   Lab_PinInit(SOFT_FMI2C_SDA_PIN, PIN_MODE_INPUT_PULLUP, 1)

#define FMI2C_SCL_H      Lab_PinWrite(SOFT_FMI2C_SCL_PIN, 1)
#define FMI2C_SCL_L      Lab_PinWrite(SOFT_FMI2C_SCL_PIN, 0)

#define FMI2C_SDA_H      Lab_PinWrite(SOFT_FMI2C_SDA_PIN, 1)
#define FMI2C_SDA_L      Lab_PinWrite(SOFT_FMI2C_SDA_PIN, 0)

#define FMI2C_SDA_READ   Lab_PinRead(SOFT_FMI2C_SDA_PIN)


void Test_RDA5807(void);
void RDA5807_Init(void);
void RDA5807_Enable(unsigned char flag);
void RDA5807_SetFreq(unsigned short freq);
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////RDA5807M �ײ�IIC����/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void FMI2C_Init(void);
void RDA5807_WriteReg(unsigned char regAddr,unsigned short val);  //оƬд�Ĵ���
unsigned short RDA5807_ReadReg(unsigned char regAddr);			 //оƬ���Ĵ���
#endif
