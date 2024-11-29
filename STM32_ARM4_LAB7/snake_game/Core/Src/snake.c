/*
 * snake.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */

#include "snake.h"

int size_of_snake=2;
int snake_speed[2]={1,0};
int draw_grid[24][20] = {0};
int snake_pos[2][24] = {0};
int old_poshx = 0;
int old_poshy = 0;
int pos_head[2] = {0};
int sw_up = 1;
int sw_down = 1;
int sw_right = 1;
int sw_left = 1;
uint8_t score = 0;
int lose = 0;

void draw_snake(int x,int y){
	lcd_DrawCircle(x, y, GREEN, 5, 1);
}

void draw_food(int x,int y){
	lcd_DrawCircle(x, y, RED, 5, 1);
}

void draw_head(int x, int y){
	lcd_DrawCircle(x, y, LIGHTGREEN, 5, 1);
}

void draw_wall(int x, int y){
	lcd_DrawCircle(x, y, GRAY, 5, 1);
}

void clear_block(int x,int y){
	lcd_DrawCircle(x, y, WHITE, 5, 1);
}

void update_grid(){
	for(int i=0;i<24;i++){
		for(int j=0;j<20;j++){
			if(draw_grid[i][j]==2){
				draw_snake(i*10+5,j*10+5);
			}
			else if(draw_grid[i][j]==4){
				draw_head(i*10+5,j*10+5);
			}
			else if(draw_grid[i][j]==1){
				draw_food(i*10+5,j*10+5);
			}
			else if(draw_grid[i][j]==3){
				draw_wall(i*10+5,j*10+5);
			}
			else{
				clear_block(i*10+5,j*10+5);
			}
		}
	}
}

void delete_wall(void){
	for(int i=0;i<24;i++){
		for(int j=0;j<20;j++){
			if(draw_grid[i][j]==3){
				draw_grid[i][j]=0;
			}
		}
	}
}

void init_grid(void){
	for(int i=0; i<24;i++){
		for(int j=0;j<20;j++){
			draw_grid[i][j]=0;
		}
	}
}

void move_snake(){
		for(int i=size_of_snake-1;i>=0;i--){
			draw_grid[snake_pos[0][i]][snake_pos[1][i]]=0;
		}
		draw_grid[snake_pos[0][0]][snake_pos[1][0]] = 0;
		old_poshx=snake_pos[0][size_of_snake-1];
		old_poshy=snake_pos[1][size_of_snake-1];
		snake_pos[0][size_of_snake-1]=snake_pos[0][size_of_snake-1]+snake_speed[0];
		snake_pos[1][size_of_snake-1]=snake_pos[1][size_of_snake-1]+snake_speed[1];
		pos_head[0]=snake_pos[0][size_of_snake-1];
		pos_head[1]=snake_pos[1][size_of_snake-1];
		for(int i=size_of_snake-2;i>=0;i--){
			int nx = snake_pos[0][i];
			int ny = snake_pos[1][i];
			snake_pos[0][i]=old_poshx;
			snake_pos[1][i]=old_poshy;
			old_poshx=nx;
			old_poshy=ny;
		}
		for(int i=size_of_snake-2;i>=0;i--){
			draw_grid[snake_pos[0][i]][snake_pos[1][i]]=2;
		}
		check_collision();
		check_food();
		draw_grid[pos_head[0]][pos_head[1]]=4;
}

void re_init(void){
	init_grid();
	draw_grid[0][0]=2;
	draw_grid[1][0]=2;
	snake_pos[0][0]=0;
	snake_pos[1][0]=0;
	snake_pos[0][1]=1;
	snake_pos[1][1]=0;
	size_of_snake=2;
	snake_speed[0]=1;
	snake_speed[1]=0;
	sw_up=1;
	sw_down=1;
	sw_right=1;
	sw_left=1;
	score=0;
	spawn_food();
}

void spawn_food(void){
	int xf=rand_no(23);
	int yf=rand_no(19);
	while(draw_grid[xf][yf]==2){
		xf=rand_no(23);
		yf=rand_no(19);
	}
	draw_grid[xf][yf]=1;
}

void spawn_wall(void){
	int xw=rand_no(23);
	int yw=rand_no(19);
	while(draw_grid[xw][yw]==2 || draw_grid[xw][yw]==1 ||
			((draw_grid[xw+1][yw]==2 || draw_grid[xw+1][yw]==1) && (draw_grid[xw-1][yw]==2 || draw_grid[xw-1][yw]==1)
			&& (draw_grid[xw][yw+1]==2 || draw_grid[xw][yw+1]==1) && (draw_grid[xw][yw-1]==2 || draw_grid[xw][yw-1]==1))){
		xw=rand_no(23);
		yw=rand_no(19);
	}
	draw_grid[xw][yw]=3;
	int d=rand_no(4);
	int flag = 0;
	while(flag == 0){
		d = rand_no(4);
		switch (d){
		case 1:
			if(draw_grid[xw+1][yw]!=2 && draw_grid[xw+1][yw]!=1){
				draw_grid[xw+1][yw]=3;
				flag = 1;
			}
			break;
		case 2:
			if(draw_grid[xw-1][yw]!=2 && draw_grid[xw-1][yw]!=1){
				draw_grid[xw-1][yw]=3;
				flag = 1;
			}
			break;
		case 3:
			if(draw_grid[xw][yw+1]!=2 && draw_grid[xw][yw+1]!=1){
				draw_grid[xw][yw+1]=3;
				flag = 1;
			}
			break;
		case 4:
			if(draw_grid[xw][yw-1]!=2 && draw_grid[xw][yw-1]!=1){
				draw_grid[xw][yw-1]=3;
				flag = 1;
			}
			break;
		default:
			break;
		}
	}
}

int rand_no(int m){
	int num = (rand()%(m+1));
	return num;
}

void check_collision(void){
	if(pos_head[0]>23 || pos_head[0]<0){
		lose = 1;
	}
	if(pos_head[1]>19 || pos_head[1]<0){
		lose = 1;
	}
	if(draw_grid[pos_head[0]][pos_head[1]]==2){
		lose = 1;
	}
	if(draw_grid[pos_head[0]][pos_head[1]]==3){
		lose = 1;
	}
	if(countdown == 0){
		lose = 1;
		countdown = 180;
	}
}

void wait_check(void){
	if(sw_down==0 && snake_speed[1]==0){
		snake_speed[0]=0;
		snake_speed[1]=1;
		sw_down=1;
	}
	if(sw_up==0 && snake_speed[1]==0){
		snake_speed[0]=0;
		snake_speed[1]=-1;
		sw_up=1;
	}
	if(sw_right==0 && snake_speed[0]==0){
		snake_speed[0]=1;
		snake_speed[1]=0;
		sw_right=1;
	}
	if(sw_left==0 && snake_speed[0]==0){
		snake_speed[0]=-1;
		snake_speed[1]=0;
		sw_left=1;
	}
}

//void check_food(void){
//	if(draw_grid[pos_head[0]][pos_head[1]]==1){
//		score++;
//		size_of_snake++;
//		snake_pos[0][size_of_snake-1]=pos_head[0];
//		snake_pos[1][size_of_snake-1]=pos_head[1];
//		spawn_food();
//	}
//}

void check_food(void){
    if(draw_grid[pos_head[0]][pos_head[1]]==1){
        score++;
        size_of_snake++;

        for (int i = size_of_snake - 1; i > 0; i--) {
            snake_pos[0][i] = snake_pos[0][i - 1];
            snake_pos[1][i] = snake_pos[1][i - 1];
        }

        snake_pos[0][0] = pos_head[0];
        snake_pos[1][0] = pos_head[1];

        for (int i = 0; i < size_of_snake; i++) {
            draw_grid[snake_pos[0][i]][snake_pos[1][i]] = 2;
        }

        spawn_food();
    }
}



