#include "sys.h"
#include "usart.h"


//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
_sys_exit(int x)
{
	x = x;
}

//重定义fputc函数
int fputc(int ch, FILE *f)
{
	while((USART2->SR&0X40)==0); //循环发送,直到发送完毕
    USART2->DR = (u8) ch;
	return ch;
}
#endif


#if EN_USART2_RX   //如果使能了接收

void uart_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //使能USART2
	
	//USART2_RX	  GPIOA.3初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化GPIOA.3
	
	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //响应优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound; //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx;	//接收模式
	
	USART_Init(USART2, &USART_InitStructure);      //初始化串口2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //开启串口接受中断
	USART_Cmd(USART2, ENABLE);                     //使能串口2
}

void USART2_IRQHandler(void) //串口2中断服务程序
{
	u8 data;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		data = USART_ReceiveData(USART2); //读取接收到的数据
		
		if(data == 255)
		{
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
		else if(data == 192)
		{
			k = 0;
			speed_z = 500;
		}
		else if(data == 64)
		{
			k = 0;
			speed_z = -500;
		}
		else if((data&0x80) == 0x80)
		{
			if((data&0x40) == 0)
			{
				speed_y = 30*((int)(data&0x3F));
			}
			else
			{
				speed_y = -30*((int)(data&0x3F));
			}
		}
		else if((data&0x80) == 0)
		{
			if((data&0x40) == 0)
			{
				speed_x = 30*((int)(data&0x3F));
			}
			else
			{
				speed_x = -30*((int)(data&0x3F));
			}
		}
	}
}

#endif

