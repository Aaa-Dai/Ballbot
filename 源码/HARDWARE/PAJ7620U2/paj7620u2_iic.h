#ifndef __PAJ7620U2_IIC_H
#define __PAJ7620U2_IIC_H

#include "sys.h"

#define GS_SDA_IN()  {GPIOF->CRL&=0XFF0FFFFF;GPIOF->CRL|=8<<20;}
#define GS_SDA_OUT() {GPIOF->CRL&=0XFF0FFFFF;GPIOF->CRL|=3<<20;}

//IO²Ù×÷º¯Êý	
#define GS_IIC_SCL    PFout(7)		//SCL
#define GS_IIC_SDA    PFout(5) 		//SDA
#define GS_READ_SDA   PFin(5) 		//ÊäÈëSDA

u8 GS_Write_Byte(u8 REG_Address,u8 REG_data);
u8 GS_Read_Byte(u8 REG_Address);
u8 GS_Read_nByte(u8 REG_Address,u16 len,u8 *buf);
void GS_i2c_init(void);
void GS_WakeUp(void);

#endif

