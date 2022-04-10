# NXP_智能车 Demo
```
平台:       NXP i.MX MIMXRT1052VDL6B
函数:       FSL标准库
Keil:       MDK3.30
RTOS:       RT-Thread Nano 3.1.3
版本:       1.0
author:     BlackSheep & xiongyongchang
Date:       2021.5.14
```
## 说明
基于 RT-Thread Nano的智能车初始工程
RT-Thread 的 Board.c 文件 进行了修改, 自己新建文件记得 copy 否则 时基会有问题
fsl 库的 板级初始化 已经移植到 RT-Thread 的 board.c 文件中, 无需在主函数中再次调用

舵机脉冲:
    舵盘换成铁质的舵机,安装的时候出现偏差
    舵机工作范围: 230 ~ 360 
    中值为: 292


LPUART3 作为    FinSH   的输出串口
    C9  -->     RX
    B9  -->     TX
    BaudRate    115200
FinSH 可在 `enabledef.h` 中配置是否开启, 在 `FinSH_driver.h` 中选择 `LPUART`

PID:
    kp = 7
    ki = 0.5
    kd = 0.14
大概会有 ±2~17 的误差,由于 编码器在固定 PWM 下 编码器读数会有 ±3~8 的波动
所以转速查在接受范围之内

下载现象:
    母版 蓝色 LED 500ms 闪烁
    串口输出 RT-Thread Logo
    OLED 显示 BlackSheep , motorR:0 motorL:0, ENCR:0 ENCL:0, diff: 0
    按键按下 `speed` 会改变
    其余参数会实时变化
    串口输入 `ps` 查看 能看见 `KeyScan` , `oled`, `led_B` 线程

## 思路
### 中线
采用线性回归 y=kx+b 进行中线绘制, 对斜率进行一阶滞后滤波.
### 舵机控制
采用权重分布对中线的每一个点按权重进行分布和规划,
传入线性回归函数,再获取偏差值反馈给舵机

## 问题
* 如果出现找不到 DRs 成员,请将 Device 文件中的 `MIMXRT1052_features.h` 和 `MIMXRT1052.h` 覆盖 Keil 软件 ARM 的 PACK 里 和 NXP 相关的 头文件
* 如果不能 断点 将 debug ->setting 里的 verify Code Download 和 Download to Flash 取消勾选即可
* 如果使用 VSCode 打开建议下载 Keil Assistant 自动生成 `c_cpp_properties.json` 后,新建模板添加 C语言标准库头文件路径 以及 RT-Thrad Nano 头文件路径

## 文件分布
```     
├─Application       用户程序
│  │  enabledef.h
│  │  include.h
│  │  irq.c
│  │  main.c
│  │  
│  └─myDriver       FINSH 驱动
│          bsp.c
│          bsp.h
│          FinSH_driver.c
│          FinSH_driver.h
│          ringbuffer.c
│          ringbuffer.h
│          
├─CMSIS
│  │  LICENSE.txt
│  │  
│  ├─Driver         ARM 驱动
│  │  ├─DriverTemplates
│  │  │      Driver_CAN.c
│  │  │      Driver_ETH_MAC.c
│  │  │      Driver_ETH_PHY.c
│  │  │      Driver_Flash.c
│  │  │      Driver_I2C.c
│  │  │      Driver_MCI.c
│  │  │      Driver_SAI.c
│  │  │      Driver_SPI.c
│  │  │      Driver_Storage.c
│  │  │      Driver_USART.c
│  │  │      Driver_USBD.c
│  │  │      Driver_USBH.c
│  │  │      
│  │  └─Include
│  │          Driver_CAN.h
│  │          Driver_Common.h
│  │          Driver_ETH.h
│  │          Driver_ETH_MAC.h
│  │          Driver_ETH_PHY.h
│  │          Driver_Flash.h
│  │          Driver_I2C.h
│  │          Driver_MCI.h
│  │          Driver_NAND.h
│  │          Driver_SAI.h
│  │          Driver_SPI.h
│  │          Driver_USART.h
│  │          Driver_USB.h
│  │          Driver_USBD.h
│  │          Driver_USBH.h
│  │          
│  └─Include
│          arm_common_tables.h
│          arm_const_structs.h
│          arm_math.h
│          cmsis_armcc.h
│          cmsis_armclang.h
│          cmsis_compiler.h
│          cmsis_gcc.h
│          cmsis_iccarm.h
│          cmsis_version.h
│          core_armv8mbl.h
│          core_armv8mml.h
│          core_cm0.h
│          core_cm0plus.h
│          core_cm23.h
│          core_cm3.h
│          core_cm33.h
│          core_cm4.h
│          core_cm7.h
│          core_sc000.h
│          core_sc300.h
│          mpu_armv7.h
│          mpu_armv8.h
│          tz_context.h
│          
├─Device
│  │  fsl_device_registers.h
│  │  MIMXRT1052.h
│  │  MIMXRT1052_features.h
│  │  system_MIMXRT1052.c
│  │  system_MIMXRT1052.h
│  │  
│  ├─board              rt1052 板级驱动
│  │      board.c
│  │      board.h
│  │      clock_config.c
│  │      clock_config.h
│  │      pin_mux.c
│  │      pin_mux.h
│  │      
│  ├─drivers
│  │  ├─Lab_RT1052      实验室驱动库
│  │  │      ANO_DT.c
│  │  │      ANO_DT.h
│  │  │      ICM20602_SOFTSPI.c
│  │  │      ICM20602_SOFTSPI.h
│  │  │      Lab_12864.h
│  │  │      Lab_12864SPI.c
│  │  │      Lab_9AX.c
│  │  │      Lab_9AX.h
│  │  │      Lab_ADC.c
│  │  │      Lab_ADC.h
│  │  │      Lab_Camera.c
│  │  │      Lab_Camera.h
│  │  │      Lab_CSI.c
│  │  │      Lab_CSI.h
│  │  │      Lab_DMA.c
│  │  │      Lab_DMA.h
│  │  │      Lab_Encoder.c
│  │  │      Lab_Encoder.h
│  │  │      Lab_FLASH.c
│  │  │      Lab_FLASH.h
│  │  │      Lab_FlexCAN.c
│  │  │      Lab_FlexCAN.h
│  │  │      Lab_GPIO.c
│  │  │      Lab_GPIO.h
│  │  │      Lab_GPIO_Cfg.h
│  │  │      Lab_GPT.c
│  │  │      Lab_GPT.h
│  │  │      Lab_ICM20602.c
│  │  │      Lab_ICM20602.h
│  │  │      Lab_IIC.c
│  │  │      Lab_IIC.h
│  │  │      Lab_KEY.c
│  │  │      Lab_KEY.h
│  │  │      Lab_LED.c
│  │  │      Lab_LED.h
│  │  │      Lab_MPU6050.c
│  │  │      Lab_MPU6050.h
│  │  │      Lab_MT9V034M.c
│  │  │      Lab_MT9V034M.h
│  │  │      Lab_OV7725M.c
│  │  │      Lab_OV7725M.h
│  │  │      Lab_PIT.c
│  │  │      Lab_PIT.h
│  │  │      Lab_PWM.c
│  │  │      Lab_PWM.h
│  │  │      Lab_QTMR.c
│  │  │      Lab_QTMR.h
│  │  │      Lab_RDA5807.c
│  │  │      Lab_RDA5807.h
│  │  │      Lab_Rtwdog.c
│  │  │      Lab_Rtwdog.h
│  │  │      Lab_SDCard.c
│  │  │      Lab_SDCard.h
│  │  │      Lab_SGP18T.c
│  │  │      Lab_SGP18T.h
│  │  │      Lab_SOFTIIC.c
│  │  │      Lab_SOFTIIC.h
│  │  │      Lab_SPI.c
│  │  │      Lab_SPI.h
│  │  │      Lab_SYSTICK.c
│  │  │      Lab_SYSTICK.h
│  │  │      Lab_Tempmon.c
│  │  │      Lab_Tempmon.h
│  │  │      Lab_TRNG.c
│  │  │      Lab_TRNG.h
│  │  │      Lab_UART.c
│  │  │      Lab_UART.h
│  │  │      Lab_UART_DMA.c
│  │  │      Lab_UART_DMA.h
│  │  │      Lab_Ultrasonic.c
│  │  │      Lab_Ultrasonic.h
│  │  │      Lab_VL53.c
│  │  │      Lab_VL53.h
│  │  │      Lab_W25Q128.c
│  │  │      Lab_W25Q128.h
│  │  │      Lab_WDog.c
│  │  │      Lab_WDog.h
│  │  │      picture.h
│  │  │      pictures.h
│  │  │      
│  │  └─MIMXRT1052          官方库函数
│  │      │  fsl_adc.c
│  │      │  fsl_adc.h
│  │      │  fsl_adc_etc.c
│  │      │  fsl_adc_etc.h
│  │      │  fsl_aipstz.c
│  │      │  fsl_aipstz.h
│  │      │  fsl_aoi.c
│  │      │  fsl_aoi.h
│  │      │  fsl_bee.c
│  │      │  fsl_bee.h
│  │      │  fsl_cache.c
│  │      │  fsl_cache.h
│  │      │  fsl_clock.c
│  │      │  fsl_clock.h
│  │      │  fsl_cmp.c
│  │      │  fsl_cmp.h
│  │      │  fsl_common.c
│  │      │  fsl_common.h
│  │      │  fsl_csi.c
│  │      │  fsl_csi.h
│  │      │  fsl_dcdc.c
│  │      │  fsl_dcdc.h
│  │      │  fsl_dcp.c
│  │      │  fsl_dcp.h
│  │      │  fsl_dmamux.c
│  │      │  fsl_dmamux.h
│  │      │  fsl_edma.c
│  │      │  fsl_edma.h
│  │      │  fsl_elcdif.c
│  │      │  fsl_elcdif.h
│  │      │  fsl_enc.c
│  │      │  fsl_enc.h
│  │      │  fsl_enet.c
│  │      │  fsl_enet.h
│  │      │  fsl_ewm.c
│  │      │  fsl_ewm.h
│  │      │  fsl_flexcan.c
│  │      │  fsl_flexcan.h
│  │      │  fsl_flexio.c
│  │      │  fsl_flexio.h
│  │      │  fsl_flexio_i2c_master.c
│  │      │  fsl_flexio_i2c_master.h
│  │      │  fsl_flexio_i2s.c
│  │      │  fsl_flexio_i2s.h
│  │      │  fsl_flexio_i2s_edma.c
│  │      │  fsl_flexio_i2s_edma.h
│  │      │  fsl_flexio_spi.c
│  │      │  fsl_flexio_spi.h
│  │      │  fsl_flexio_spi_edma.c
│  │      │  fsl_flexio_spi_edma.h
│  │      │  fsl_flexio_uart.c
│  │      │  fsl_flexio_uart.h
│  │      │  fsl_flexio_uart_edma.c
│  │      │  fsl_flexio_uart_edma.h
│  │      │  fsl_flexram.c
│  │      │  fsl_flexram.h
│  │      │  fsl_flexspi.c
│  │      │  fsl_flexspi.h
│  │      │  fsl_gpc.c
│  │      │  fsl_gpc.h
│  │      │  fsl_gpio.c
│  │      │  fsl_gpio.h
│  │      │  fsl_gpt.c
│  │      │  fsl_gpt.h
│  │      │  fsl_iomuxc.h
│  │      │  fsl_kpp.c
│  │      │  fsl_kpp.h
│  │      │  fsl_lpi2c.c
│  │      │  fsl_lpi2c.h
│  │      │  fsl_lpi2c_edma.c
│  │      │  fsl_lpi2c_edma.h
│  │      │  fsl_lpspi.c
│  │      │  fsl_lpspi.h
│  │      │  fsl_lpspi_edma.c
│  │      │  fsl_lpspi_edma.h
│  │      │  fsl_lpuart.c
│  │      │  fsl_lpuart.h
│  │      │  fsl_lpuart_edma.c
│  │      │  fsl_lpuart_edma.h
│  │      │  fsl_pit.c
│  │      │  fsl_pit.h
│  │      │  fsl_pmu.c
│  │      │  fsl_pmu.h
│  │      │  fsl_pwm.c
│  │      │  fsl_pwm.h
│  │      │  fsl_pxp.c
│  │      │  fsl_pxp.h
│  │      │  fsl_qtmr.c
│  │      │  fsl_qtmr.h
│  │      │  fsl_rtwdog.c
│  │      │  fsl_rtwdog.h
│  │      │  fsl_sai.c
│  │      │  fsl_sai.h
│  │      │  fsl_sai_edma.c
│  │      │  fsl_sai_edma.h
│  │      │  fsl_semc.c
│  │      │  fsl_semc.h
│  │      │  fsl_snvs_hp.c
│  │      │  fsl_snvs_hp.h
│  │      │  fsl_snvs_lp.c
│  │      │  fsl_snvs_lp.h
│  │      │  fsl_spdif.c
│  │      │  fsl_spdif.h
│  │      │  fsl_spdif_edma.c
│  │      │  fsl_spdif_edma.h
│  │      │  fsl_src.c
│  │      │  fsl_src.h
│  │      │  fsl_tempmon.c
│  │      │  fsl_tempmon.h
│  │      │  fsl_trng.c
│  │      │  fsl_trng.h
│  │      │  fsl_tsc.c
│  │      │  fsl_tsc.h
│  │      │  fsl_usdhc.c
│  │      │  fsl_usdhc.h
│  │      │  fsl_wdog.c
│  │      │  fsl_wdog.h
│  │      │  fsl_xbara.c
│  │      │  fsl_xbara.h
│  │      │  fsl_xbarb.c
│  │      │  fsl_xbarb.h
│  │      │  
│  │      └─camera
│  │              fsl_camera.h
│  │              fsl_camera_device.h
│  │              fsl_camera_receiver.h
│  │              fsl_csi_camera_adapter.c
│  │              fsl_csi_camera_adapter.h
│  │              fsl_sccb.c
│  │              fsl_sccb.h
│  │              fsl_video_common.h
│  │              
│  ├─fatfs              文件系统
│  │  ├─fatfs
│  │  │  ├─documents
│  │  │  │  │  css_e.css
│  │  │  │  │  updates.txt
│  │  │  │  │  
│  │  │  │  ├─doc
│  │  │  │  └─res
│  │  │  │          app1.c
│  │  │  │          app2.c
│  │  │  │          app3.c
│  │  │  │          app4.c
│  │  │  │          app5.c
│  │  │  │          f1.png
│  │  │  │          f2.png
│  │  │  │          f3.png
│  │  │  │          f4.png
│  │  │  │          f5.png
│  │  │  │          f6.png
│  │  │  │          f7.png
│  │  │  │          funcs.png
│  │  │  │          layers.png
│  │  │  │          layers1.png
│  │  │  │          layers2.png
│  │  │  │          layers3.png
│  │  │  │          mkfatimg.zip
│  │  │  │          mkfs.xls
│  │  │  │          modules.png
│  │  │  │          rwtest1.png
│  │  │  │          rwtest2.png
│  │  │  │          rwtest3.png
│  │  │  │          
│  │  │  └─source
│  │  │      │  00history.txt
│  │  │      │  00readme.txt
│  │  │      │  diskio.c
│  │  │      │  diskio.h
│  │  │      │  ff.c
│  │  │      │  ff.h
│  │  │      │  ffconf_template.h
│  │  │      │  ffsystem.c
│  │  │      │  ffunicode.c
│  │  │      │  integer.h
│  │  │      │  
│  │  │      ├─fsl_mmc_disk
│  │  │      │      fsl_mmc_disk.c
│  │  │      │      fsl_mmc_disk.h
│  │  │      │      
│  │  │      ├─fsl_nand_disk
│  │  │      │      fsl_nand_disk.c
│  │  │      │      fsl_nand_disk.h
│  │  │      │      
│  │  │      ├─fsl_ram_disk
│  │  │      │      fsl_ram_disk.c
│  │  │      │      fsl_ram_disk.h
│  │  │      │      
│  │  │      ├─fsl_sd_disk
│  │  │      │      fsl_sd_disk.c
│  │  │      │      fsl_sd_disk.h
│  │  │      │      
│  │  │      └─fsl_usb_disk
│  │  │              fsl_usb_disk.h
│  │  │              fsl_usb_disk_bm.c
│  │  │              fsl_usb_disk_freertos.c
│  │  │              
│  │  └─sdmmc
│  │      ├─inc
│  │      │      fsl_mmc.h
│  │      │      fsl_sd.h
│  │      │      fsl_sdio.h
│  │      │      fsl_sdmmc_common.h
│  │      │      fsl_sdmmc_host.h
│  │      │      fsl_sdmmc_spec.h
│  │      │      
│  │      ├─port
│  │      │  │  fsl_sdmmc_event.h
│  │      │  │  
│  │      │  └─usdhc
│  │      │      ├─freertos
│  │      │      │      fsl_sdmmc_event.c
│  │      │      │      fsl_sdmmc_host.c
│  │      │      │      
│  │      │      ├─interrupt
│  │      │      │      fsl_sdmmc_event.c
│  │      │      │      fsl_sdmmc_host.c
│  │      │      │      
│  │      │      └─polling
│  │      │              fsl_sdmmc_event.c
│  │      │              fsl_sdmmc_host.c
│  │      │              
│  │      └─src
│  │              fsl_mmc.c
│  │              fsl_sd.c
│  │              fsl_sdio.c
│  │              fsl_sdmmc_common.c
│  │              
│  ├─startup            启动文件
│  │  ├─arm
│  │  │      MIMXRT1050_QSP16MB.FLM
│  │  │      MIMXRT1052xxxxx_flexspi_nor.scf
│  │  │      MIMXRT1052xxxxx_flexspi_nor_sdram.scf
│  │  │      MIMXRT1052xxxxx_flexspi_nor_sdram_quick.scf
│  │  │      MIMXRT1052xxxxx_ram.scf
│  │  │      MIMXRT1052xxxxx_sdram.scf
│  │  │      MIMXRT1052xxxxx_sdram_txt.scf
│  │  │      MIMXRT105x_HYPER_256KB_SEC.FLM
│  │  │      MIMXRT105x_QuadSPI_4KB_SEC.FLM
│  │  │      startup_MIMXRT1052.s
│  │  │      
│  │  ├─gcc
│  │  │      MIMXRT1052xxxxx_flexspi_nor.ld
│  │  │      MIMXRT1052xxxxx_flexspi_nor_sdram.ld
│  │  │      MIMXRT1052xxxxx_ram.ld
│  │  │      MIMXRT1052xxxxx_sdram.ld
│  │  │      MIMXRT1052xxxxx_sdram_txt.ld
│  │  │      startup_MIMXRT1052.S
│  │  │      
│  │  ├─iar
│  │  │      LQ_RT1052QSPI_SDRAM_ITCRAM.icf
│  │  │      LQ_RT1052QSPI_SDRAM_QUICK.icf
│  │  │      MIMXRT1052xxxxx_flexspi_nor.icf
│  │  │      MIMXRT1052xxxxx_flexspi_nor_sdram.icf
│  │  │      MIMXRT1052xxxxx_ram.icf
│  │  │      MIMXRT1052xxxxx_sdram.icf
│  │  │      MIMXRT1052xxxxx_sdram_txt.icf
│  │  │      startup_MIMXRT1052.s
│  │  │      startup_MIMXRT1052_ITCRAM.s
│  │  │      
│  │  └─mcuxpresso
│  │          MIMXRT1050-EVK_IS25WP064A.cfx
│  │          MIMXRT1050-EVK_S26KS512S.cfx
│  │          startup_mimxrt1052.c
│  │          startup_mimxrt1052.cpp
│  │          
│  ├─utilities
│  │      fsl_assert.c
│  │      fsl_debug_console.c
│  │      fsl_debug_console.h
│  │      fsl_debug_console_conf.h
│  │      fsl_str.c
│  │      fsl_str.h
│  │      lpuart_adapter.c
│  │      serial_manager.c
│  │      serial_manager.h
│  │      serial_port_uart.c
│  │      serial_port_uart.h
│  │      serial_port_usb.c
│  │      serial_port_usb.h
│  │      uart.h
│  │      
│  └─xip
│          external_flash_config.h
│          fsl_flexspi_nor_boot.c
│          fsl_flexspi_nor_boot.h
│          qspi_config.c
│          xip_config.c
│          
├─Download_Algorithm    下载算法
│      evkbimxrt1050_flexspi_nor.ini
│      evkbimxrt1050_flexspi_nor_sdram.ini
│      evkbimxrt1050_ram.ini
│      evkbimxrt1050_ram_0x1400.ini
│      evkbimxrt1050_sdram_init.ini
│      evkbimxrt1050_sdram_txt_init.ini
│      MIMXRT1052xxxxx_flexspi_nor.scf
│      MIMXRT1052xxxxx_flexspi_nor_sdram.scf
│      MIMXRT1052xxxxx_ram.scf
│      MIMXRT1052xxxxx_ram_0x1400.scf
│      MIMXRT1052xxxxx_sdram.scf
│      MIMXRT1052xxxxx_sdram_txt.scf
│      
├─flexspi_nor_sdram_release
│      NXP_Demo.out
│      
├─output
└─RTE
    ├─RTOS
    │      board.c
    │      rtconfig.h
    │      
    ├─_NXP_Lab_Demo
    │      RTE_Components.h
    │      
    └─_release
            RTE_Components.h
            

```
