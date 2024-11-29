/*
 * touch_screen.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */

#include "touch_screen.h"

uint8_t isButtonStart(){
	if(!touch_IsTouched()) return 0;
	return touch_GetX() > 50 && touch_GetX() < 190 && touch_GetY() > 200 && touch_GetY() < 300;
}
uint8_t isButtonUp(){
	if(!touch_IsTouched()) return 0;
	return touch_GetX() > 90 && touch_GetX() < 150 && touch_GetY() > 210 && touch_GetY() < 250;
}
uint8_t isButtonDown(){
	if(!touch_IsTouched()) return 0;
	return touch_GetX() > 90 && touch_GetX() < 150 && touch_GetY() > 260 && touch_GetY() < 300;
}
uint8_t isButtonLeft(){
	if(!touch_IsTouched()) return 0;
	return touch_GetX() > 20 && touch_GetX() < 80 && touch_GetY() > 260 && touch_GetY() < 300;
}
uint8_t isButtonRight(){
	if(!touch_IsTouched()) return 0;
	return touch_GetX() > 160 && touch_GetX() < 220 && touch_GetY() > 260 && touch_GetY() < 300;
}
uint8_t isButtonRestart(){
	if(!touch_IsTouched()) return 0;
	return touch_GetX() > 50 && touch_GetX() < 190 && touch_GetY() > 250 && touch_GetY() < 350;
}

