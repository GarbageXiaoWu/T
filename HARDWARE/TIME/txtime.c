#include<stm32f10x.h>
#include<txtime.h>
#include<txgpio.h>

#define Perimter 0.2041;//�����ܳ���m��
#define K 360*4;

void Encoder_TIME2_Init()//������1��ʼ��
{

	GPIO_InitTypeDef GPIO_InitStructure;	//����һ��GPIO�ṹ�����
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//����һ����ʱ���ṹ�����
	TIM_ICInitTypeDef TIM_ICInitStructure;	//����һ����ʱ���������ṹ�����
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��2
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;		//����PA0->TIM2_CH1,PA1->TIM2_CH2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����50MHzʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//����Ϊ��������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//���������ֵ	��������������
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	//��ʼ����ʱ��2
 
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;//�˲���ֵ
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
 
	TIM_SetCounter(TIM2,0);
	//TIM2->CNT = 0x7fff;
 
	//TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//�����ʱ��2�жϱ�־λ
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//�򿪶�ʱ��2�ж�
	
	TIM_Cmd(TIM2, ENABLE);
  //������ʹ�ܣ���ʼ���� 
}

void Encoder_TIME3_Init() //������2��ʼ��
{

	GPIO_InitTypeDef GPIO_InitStructure;	//����һ��GPIO�ṹ�����
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//����һ����ʱ���ṹ�����
	TIM_ICInitTypeDef TIM_ICInitStructure;	//����һ����ʱ���������ṹ�����
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ�ܶ�ʱ��2
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;		//����PA6->TIM3_CH1,PA7->TIM3_CH2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����50MHzʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//����Ϊ��������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//���������ֵ	��������������
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	//��ʼ����ʱ��2
 
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;//�˲���ֵ
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
 
	TIM_SetCounter(TIM3,0);
	//TIM2->CNT = 0x7fff;
 
	//TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//�����ʱ��2�жϱ�־λ
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
 
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		//�򿪶�ʱ��2�ж�
	
	TIM_Cmd(TIM3, ENABLE);
  //������ʹ�ܣ���ʼ���� 
}

void TIME1_PWM_Init() //�߼���ʱ��1������·PWM��ʼ��
{

	GPIO_InitTypeDef GPIO_InitStructure;	//����һ��GPIO�ṹ�����
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//����һ����ʱ���ṹ�����
	TIM_OCInitTypeDef TIM_OCInitStructing;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//ʹ�ܶ�ʱ��1
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;		//����PA8->TIM1_CH1 PA9->TIM1_CH2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����50MHzʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//����Ϊ�����������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = 7199;	//���������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 2000;	//ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);	//��ʼ����ʱ��2
	
	TIM_OCInitStructing.TIM_OCMode = TIM_OCMode_PWM2; //��ʱ��ģʽ2
	TIM_OCInitStructing.TIM_OutputState = TIM_OutputState_Enable;  //ʹ��
	TIM_OCInitStructing.TIM_OCPolarity = TIM_OCPolarity_High;  //������Ըߵ�ƽ
	TIM_OC1Init(TIM1, &TIM_OCInitStructing);
	TIM_OC2Init(TIM1, &TIM_OCInitStructing);
	
	TIM_Cmd(TIM1, ENABLE);
  //������ʹ�ܣ���ʼ���� 
	
	TIM_SetCompare1(TIM1,6000);//����Ƚ�ֵ
	TIM_SetCompare2(TIM1,6000);//����Ƚ�ֵ
}

void TIME4_Init() //������ʱʱ�ӳ�ʼ��
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//����һ����ʱ���ṹ�����
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��2
 
	TIM_TimeBaseStructure.TIM_Period = 7199;	//���������ֵ	��������������
	TIM_TimeBaseStructure.TIM_Prescaler = 9999;	//ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);	//��ʼ����ʱ��2
 
	TIM_SetCounter(TIM4,0);
 
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);		//�����ʱ��2�жϱ�־λ
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
 
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);		//�򿪶�ʱ��2�ж�
	
	TIM_Cmd(TIM4, ENABLE);
  //������ʹ�ܣ���ʼ���� 
}

void TIM2_IRQHandler()
{
	
 if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)//�ж�ĳ�����ϵ��ж��Ƿ��� { 
 { 
	 
 }
 TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //��� LINE �ϵ��жϱ�־λ 
} 

//extern number Encoder;
number Encoder = {0.0,0.0,0.0};

void TIM4_IRQHandler()
{
 if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)//�ж�ĳ�����ϵ��ж��Ƿ��� { 
 { 
	//printf("count1: %d\r\n",TIM2->CNT);
	Encoder.M1_rev=TIM2->CNT/K;
	Encoder.M1_M1speed=Encoder.M1_rev*Perimter;      // �����ٶ� m/s
	Encoder.M1_M1speed/=1;
	Encoder.M1Lneth+=Encoder.M1_M1speed*1;//·�� t=1s
	//printf("M1ת�٣�%0.2fr/s \r\n",Encoder.M1_rev);
	//printf("M1���٣�%fm/s\r\n",Encoder.M1_M1speed);
	//printf("M1·�̣�%fm\r\n",Encoder.M1Lneth);
  //TIM_SetCompare1(TIM3,Encoder.M1_M1speed);
	//TIM_SetCounter(TIM2,0);
 }
 TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //��� LINE �ϵ��жϱ�־λ 
} 



























