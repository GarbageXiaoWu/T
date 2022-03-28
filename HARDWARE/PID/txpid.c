#include<stm32f10x.h>
#include<txpid.h>
#include<stdlib.h>


struct _pid{
	float SetSpeed;  //期望速度
	float ActualSpeed;	//实际速度
	float err;		//偏差
	float err_last; //上一次偏差
	float Kp,Ki,Kd;  //p,i,d 参数
	float intergral; //积分值
	float umax;  //PWM可调的最大值
	float umin;		//PWM可调的最小值
}pid;

void pid_init()	//pid初始化
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










