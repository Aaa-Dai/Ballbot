#include "paj7620u2.h"
#include "paj7620u2_cfg.h"
#include "delay.h"


//选择PAJ7620U2 BANK区域
void paj7620u2_selectBank(bank_e bank)
{
	switch(bank)
	{
		case BANK0: GS_Write_Byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);break;//BANK0寄存器区域
		case BANK1: GS_Write_Byte(PAJ_REGITER_BANK_SEL,PAJ_BANK1);break;//BANK1寄存器区域
	}
			
}

//PAJ7620U2唤醒
u8 paj7620u2_wakeup(void)
{ 
	u8 data=0x0a;
	GS_WakeUp();//唤醒PAJ7620U2
	delay_ms(5);//唤醒时间>400us
	GS_WakeUp();//唤醒PAJ7620U2
	delay_ms(5);//唤醒时间>400us
	paj7620u2_selectBank(BANK0);//进入BANK0寄存器区域
	data = GS_Read_Byte(0x00);//读取状态
	if(data!=0x20) return 0; //唤醒失败
	
	return 1;
}

//PAJ7620U2初始化
//返回值：0:失败 1:成功
u8 paj7620u2_init(void)
{
	u8 i;
	u8 status;
	
	GS_i2c_init();//IIC初始化
    status = paj7620u2_wakeup();//唤醒PAJ7620U2
	if(!status) return 0;
	paj7620u2_selectBank(BANK0);//进入BANK0寄存器区域
	for(i=0;i<INIT_SIZE;i++)
	{
		GS_Write_Byte(init_Array[i][0],init_Array[i][1]);//初始化PAJ7620U2
	}
    paj7620u2_selectBank(BANK0);//切换回BANK0寄存器区域
	
	return 1;
}

void paj7620u2_ready(void)
{
	u8 i;
	
	paj7620u2_selectBank(BANK0); //进入BANK0寄存器区域
	for(i=0;i<GESTURE_SIZE;i++)
	{
		GS_Write_Byte(gesture_arry[i][0],gesture_arry[i][1]); //手势识别模式初始化
	}
	paj7620u2_selectBank(BANK0); //切换回BANK0寄存器区域
}

void gesture_recognition(void)
{
	u8 status;
	u8 data[2]={0x00};
	u16 gesture_data;
	
	status = GS_Read_nByte(PAJ_GET_INT_FLAG1,2,&data[0]); //读取手势状态	
	if(!status)
	{   
		gesture_data = (u16)data[1]<<8 | data[0];
		if(gesture_data) 
		{
			switch(gesture_data)
			{
				case GES_UP:
							if(speed_x < 0)
							{
								speed_x = 0;
							}
							else
							{
								speed_x = 1800;
							}
							break; //向右
				case GES_DOWM:
							if(speed_x > 0)
							{
								speed_x = 0;
							}
							else
							{
								speed_x = -1800;
							}
							break; //向左
				case GES_LEFT:
							if(speed_y < 0)
							{
								speed_y = 0;
							}
							else
							{
								speed_y = 1800;
							}
							break; //向上
				case GES_RIGHT:
							if(speed_y > 0)
							{
								speed_y = 0;
							}
							else
							{
								speed_y = -1800;
							}
							break; //向下
				case GES_FORWARD:
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
							break; //向前
				case GES_BACKWARD:
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
							break; //向后
				case GES_CLOCKWISE:
							k = 0;
							speed_z = -500;
							break; //顺时针
				case GES_COUNT_CLOCKWISE:
							k = 0;
							speed_z = 500;
							break; //逆时针
				case GES_WAVE:
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
							break; //挥动
			}							
		}
	}
}

