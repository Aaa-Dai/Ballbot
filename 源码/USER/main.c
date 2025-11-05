#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "motor.h"
#include "exti.h"
#include "remote.h"
#include "timer.h"
#include "paj7620u2.h"
#include "usart.h"

void Remote_Mode(void);//遥控模式
void Gestures_Mode(void);//手势模式
void Bluetooth_Mode(void);//蓝牙模式
void MPU6050_Calibration(void);//MPU6050校准

float pitch,roll,yaw; 		//欧拉角
short gyrox,gyroy,gyroz,jzgx=0,jzgy=0,jzgz=0; //角速度
int na1=0,na2=0,nb1=0,nb2=0,vx=0,vy=0; //编码器数据
int jx,jy,jz,qw_jx=0,qw_jy=0,qw_jz=0,e_jx,e_jy,e_jz,k=1; //PID角度数据
int qw_vx=0,qw_vy=0,e_vx,e_vy,ei_vx=0,ei_vy=0,speed_y=0,speed_x=0,speed_z=0; //PID编码器数据
int PWMA1,PWMA2,PWMB1,PWMB2; //电机输出

int main(void)
{
	u8 key;
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	KEY_Init();
	Motor_Init();
	EXTIX_Init();
	MPU_Init();
	TIM3_PWM_Init(7199,0); //72000000/7200*1=10KHZ
	
	LED0 = 0;
	LED1 = 1;
	delay_ms(1000);
	while(mpu_dmp_init())
 	{
		delay_ms(200);
		LED0 = !LED0;
		LED1 = !LED1;
	}
	delay_ms(100);
	MPU6050_Calibration();
	LED0 = 1;
	LED1 = 1;
	
	while(1)
	{
		key = KEY_Scan(0);
		if(key == KEY0_PRES)
		{
			Remote_Mode(); //遥控模式
		}
		else if(key == KEY1_PRES)
		{
			Gestures_Mode(); //手势模式
		}
		else if(key == WKUP_PRES)
		{
			Bluetooth_Mode(); //蓝牙模式
		}
	}
}

void Remote_Mode(void) //遥控模式
{
	u8 remote_key=0,n=0;
	
	Remote_Init();
	EXTI->IMR |= EXTI_Line0;
	EXTI->IMR |= EXTI_Line1;
	EXTI->IMR |= EXTI_Line2;
	EXTI->IMR |= EXTI_Line3;
	EXTI->IMR |= EXTI_Line4;
	EXTI->IMR |= EXTI_Line5;
	EXTI->IMR |= EXTI_Line11;
	EXTI->IMR |= EXTI_Line13;
	TIM2_Int_Init(199,7199);
	LED0 = 0;
	LED1 = 1;
	
	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw) == 0)
		{
			jx = 100*pitch;
			jy = 100*roll;
			jz = 100*yaw;
			
			if(qw_jz > 12000)
			{
				if(jz < -12000)
				{
					jz = jz + 36000;
				}
			}
			else if(qw_jz < -12000)
			{
				if(jz > 12000)
				{
					jz = jz - 36000;
				}
			}
		}
		else
		{
			continue;
		}
		
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
		gyrox = gyrox - jzgx;
		gyroy = gyroy - jzgy;
		gyroz = gyroz - jzgz;
		
		e_jx = qw_jx - jx;
		e_jy = qw_jy - jy;
		e_jz = qw_jz - jz;
		
		PWMA1 = -15*e_jy+2.8*gyrox-0.1*k*e_jz+0.8*e_vy+0.008*ei_vy-speed_z+speed_y;
		PWMA2 = -15*e_jy+2.8*gyrox+0.1*k*e_jz+0.8*e_vy+0.008*ei_vy+speed_z+speed_y;
		PWMB1 = 15*e_jx-2.8*gyroy-0.1*k*e_jz+0.8*e_vx+0.008*ei_vx-speed_z+speed_x;
		PWMB2 = 15*e_jx-2.8*gyroy+0.1*k*e_jz+0.8*e_vx+0.008*ei_vx+speed_z+speed_x;
		
		A1(PWMA1);
		A2(PWMA2);
		B1(PWMB1);
		B2(PWMB2);
		
		remote_key=Remote_Scan();
		if(remote_key&&n==0)
		{
			n = 1;
			switch(remote_key)
			{
				case 34:speed_x = -1800;break; //左
				case 194:speed_x = 1800;break; //右
				case 98:speed_y = 1800;break; //前
				case 168:speed_y = -1800;break; //后
				case 144:
						k = 0;
						speed_z = -500;
										break; //顺
				case 224:
						k = 0;
						speed_z = 500;
										break; //逆
			}
		}
		else if(remote_key==0&&n==1)
		{
			n = 0;
			speed_y = 0;
			speed_x = 0;
			if(jz > 18000)
			{
				qw_jz = jz - 36000;
			}
			else if(jz < -18000)
			{
				qw_jz = jz + 36000;
			}
			else
			{
				qw_jz = jz;
			}
			speed_z = 0;
			k = 1;
		}
	}
}

void Gestures_Mode(void) //手势模式
{
	while(!paj7620u2_init()) //PAJ7620U2传感器初始化
	{
		delay_ms(500);
	}
	paj7620u2_ready();
	EXTI->IMR |= EXTI_Line0;
	EXTI->IMR |= EXTI_Line1;
	EXTI->IMR |= EXTI_Line2;
	EXTI->IMR |= EXTI_Line3;
	EXTI->IMR |= EXTI_Line4;
	EXTI->IMR |= EXTI_Line5;
	EXTI->IMR |= EXTI_Line11;
	EXTI->IMR |= EXTI_Line13;
	TIM2_Int_Init(199,7199);
	LED0 = 1;
	LED1 = 0;
	
	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw) == 0)
		{
			jx = 100*pitch;
			jy = 100*roll;
			jz = 100*yaw;
			
			if(qw_jz > 12000)
			{
				if(jz < -12000)
				{
					jz = jz + 36000;
				}
			}
			else if(qw_jz < -12000)
			{
				if(jz > 12000)
				{
					jz = jz - 36000;
				}
			}
		}
		else
		{
			continue;
		}
		
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
		gyrox = gyrox - jzgx;
		gyroy = gyroy - jzgy;
		gyroz = gyroz - jzgz;
		
		e_jx = qw_jx - jx;
		e_jy = qw_jy - jy;
		e_jz = qw_jz - jz;
		
		PWMA1 = -15*e_jy+2.8*gyrox-0.1*k*e_jz+0.8*e_vy+0.008*ei_vy-speed_z+speed_y;
		PWMA2 = -15*e_jy+2.8*gyrox+0.1*k*e_jz+0.8*e_vy+0.008*ei_vy+speed_z+speed_y;
		PWMB1 = 15*e_jx-2.8*gyroy-0.1*k*e_jz+0.8*e_vx+0.008*ei_vx-speed_z+speed_x;
		PWMB2 = 15*e_jx-2.8*gyroy+0.1*k*e_jz+0.8*e_vx+0.008*ei_vx+speed_z+speed_x;
		
		A1(PWMA1);
		A2(PWMA2);
		B1(PWMB1);
		B2(PWMB2);
		
		gesture_recognition();
	}
}

void Bluetooth_Mode(void) //蓝牙模式
{
	uart_init(2400);
	EXTI->IMR |= EXTI_Line0;
	EXTI->IMR |= EXTI_Line1;
	EXTI->IMR |= EXTI_Line2;
	EXTI->IMR |= EXTI_Line3;
	EXTI->IMR |= EXTI_Line4;
	EXTI->IMR |= EXTI_Line5;
	EXTI->IMR |= EXTI_Line11;
	EXTI->IMR |= EXTI_Line13;
	TIM2_Int_Init(199,7199);
	LED0 = 0;
	LED1 = 0;
	
	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw) == 0)
		{
			jx = 100*pitch;
			jy = 100*roll;
			jz = 100*yaw;
			
			if(qw_jz > 12000)
			{
				if(jz < -12000)
				{
					jz = jz + 36000;
				}
			}
			else if(qw_jz < -12000)
			{
				if(jz > 12000)
				{
					jz = jz - 36000;
				}
			}
		}
		else
		{
			continue;
		}
		
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
		gyrox = gyrox - jzgx;
		gyroy = gyroy - jzgy;
		gyroz = gyroz - jzgz;
		
		e_jx = qw_jx - jx;
		e_jy = qw_jy - jy;
		e_jz = qw_jz - jz;
		
		PWMA1 = -15*e_jy+2.8*gyrox-0.1*k*e_jz+0.8*e_vy+0.008*ei_vy-speed_z+speed_y;
		PWMA2 = -15*e_jy+2.8*gyrox+0.1*k*e_jz+0.8*e_vy+0.008*ei_vy+speed_z+speed_y;
		PWMB1 = 15*e_jx-2.8*gyroy-0.1*k*e_jz+0.8*e_vx+0.008*ei_vx-speed_z+speed_x;
		PWMB2 = 15*e_jx-2.8*gyroy+0.1*k*e_jz+0.8*e_vx+0.008*ei_vx+speed_z+speed_x;
		
		A1(PWMA1);
		A2(PWMA2);
		B1(PWMB1);
		B2(PWMB2);
	}
}

void MPU6050_Calibration(void)
{
	int i=0;
	jzgx = 0;
	jzgy = 0;
	jzgz = 0;
	
	while(1)
	{
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
		jzgx = jzgx + gyrox;
		jzgy = jzgy + gyroy;
		jzgz = jzgz + gyroz;
		i++;
		if(i == 30)
		{
			jzgx = jzgx/30;
			jzgy = jzgy/30;
			jzgz = jzgz/30;
			return;
		}
		delay_ms(10);
	}
}

