#ifndef __Lab_9AX_H
#define __Lab_9AX_H

#define FXAS21002C_ADDR                  0x20

#define FXAS21002C_STATUS                0x00
#define FXAS21002C_OUT_X_MSB             0x01
#define FXAS21002C_OUT_X_LSB             0x02
#define FXAS21002C_OUT_Y_MSB             0x03
#define FXAS21002C_OUT_Y_LSB             0x04
#define FXAS21002C_OUT_Z_MSB             0x05
#define FXAS21002C_OUT_Z_LSB             0x06

#define FXAS21002C_DR_STATUS             0x07
#  define DR_STATUS_ZYXOW                (1 << 7)
#  define DR_STATUS_ZOW                  (1 << 6)
#  define DR_STATUS_YOW                  (1 << 5)
#  define DR_STATUS_XOW                  (1 << 4)
#  define DR_STATUS_ZYXDR                (1 << 3)
#  define DR_STATUS_ZDR                  (1 << 2)
#  define DR_STATUS_YDR                  (1 << 1)
#  define DR_STATUS_XDR                  (1 << 0)

#define FXAS21002C_F_STATUS              0x08
#  define F_STATUS_F_OVF                 (1 << 7)
#  define F_STATUS_F_WMKF                (1 << 6)
#  define F_STATUS_F_CNT_SHIFTS          0
#  define F_STATUS_F_CNT_MASK            (0x3f << F_STATUS_F_CNT_SHIFTS)

#define FXAS21002C_F_SETUP               0x09
#  define F_SETUP_F_MODE_SHIFTS          6
#  define F_SETUP_F_MODE_MASK            (0x3 << F_SETUP_F_MODE_SHIFTS)
#  define F_SETUP_F_WMRK_SHIFTS          0
#  define F_SETUP_F_WMRK_MASK            (0x3f << F_SETUP_F_WMRK_SHIFTS)

#define FXAS21002C_F_EVENT               0x0a
#  define F_EVENT_F_EVENT                (1 << 5)
#  define F_EVENT_FE_TIME_SHIFTS         0
#  define F_EVENT_FE_TIME_MASK           (0x1f << F_EVENT_FE_TIME_SHIFTS)

#define FXAS21002C_INT_SRC_FLAG          0x0b
#  define INT_SRC_FLAG_BOOTEND           (1 << 3)
#  define INT_SRC_FLAG_SRC_FIFO          (1 << 2)
#  define INT_SRC_FLAG_SRC_RT            (1 << 1)
#  define INT_SRC_FLAG_SRC_DRDY          (1 << 0)

#define FXAS21002C_WHO_AM_I              0x0c
#define FXAS21002C_ID                    0xd7

#define FXAS21002C_CTRL_REG0             0x0d
#  define CTRL_REG0_BW_SHIFTS            6
#  define CTRL_REG0_BW_MASK              (0x3 << CTRL_REG0_BW_SHIFTS)
#  define CTRL_REG0_SPIW                 (1 << 6)
#  define CTRL_REG0_SEL_SHIFTS           3
#  define CTRL_REG0_SEL_MASK             (0x2 << CTRL_REG0_SEL_SHIFTS)
#  define CTRL_REG0_HPF_EN               (1 << 2)
#  define CTRL_REG0_FS_SHIFTS            0
#  define CTRL_REG0_FS_MASK              (0x3 << CTRL_REG0_FS_SHIFTS)
#  define CTRL_REG0_FS_2000_DPS          (0 << CTRL_REG0_FS_SHIFTS)
#  define CTRL_REG0_FS_1000_DPS          (1 << CTRL_REG0_FS_SHIFTS)
#  define CTRL_REG0_FS_500_DPS           (2 << CTRL_REG0_FS_SHIFTS)
#  define CTRL_REG0_FS_250_DPS           (3 << CTRL_REG0_FS_SHIFTS)

#define FXAS21002C_RT_CFG                0x0e
#  define RT_CFG_ELE                     (1 << 3)
#  define RT_CFG_ZTEFE                   (1 << 2)
#  define RT_CFG_YTEFE                   (1 << 1)
#  define RT_CFG_XTEFE                   (1 << 0)

#define FXAS21002C_RT_SRC                0x0f
#  define RT_SRC_EA                      (1 << 6)
#  define RT_SRC_ZRT                     (1 << 5)
#  define RT_SRC_Z_RT_POL                (1 << 4)
#  define RT_SRC_YRT                     (1 << 3)
#  define RT_SRC_Y_RT_POL                (1 << 2)
#  define RT_SRC_XRT                     (1 << 1)
#  define RT_SRC_X_RT_POL                (1 << 0)

#define FXAS21002C_RT_THS                0x10
#  define RT_THS_DBCNTM                  (1 << 7)
#  define RT_THS_THS_SHIFTS              0
#  define RT_THS_THS_MASK                (0x7f << RT_THS_THS_SHIFTS)

#define FXAS21002C_RT_COUNT              0x11
#define FXAS21002C_TEMP                  0x12

#define FXAS21002C_CTRL_REG1             0x13
#  define CTRL_REG1_RST                  (1 << 6)
#  define CTRL_REG1_ST                   (1 << 5)
#  define CTRL_REG_DR_SHIFTS             2
#  define CTRL_REG_DR_MASK               (0x07 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG_DR_12_5               (7 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG_DR_12_5_1             (6 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG_DR_25HZ               (5 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG_DR_50HZ               (4 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG_DR_100HZ              (3 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG_DR_200HZ              (2 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG_DR_400HZ              (1 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG_DR_800HZ              (0 << CTRL_REG_DR_SHIFTS)
#  define CTRL_REG1_ACTIVE               (1 << 1)
#  define CTRL_REG1_READY                (1 << 0)

#define FXAS21002C_CTRL_REG2             0x14
#  define CTRL_REG2_INT_CFG_FIFO         (1 << 7)
#  define CTRL_REG2_INT_EN_FIFO          (1 << 6)
#  define CTRL_REG2_INT_CFG_RT           (1 << 5)
#  define CTRL_REG2_INT_EN_RT            (1 << 4)
#  define CTRL_REG2_INT_CFG_DRDY         (1 << 3)
#  define CTRL_REG2_INT_EN_DRDY          (1 << 2)
#  define CTRL_REG2_IPOL                 (1 << 1)
#  define CTRL_REG2_PP_OD                (1 << 0)

#define FXAS21002C_CTRL_REG3             0x15
#  define CTRL_REG3_WRAPTOONE            (1 << 3)
#  define CTRL_REG3_EXTCTRLEN            (1 << 2)
#  define CTRL_REG3_FS_DOUBLE            (1 << 0)

#define DEF_REG(r)   {r, #r}

/* default values for this device */
#define FXAS21002C_DEFAULT_RATE          400
#define FXAS21002C_MAX_RATE              800
#define FXAS21002C_MAX_OUTPUT_RATE       280
#define FXAS21002C_DEFAULT_RANGE_DPS     2000
#define FXAS21002C_DEFAULT_FILTER_FREQ   30
#define FXAS21002C_TEMP_OFFSET_CELSIUS   40

#define FXAS21002C_MAX_OFFSET			0.45f /**< max offset: 25 degrees/s */




/*--------------------------------------------------------------------------------------
----------------------------------FXAS21002????------------------------------------------
----------------------------------------------------------------------------------------*/
/**
  * @brief    ????????????????????
  *
  * @param    gyrox,gyroy,gyroz:??????x,y,z????????????(??????)
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_21002_GetRaw(short * gyrox, short *gyroy, short *gyroz);

/**
  * @brief    ????FXAS21002 ????????
  *
  * @param    enable :  1??????  0??????
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_21002_Active(bool enable);





/**
  * @brief    ????FXAS21002 ???? ????
  *
  * @param    BW :  ???????????????????????????? 
  *
  * @return   
  *
  * @note     ??????????????  ??????????????????????????
  *    
  *    mode        ????????    800 Hz 400 Hz 200 Hz  100 Hz 50 Hz  25 Hz 12.5 Hz
  *     0          ????????      15    7.5    3.75   1.875  0.937 0.468  0.234
  *     1          ????????     7.7   3.85   1.925   0.963  0.481 0.241  0.120
  *     2          ????????     3.9   1.95   0.975   0.488  0.244 0.122  0.061
  *     3          ????????    1.98   0.99   0.495   0.248  0.124 0.062  0.031
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_21002_SetHP(uint8_t mode);






/**
  * @brief    ????FXAS21002 ???? ????
  *
  * @param    BW :  ???????????????????????????? 
  *
  * @return   
  *
  * @note     ??????????????  ??????????????????????????
  *  mode     ????????  800 Hz  400 Hz  200 Hz  100 Hz  50 Hz  25 Hz  12.5 Hz
  *  0        ????????  256     128      64      32     16      8        4
  *  1        ????????  128      64      32      16      8      4       ??
  *  2        ????????   64      32      16       8      4     ??       ??
  *
  * @example  FX_21002_SetLP(0) //???????????? 800Hz ?????????????????? 256
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_21002_SetLP(uint8_t mode);



/**
  * @brief    ????FXAS21002 ????
  *
  * @param    dps :  ???????? ???? ??????
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_21002_SetRange(uint16_t dps);




/**
  * @brief    ????FXAS21002 ????????
  *
  * @param    fps ???????????? ???? 1????????????
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_21002_SetRate(uint16_t fps);




/**
  * @brief    FXAS21002 ????
  *
  * @param    
  *
  * @return   0 : ????   ?????????? 
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_21002_Check(void);



#define FXOS8700_ADDR              0x1e

#define FXOS8701CQ_DR_STATUS       0x00
#  define DR_STATUS_ZYXDR          (1 << 3)

#define FXOS8701CQ_OUT_X_MSB       0x01

#define FXOS8701CQ_XYZ_DATA_CFG    0x0e
#  define XYZ_DATA_CFG_FS_SHIFTS   0
#  define XYZ_DATA_CFG_FS_MASK     (3 << XYZ_DATA_CFG_FS_SHIFTS)
#  define XYZ_DATA_CFG_FS_2G       (0 << XYZ_DATA_CFG_FS_SHIFTS)
#  define XYZ_DATA_CFG_FS_4G       (1 << XYZ_DATA_CFG_FS_SHIFTS)
#  define XYZ_DATA_CFG_FS_8G       (2 << XYZ_DATA_CFG_FS_SHIFTS)

#define FXOS8701CQ_WHOAMI          0x0d
#  define FXOS8700CQ_WHOAMI_VAL    0xC7
#  define FXOS8701CQ_WHOAMI_VAL    0xCA

#define FXOS8701CQ_CTRL_REG1       0x2a
#  define FXOS8701CQ_CTRL_REG1_ACTIVE         (1 << 0)
#  define CTRL_REG1_DR_SHIFTS      3
#  define CTRL_REG1_DR_MASK        (7 << CTRL_REG1_DR_SHIFTS)
#  define CTRL_REG1_DR(n)          (((n) & 7) << CTRL_REG1_DR_SHIFTS)
#define FXOS8701CQ_CTRL_REG2       0x2b
#  define CTRL_REG2_AUTO_INC       (1 << 5)

#define FXOS8701CQ_M_DR_STATUS     0x32
#  define M_DR_STATUS_ZYXDR         (1 << 3)
#define FXOS8701CQ_M_OUT_X_MSB     0x33
#define FXOS8701CQ_TEMP            0x51
#define FXOS8701CQ_M_CTRL_REG1     0x5b
#  define M_CTRL_REG1_HMS_SHIFTS   0
#  define M_CTRL_REG1_HMS_MASK     (3 << M_CTRL_REG1_HMS_SHIFTS)
#  define M_CTRL_REG1_HMS_A        (0 << M_CTRL_REG1_HMS_SHIFTS)
#  define M_CTRL_REG1_HMS_M        (1 << M_CTRL_REG1_HMS_SHIFTS)
#  define M_CTRL_REG1_HMS_AM       (3 << M_CTRL_REG1_HMS_SHIFTS)
#  define M_CTRL_REG1_OS_SHIFTS    2
#  define M_CTRL_REG1_OS_MASK      (7 << M_CTRL_REG1_HMS_SHIFTS)
#  define M_CTRL_REG1_OS(n)        (((n) & 7) << M_CTRL_REG1_OS_SHIFTS)

#define FXOS8701CQ_M_CTRL_REG2     0x5c
#define FXOS8701CQ_M_CTRL_REG3     0x5d

#define DEF_REG(r)   {r, #r}

/* default values for this device */
#define FXOS8701C_ACCEL_DEFAULT_RANGE_G              8
#define FXOS8701C_ACCEL_DEFAULT_RATE                 400 /* ODR is 400 in Hybird mode (accel + mag) */
#define FXOS8701C_ACCEL_DEFAULT_ONCHIP_FILTER_FREQ   50
#define FXOS8701C_ACCEL_DEFAULT_DRIVER_FILTER_FREQ   30
#define FXOS8701C_ACCEL_MAX_OUTPUT_RATE              280

#define FXOS8701C_MAG_DEFAULT_RANGE_GA               12 /* It is fixed at 12 G */
#define FXOS8701C_MAG_DEFAULT_RATE                   100
#define FXOS8701C_ONE_G                              9.80665f




/**
  * @brief    FXOS8700 ????
  *
  * @param    
  *
  * @return   0 : ????   ?????????? 
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_8700_Check(void);


/**
  * @brief    ????FXOS8700 ????????
  *
  * @param    fps  ???????????? ???? 1????????????
  * @param    mode 0: ??????????????  1??????????????  2????????????????????????????????????????????
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_8700_SetRate(uint16_t fps, uint8_t mode);


/**
  * @brief    ????FXOS8700 ????
  *
  * @param    dps :  ???????? ???? ??????
  *
  * @return   
  *
  * @note     ???????????????? ???????????????? ??2g;??0.244 mg/LSB   ??4g;??0.488 mg/LSB   ??8g ??0.976 mg/LSB
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_8700_SetRange(uint8_t mg);


/**
  * @brief    ????????????????????
  *
  * @param    mx,my,mz:??????x,y,z????????????(??????)
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_8700_GetMAGRaw(short *mx,short *my,short *mz);


/**
  * @brief    ????????????????????
  *
  * @param    ax,ay,az:????????x,y,z????????????(??????)
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_8700_GetACCRaw(short *ax,short *ay,short *az);


/**
  * @brief    ????FXOS8700 ????????
  *
  * @param    enable :  1??????  0?????? 
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t FX_8700_Active(bool enable);



/*--------------------------------------------------------------------------------------
----------------------------------????????????------------------------------------------
----------------------------------------------------------------------------------------*/

/**
  * @brief    IIC ??????
  *
  * @param    addr:???????? 
  * @param    reg :??????????????????
  * @param    len :????????????
  * @param    buf :??????????????????
  *
  * @return   0 ??????????
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/12 ??????
  */
uint8_t FX_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);




/**
  * @brief    IIC ????????????
  *
  * @param    addr  :???????? 
  * @param    reg   :????????????????
  * @param    value :??????????
  *
  * @return   0 ??????????
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/12 ??????
  */
uint8_t FX_Write_Byte(uint8_t addr,uint8_t reg,uint8_t value);



/**
  * @brief    IIC ????????????
  *
  * @param    addr  :???????? 
  * @param    reg   :????????????????
  * @param    value :??????????
  *
  * @return   0 ??????????
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/12 ??????
  */
uint8_t FX_Read_Byte(uint8_t addr,uint8_t reg);


/**
  * @brief    ????????????????
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
uint8_t Lab_9AX_Init(void);


/**
  * @brief    ????????
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ??????
  */
void Test_9AX(void);


#endif


