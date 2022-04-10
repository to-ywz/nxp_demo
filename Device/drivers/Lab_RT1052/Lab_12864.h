/**
 * @file Lab_12864.h
 * @author BlackSheep (ywz_123xxx@163.com)
 * @brief OLED 12864 µÄÇý¶¯
 * @version 0.1
 * @date 2021-05-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _LabOLED_H
#define _LabOLED_H

#include "include.h"

extern void LCD_Init(void);
extern void LCD_CLS(void);
extern void LCD_P6x8Str(unsigned char x,unsigned char y, char ch[]);
extern void LCD_P8x16Str(unsigned char x,unsigned char y, char ch[]);
extern void LCD_P14x16Str(unsigned char x,unsigned char y, char ch[]);
extern void LCD_Print(unsigned char x, unsigned char y,  char ch[]);
extern void LCD_PutPixel(unsigned char x,unsigned char y);
extern void LCD_Set_Pos(unsigned char x, unsigned char y);
extern void LCD_WrDat(unsigned char data);
extern void LCD_WrCmd(unsigned char cmd);
extern void LCD_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char gif);
extern void LCD_Show_LabLogo(void);
extern void LCD_Show_LibLogo(void);
extern void LCD_Show_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char * bmp); 
extern void LCD_Show_Road(void);
extern void LCD_Show_Frame80(void);
void LCD_Show_Frame94(void);
extern void LCD_Show_Frame100(void);
extern void LCD_Set_Pos(unsigned char x, unsigned char y);
extern void LCD_WrDat(unsigned char data);
extern void LCD_WrCmd(unsigned char cmd);
void LCD_Fill(unsigned char bmp_data);
extern void Test_OLED(void);

#endif

