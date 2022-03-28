#include<stm32f10x.h>
#include<txgpio.h>

void tb6612_gpio_init() //tb6612的STBY引脚初始化
{
	GPIO_InitTypeDef GPIO_InitStructing;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructing.GPIO_Mode=GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructing.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructing.GPIO_Pin=GPIO_Pin_3;
	
	GPIO_Init(GPIOB,&GPIO_InitStructing);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_3);  //初始化引脚PB3
}

void motor1_gpio_init() //初始化电机1转向的控制引脚
{
	GPIO_InitTypeDef GPIO_InitStructing;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructing.GPIO_Mode=GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructing.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructing.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_12;
	
	GPIO_Init(GPIOB,&GPIO_InitStructing);//初始化引脚PB12 PB13
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);  //初始化电机正转
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
}


void motor2_gpio_init() //初始化电机2转向的控制引脚
{
	GPIO_InitTypeDef GPIO_InitStructing;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructing.GPIO_Mode=GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructing.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructing.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	
	GPIO_Init(GPIOB,&GPIO_InitStructing);//初始化引脚PB4 PB5
	
	GPIO_SetBits(GPIOB, GPIO_Pin_4);  //初始化电机正转
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}










