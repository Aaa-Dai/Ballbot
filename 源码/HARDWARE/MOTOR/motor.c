#include "motor.h"
#include "timer.h"


void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOF,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_8;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOG,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_8);
}

void A1(int PWM)
{
	if(PWM > 0)
	{
		if(PWM > 3000)
		{
			PWM = 3000;
		}
		GPIO_SetBits(GPIOF,GPIO_Pin_15);
		GPIO_ResetBits(GPIOF,GPIO_Pin_14);
		TIM_SetCompare4(TIM3,600+PWM);
	}
	else if(PWM < 0)
	{
		if(PWM < -3000)
		{
			PWM = -3000;
		}
		GPIO_ResetBits(GPIOF,GPIO_Pin_15);
		GPIO_SetBits(GPIOF,GPIO_Pin_14);
		TIM_SetCompare4(TIM3,600-PWM);
	}
	else if(PWM == 0)
	{
		GPIO_ResetBits(GPIOF,GPIO_Pin_15);
		GPIO_ResetBits(GPIOF,GPIO_Pin_14);
		TIM_SetCompare4(TIM3,0);
	}
}

void A2(int PWM)
{
	if(PWM > 0)
	{
		if(PWM > 3000)
		{
			PWM = 3000;
		}
		GPIO_SetBits(GPIOF,GPIO_Pin_13);
		GPIO_ResetBits(GPIOF,GPIO_Pin_12);
		TIM_SetCompare2(TIM3,600+PWM);
	}
	else if(PWM < 0)
	{
		if(PWM < -3000)
		{
			PWM = -3000;
		}
		GPIO_ResetBits(GPIOF,GPIO_Pin_13);
		GPIO_SetBits(GPIOF,GPIO_Pin_12);
		TIM_SetCompare2(TIM3,600-PWM);
	}
	else if(PWM == 0)
	{
		GPIO_ResetBits(GPIOF,GPIO_Pin_13);
		GPIO_ResetBits(GPIOF,GPIO_Pin_12);
		TIM_SetCompare2(TIM3,0);
	}
}

void B1(int PWM)
{
	if(PWM > 0)
	{
		if(PWM > 3000)
		{
			PWM = 3000;
		}
		GPIO_SetBits(GPIOG,GPIO_Pin_2);
		GPIO_ResetBits(GPIOG,GPIO_Pin_3);
		TIM_SetCompare3(TIM3,600+PWM);
	}
	else if(PWM < 0)
	{
		if(PWM < -3000)
		{
			PWM = -3000;
		}
		GPIO_ResetBits(GPIOG,GPIO_Pin_2);
		GPIO_SetBits(GPIOG,GPIO_Pin_3);
		TIM_SetCompare3(TIM3,600-PWM);
	}
	else if(PWM == 0)
	{
		GPIO_ResetBits(GPIOG,GPIO_Pin_2);
		GPIO_ResetBits(GPIOG,GPIO_Pin_3);
		TIM_SetCompare3(TIM3,0);
	}
}

void B2(int PWM)
{
	if(PWM > 0)
	{
		if(PWM > 3000)
		{
			PWM = 3000;
		}
		GPIO_SetBits(GPIOG,GPIO_Pin_8);
		GPIO_ResetBits(GPIOG,GPIO_Pin_6);
		TIM_SetCompare1(TIM3,600+PWM);
	}
	else if(PWM < 0)
	{
		if(PWM < -3000)
		{
			PWM = -3000;
		}
		GPIO_ResetBits(GPIOG,GPIO_Pin_8);
		GPIO_SetBits(GPIOG,GPIO_Pin_6);
		TIM_SetCompare1(TIM3,600-PWM);
	}
	else if(PWM == 0)
	{
		GPIO_ResetBits(GPIOG,GPIO_Pin_8);
		GPIO_ResetBits(GPIOG,GPIO_Pin_6);
		TIM_SetCompare1(TIM3,0);
	}
}

