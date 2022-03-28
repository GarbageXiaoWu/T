#include<stm32f10x.h>
#include<txgpio.h>

void tb6612_gpio_init() //tb6612��STBY���ų�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructing;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructing.GPIO_Mode=GPIO_Mode_Out_PP; //�������
	GPIO_InitStructing.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructing.GPIO_Pin=GPIO_Pin_3;
	
	GPIO_Init(GPIOB,&GPIO_InitStructing);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_3);  //��ʼ������PB3
}

void motor1_gpio_init() //��ʼ�����1ת��Ŀ�������
{
	GPIO_InitTypeDef GPIO_InitStructing;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructing.GPIO_Mode=GPIO_Mode_Out_PP; //�������
	GPIO_InitStructing.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructing.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_12;
	
	GPIO_Init(GPIOB,&GPIO_InitStructing);//��ʼ������PB12 PB13
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);  //��ʼ�������ת
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
}


void motor2_gpio_init() //��ʼ�����2ת��Ŀ�������
{
	GPIO_InitTypeDef GPIO_InitStructing;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructing.GPIO_Mode=GPIO_Mode_Out_PP; //�������
	GPIO_InitStructing.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructing.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	
	GPIO_Init(GPIOB,&GPIO_InitStructing);//��ʼ������PB4 PB5
	
	GPIO_SetBits(GPIOB, GPIO_Pin_4);  //��ʼ�������ת
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}










