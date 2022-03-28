#include<stm32f10x.h>
#include<txtime.h>
#include<txgpio.h>

#define Perimter 0.2041;//车轮周长（m）
#define K 360*4;

void Encoder_TIME2_Init()//编码器1初始化
{

	GPIO_InitTypeDef GPIO_InitStructure;	//定义一个GPIO结构体变量
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义一个定时器结构体变量
	TIM_ICInitTypeDef TIM_ICInitStructure;	//定义一个定时器编码器结构体变量
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器2
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;		//配置PA0->TIM2_CH1,PA1->TIM2_CH2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置50MHz时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//设置为浮空输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//计数器最大值	编码器的脉冲数
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//时钟不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// 使用的采样频率之间的分频比例
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	//初始化定时器2
 
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;//滤波器值
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
 
	TIM_SetCounter(TIM2,0);
	//TIM2->CNT = 0x7fff;
 
	//TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//清除定时器2中断标志位
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//打开定时器2中断
	
	TIM_Cmd(TIM2, ENABLE);
  //计数器使能，开始计数 
}

void Encoder_TIME3_Init() //编码器2初始化
{

	GPIO_InitTypeDef GPIO_InitStructure;	//定义一个GPIO结构体变量
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义一个定时器结构体变量
	TIM_ICInitTypeDef TIM_ICInitStructure;	//定义一个定时器编码器结构体变量
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器2
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;		//配置PA6->TIM3_CH1,PA7->TIM3_CH2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置50MHz时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//设置为浮空输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//计数器最大值	编码器的脉冲数
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//时钟不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// 使用的采样频率之间的分频比例
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	//初始化定时器2
 
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;//滤波器值
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
 
	TIM_SetCounter(TIM3,0);
	//TIM2->CNT = 0x7fff;
 
	//TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//清除定时器2中断标志位
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
 
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		//打开定时器2中断
	
	TIM_Cmd(TIM3, ENABLE);
  //计数器使能，开始计数 
}

void TIME1_PWM_Init() //高级定时器1产生两路PWM初始化
{

	GPIO_InitTypeDef GPIO_InitStructure;	//定义一个GPIO结构体变量
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义一个定时器结构体变量
	TIM_OCInitTypeDef TIM_OCInitStructing;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//使能定时器1
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;		//配置PA8->TIM1_CH1 PA9->TIM1_CH2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置50MHz时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//设置为复用推挽输出模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = 7199;	//计数器最大值
	TIM_TimeBaseStructure.TIM_Prescaler = 2000;	//时钟不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// 使用的采样频率之间的分频比例
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);	//初始化定时器2
	
	TIM_OCInitStructing.TIM_OCMode = TIM_OCMode_PWM2; //定时器模式2
	TIM_OCInitStructing.TIM_OutputState = TIM_OutputState_Enable;  //使能
	TIM_OCInitStructing.TIM_OCPolarity = TIM_OCPolarity_High;  //输出极性高电平
	TIM_OC1Init(TIM1, &TIM_OCInitStructing);
	TIM_OC2Init(TIM1, &TIM_OCInitStructing);
	
	TIM_Cmd(TIM1, ENABLE);
  //计数器使能，开始计数 
	
	TIM_SetCompare1(TIM1,6000);//输出比较值
	TIM_SetCompare2(TIM1,6000);//输出比较值
}

void TIME4_Init() //基本定时时钟初始化
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义一个定时器结构体变量
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器2
 
	TIM_TimeBaseStructure.TIM_Period = 7199;	//计数器最大值	编码器的脉冲数
	TIM_TimeBaseStructure.TIM_Prescaler = 9999;	//时钟不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// 使用的采样频率之间的分频比例
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);	//初始化定时器2
 
	TIM_SetCounter(TIM4,0);
 
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);		//清除定时器2中断标志位
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
 
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);		//打开定时器2中断
	
	TIM_Cmd(TIM4, ENABLE);
  //计数器使能，开始计数 
}

void TIM2_IRQHandler()
{
	
 if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)//判断某个线上的中断是否发生 { 
 { 
	 
 }
 TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //清除 LINE 上的中断标志位 
} 

//extern number Encoder;
number Encoder = {0.0,0.0,0.0};

void TIM4_IRQHandler()
{
 if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)//判断某个线上的中断是否发生 { 
 { 
	//printf("count1: %d\r\n",TIM2->CNT);
	Encoder.M1_rev=TIM2->CNT/K;
	Encoder.M1_M1speed=Encoder.M1_rev*Perimter;      // 车轮速度 m/s
	Encoder.M1_M1speed/=1;
	Encoder.M1Lneth+=Encoder.M1_M1speed*1;//路程 t=1s
	//printf("M1转速：%0.2fr/s \r\n",Encoder.M1_rev);
	//printf("M1车速：%fm/s\r\n",Encoder.M1_M1speed);
	//printf("M1路程：%fm\r\n",Encoder.M1Lneth);
  //TIM_SetCompare1(TIM3,Encoder.M1_M1speed);
	//TIM_SetCounter(TIM2,0);
 }
 TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //清除 LINE 上的中断标志位 
} 



























