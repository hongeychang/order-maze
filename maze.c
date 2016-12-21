#include<stdio.h>
#include<stdlib.h>

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


int map[MAP_HEIGHT][MAP_WIDTH]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {4,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1},
    {1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1},
    {1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,1,0,1},
    {1,0,1,0,1,1 ,1,1,0,0,1,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,5},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

void draw_map(void){
	int i,j;
	for(i=0; i<MAP_HEIGHT; i++){
		for(j=0; j<MAP_WIDTH; j++){
			switch(map[i][j]){
				case 0: printf("  "); break;//빈공간
				case 1: printf("■ "); break;//벽
				case 4: printf("  "); break;//캐릭터?
				case 5: printf("→ "); break;//출구
			}
		}
		printf("\n");
	}
}

 void move_character(int dire, int *cp_x, int *cp_y){
	     switch(dire){
	         case UP:
	             if( map[*cp_y-1][*cp_x] != 1){
	                 map[*cp_y-1][*cp_x] = 4;
	                 map[*cp_y][*cp_x] = 0;
	                 *cp_y -= 1;
	             }
	             return;
	         case DOWN:
	             if( map[*cp_y+1][*cp_x] != 1){
	                map[*cp_y+1][*cp_x] = 4;
	                 map[*cp_y][*cp_x] = 0;
	                 *cp_y += 1;
	             }
	             return;
	         case RIGHT:
	             if( map[*cp_y][*cp_x+1] !=1){
	                 map[*cp_y][*cp_x+1] = 4;
	                map[*cp_y][*cp_x] = 0;
	                 *cp_x += 1;
	             }
	             return;
	         case LEFT:
	            if( map[*cp_y][*cp_x-1] !=1){
	               map[*cp_y][*cp_x-1] = 4;
	                map[*cp_y][*cp_x] = 0;
	                 *cp_x -= 1;
	          }
	           return;
	     }
	 }
	
	 void clear(){
	    system("clear");
	 }
	
	 void find_character(int *cp_x, int *cp_y){
	   int i,j;
	    for(i=0; i<MAP_HEIGHT; i++){
	        for(j=0; j<MAP_WIDTH; j++){
	             if( map[j][i] == 4 ){
								                  *cp_x = i;
									                   *cp_y = j;
									                    return;
									                 }
								          }
						         }
					    }
					   
					   
					   
					    int main(){
						        int cha_x, cha_y;
						        find_character( &cha_x, &cha_y);
						        char key;
						        clear();
						        draw_map();
						        while( (key = getch()) != '\n' ){
							            clear();
							            move_character(key, &cha_x, &cha_y);
							            draw_map();
							        }
