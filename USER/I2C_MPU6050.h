#ifndef __I2C_MMA_H
#define	__I2C_MMA_H
#include "stm32f10x.h"

/* MPU6050 Register Address ------------------------------------------------------------*/
//硬件ID  0x75 值是113
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG				0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

#define	ACCEL_XOUT_H	0x3B	//加速度计输出数据
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41	//温度计计输出数据
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43	//陀螺仪输出数据
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48

#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)

#define	MPU6050_ADDRESS	 0xD0	//从机地址



/****************MAG_Register Address***********************************/
//硬件ID 0x00 值是72
#define MAG_ADDRESS	  0x18 

#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08



/****************BMP280_Register Address***********************************/
//硬件id 0xd0 值为88
#define BMP280_ADDRESS	  0xEC//当SDO为0时地址为1110110  
  
#define BMP280_RESET_VALUE 0xB6  
  
/*calibration parameters */  
#define BMP280_DIG_T1_LSB_REG                0x88  
#define BMP280_DIG_T1_MSB_REG                0x89  
#define BMP280_DIG_T2_LSB_REG                0x8A  
#define BMP280_DIG_T2_MSB_REG                0x8B  
#define BMP280_DIG_T3_LSB_REG                0x8C  
#define BMP280_DIG_T3_MSB_REG                0x8D  
#define BMP280_DIG_P1_LSB_REG                0x8E  
#define BMP280_DIG_P1_MSB_REG                0x8F  
#define BMP280_DIG_P2_LSB_REG                0x90  
#define BMP280_DIG_P2_MSB_REG                0x91  
#define BMP280_DIG_P3_LSB_REG                0x92  
#define BMP280_DIG_P3_MSB_REG                0x93  
#define BMP280_DIG_P4_LSB_REG                0x94  
#define BMP280_DIG_P4_MSB_REG                0x95  
#define BMP280_DIG_P5_LSB_REG                0x96  
#define BMP280_DIG_P5_MSB_REG                0x97  
#define BMP280_DIG_P6_LSB_REG                0x98  
#define BMP280_DIG_P6_MSB_REG                0x99  
#define BMP280_DIG_P7_LSB_REG                0x9A  
#define BMP280_DIG_P7_MSB_REG                0x9B  
#define BMP280_DIG_P8_LSB_REG                0x9C  
#define BMP280_DIG_P8_MSB_REG                0x9D  
#define BMP280_DIG_P9_LSB_REG                0x9E  
#define BMP280_DIG_P9_MSB_REG                0x9F  
  
#define BMP280_CHIPID_REG                    0xD0  /*Chip ID Register */  
#define BMP280_RESET_REG                     0xE0  /*Softreset Register */  
#define BMP280_STATUS_REG                    0xF3  /*Status Register */  
#define BMP280_CTRLMEAS_REG                  0xF4  /*Ctrl Measure Register */  
#define BMP280_CONFIG_REG                    0xF5  /*Configuration Register */  
#define BMP280_PRESSURE_MSB_REG              0xF7  /*Pressure MSB Register */  
#define BMP280_PRESSURE_LSB_REG              0xF8  /*Pressure LSB Register */  
#define BMP280_PRESSURE_XLSB_REG             0xF9  /*Pressure XLSB Register */  
#define BMP280_TEMPERATURE_MSB_REG           0xFA  /*Temperature MSB Reg */  
#define BMP280_TEMPERATURE_LSB_REG           0xFB  /*Temperature LSB Reg */  
#define BMP280_TEMPERATURE_XLSB_REG          0xFC  /*Temperature XLSB Reg */ 




void 	I2C_config(void); 
void 	InitSensor(void);
int16_t GetData_GYRO(unsigned char REG_Address);
int16_t GetData_MAG(unsigned char REG_Address);
short GetData_BMP280(unsigned char REG_Address);

#endif /* __I2C_MMA_H */


