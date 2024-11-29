/*
 * fsm.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */


#include "fsm.h"

int status = INIT;
int ID = 0;
int mode = NORMAL;
int speed = 1000;
int check_sent;
int count = 0;
char sec = '/';
//uint8_t count_adc = 0;
int wall = 0;
int walls = 0;
int countdown = 180;
int timer = 0;
int buzzer_flag = BUZZER_OFF;
int buzzer_check = 0;
int colon = 0;
int send_flag = 0;

struct player *leaderboard = NULL;

void fsm_mode(){
	switch(mode){
	case NORMAL:
		wall = 0;
		walls = 0;
		break;
	case WALL:
		wall = 1;
		walls = 0;
		spawn_wall();
		break;
	case WALLS:
		wall = 1;
		walls = 1;
		spawn_wall();
		break;
	case TIMER:
		wall = 0;
		walls = 0;
		countdown = 180;
		break;
	}
}

void fsm_buzzer(){// gui canh bao do am > 70% loa bao hieu moi 1 giay, tan so 0.5Hz
	switch (buzzer_flag) {
		case BUZZER_OFF:
			if(flag_timer7 == 1){
				uart_EspSendString("Humidity is higher than 70%\n/");
				setTimer7(1000);
				buzzer_flag = BUZZER_ON;
			}
			buzzer_SetVolume(0);
			break;
		case BUZZER_ON:
			if(flag_timer7 == 1){
				setTimer7(1000);
				buzzer_flag = BUZZER_OFF;
			}
			buzzer_SetVolume(50);
			break;
		default:
			break;
	}
}

void fsm_send_buzzer(){
	switch (buzzer_check) {
		case 0:
			buzzer_SetVolume(0);
			break;
		case 1:
			fsm_buzzer();
			break;
		default:
			break;
	}
}

void enter_ID(){//nhap id nguoi choi
	if(button_count[0] == 1)
		ID = ID*10+1;
	if(button_count[1] == 1)
		ID = ID*10+2;
	if(button_count[2] == 1)
		ID = ID*10+3;
	if(button_count[4] == 1)
		ID = ID*10+4;
	if(button_count[5] == 1)
		ID = ID*10+5;
	if(button_count[6] == 1)
		ID = ID*10+6;
	if(button_count[8] == 1)
		ID = ID*10+7;
	if(button_count[9] == 1)
		ID = ID*10+8;
	if(button_count[10] == 1)
		ID = ID*10+9;
	if(button_count[13] == 1)
		ID = ID*10;
	if(ID > 9999)
		ID = ID % 10;
}

void change_mode(){// doi che do choi
	if(button_count[12] == 1){
		lcd_Clear(BLACK);
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
		status = INIT;
		return;
	}
	lcd_ShowStr(0, 10, "1. NORMAL", WHITE, BLACK, 16, 0);
	lcd_ShowStr(0, 30, "2. WALL", WHITE, BLACK, 16, 0);
	lcd_ShowStr(0, 50, "3. WALLS", WHITE, BLACK, 16, 0);
	lcd_ShowStr(0, 70, "4. TIMER", WHITE, BLACK, 16, 0);
	lcd_ShowStr(0, 90, "E. EXIT", WHITE, BLACK, 16, 0);

	if(button_count[0] == 1){
		mode = NORMAL;
		lcd_Clear(BLACK);
		status = INIT;
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
	}
	if(button_count[1] == 1){
		mode = WALL;
		lcd_Clear(BLACK);
		status = INIT;
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
	}
	if(button_count[2] == 1){
		mode = WALLS;
		lcd_Clear(BLACK);
		status = INIT;
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
	}
	if(button_count[4] == 1){
		mode = TIMER;
		lcd_Clear(BLACK);
		status = INIT;
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
	}
}

void change_speed(){// doi toc do ran
	if(button_count[12] == 1){
		lcd_Clear(BLACK);
		status = INIT;
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
		return;
	}
	lcd_ShowStr(0, 10, "1. EASY", WHITE, BLACK, 16, 0);
	lcd_ShowStr(0, 30, "2. MEDIUM", WHITE, BLACK, 16, 0);
	lcd_ShowStr(0, 50, "3. HARD", WHITE, BLACK, 16, 0);
	lcd_ShowStr(0, 70, "E. EXIT", WHITE, BLACK, 16, 0);

	if(button_count[0] == 1){
		speed = 1000;
		lcd_Clear(BLACK);
		status = INIT;
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
	}
	if(button_count[1] == 1){
		speed = 500;
		lcd_Clear(BLACK);
		status = INIT;
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
	}
	if(button_count[2] == 1){
		speed = 100;
		lcd_Clear(BLACK);
		status = INIT;
		lcd_Fill(50, 200, 190, 300, GREEN);
		lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
	}
}

void displayLeaderBoard(struct player *head){
	struct player *temp = head;
	int count_leaderboard = 1;
//	uart_EspSendString("Leaderboard :\n");
//	while(temp != NULL){
//		if(count_leaderboard < 7){
//		char res[100];
//		if(temp->player_mode == NORMAL)
//			sprintf(res, "#%d ID: %d, score: %d, mode : NORMAL\n", count_leaderboard, temp->player_ID, temp->player_score);
//		else if(temp->player_mode == WALL)
//			sprintf(res, "#%d ID: %d, score: %d, mode : WALL\n", count_leaderboard, temp->player_ID, temp->player_score);
//		else if(temp->player_mode == WALLS)
//			sprintf(res, "#%d ID: %d, score: %d, mode : WALLS\n", count_leaderboard, temp->player_ID, temp->player_score);
//		else
//			sprintf(res, "#%d ID: %d, score: %d, mode : TIMER\n", count_leaderboard, temp->player_ID, temp->player_score);
//		uart_EspSendString(res);
//		count_leaderboard++;
//		temp = temp -> next;
//		}else
//			break;
//	}
//	uart_EspSendString("/");
//
//	temp = head;
//	count_leaderboard = 1;
	lcd_ShowStr(15, 10, "ID", WHITE, BLACK, 24, 0);
	lcd_ShowStr(80, 10, "SCORE", WHITE, BLACK, 24, 0);
	lcd_ShowStr(170, 10, "MODE", WHITE, BLACK, 24, 0);
	while(temp != NULL && 50+(count_leaderboard-1)*20 < 300){
		lcd_ShowIntNum(15, 50+(count_leaderboard-1)*20, temp->player_ID, 4, WHITE, BLACK, 16);
		lcd_ShowIntNum(83, 50+(count_leaderboard-1)*20, temp->player_score, 4, WHITE, BLACK, 16);
		if(temp->player_mode == NORMAL)
			lcd_ShowStr(170, 50+(count_leaderboard-1)*20, "NORMAL", WHITE, BLACK, 16, 0);
		else if(temp->player_mode == WALL)
			lcd_ShowStr(170, 50+(count_leaderboard-1)*20, "WALL", WHITE, BLACK, 16, 0);
		else if(temp->player_mode == WALLS)
			lcd_ShowStr(170, 50+(count_leaderboard-1)*20, "WALLS", WHITE, BLACK, 16, 0);
		else
			lcd_ShowStr(170, 50+(count_leaderboard-1)*20, "TIMER", WHITE, BLACK, 16, 0);
		temp=temp->next;
		count_leaderboard++;
	}
}

void fsm_machine(){
	switch (status) {
	case DISPLAY_LEADERBOARD:
//		displayLeaderBoard(leaderboard);
		if(button_count[12] == 1){
			lcd_Clear(BLACK);
			lcd_Fill(50, 200, 190, 300, GREEN);
			lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
			status = INIT;
		}
		break;
	case CHANGE_MODE:
		change_mode();
		break;
	case CHANGE_SPEED:
		change_speed();
		break;
	case INIT:
		screen_init();
		enter_ID();
		//test_Adc();

		if(button_count[14] == 1){
			lcd_Clear(BLACK);
			status = CHANGE_MODE;
		}
		if(button_count[12] == 1){
			lcd_Clear(BLACK);
			status = CHANGE_SPEED;
		}
		if(button_count[15] == 1){
			lcd_Clear(BLACK);
			displayLeaderBoard(leaderboard);
			status = DISPLAY_LEADERBOARD;
		}

		if(isButtonStart()){
			status = PLAY;
			char res[100];
			sprintf(res, "%d is playing %c", ID, sec);//gui len Wifi
			uart_EspSendString(res);
			count = 0;
			lcd_Clear(BLACK);
			re_init();
			screen_play();
			fsm_mode();
			setTimer4(1000);
		}
		break;
	case PLAY:
		if(flag_timer4 == 1){
			setTimer4(1000);
			if(colon == 0){
				led7_SetColon(1);
				colon = 1;
			}else{
				led7_SetColon(0);
				colon = 0;
			}
			count++;
			timer = count;
			if(wall == 1){
				if(count%5 == 0){
					if(walls == 0){
						delete_wall();
					}
					spawn_wall();
				}
			}
			if(mode == TIMER){
				countdown--;
				timer = countdown;
			}
			led7_SetDigit((timer%60)%10, 3, 0);
			led7_SetDigit((timer%60)/10, 2, 0);
			led7_SetDigit((timer/60)%10, 1, 0);
			led7_SetDigit((timer/60)/10, 0, 0);
		}
		if(isButtonUp()){
			sw_up = 0;
			sw_down = 1;
			sw_left = 1;
			sw_right = 1;
			//flag_timer3 = 1;
		}
		if(isButtonDown()){
			sw_up = 1;
			sw_down = 0;
			sw_left = 1;
			sw_right = 1;
			//flag_timer3 = 1;
		}
		if(isButtonLeft()){
			sw_up = 1;
			sw_down = 1;
			sw_left = 0;
			sw_right = 1;
			//flag_timer3 = 1;
		}
		if(isButtonRight()){
			sw_up = 1;
			sw_down = 1;
			sw_left = 1;
			sw_right = 0;
			//flag_timer3 = 1;
		}
		wait_check();
		update_grid();
		if(flag_timer3 == 1){
			//wait_check();
			setTimer3(speed);
			move_snake();
			//check_food();
			//check_collision();
			screen_score();
			update_grid();
		}
		if(lose == 1){
			status = GAME_OVER;
			addPlayer(&leaderboard, ID, score, mode);
			send_flag = 1;
			char res[100];
			sprintf(res, "%d was game over\nScore : %d\nTime : %d:%d %c", ID, score, count/60, count%60, sec);//STM32 -> wifi
			uart_EspSendString(res);
			send_flag =0;
			lcd_Clear(BLACK);
			lcd_Fill(50, 250, 190, 300, GREEN);
			lcd_ShowStr(80,260,"RESTART",BLACK,BLACK,24,1);
			lose = 0;
		}
		break;
	case GAME_OVER:
		enter_ID();
		screen_game_over();
		if(button_count[14] == 1){
			lcd_Clear(BLACK);
			status = CHANGE_MODE;
		}

		if(button_count[12] == 1){
			lcd_Clear(BLACK);
			status = CHANGE_SPEED;
		}

		if(button_count[15] == 1){
			lcd_Clear(BLACK);
			displayLeaderBoard(leaderboard);
			status = DISPLAY_LEADERBOARD;
		}

		if(isButtonRestart()){
//			status = INIT;
//			lcd_Clear(BLACK);
//			re_init();
			char res[100];
			sprintf(res, "%d is playing %c", ID, sec);//STM32->Wifi
			uart_EspSendString(res);
			count = 0;
			status = PLAY;
			lcd_Clear(BLACK);
			re_init();
			screen_play();
			fsm_mode();
		}
		break;
	default:
		break;
	}
}


