#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM2_Int_Init(u16 arr,u16 psc);

extern int na1,na2,nb1,nb2,vx,vy,qw_vx,qw_vy,e_vx,e_vy,ei_vx,ei_vy,speed_x,speed_y;

#endif

