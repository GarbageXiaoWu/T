#include<stm32f10x.h>
#include<txpid.h>
#include<stdlib.h>


struct _pid{
	float SetSpeed;  //�����ٶ�
	float ActualSpeed;	//ʵ���ٶ�
	float err;		//ƫ��
	float err_last; //��һ��ƫ��
	float Kp,Ki,Kd;  //p,i,d ����
	float intergral; //����ֵ
	float umax;  //PWM�ɵ������ֵ
	float umin;		//PWM�ɵ�����Сֵ
}pid;

void pid_init()	//pid��ʼ��
{
	pid.SetSpeed = 0.0;
	pid.ActualSpeed = 0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.intergral = 0.0;
	pid.Kd = 0;
	pid.Ki = 5;
	pid.Kp = 80;
	//0pid.umax = 7000;
	//pid.umin = 1000;
}

float pid_realize(float speed)
{
	int index;
	float incrementSpeed;
	pid.ActualSpeed = speed;
	pid.err = pid.SetSpeed - pid.ActualSpeed;
	if(abs(pid.SetSpeed - pid.ActualSpeed) > 50 )
	{
	index = 0;
	}else if(abs(pid.SetSpeed - pid.ActualSpeed) <= 50) {
		index = 1;
		pid.intergral +=pid.err;
	}
	incrementSpeed = pid.Kp*(pid.err - pid.err_last) + pid.Ki*index*pid.err + pid.Kd;
	speed += incrementSpeed;
	pid.err_last = pid.err;
	
	return speed;
}










