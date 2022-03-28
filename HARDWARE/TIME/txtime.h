#ifndef __TXTIME_H
#define __TXTIME_H


typedef struct number{
	float M1_rev;
	float M1_M1speed;
	float M1Lneth;

}number;


void Encoder_TIME2_Init(void);//编码器1初始化
void Encoder_TIME3_Init(void); //编码器2初始化
void TIME1_PWM_Init(void); //高级定时器1产生两路PWM初始化
void TIME4_Init(void); //基本定时时钟初始化



#endif



