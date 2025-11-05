#include "exti.h"


void EXTIX_Init(void)
{
   	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);//使能PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成浮空输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成浮空输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成浮空输入
 	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成浮空输入
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发
  	EXTI_Init(&EXTI_InitStructure);
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource5);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource11);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
  	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource13);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  	EXTI_Init(&EXTI_InitStructure);
	
	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //使能外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03; //抢占优先级3
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00; //响应优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	EXTI->IMR &= ~(EXTI_Line0);
	EXTI->IMR &= ~(EXTI_Line1);
	EXTI->IMR &= ~(EXTI_Line2);
	EXTI->IMR &= ~(EXTI_Line3);
	EXTI->IMR &= ~(EXTI_Line4);
	EXTI->IMR &= ~(EXTI_Line5);
	EXTI->IMR &= ~(EXTI_Line11);
	EXTI->IMR &= ~(EXTI_Line13);
}


void EXTI0_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1) == 1)
	{
		na2++;
	}
	else
	{
		na2--;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0) == 0)
	{
		na2++;
	}
	else
	{
		na2--;
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3) == 0)
	{
		na1++;
	}
	else
	{
		na1--;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2) == 1)
	{
		na1++;
	}
	else
	{
		na1--;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5) == 1)
	{
		nb2++;
	}
	else
	{
		nb2--;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI9_5_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4) == 0)
	{
		nb2++;
	}
	else
	{
		nb2--;
	}
	EXTI_ClearITPendingBit(EXTI_Line5);
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line11)!=RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13) == 0)
		{
			nb1++;
		}
		else
		{
			nb1--;
		}
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	else if(EXTI_GetITStatus(EXTI_Line13)!=RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11) == 1)
		{
			nb1++;
		}
		else
		{
			nb1--;
		}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
}

