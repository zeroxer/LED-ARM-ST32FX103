
#include "init.h"
#include <math.h>
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 * 返回  ：无
 */
int main(void)
{	
	Stm32_Clock_Init(6);//系统时钟设置为外部晶振，9倍频
	delay_init(72);//系统SysTick初始化 感觉不太准，而且delayms()最大参数为1864
	
  GPIO_Configuration();//按键、led、
	USART1_Config();	
	
	I2C_config(); 
  InitSensor();/*传感器初始化*/

	SPI1_Init();
	PWM_Init(7199,0);//10kHZ
	TIM3_Init(29,7199);//10Khz的计数频率，计数到5000为500ms  30为3ms

	/***********************************************************************/
	for(;;)
	{		
		u8 data1[20] = {0x00,0x00,0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x7e,0x18,0x24,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
			
    int k=0,j=0;	
		
		//开机动画
		for(j=0;j<1;j++)
		{
			Led_RollShowStart(start);
		}
		
		
	//列扫描
		for(k=0;k<3;k++)
		{
			Led_StaticShow1(data1);
		}
		
		
		//滚动显示1
		for(j=0;j<3;j++)
		{
			Led_RollShow(emoje);
		}

		/*
    for(;j<200;j++)
		{
			Led_StaticShow(data);
		}
*/
		
	/*
		//静态显示数字1
		for(j=0;j<200;j++)
		{
			Led_StaticShowHello(hello);
		}
		*/
			//Angle融合角度
			//Gyro_y;//陀螺仪速度
			//Angle_gy;//积分角度
			//0：代表没有输出
			//showwave(Angle,Gyro_y,Angle_gy,0);


	}//while结束		

}

