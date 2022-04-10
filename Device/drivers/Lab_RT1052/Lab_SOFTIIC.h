/**
 * @file Lab_SOFTIIC.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief ��� IIC 
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __IIC_H
#define __IIC_H

#include "Lab_GPIO_Cfg.h"
#include "fsl_common.h"

/* ע�� IIC���߹涨��IIC����ʱ SCL��SDA��Ϊ�ߵ�ƽ ����ⲿ������һ������������ */
/* ģ�� IIC��Ҫע�⣬��ַ��ҪӲ��IIC��ַ����һλ ����MPU6050 Ӳ��IIC��ַ�� 0x68  ��ģ�����0xD0*/
/* C12 GPIO2_22  ��Ϊ SCL */
/* A13 GPIO2_25  ��Ϊ SDA */
#define IIC_SCL_PIN  DIR2_22  //ģ��IIC��SCL�ź�  1.�޸����ż����޸�IIC�ӿ�
#define IIC_SDA_PIN  DIR2_25   //ģ��IIC��SDA�ź�

#define SDA_IN()  IIC_SDA_PIN = 0;	//����
#define SDA_OUT() IIC_SDA_PIN = 1;	//���

#define IIC_SCL    PT2_22       //SCL              2.�޸����ż����޸�IIC�ӿ�    
#define IIC_SDA    PT2_25       //SDA	 
#define READ_SDA   PT2_25       //����SDA 


/*---------------------------------------------------------------
            IIC�ڲ�����
----------------------------------------------------------------*/		 
void IIC_Start(void);			        //����IIC��ʼ�ź�
void IIC_Stop(void);	  	            //����IICֹͣ�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				    //IIC������ACK�ź�
uint8_t IIC_WaitAck(void); 		        //IIC�ȴ�ACK�ź�
void IIC_SendByte(uint8_t data);        //IIC����һ���ֽ�
uint8_t IIC_ReadByte(uint8_t ack);       //IIC��ȡһ���ֽ�


/*---------------------------------------------------------------
            IIC�û�����
----------------------------------------------------------------*/
void IIC_Init(void);                    //��ʼ��IIC��IO��   
uint8_t IIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf);
uint8_t IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t IIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t buf);
uint8_t IIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);



#endif
