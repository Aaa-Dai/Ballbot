#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "sys.h"

#define EN_USART2_RX 1 //使能（1）/禁止（0）串口2接收

void uart_init(u32 bound);

extern int speed_y,speed_x,speed_z,qw_jz,jz,k;

#endif

