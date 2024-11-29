/*
 * screen.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_


#include "lcd.h"
#include "snake.h"
#include "uart.h"


void screen_init();
void screen_play();
void screen_score();
void screen_game_over();

#endif /* INC_SCREEN_H_ */
