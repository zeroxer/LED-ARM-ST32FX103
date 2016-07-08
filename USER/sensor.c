#include  "init.h"

//******角度参数************
float Gyro_y;        //Y轴陀螺仪数据暂存
float Angle_gy;      //由角速度计算的倾斜角度
float Accel_x;	     //X轴加速度值暂存
float Angle_ax;      //由加速度计算的倾斜角度
float Angle;         //最终测量角度


//----------------------------角度控制PD------------------------------//
float     Angle_Control_P = 40;                        
float     Angle_Control_D = 0.3;  

float     Angle_Control_Out_Max = 5000.0;
 
float     g_Angle_Control_Out=0;//角度控制输出

//----------------------------电机死区---------------------------------//
float     g_Left_Motor_Dead_Value = 680;//
float     g_Right_Motor_Dead_Value = 850;


/*************卡尔曼滤波*********************************/

void Kalman_Filter(float Accel,float Gyro)		
{
		
	static const float Q_angle=0.001;  
	static const float Q_gyro=0.003;
	static const float R_angle=0.5;
	static const float dt=0.009;	                  //dt为kalman滤波器采样时间;
	static const char  C_0 = 1;
	static float Q_bias, Angle_err;
	static float PCt_0, PCt_1, E;
	static float K_0, K_1, t_0, t_1;
	static float Pdot[4] ={0,0,0,0};
	static float PP[2][2] = { { 1, 0 },{ 0, 1 } };
	
	Angle+=(Gyro - Q_bias) * dt; //先验估计

	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

	Pdot[1]= -PP[1][1];
	Pdot[2]= -PP[1][1];
	Pdot[3]=Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - Angle;	//zk-先验估计
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;	 //后验估计
	Q_bias	+= K_1 * Angle_err;	 //后验估计
	Gyro_y   = Gyro - Q_bias;	 //输出值(后验估计)的微分=角速度
}
void Angle_Calculate(void)
{
/****************************加速度****************************************/

	Angle_ax = (Accel_x - 400 ) /16384;   //去除零点偏移,计算得到角度（弧度）
	Angle_ax = Angle_ax*1.2*180/3.14;     //弧度转换为度,

/****************************角速度****************************************/

	Gyro_y = -(Gyro_y - 8)/16.4;         //去除零点偏移，计算角速度值 
	Angle_gy = Angle_gy + Gyro_y*0.009;  //角速度积分得到倾斜角度.	

/***************************卡尔曼滤波+角度融合*************************************/
	Kalman_Filter(Angle_ax,Gyro_y);       //+卡尔曼滤波计算倾角

/*******************************互补滤波******************************************/
/*补偿原理是取当前倾角和加速度获
	得倾角差值进行放大，然后与陀螺
	仪角速度叠加后再积分，从而使倾
	角最跟踪为加速度获得的角度0.5
	为放大倍数，可调节补偿度;
	0.01为系统周期10ms	
*/	
	Angle = Angle + (((Angle_ax-Angle)*0.3 + Gyro_y)*0.009);
															  		
}


void Angle_Control(void)
{
    float value;

    value = Angle * Angle_Control_P
					 + Gyro_y* Angle_Control_D;

    if(value > Angle_Control_Out_Max)
    {
        value = Angle_Control_Out_Max;
    }
    else if(value < -Angle_Control_Out_Max)
    {
        value = -Angle_Control_Out_Max;
    }
       g_Angle_Control_Out = value;
		
}

void Set_Motor_Pwm(void)
{
    float Left_Motor_Voltage;
    float Right_Motor_Voltage;
		

    Left_Motor_Voltage =g_Angle_Control_Out;// g_Angle_Control_Out- g_Speed_Control_Out + g_Direction_Control_Out;
    Right_Motor_Voltage =g_Angle_Control_Out;//g_Angle_Control_Out- g_Speed_Control_Out - g_Direction_Control_Out;
  
		if(Angle>30||Angle<-30)//跌倒停止
		{
				pwm_set_off(TIM1, TIM_Channel_1);
				pwm_set_off(TIM8, TIM_Channel_3);
				pwm_set_off(TIM8, TIM_Channel_1);
				pwm_set_off(TIM8, TIM_Channel_2);
			  TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);//使能或者失能指定的TIM中断
			return;
		}
		//死区控制,
    if(Left_Motor_Voltage > 0)
    {
        Left_Motor_Voltage += g_Left_Motor_Dead_Value;
    }
    else if(Left_Motor_Voltage < 0)
    {
        Left_Motor_Voltage -= g_Left_Motor_Dead_Value;
    }
    if(Right_Motor_Voltage > 0)
    {
        Right_Motor_Voltage += g_Right_Motor_Dead_Value;
    }
    else if(Right_Motor_Voltage < 0)
    {
        Right_Motor_Voltage -= g_Right_Motor_Dead_Value;
    }

    //================饱和处理===================//
    if(Left_Motor_Voltage > Angle_Control_Out_Max)
    {
        Left_Motor_Voltage = Angle_Control_Out_Max;
    }
    else if(Left_Motor_Voltage < -Angle_Control_Out_Max)
    {
        Left_Motor_Voltage = -Angle_Control_Out_Max;
    }
    if(Right_Motor_Voltage > Angle_Control_Out_Max)
    {
        Right_Motor_Voltage = Angle_Control_Out_Max;
    }
    else if(Right_Motor_Voltage < -Angle_Control_Out_Max)
    {
        Right_Motor_Voltage = -Angle_Control_Out_Max;
    }
    //==================电机输出=================//
		
    if(Left_Motor_Voltage > 0)
    {    	
				pwm_set_high(TIM8, TIM_Channel_1);
				pwm_set_on(TIM8, TIM_Channel_2);
				TIM_SetCompare2(TIM8, 7200-(u16)Left_Motor_Voltage);
    }
    else
    {    
        Left_Motor_Voltage = -Left_Motor_Voltage; 
				pwm_set_high(TIM8, TIM_Channel_2);
        pwm_set_on(TIM8, TIM_Channel_1);				
				TIM_SetCompare1(TIM8, 7200-(u16)Left_Motor_Voltage);
    }
    if(Right_Motor_Voltage > 0)
    {   
		
				pwm_set_high(TIM8, TIM_Channel_3);
				pwm_set_on(TIM1, TIM_Channel_1);
				TIM_SetCompare1(TIM1, 7200-(u16)Right_Motor_Voltage);
    }
    else
    {     
				Right_Motor_Voltage = -Right_Motor_Voltage;  	      
				pwm_set_high(TIM1, TIM_Channel_1);
				pwm_set_on(TIM8, TIM_Channel_3);
				TIM_SetCompare3(TIM8, 7200-(u16)Right_Motor_Voltage);
    }
}
