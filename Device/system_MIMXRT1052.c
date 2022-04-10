/*
** ###################################################################
**     Processors:          MIMXRT1052CVJ5B
**                          MIMXRT1052CVL5B
**                          MIMXRT1052DVJ6B
**                          MIMXRT1052DVL6B
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          MCUXpresso Compiler
**
**     Reference manual:    IMXRT1050RM Rev.1, 03/2018
**     Version:             rev. 0.1, 2017-01-10
**     Build:               b180509
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     The Clear BSD License
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2018 NXP
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without
**     modification, are permitted (subject to the limitations in the
**     disclaimer below) provided that the following conditions are met:
**
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**
**     * Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from
**       this software without specific prior written permission.
**
**     NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
**     GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
**     HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
**     WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
**     MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
**     LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
**     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
**     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
**     BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
**     WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
**     OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
**     IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2017-01-10)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MIMXRT1052
 * @version 0.1
 * @date 2017-01-10
 * @brief Device specific configuration file for MIMXRT1052 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"
#include "fsl_semc.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"

/*!
  * @brief    ���µ�������ITCRAM DTCRAM OCRAM
  *
  * @param    ITCRAM_SIZE  �� 0�� 0KB    6�� 32KB  7�� 64KB  8�� 128KB  9�� 256KB  10: 512KB
  * @param    DTCRAM_SIZE  �� 0�� 0KB    6�� 32KB  7�� 64KB  8�� 128KB  9�� 256KB  10: 512KB
  *
  * @return   
  *
  * @note     ITCRAM + DTCRAM ���512KB
  * @note     Ĭ��RT1052/RT1064 ITCRAM 128K  DTCRAM 128K
  * @note     ��Ҫ�ڶ�ջ�����ݳ�ʼ��֮ǰ���з���
  * @note     ��Ҫ��϶�Ӧ�ķ�ɢ�����ļ�һ��ʹ��
  * @note     OCRAM ����ռ��һ��blank  The OCRAM cannot be configured to 0 kB due to the boot ROM coderequirements 
  * @note     The Arm Cortex-M7 specifications require the size of ITCM/DTCM to be
  *           a power-of-two number, which can conflict with the FlexRAM configuration capability
  * @note     ITCRAM ��ʼ��ַ 0x0000 0000
  * @note     DTCRAM ��ʼ��ַ 0x2000 0000
  * @note     DTCRAM ��ʼ��ַ 0x2020 0000
  *
  * @see      
  *
  * @date     2019/8/7 ������
  */
void FLEX_RAM(int ITCRAM_SIZE, int DTCRAM_SIZE)
{
    /* Ĭ��ȫ���� OCRAM */
    register uint32_t temp = 0x55555555;
    
    
#if (defined(CPU_MIMXRT1064CVL5A) || defined(CPU_MIMXRT1064DVL6A))  
    
    switch(DTCRAM_SIZE)
    {
      case 7:  
        temp = 0x95555555;
        break;
      case 8:
        temp = 0xA5555555;
        break;
      case 9:
        temp = 0xAA555555;
        break;
      case 10:
        temp = 0xAAAA5555;
        break;
      default:
        temp = 0xA5555555;
        break;
    }
    
    switch(ITCRAM_SIZE)
    {
      case 7:  
        temp |= 0x03;
        break;
      case 8:
        temp |= 0x0F;
        break;
      case 9:
        temp |= 0xFF;
        break;
      case 10:
        temp |= 0xFFFF;
        break;
      default:
        temp |= 0x0F;
        break;
    }
    
#else 
    switch(DTCRAM_SIZE)
    {
      case 6:  
        temp = 0x95555555;
        break;
      case 7:  
        temp = 0xA5555555;
        break;
      case 8:
        temp = 0xAA555555;
        break;
      case 9:
        temp = 0xAAAA5555;
        break;
      case 10:
        temp = 0xAAAAAAAA;
        break;
      default:
        temp = 0xAA555555;
        break;
    }
    
    switch(ITCRAM_SIZE)
    {
      case 6:  
        temp |= 0x03;
        break;
      case 7:  
        temp |= 0x0F;
        break;
      case 8:
        temp |= 0xFF;
        break;
      case 9:
        temp |= 0xFFFF;
        break;
      case 10:
        temp |= 0xFFFFFFFF;
        break;
      default:
        temp |= 0xFF;
        break;
    }
#endif
    /* RT1052/1064 �ڲ�SRAMһ����Ϊ16��blank ÿ��blank ������ѡ������ 
     * RT1052 A bank size of 512 kB / 16 = 32 kB��RT1064 һ��blank 64K��
     * IOMUXC_GPR_GPR17�Ĵ���һ��32λ�� ÿ��λ����һ��blank������
     * 00b��bank is not used.
     * 01b��bank is configured for OCRAM.
     * 10b��bank is configured for DTCM.
     * 11b��bank is configured for ITCM.
     */
    IOMUXC_GPR->GPR17 = IOMUXC_GPR_GPR17_FLEXRAM_BANK_CFG(temp);
    
        
    /*! CM7_CFGITCMSZ
     *  0b0000..0 KB (No ITCM)
     *  0b0011..4 KB
     *  0b0100..8 KB
     *  0b0101..16 KB
     *  0b0110..32 KB
     *  0b0111..64 KB
     *  0b1000..128 KB
     *  0b1001..256 KB
     *  0b1010..512 KB
     */
    IOMUXC_GPR->GPR14 &= ~IOMUXC_GPR_GPR14_CM7_CFGITCMSZ_MASK;
    IOMUXC_GPR->GPR14 |= IOMUXC_GPR_GPR14_CM7_CFGITCMSZ(ITCRAM_SIZE);
    IOMUXC_GPR->GPR16 |= IOMUXC_GPR_GPR16_INIT_ITCM_EN(1);
    
    /*! CM7_CFGDTCMSZ
     *  0b0000..0 KB (No DTCM)
     *  0b0011..4 KB
     *  0b0100..8 KB
     *  0b0101..16 KB
     *  0b0110..32 KB
     *  0b0111..64 KB
     *  0b1000..128 KB
     *  0b1001..256 KB
     *  0b1010..512 KB
     */
    IOMUXC_GPR->GPR14 &= ~IOMUXC_GPR_GPR14_CM7_CFGDTCMSZ_MASK;
    IOMUXC_GPR->GPR14 |= IOMUXC_GPR_GPR14_CM7_CFGDTCMSZ(DTCRAM_SIZE);
    IOMUXC_GPR->GPR16 |= IOMUXC_GPR_GPR16_INIT_DTCM_EN(1);
    
    /* ʹ������ */
    IOMUXC_GPR->GPR16 |= IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL(1);
    
}

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

void SDRAM_WaitIpCmdDone(void) 
{
  unsigned int reg;
  do
  {
      reg =*(uint32_t*)(0x400FC068);
  }while((reg & 0x3) == 0);
}
void LQ_QSPI_BOOT_SDRAM_INIT(void)
{
  
// ʹ��ȫ��ʱ��  
  *(uint32_t*)(0x400FC068)=0xffffffff;
  *(uint32_t*)(0x400FC06C)=0xffffffff;
  *(uint32_t*)(0x400FC070)=0xffffffff;
  *(uint32_t*)(0x400FC074)=0xffffffff;
  *(uint32_t*)(0x400FC078)=0xffffffff;
  *(uint32_t*)(0x400FC07C)=0xffffffff;
  *(uint32_t*)(0x400FC080)=0xffffffff;
  SDRAM_WaitIpCmdDone() ;
  *(uint32_t*)(0x400D8030)=0x00002001;  
  *(uint32_t*)(0x400D8100)=0x001d0000;   
  *(uint32_t*)(0x400FC014)=0x00010D40;   
  SDRAM_WaitIpCmdDone() ;
  
  // ����SDRAM�ܽŸ��ã�IOMUX
  *(uint32_t*)(0x401F8014)=0x00000000; 
  *(uint32_t*)(0x401F8018)=0x00000000;
  *(uint32_t*)(0x401F801C)=0x00000000;
  *(uint32_t*)(0x401F8020)=0x00000000;
  *(uint32_t*)(0x401F8024)=0x00000000;
  *(uint32_t*)(0x401F8028)=0x00000000;
  *(uint32_t*)(0x401F802C)=0x00000000;
  *(uint32_t*)(0x401F8030)=0x00000000;
  *(uint32_t*)(0x401F8034)=0x00000000;
  *(uint32_t*)(0x401F8038)=0x00000000;
  *(uint32_t*)(0x401F803C)=0x00000000;
  *(uint32_t*)(0x401F8040)=0x00000000;
  *(uint32_t*)(0x401F8044)=0x00000000;
  *(uint32_t*)(0x401F8048)=0x00000000;
  *(uint32_t*)(0x401F804C)=0x00000000;
  *(uint32_t*)(0x401F8050)=0x00000000;
  *(uint32_t*)(0x401F8054)=0x00000000;
  *(uint32_t*)(0x401F8058)=0x00000000;
  *(uint32_t*)(0x401F805C)=0x00000000;
  *(uint32_t*)(0x401F8060)=0x00000000;
  *(uint32_t*)(0x401F8064)=0x00000000;
  *(uint32_t*)(0x401F8068)=0x00000000;
  *(uint32_t*)(0x401F806C)=0x00000000;
  *(uint32_t*)(0x401F8070)=0x00000000;
  *(uint32_t*)(0x401F8074)=0x00000000;
  *(uint32_t*)(0x401F8078)=0x00000000;
  *(uint32_t*)(0x401F807C)=0x00000000;
  *(uint32_t*)(0x401F8080)=0x00000000;
  *(uint32_t*)(0x401F8084)=0x00000000;
  *(uint32_t*)(0x401F8088)=0x00000000;
  *(uint32_t*)(0x401F808C)=0x00000000;
  *(uint32_t*)(0x401F8090)=0x00000000;
  *(uint32_t*)(0x401F8094)=0x00000000;
  *(uint32_t*)(0x401F8098)=0x00000000;
  *(uint32_t*)(0x401F809C)=0x00000000;
  *(uint32_t*)(0x401F80A0)=0x00000000;
  *(uint32_t*)(0x401F80A4)=0x00000000;
  *(uint32_t*)(0x401F80A8)=0x00000000;
  *(uint32_t*)(0x401F80AC)=0x00000000;
  *(uint32_t*)(0x401F80B0)=0x00000010; //�ⲿ�˿ڲ���ռ�ã�EMC_39)= DQS PIN)= enable SION
  *(uint32_t*)(0x401F80B4)=0x00000000;
  *(uint32_t*)(0x401F80B8)=0x00000000;

  // PAD ctrl
  // drive strength = 0x7 to increase drive strength
  // otherwise the data7 bit may fail.
  *(uint32_t*)(0x401F8204)=0x000110F9;
  *(uint32_t*)(0x401F8208)=0x000110F9;
  *(uint32_t*)(0x401F820C)=0x000110F9;
  *(uint32_t*)(0x401F8210)=0x000110F9;
  *(uint32_t*)(0x401F8214)=0x000110F9;
  *(uint32_t*)(0x401F8218)=0x000110F9;
  *(uint32_t*)(0x401F821C)=0x000110F9;
  *(uint32_t*)(0x401F8220)=0x000110F9;
  *(uint32_t*)(0x401F8224)=0x000110F9;
  *(uint32_t*)(0x401F8228)=0x000110F9;
  *(uint32_t*)(0x401F822C)=0x000110F9;
  *(uint32_t*)(0x401F8230)=0x000110F9;
  *(uint32_t*)(0x401F8234)=0x000110F9;
  *(uint32_t*)(0x401F8238)=0x000110F9;
  *(uint32_t*)(0x401F823C)=0x000110F9;
  *(uint32_t*)(0x401F8240)=0x000110F9;
  *(uint32_t*)(0x401F8244)=0x000110F9;
  *(uint32_t*)(0x401F8248)=0x000110F9;
  *(uint32_t*)(0x401F824C)=0x000110F9;
  *(uint32_t*)(0x401F8250)=0x000110F9;
  *(uint32_t*)(0x401F8254)=0x000110F9;
  *(uint32_t*)(0x401F8258)=0x000110F9;
  *(uint32_t*)(0x401F825C)=0x000110F9;
  *(uint32_t*)(0x401F8260)=0x000110F9;
  *(uint32_t*)(0x401F8264)=0x000110F9;
  *(uint32_t*)(0x401F8268)=0x000110F9;
  *(uint32_t*)(0x401F826C)=0x000110F9;
  *(uint32_t*)(0x401F8270)=0x000110F9;
  *(uint32_t*)(0x401F8274)=0x000110F9;
  *(uint32_t*)(0x401F8278)=0x000110F9;
  *(uint32_t*)(0x401F827C)=0x000110F9;
  *(uint32_t*)(0x401F8280)=0x000110F9;
  *(uint32_t*)(0x401F8284)=0x000110F9;
  *(uint32_t*)(0x401F8288)=0x000110F9;
  *(uint32_t*)(0x401F828C)=0x000110F9;
  *(uint32_t*)(0x401F8290)=0x000110F9;
  *(uint32_t*)(0x401F8294)=0x000110F9;
  *(uint32_t*)(0x401F8298)=0x000110F9;
  *(uint32_t*)(0x401F829C)=0x000110F9;
  *(uint32_t*)(0x401F82A0)=0x000110F9;
  *(uint32_t*)(0x401F82A4)=0x000110F9;
  *(uint32_t*)(0x401F82A8)=0x000110F9;

  // Config SDR Controller Registers/
  *(uint32_t*)(0x402F0000)=0x10000004; // MCR
  *(uint32_t*)(0x402F0008)=0x00030524; // BMCR0
  *(uint32_t*)(0x402F000C)=0x06030524; // BMCR1
  *(uint32_t*)(0x402F0010)=0x8000001B; // BR0))= 32MB�ռ�
  *(uint32_t*)(0x402F0014)=0x8200001B; // BR1))= 32MB
  *(uint32_t*)(0x402F0018)=0x8400001B; // BR2))= 32MB
  *(uint32_t*)(0x402F001C)=0x8600001B; // BR3))= 32MB
  *(uint32_t*)(0x402F0020)=0x90000021; // BR4))=
  *(uint32_t*)(0x402F0024)=0xA0000019; // BR5))=
  *(uint32_t*)(0x402F0028)=0xA8000017; // BR6))=
  *(uint32_t*)(0x402F002C)=0xA900001B; // BR7))=
  *(uint32_t*)(0x402F0030)=0x00000021; // BR8))=
  *(uint32_t*)(0x402F0004)=0x000079A8;  //IOCR))=SEMC_CCSX0 as NOR CE))= SEMC_CSX1 as PSRAM CE))= SEMC_CSX2 as NAND CE))= SEMC_CSX3 as DBI CE.
 
  // *(uint32_t*)(0x00000008))= 0x402F0004)=   ; // IOCR))= SEMC_CCSX0 as SDRAM_CS1
  *(uint32_t*)(0x402F0040)=0x00000F31; // SDRAMCR0
  *(uint32_t*)(0x402F0044)=0x00652922; // SDRAMCR1
  *(uint32_t*)(0x402F0048)=0x00010920; // SDRAMCR2
  *(uint32_t*)(0x402F004C)=0x50210A08; // SDRAMCR3
  *(uint32_t*)(0x402F0080)=0x00000021; // DBICR0
  *(uint32_t*)(0x402F0084)=0x00888888; // DBICR1
  *(uint32_t*)(0x402F0094)=0x00000002; // IPCR1
  *(uint32_t*)(0x402F0098)=0x00000000; // IPCR2
  *(uint32_t*)(0x402F0090)=0x80000000; // IPCR0
  *(uint32_t*)(0x402F009C)=0xA55A000F; // IPCMD))= SD_CC_IPREA
  SDRAM_WaitIpCmdDone() ;
  *(uint32_t*)(0x402F0090)=0x80000000; // IPCR0
  *(uint32_t*)(0x402F009C)=0xA55A000C; // SD_CC_IAF
  SDRAM_WaitIpCmdDone() ;
  *(uint32_t*)(0x402F0090)=0x80000000; // IPCR0
  *(uint32_t*)(0x402F009C)=0xA55A000C; // SD_CC_IAF
  SDRAM_WaitIpCmdDone() ;
  *(uint32_t*)(0x402F00A0)=0x00000033; // IPTXDAT
  *(uint32_t*)(0x402F0090)=0x80000000; // IPCR0
  *(uint32_t*)(0x402F009C)=0xA55A000A; // SD_CC_IMS
  SDRAM_WaitIpCmdDone() ;
  *(uint32_t*)(0x402F004C)=0x50210A09; // enable sdram self refresh again after initialization done.
  
  /*
  // Clock init 
  //CCM->CCGR3 |= CCM_CCGR3_CG2(3);//SEMC clock enable
  //CCM->CCGR4 |= CCM_CCGR4_CG1(3);//IOMUXC clock enable
  CCM->CCGR0 = 0xFFFFFFFF;
  CCM->CCGR1 = 0xFFFFFFFF;
  CCM->CCGR2 = 0xFFFFFFFF;
  CCM->CCGR3 = 0xFFFFFFFF;
  CCM->CCGR4 = 0xFFFFFFFF;
  CCM->CCGR5 = 0xFFFFFFFF;
  CCM->CCGR5 = 0xFFFFFFFF;
  
  
  CCM_ANALOG->PLL_SYS = 0x00002001;//Enable PLL output, Fout=Fref*22
  CCM_ANALOG->PFD_528 = 0x001d0000;
  CCM->CBCDR = 0x00010D40;
   
  // SDRAM IO MUX Config 
  IOMUXC->SW_MUX_CTL_PAD[0] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[1] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[2] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[3] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[4] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[5] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[6] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[7] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[8] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[9] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[10] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[11] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[12] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[13] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[14] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[15] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[16] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[17] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[18] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[19] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[20] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[21] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[22] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[23] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[24] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[25] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[26] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[27] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[28] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[29] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[30] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[31] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[32] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[33] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[34] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[35] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[36] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[37] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[38] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[39] = 0x00000010;
  IOMUXC->SW_MUX_CTL_PAD[40] = 0x00000000;
  IOMUXC->SW_MUX_CTL_PAD[41] = 0x00000000;
  
  // SDRAM IO Pad Config 
  IOMUXC->SW_PAD_CTL_PAD[0] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[1] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[2] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[3] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[4] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[5] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[6] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[7] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[8] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[9] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[10] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[11] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[12] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[13] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[14] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[15] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[16] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[17] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[18] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[19] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[20] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[21] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[22] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[23] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[24] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[25] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[26] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[27] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[28] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[29] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[30] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[31] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[32] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[33] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[34] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[35] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[36] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[37] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[38] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[39] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[40] = 0x000110F9;
  IOMUXC->SW_PAD_CTL_PAD[41] = 0x000110F9;
  
  SEMC->MCR = 0x1000E000;
  SEMC->BMCR0 = 0x00030524;
  SEMC->BMCR1 = 0x06030524;
  SEMC->BR[0] = 0x8000001B;
  SEMC->BR[1] = 0x90000021;
  SEMC->IOCR = 0x00000008;
  SEMC->SDRAMCR0 = 0x00000B27;
  SEMC->SDRAMCR1 = 0x00100100;
  SEMC->SDRAMCR2 = 0x00020201;
  SEMC->SDRAMCR3 = 0x08193D0E;
  SEMC->DBICR0 = 0x00000021;
  SEMC->DBICR1 = 0x00888888;
  SEMC->IPCR1 = 0x00000002;
  SEMC->IPCR2 = 0x00000000;
  
  // Config SDR Controller Registers 
  SEMC->MCR = 0x10000004;
  SEMC->BMCR0 = 0x00030524;
  SEMC->BMCR1 = 0x06030524;
  SEMC->BR[0] = 0x8000001B;
  SEMC->BR[1] = 0x8200001B;
  SEMC->BR[2] = 0x8400001B;
  SEMC->BR[3] = 0x8600001B;
  SEMC->BR[4] = 0x90000021;
  SEMC->BR[5] = 0xA0000019;
  SEMC->BR[6] = 0xA8000017;
  SEMC->BR[7] = 0xA900001B;
  SEMC->BR[8] = 0x00000021;
  SEMC->IOCR = 0x000079A8;//SEMC_CCSX0 as NOR CE, SEMC_CSX1 as PSRAM CE, SEMC_CSX2 as NAND CE, SEMC_CSX3 as DBI CE
    
  // __writeMemory32(0x00000008, 0x402F0004, "Memory"); // IOCR, SEMC_CCSX0 as SDRAM_CS1
  SEMC->SDRAMCR0 = 0x00000F31;
  SEMC->SDRAMCR1 = 0x00652922;
  SEMC->SDRAMCR2 = 0x00010920;
  SEMC->SDRAMCR3 = 0x50210A08;
  
  SEMC->DBICR0 = 0x00000021;
  SEMC->DBICR1 = 0x00888888;
  SEMC->IPCR1 = 0x00000002;
  SEMC->IPCR2 = 0x00000000;
  
  SEMC->IPCR0 = 0x80000000;
  SEMC->IPCMD = 0xA55A000F;//SD_CC_IPREA
  SDRAM_WaitIpCmdDone();
  SEMC->IPCR0 = 0x80000000;
  SEMC->IPCMD = 0xA55A000C;//SD_CC_IAF
  SDRAM_WaitIpCmdDone();
  SEMC->IPCR0 = 0x80000000;
  SEMC->IPCMD = 0xA55A000C;//SD_CC_IAF
  SDRAM_WaitIpCmdDone();
  SEMC->IPTXDAT = 0x00000033;
  SEMC->IPCR0 = 0x80000000;
  SEMC->IPCMD = 0xA55A000A;//SD_CC_IMS
  SDRAM_WaitIpCmdDone();
  
  SEMC->SDRAMCR3 = 0x50210A09;//enable sdram self refresh again after initialization done.
*/
}

 /* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

#if defined(__MCUXPRESSO)
    extern uint32_t g_pfnVectors[];  // Vector table defined in startup code
    SCB->VTOR = (uint32_t)g_pfnVectors;
#endif

/* Disable Watchdog Power Down Counter */
WDOG1->WMCR &= ~WDOG_WMCR_PDE_MASK;
WDOG2->WMCR &= ~WDOG_WMCR_PDE_MASK;

/* Watchdog disable */

#if (DISABLE_WDOG)
    if (WDOG1->WCR & WDOG_WCR_WDE_MASK)
    {
        WDOG1->WCR &= ~WDOG_WCR_WDE_MASK;
    }
    if (WDOG2->WCR & WDOG_WCR_WDE_MASK)
    {
        WDOG2->WCR &= ~WDOG_WCR_WDE_MASK;
    }
    RTWDOG->CNT = 0xD928C520U; /* 0xD928C520U is the update key */
    RTWDOG->TOVAL = 0xFFFF;
    RTWDOG->CS = (uint32_t) ((RTWDOG->CS) & ~RTWDOG_CS_EN_MASK) | RTWDOG_CS_UPDATE_MASK;
#endif /* (DISABLE_WDOG) */

    /* Disable Systick which might be enabled by bootrom */
    if (SysTick->CTRL & SysTick_CTRL_ENABLE_Msk)
    {
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }

    /* Enable instruction and data caches */
#if defined(__ICACHE_PRESENT) && __ICACHE_PRESENT
    if (SCB_CCR_IC_Msk != (SCB_CCR_IC_Msk & SCB->CCR)) {
      SCB_EnableICache();
    }
#endif
#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
    if (SCB_CCR_DC_Msk != (SCB_CCR_DC_Msk & SCB->CCR)) {
      SCB_EnableDCache();
    }
#endif    
   
#if defined (XIP_BOOT_HEADER_DCD_ENABLE) && (XIP_BOOT_HEADER_DCD_ENABLE == 1)
    LQ_QSPI_BOOT_SDRAM_INIT(); //��ʼ���ⲿSDRAM�Ĺܽż��ܽ�ʱ��
#endif
#if defined LQRELEASE    
    //SDRAM���Ե�ʱ�򣬲�Ҫ�����ⲿ�֣�������õ����ʽϵͣ���Ӧ�ͺ���
    //FLASH������ʱ�򣬱����ȳ�ʼ��SDRAM���У������޷�����SDRAM 
    LQ_QSPI_BOOT_SDRAM_INIT(); //��ʼ���ⲿSDRAM�Ĺܽż��ܽ�ʱ��
#endif 
    SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

    uint32_t freq;
    uint32_t PLL1MainClock;
    uint32_t PLL2MainClock;

    /* Periph_clk2_clk ---> Periph_clk */
    if (CCM->CBCDR & CCM_CBCDR_PERIPH_CLK_SEL_MASK)
    {
        switch (CCM->CBCMR & CCM_CBCMR_PERIPH_CLK2_SEL_MASK)
        {
            /* Pll3_sw_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(0U):
                if(CCM_ANALOG->PLL_USB1 & CCM_ANALOG_PLL_USB1_BYPASS_MASK)
                {
                    freq = (((CCM_ANALOG->PLL_USB1 & CCM_ANALOG_PLL_USB1_BYPASS_CLK_SRC_MASK) >> CCM_ANALOG_PLL_USB1_BYPASS_CLK_SRC_SHIFT) == 0U) ?
                           CPU_XTAL_CLK_HZ : CPU_CLK1_HZ;
                }
                else
                {
                    freq = (CPU_XTAL_CLK_HZ * ((CCM_ANALOG->PLL_USB1 & CCM_ANALOG_PLL_USB1_DIV_SELECT_MASK) ? 22U : 20U));
                }
                break;

            /* Osc_clk ---> Periph_clk2_clk ---> Periph_clk */
            case CCM_CBCMR_PERIPH_CLK2_SEL(1U):
                freq = CPU_XTAL_CLK_HZ;
                break;

            case CCM_CBCMR_PERIPH_CLK2_SEL(2U):
                freq = (((CCM_ANALOG->PLL_SYS & CCM_ANALOG_PLL_SYS_BYPASS_CLK_SRC_MASK) >> CCM_ANALOG_PLL_SYS_BYPASS_CLK_SRC_SHIFT) == 0U) ?
                   CPU_XTAL_CLK_HZ : CPU_CLK1_HZ;

            case CCM_CBCMR_PERIPH_CLK2_SEL(3U):
            default:
                freq = 0U;
                break;
        }

        freq /= (((CCM->CBCDR & CCM_CBCDR_PERIPH_CLK2_PODF_MASK) >> CCM_CBCDR_PERIPH_CLK2_PODF_SHIFT) + 1U);
    }
    /* Pre_Periph_clk ---> Periph_clk */
    else
    {
        /* check if pll is bypassed */
        if(CCM_ANALOG->PLL_ARM & CCM_ANALOG_PLL_ARM_BYPASS_MASK)
        {
            PLL1MainClock = (((CCM_ANALOG->PLL_ARM & CCM_ANALOG_PLL_ARM_BYPASS_CLK_SRC_MASK) >> CCM_ANALOG_PLL_ARM_BYPASS_CLK_SRC_SHIFT) == 0U) ?
                   CPU_XTAL_CLK_HZ : CPU_CLK1_HZ;
        }
        else
        {
            PLL1MainClock = ((CPU_XTAL_CLK_HZ * ((CCM_ANALOG->PLL_ARM & CCM_ANALOG_PLL_ARM_DIV_SELECT_MASK) >>
                                             CCM_ANALOG_PLL_ARM_DIV_SELECT_SHIFT)) >> 1U);
        }

        /* check if pll is bypassed */
        if(CCM_ANALOG->PLL_SYS & CCM_ANALOG_PLL_SYS_BYPASS_MASK)
        {
            PLL2MainClock = (((CCM_ANALOG->PLL_SYS & CCM_ANALOG_PLL_SYS_BYPASS_CLK_SRC_MASK) >> CCM_ANALOG_PLL_SYS_BYPASS_CLK_SRC_SHIFT) == 0U) ?
                   CPU_XTAL_CLK_HZ : CPU_CLK1_HZ;
        }
        else
        {
            PLL2MainClock = (CPU_XTAL_CLK_HZ * ((CCM_ANALOG->PLL_SYS & CCM_ANALOG_PLL_SYS_DIV_SELECT_MASK) ? 22U : 20U));
        }
        PLL2MainClock += ((uint64_t)CPU_XTAL_CLK_HZ * ((uint64_t)(CCM_ANALOG->PLL_SYS_NUM))) / ((uint64_t)(CCM_ANALOG->PLL_SYS_DENOM));


        switch (CCM->CBCMR & CCM_CBCMR_PRE_PERIPH_CLK_SEL_MASK)
        { 
            /* PLL2 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(0U):
                freq = PLL2MainClock;
                break;

            /* PLL2 PFD2 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(1U):
                freq = PLL2MainClock / ((CCM_ANALOG->PFD_528 & CCM_ANALOG_PFD_528_PFD2_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD2_FRAC_SHIFT) * 18U;
                break;

            /* PLL2 PFD0 ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(2U):
                freq = PLL2MainClock / ((CCM_ANALOG->PFD_528 & CCM_ANALOG_PFD_528_PFD0_FRAC_MASK) >> CCM_ANALOG_PFD_528_PFD0_FRAC_SHIFT) * 18U;
                break;

            /* PLL1 divided(/2) ---> Pre_Periph_clk ---> Periph_clk */
            case CCM_CBCMR_PRE_PERIPH_CLK_SEL(3U):
                freq = PLL1MainClock / (((CCM->CACRR & CCM_CACRR_ARM_PODF_MASK) >> CCM_CACRR_ARM_PODF_SHIFT) + 1U);
                break;

            default:
                freq = 0U;
                break;
        }
    }

    SystemCoreClock = (freq / (((CCM->CBCDR & CCM_CBCDR_AHB_PODF_MASK) >> CCM_CBCDR_AHB_PODF_SHIFT) + 1U));

}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
