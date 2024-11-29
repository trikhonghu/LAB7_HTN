/*
 * snake.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#include "lcd.h"
#include "software_timer.h"
#include "fsm.h"

extern int draw_grid[24][20];
extern int snake_speed[2];
extern int size_of_snake;
extern int snake_pos[2][24];
extern int old_poshx;
extern int old_poshy;
extern int pos_head[2];
extern int sw_up;
extern int sw_down;
extern int sw_right;
extern int sw_left;
extern uint8_t score;

extern int lose;

void init_grid(void);
void update_grid(void);
void draw_snake(int x,int y);
void draw_food(int x,int y);
void draw_wall(int x, int y);
void delete_wall(void);
void clear_block(int x,int y);
void move_snake(void);
void re_init(void);
void spawn_food(void);
void spawn_wall(void);
int rand_no(int m);
void check_collision(void);
void wait_check(void);
void check_food(void);


#endif /* INC_SNAKE_H_ */
