#include "pwm.h"
/*对应管脚
	PC6			PC7			PC8			PA8	
	T8C1		T8C2		T8C3		T1C1
	
	PA7			PB0			PB1			PB13
	T8C1N		T8C2N		T8C3N		T1C1N
*/
//arr：自动重装值
//psc：时钟预分频数
void PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//初始化TIMx的时间基数
	TIM_OCInitTypeDef  TIM_OCInitStructure;//初始化外设TIMx
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;//死区设置
	
/*************1、引脚io设置*************************/
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);//使能GPIO外设时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//使能复用功能   
	
	//设置该引脚为复用输出功能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //端口频率可设为2,10,50 
	GPIO_Init(GPIOA, &GPIO_InitStructure);//启动A端口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//启动B端口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//启动C端口
	
/*****************2、通道设置*****************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_TIM8, ENABLE);//使能外设时钟TIMx,TIM8
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //TIM脉冲宽度调制模式1：小于设定值则为高；2反之
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //选择互补输出比较状态
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High; //TIM互补输出极性为高
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //选择空闲状态
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //重置互补输出的输出比较状态
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //TIMx通道1设置
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //预装载使能，为了让控制更精准，更改不是立马改变，在本次波形执行完之后
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //不用也可以
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //
 

	//死区设置
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;//设置在运行模式下非工作状态选项         
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;//设置空闲状态下的非工作状态        
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;//设置锁电平参数，不锁定任何位            
	TIM_BDTRInitStructure.TIM_DeadTime  = 100;//死区时间,0-0xff,设置了输出打开和关闭之间的延时                        
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;//刹车功能使能                              
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;   
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//自动输出使能 
	TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure); //
	TIM_BDTRConfig(TIM8,&TIM_BDTRInitStructure); //
	
	
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIMx
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	
	TIM_Cmd(TIM8, ENABLE);  //使能TIM8
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	
	
	pwm_set_off(TIM8, TIM_Channel_1);
	pwm_set_off(TIM8, TIM_Channel_2);
	pwm_set_off(TIM8, TIM_Channel_3);
	pwm_set_off(TIM1, TIM_Channel_1);
}

//********************************************************************************  
/* set phase to "positive without PWM" */
void pwm_set_high(TIM_TypeDef* TIMx, uint16_t TIM_Channel)
{
	TIM_SelectOCxM(TIMx, TIM_Channel, TIM_ForcedAction_Active);
	TIM_CCxCmd(TIMx, TIM_Channel, TIM_CCx_Enable);
	TIM_CCxNCmd(TIMx, TIM_Channel, TIM_CCxN_Disable);
}
//********************************************************************************  
/* set phase to "negative without PWM */
void pwm_set_low(TIM_TypeDef* TIMx, uint16_t TIM_Channel)
{
    TIM_SelectOCxM(TIMx, TIM_Channel, TIM_ForcedAction_InActive);
    TIM_CCxCmd(TIMx, TIM_Channel, TIM_CCx_Disable);
    TIM_CCxNCmd(TIMx, TIM_Channel, TIM_CCxN_Enable);
}
//互补输出使能
void pwm_set_on(TIM_TypeDef* TIMx, uint16_t TIM_Channel)
{
		TIM_SelectOCxM(TIMx, TIM_Channel, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIMx, TIM_Channel, TIM_CCx_Enable);
		TIM_CCxNCmd(TIMx, TIM_Channel, TIM_CCxN_Enable);
}

//输出比较关断
void pwm_set_off(TIM_TypeDef* TIMx, uint16_t TIM_Channel)
{
    TIM_CCxCmd(TIMx, TIM_Channel, TIM_CCx_Disable);
    TIM_CCxNCmd(TIMx, TIM_Channel, TIM_CCxN_Disable);
}





