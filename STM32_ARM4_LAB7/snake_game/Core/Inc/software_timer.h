/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "tim.h"
#include "led_7seg.h"
#include "touch.h"

extern uint16_t flag_timer2;
extern uint16_t flag_timer3;
extern uint16_t flag_timer4;
extern uint16_t flag_timer5;
extern uint16_t flag_timer6;
extern uint16_t flag_timer7;

void timer_init();
void setTimer2(uint16_t duration);
void setTimer3(uint16_t duration);
void setTimer4(uint16_t duration);
void setTimer5(uint16_t duration);
void setTimer6(uint16_t duration);
void setTimer7(uint16_t duration);
void timer_EnableDelayUs();
void delay_us (uint16_t us);

#endif /* INC_SOFTWARE_TIMER_H_ */
