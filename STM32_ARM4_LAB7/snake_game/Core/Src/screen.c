/*
 * screen.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */

#include "screen.h"

void screen_init(){
	lcd_ShowStr(60,10,"SNAKE GAME",WHITE,WHITE,24,1);
	lcd_ShowStr(40,60,"Player ID:",WHITE,BLACK,16,0);
	lcd_ShowIntNum(120, 60, ID, 4, WHITE, BLACK, 16);
//	lcd_Fill(50, 200, 190, 300, GREEN);
	lcd_ShowStr(40, 90, "Mode (B):", WHITE, BLACK, 16, 0);
	if(mode == NORMAL)
		lcd_ShowStr(120, 90, "NORMAL", WHITE, BLACK, 16, 0);
	if(mode == WALL)
		lcd_ShowStr(120, 90, "WALL", WHITE, BLACK, 16, 0);
	if(mode == WALLS)
		lcd_ShowStr(120, 90, "WALLS", WHITE, BLACK, 16, 0);
	if(mode == TIMER)
		lcd_ShowStr(120, 90, "TIMER", WHITE, BLACK, 16, 0);
	lcd_ShowStr(40, 120, "Speed (E):", WHITE, BLACK, 16, 0);
	if(speed == 1000)
		lcd_ShowStr(120, 120, "EASY", WHITE, BLACK, 16, 0);
	if(speed == 500)
		lcd_ShowStr(120, 120, "MEDIUM", WHITE, BLACK, 16, 0);
	if(speed == 100)
		lcd_ShowStr(120, 120, "HARD", WHITE, BLACK, 16, 0);

	lcd_ShowStr(40,150,"Leaderboard (<)",WHITE,BLACK,16,0);
//	lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
}

void screen_play(){
	lcd_Fill(0, 0, 240, 200, WHITE);
	lcd_Fill(90, 210, 150, 250, BLUE);//UP
	lcd_Fill(90, 260, 150, 300, BLUE);//DOWN
	lcd_Fill(20, 260, 80, 300, BLUE);//LEFT
	lcd_Fill(160, 260, 220, 300, BLUE);//RIGHT
}

void screen_score(){
	lcd_ShowStr(0, 205, "Score: ", WHITE, WHITE, 24, 1);
	lcd_ShowIntNum(0, 230, score, 4, WHITE, BLACK, 24);
}

void screen_game_over(){
	lcd_ShowStr(70,10,"GAME OVER",WHITE,WHITE,24,1);
	lcd_ShowStr(80, 220, "Score: ", WHITE, WHITE, 24, 1);
	lcd_ShowStr(40,60,"Player ID:",WHITE,BLACK,16,0);
	lcd_ShowIntNum(120, 60, ID, 4, WHITE, BLACK, 16);
	lcd_ShowStr(40, 90, "Mode (B):", WHITE, BLACK, 16, 0);
	if(mode == NORMAL)
		lcd_ShowStr(120, 90, "NORMAL", WHITE, BLACK, 16, 0);
	if(mode == WALL)
		lcd_ShowStr(120, 90, "WALL", WHITE, BLACK, 16, 0);
	if(mode == WALLS)
		lcd_ShowStr(120, 90, "WALLS", WHITE, BLACK, 16, 0);
	if(mode == TIMER)
		lcd_ShowStr(120, 90, "TIMER", WHITE, BLACK, 16, 0);
	lcd_ShowStr(40, 120, "Speed (E):", WHITE, BLACK, 16, 0);
	if(speed == 1000)
		lcd_ShowStr(120, 120, "EASY", WHITE, BLACK, 16, 0);
	if(speed == 500)
		lcd_ShowStr(120, 120, "MEDIUM", WHITE, BLACK, 16, 0);
	if(speed == 100)
		lcd_ShowStr(120, 120, "HARD", WHITE, BLACK, 16, 0);
	lcd_ShowStr(40, 150, "Leaderboard (<)", WHITE, BLACK, 16, 0);
	lcd_ShowStr(40, 180, "Time:", WHITE, BLACK, 16, 0);
	lcd_ShowIntNum(90, 180, count/60, 2, WHITE, BLACK, 16);
	lcd_ShowStr(110, 180, ":", WHITE, BLACK, 16, 0);
	lcd_ShowIntNum(120, 180, count%60, 2, WHITE, BLACK, 16);
	lcd_ShowIntNum(150, 220, score, 2, WHITE, BLACK, 24);
//	lcd_Fill(50, 250, 190, 300, GREEN);
//	lcd_ShowStr(80,260,"RESTART",BLACK,BLACK,24,1);
}

