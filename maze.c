#include<stdio.h>
#include<stdlib.h>
#include<termio.h>

#define MAP_HEIGHT	10
#define	MAP_WIDTH	20
#define EXIT 27

enum{UP = 65, DOWN, RIGHT, LEFT};

int getch(void){
	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}
int end, score;

int map[5][MAP_HEIGHT][MAP_WIDTH]={
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,4,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1},
    {1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1},
    {1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,1,0,1},
    {1,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,5},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
	{//스테이지1 끝
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,4,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1},
	{1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1},
	{1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,1,0,1},
	{1,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,5},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
	{//스테이지2 끝
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,4,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1},
	{1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1},
	{1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,1,0,1},
	{1,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,5},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
	{//스테이지3 끝
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,4,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1},
	{1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1},
	{1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,1,0,1},
	{1,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,5},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
	{//스테이지4 끝
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,4,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1},
	{1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1},
	{1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,1,0,1},
	{1,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,5},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}
};//스테이지5 끝

void draw_map(int now){
	int i,j;
	printf("stage : %d		score : %d\n",now+1, score);
	for(i=0; i<MAP_HEIGHT; i++){
		for(j=0; j<MAP_WIDTH; j++){
			switch(map[now][i][j]){
				case 0: printf("  "); break;//빈공간
				case 1: printf("■ "); break;//벽
				case 2: printf("○ "); break;//점수
				case 4: printf("옷"); break;//캐릭터?
				case 5: printf("→ "); break;//출구
			}
		}
		printf("\n");
	}
}

void move_character(int dire, int *cp_x, int *cp_y, int now){
	switch(dire){
		case UP:
			if( map[now][*cp_y-1][*cp_x] == 5){
				end=1;		
			}
			if( map[now][*cp_y-1][*cp_x] == 2){
				score+=1;
			}
			if( map[now][*cp_y-1][*cp_x] != 1){
				map[now][*cp_y-1][*cp_x] = 4;
	            map[now][*cp_y][*cp_x] = 0;
	            *cp_y -= 1;
			}
	        return;
		case DOWN:
			if( map[now][*cp_y+1][*cp_x] == 5){
				end=1;
			}
			if( map[now][*cp_y+1][*cp_x] == 2){
				score+=1;
			}
			if( map[now][*cp_y+1][*cp_x] != 1){
				map[now][*cp_y+1][*cp_x] = 4;
				map[now][*cp_y][*cp_x] = 0;
	            *cp_y += 1;
	        }
			return;
		case RIGHT:
			if( map[now][*cp_y][*cp_x+1] == 5){
				end=1;
			}
			if( map[now][*cp_y][*cp_x+1] == 2){
				score+=1;
			}
			if( map[now][*cp_y][*cp_x+1] !=1){
				map[now][*cp_y][*cp_x+1] = 4;
				map[now][*cp_y][*cp_x] = 0;
	            *cp_x += 1;
	        }
			return;
		case LEFT:
			if( map[now][*cp_y][*cp_x-1] ==5){
				end=1;
			}
			if( map[now][*cp_y][*cp_x-1] ==2){
				score+=1;
			}
			if( map[now][*cp_y][*cp_x-1] !=1){
				map[now][*cp_y][*cp_x-1] = 4;
	            map[now][*cp_y][*cp_x] = 0;
	            *cp_x -= 1;
			}
			return;
	}
}

void clear(){
	system("clear");
}

void find_character(int *cp_x, int *cp_y, int now){
	int i,j;
	for(i=0; i<MAP_HEIGHT; i++){
		for(j=0; j<MAP_WIDTH; j++){
	    	if( map[now][j][i] == 4 ){
				*cp_x = i;
				*cp_y = j;
				return;
			}
		}
	}
}
					   			   
int main(){
	int cha_x, cha_y;
	int now_map=0;
	end = 0;
	score=0;
	find_character( &cha_x, &cha_y, now_map);
	char key;
	clear();
	draw_map(now_map);
	while( (key = getch()) != '\n' ){
		clear();
		move_character(key, &cha_x, &cha_y, now_map);
		if(end==1){
			end=0;
			now_map+=1;
			if(now_map == 5){
				printf("clear\nclear\nclear\n");
				exit(0);
			}
			find_character( &cha_x, &cha_y, now_map);
		}
		draw_map(now_map);
	}
}
