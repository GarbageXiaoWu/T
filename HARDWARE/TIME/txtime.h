#ifndef __TXTIME_H
#define __TXTIME_H


typedef struct number{
	float M1_rev;
	float M1_M1speed;
	float M1Lneth;

}number;


void Encoder_TIME2_Init(void);//������1��ʼ��
void Encoder_TIME3_Init(void); //������2��ʼ��
void TIME1_PWM_Init(void); //�߼���ʱ��1������·PWM��ʼ��
void TIME4_Init(void); //������ʱʱ�ӳ�ʼ��



#endif



