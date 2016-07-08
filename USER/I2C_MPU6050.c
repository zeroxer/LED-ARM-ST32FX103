/******************** (C) COPYRIGHT 2012  **************************

 * 硬件连接：-----------------
 *          |                 |
 *          |  PB6-I2C1_SCL		|
 *          |  PB7-I2C1_SDA   |
 *          |                 |
 *           -----------------
 * 库版本  ：ST3.5.0
 * 作者    ： Orange 
**********************************************************************************/
#include "stm32f10x.h"
#include "I2C_MPU6050.h"
#include "delay.h"

/*
 * 函数名：I2C_GPIO_Config
 * 描述  ：I2C1 I/O配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
		/* 使能与 I2C1 有关的时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB,ENABLE); 
	  
	 /* PB6-I2C1_SCL、PB7-I2C1_SDA*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; //开漏输出
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
}


/*
 * 函数名：I2C_Mode_Config
 * 描述  ：I2C 工作模式配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void I2C_Mode_Config(void)
{
	I2C_InitTypeDef I2C_InitStructure; 
	 
	  /* I2C 配置 */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C ; 
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; 
	I2C_InitStructure.I2C_OwnAddress1 = 0x01; //自身地址，不要与从设备地址相同
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; 
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
	I2C_InitStructure.I2C_ClockSpeed = 400000;//最高为400khz  
	I2C_Init(I2C1, &I2C_InitStructure);		/* I2C1 初始化 */ 
	
	I2C_Cmd(I2C1,ENABLE); /* 使能 I2C1 */
	I2C_AcknowledgeConfig(I2C1, ENABLE);/*允许应答模式*/   
}
/***************************************************************************************/
/*
 * 函数名：I2C_MMA_Init
 * 描述  ：I2C 外设(MMA7455)初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void I2C_config(void)
{	   
 	I2C_GPIO_Config();
	I2C_Mode_Config();
}  

/*
 * 函数名：I2C_ByteWrite
 * 描述  ：写一个字节到I2C设备寄存器中
 * 输入  ：REG_Address 接收数据的IIC设备寄存器的地址 
 *         REG_data 待写入的数据
 * 输出  ：无
 * 返回  ：无
 * 调用  ：内部调用
 */	
void I2C_ByteWrite(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));//检测总线是否忙 就是看 SCL 或SDA是否为 低 
	I2C_AcknowledgeConfig(I2C1,ENABLE);//允许接受应答
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1,SlaveAddress,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1,REG_Address);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1,REG_data);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C1,ENABLE);

}


/*
 * 函数名：I2C_ByteRead
 * 描述  ：从IIC设备寄存器中读取一个字节
 * 输入  ：REG_Address 读取数据的寄存器的地址 
 * 输出  ：无
 * 返回  ：无
 * 调用  ：内部调用 
*/
uint8_t I2C_ByteRead(uint8_t SlaveAddress, uint8_t REG_Address)
{
uint8_t REG_data;

while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));//检测总线是否忙 就是看 SCL 或SDA是否为 低 

I2C_GenerateSTART(I2C1,ENABLE);//发送起始信号
while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));//设置为主模式完毕

I2C_Send7bitAddress(I2C1,SlaveAddress,I2C_Direction_Transmitter);//发送设备地址+写信号

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//

I2C_Cmd(I2C1,ENABLE);

I2C_SendData(I2C1,REG_Address);//发送存储单元地址，从0开始

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

I2C_GenerateSTART(I2C1,ENABLE);//起始信号
while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

I2C_Send7bitAddress(I2C1,SlaveAddress,I2C_Direction_Receiver);//发送设备地址+读信号
while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));//地址发送完毕

I2C_AcknowledgeConfig(I2C1,DISABLE);//有数据要读时，关闭应答
I2C_GenerateSTOP(I2C1,ENABLE);//产生停止信号
while(!(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)));//等待接受完成

REG_data=I2C_ReceiveData(I2C1);//读出寄存器数据

return REG_data;

}

/*
 * 函数名：void InitMPU6050(void)
 * 描述  ：初始化Mpu6050
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void InitSensor(void)
{
	/***********************MPU9250_SET********************************************/
	delayms(10);
	I2C_ByteWrite(MPU6050_ADDRESS,PWR_MGMT_1,0x00);//解除休眠状态
	delayms(10);
	I2C_ByteWrite(MPU6050_ADDRESS,SMPLRT_DIV,0x07);//采样率1000/(1+7)=125HZ
	delayms(10);
	I2C_ByteWrite(MPU6050_ADDRESS,CONFIG,0x06);//低通滤波器 0x06 5hz
	delayms(10);
	I2C_ByteWrite(MPU6050_ADDRESS,GYRO_CONFIG,0x18);//陀螺仪测量范围 0X18 正负2000度
	delayms(10);
	I2C_ByteWrite(MPU6050_ADDRESS,ACCEL_CONFIG,0x00);//加速读量程正负2g  
	delayms(10);
	I2C_ByteWrite(MPU6050_ADDRESS,0x37,0x02);// Set by pass mode for the magnetometers
	delayms(10);
	
	/***********************MAG_SET********************************************/
	I2C_ByteWrite(MAG_ADDRESS,0x0B,0x01); // Reset Device
	delayms(10);
	I2C_ByteWrite(MAG_ADDRESS,0x0A,0x10);	// Power-down mode
	delayms(10);
	I2C_ByteWrite(MAG_ADDRESS,0x0A,0x11); //Request first magnetometer single measurement
	delayms(10);
	
	/***************************BMP280_SET*************************************/
	I2C_ByteWrite(BMP280_ADDRESS,0xF4,0x25);//设置forced mode，每次测量完都要回到sleep mode
	delayms(10);
	
}


/*
 * 函数名：GetData
 * 描述  ：获得16位数据
 * 输入  ：REG_Address 寄存器地址
 * 输出  ：返回寄存器数据
 * 调用  ：外部调用
 */
//有符号数
int16_t GetData_GYRO(unsigned char REG_Address)
{
	uint8_t H,L;
	H=I2C_ByteRead(MPU6050_ADDRESS,REG_Address);
	L=I2C_ByteRead(MPU6050_ADDRESS,REG_Address+1);
	return (H<<8)+L;   //合成数据

}
//有符号数 ，是否可设置为连续读取模式
int16_t GetData_MAG(unsigned char REG_Address)
{
	uint8_t H,L;
	uint8_t ST1;
	I2C_ByteWrite(MAG_ADDRESS,0x0A,0x11);//根据手册知单次测量模什结束会回到powerdown模式，需要重置一下
	delayms(1);
	
  do// Read register Status 1 and wait for the DRDY: Data Ready
  {
    ST1=I2C_ByteRead(MAG_ADDRESS,0x02);
  }
  while(!(ST1&0x01));
	 
	L=I2C_ByteRead(MAG_ADDRESS,REG_Address);
	H=I2C_ByteRead(MAG_ADDRESS,REG_Address+1);

	return (H<<8)+L;   //合成数据

}

//是否是带符号数，待确认
int16_t GetData_BMP280(unsigned char REG_Address)
{
	uint8_t H,L;
	I2C_ByteWrite(BMP280_ADDRESS,0xF4,0x25);//设置forced mode，每次测量完都要回到sleep mode
	delayms(5);
	H=I2C_ByteRead(BMP280_ADDRESS,REG_Address);
	L=I2C_ByteRead(BMP280_ADDRESS,REG_Address+1);
	return (H<<8)+L;   //合成数据

}


/******************* (C) COPYRIGHT 2012  *****END OF FILE************/



