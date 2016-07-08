#include "init.h"

u8 data[20] = {0x00,0x04,0x12,0x24,0x40,0x40,0x24,0x12,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 start[20] = {0x00,0x04,0x25,0x1f,0x05,0x7f,0x05,0x04,0x00,0x0a,0x06,0x7f,0x06,0x0a,0x20,0x1f,0x01,0x3f,0x20,0x00};
u8 emoje[20] = {0x00,0x00,0x00,0x00,0x14,0x14,0x14,0x14,0x40,0x40,0x40,0x14,0x14,0x14,0x14,0x00,0x00,0x00,0x00,0x00};
/*
0x00,0x02,0x06,0x07,0x07,0x00,0x00,0x00,0x00,0x02,0x02,0xFE,0xFE,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

0x00,0x06,0x0E,0x1F,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
*/
u8 hello[20] = {
0x00,0x00,0x00,0x00,
0x48,0x7C,0x7C,0x40,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00};

u8 empty = 0x00,j=0,k=0;

//开机动画
void Led_RollShowStart(u8 data1[])
{
		u8 i=0,j=0,flag=0;
		u8 the[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		u8 zero[1]={0x00};
		
		for(i = 0; i < 20; i++)
		{
				//data1[i]=0xff;
				//for(flag=0;flag<100;flag++)
				/*{
				
					{the[i]=0xff;
						SPI1_WriteByte(the[i]);
						while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
						BK0_LOW;
						BK0_HIGH;
						if(i==0)
						{
							BK2_LOW;
							BK1_LOW;
							BK1_HIGH;
							BK2_HIGH;
						}
						else
						{
							BK1_LOW;
							BK1_HIGH;
						}
						delayus(80000);
						
						BK0_LOW;
				BK0_HIGH;
				for(flag=0;flag<100;flag++)
					{
						for(j = 0; j <20; j++)
						{
							if(j<=i)
							{
								SPI1_WriteByte(data1[j]);
							}
							else
							{
								SPI1_WriteByte(zero[0]);
							}
							//while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
							BK0_LOW;
							BK0_HIGH;
							if(j==0)
							{
								BK2_LOW;
								BK1_LOW;
								BK1_HIGH;
								BK2_HIGH;
							}
							else
							{
								BK1_LOW;
								BK1_HIGH;
							}
							delayus(60);

						}
				}
					
						
					}
				}
				*/
				BK0_LOW;
				BK0_HIGH;
				for(flag=0;flag<100;flag++)
					{
						for(j = 0; j <20; j++)
						{
							if(j<=i)
							{
								SPI1_WriteByte(data1[j]);
							}
							else
							{
								SPI1_WriteByte(zero[0]);
							}
							//while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
							BK0_LOW;
							BK0_HIGH;
							if(j==0)
							{
								BK2_LOW;
								BK1_LOW;
								BK1_HIGH;
								BK2_HIGH;
							}
							else
							{
								BK1_LOW;
								BK1_HIGH;
							}
							delayus(60);

						}
				}
					
		}
		/*
		for(j = 0; j < 20; j++)
		{
			//for(flag=0;flag<200;flag++)
			{
					
					SPI1_WriteByte(the[0]);
					while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
					BK0_LOW;
					BK0_HIGH;
				if(j==0)
				{
					BK2_LOW;
					BK1_LOW;
					BK1_HIGH;
					BK2_HIGH;
				}
				for(i=0;i<=j;i++)
				{
						//start[i]=0xff;
						SPI1_WriteByte(start[i]);
						while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
						
						BK0_LOW;
						BK0_HIGH;
						if(i==0)
						{
							BK2_LOW;
							BK1_LOW;
							BK1_HIGH;
							BK2_HIGH;
						}
						else
						{
							BK1_LOW;
							BK1_HIGH;
						}
						delayus(80000);
				}
			}
		}
		*/
}


/*滚动显示数字1*/
void Led_RollShow(u8 data[])
{
	u8 i=0,j=0,temp=0,flag=0;
	for(j=20;j>=0;j--)
	{
		for(flag=0;flag<200;flag++)
		{
		for(i = 0; i < 20; i++)
		{
			temp=i+j;
			temp=temp%20;
			/*if(temp>=20)
			{
				temp=temp-20;
			}*/
			SPI1_WriteByte(data[temp]);
			while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
			BK0_LOW;
			BK0_HIGH;
			if(i==0)
			{
				BK2_LOW;
				BK1_LOW;
				BK1_HIGH;
				BK2_HIGH;
			}
			else
			{
				BK1_LOW;
				BK1_HIGH;
			}
		
			//delayus(600000);
		}
		//delayus(1000000);
	}
	}
	}
/*
void Led_RollShow(u8 data[])
{
	 u8 i=0;
		for(i = 0; i < 20; i++)
		{
			//data[i]=0xff;
			if(i<k)
				SPI1_WriteByte(data[j]);
			else
				SPI1_WriteByte(empty);
			while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
			BK0_LOW;
			BK0_HIGH;
			if(i==0)
			{
				BK2_LOW;
				BK1_LOW;
				BK1_HIGH;
				BK2_HIGH;
			}
			else
			{
				BK1_LOW;
				BK1_HIGH;
			}
			delayus(1000);
		}
		if(j++>3)
		{
			k++;
			j=0;
		}
		
		if(k==20) k=0;

}	
*/								
void Led_StaticShow(u8 data[])
{
		u8 i=0;
		for(i = 0; i < 20; i++)
		{
			SPI1_WriteByte(data[i]);
			while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
			BK0_LOW;
			BK0_HIGH;
			if(i==0)
			{
				BK2_LOW;
				BK1_LOW;
				BK1_HIGH;
				BK2_HIGH;
			}
			else
			{
				BK1_LOW;
				BK1_HIGH;
			}
			delayus(600);

		}
}

void Led_StaticShowHello(u8 data[])
{
			u8 i=0;
		for(i = 0; i < 20; i++)
		{
			SPI1_WriteByte(data[i]);
			while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
			BK0_LOW;
			BK0_HIGH;
			if(i==0)
			{
				BK2_LOW;
				BK1_LOW;
				BK1_HIGH;
				BK2_HIGH;
			}
			else
			{
				BK1_LOW;
				BK1_HIGH;
			}
			delayus(600);

		}
}

//列扫描
void Led_StaticShow1(u8 data1[])
{

		u8 i=0;
		for(i = 0; i < 20; i++)
		{
			data1[i]=0xff;
			SPI1_WriteByte(data1[i]);
			while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//判断是否发送完毕
			BK0_LOW;
			BK0_HIGH;
			if(i==0)
			{
				BK2_LOW;
				BK1_LOW;
				BK1_HIGH;
				BK2_HIGH;
			}
			else
			{
				BK1_LOW;
				BK1_HIGH;
			}
			delayus(80000);
		}
		
}


//		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==Bit_RESET)  
//				{  
//					GPIO_SetBits(GPIOC,GPIO_Pin_0);  
//				}else{  
//				GPIO_ResetBits(GPIOC,GPIO_Pin_0);  
//				} 



//if(KEY0==0)//经仿真。强制方式也存在死区的
//			{		
//				delayms(5);
//				pwm_set_high(TIM8, TIM_Channel_3);
//				pwm_set_on(TIM1, TIM_Channel_1);
//				TIM_SetCompare1(TIM1, 450);
//				
//				pwm_set_high(TIM8, TIM_Channel_1);
//				pwm_set_on(TIM8, TIM_Channel_2);
//				TIM_SetCompare2(TIM8, 450);
//				
//				while(KEY0==0)
//				{					

//				}
//				pwm_set_off(TIM1, TIM_Channel_1);
//				pwm_set_off(TIM8, TIM_Channel_3);
//				pwm_set_off(TIM8, TIM_Channel_1);
//				pwm_set_off(TIM8, TIM_Channel_2);
//				
//			}	
//		 if(KEY1==0)
//			{
//				delayms(5);
//				pwm_set_on(TIM8, TIM_Channel_3);
//				pwm_set_high(TIM1, TIM_Channel_1);
//				TIM_SetCompare3(TIM8, 450);
//				
//				pwm_set_on(TIM8, TIM_Channel_1);
//				pwm_set_high(TIM8, TIM_Channel_2);
//				TIM_SetCompare1(TIM8, 450);
//				while(KEY1==0)
//				{					

//				}
//				pwm_set_off(TIM1, TIM_Channel_1);
//				pwm_set_off(TIM8, TIM_Channel_3);
//				pwm_set_off(TIM8, TIM_Channel_1);
//				pwm_set_off(TIM8, TIM_Channel_2);
//			}	


//		printf("\r\n---------加速度X轴原始数据---------%d \r\n",GetData_GYRO(ACCEL_XOUT_H));
//		printf("\r\n---------加速度Y轴原始数据---------%d \r\n",GetData_GYRO(ACCEL_YOUT_H));	
//		printf("\r\n---------加速度Z轴原始数据---------%d \r\n",GetData_GYRO(ACCEL_ZOUT_H));	
//		printf("\r\n---------陀螺仪X轴原始数据---------%d \r\n",GetData_GYRO(GYRO_XOUT_H));	
//		printf("\r\n---------陀螺仪Y轴原始数据---------%d \r\n",GetData_GYRO(GYRO_YOUT_H));	
//		printf("\r\n---------陀螺仪Z轴原始数据---------%d \r\n",GetData_GYRO(GYRO_ZOUT_H));	
//		printf("\r\n---------罗盘Z轴原始数据---------%d \r\n",GetData_MAG(MAG_XOUT_L));
//		printf("\r\n---------罗盘Z轴原始数据---------%d \r\n",GetData_MAG(MAG_YOUT_L));
//		printf("\r\n---------罗盘Z轴原始数据---------%d \r\n",GetData_MAG(MAG_ZOUT_L));
		
//		printf("\r\n%d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t\r\n",
//							GetData_GYRO(ACCEL_XOUT_H),GetData_GYRO(ACCEL_YOUT_H),GetData_GYRO(ACCEL_ZOUT_H)
//							,GetData_GYRO(GYRO_XOUT_H),GetData_GYRO(GYRO_YOUT_H),GetData_GYRO(GYRO_ZOUT_H)
//							,GetData_MAG(MAG_XOUT_L),GetData_MAG(MAG_YOUT_L),GetData_MAG(MAG_ZOUT_L)
//							,GetData_BMP280(BMP280_TEMPERATURE_MSB_REG),GetData_BMP280(BMP280_PRESSURE_MSB_REG));



//Temp+=0.1;
//		OutData[0] = 100*sin(Temp)+100;
//    OutData[1] = 100*sin(Temp+2.09)+100;
//    OutData[2] = 100*sin(Temp+4.18)+100;
//    OutData[3] = sin(Temp);
//    if(Temp >= 3.1*2) Temp = 0;
//	   OutPut_Data();


