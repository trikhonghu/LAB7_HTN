/*
 * fsm.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "snake.h"
#include "screen.h"
#include "touch_screen.h"
#include "software_timer.h"
#include "uart.h"
#include "button.h"
#include "buzzer.h"
#include "leaderboard.h"

#define INIT	0
#define PLAY	1
#define GAME_OVER	2
#define CHANGE_MODE	3
#define CHANGE_SPEED 4
#define DISPLAY_LEADERBOARD 5

#define NORMAL 0
#define WALL 1
#define WALLS 2
#define TIMER 3

#define BUZZER_OFF 0
#define BUZZER_ON  1

extern int send_flag;

extern int status;
extern int mode;
extern int ID;
extern int speed;
extern int count;
extern int countdown;
extern int buzzer_flag;
extern int buzzer_check;
extern char sec;

void fsm_machine();
void fsm_mode();
void isInput();
void test_Adc();
void fsm_buzzer();
void fsm_send_buzzer();

#endif /* INC_FSM_H_ */
