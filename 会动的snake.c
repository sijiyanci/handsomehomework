#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

void snakemove(int dy,int dx);								//移动 
void put_money(void);									//正确产生食物 
void output(void);									//更新界面 
void gameover(void);									//结束游戏 


char map[12][12]=
{
	"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"			
};
int snakex[SNAKE_MAX_LENGTH]={1,2,3,4,5};
int snakey[SNAKE_MAX_LENGTH]={1,1,1,1,1};
int snakelength=5;


int main(void)
{
	output();
	printf("press w,a,s,d for up,left,down,right "
	"and g for exit.\n");
	int ch,countobs=0,i,flagobs=0;
	while((ch=getchar())!='g')
	{
				
		switch(ch)
		{
			case 'a':snakemove(0,-1);	//left
				break;
			case 'd':snakemove(0,1);	//rigth
				break;
			case 'w':snakemove(-1,0);	//up
				break;
			case 's':snakemove(1,0);	//down
				break;
			default:break;
		}
 
		output();							 	//更新界面
		
		while((ch=getchar())!='\n')
			continue;
	}
	gameover();
	
}

void snakemove(int dy,int dx)								//移动
{
	int i;													 	
	map[snakey[0]][snakex[0]]=BLANK_CELL;
	for(i=0;i<snakelength-1;i++)
	{
		snakex[i]=snakex[i+1];
		snakey[i]=snakey[i+1];
	}
	snakex[snakelength-1]=snakex[snakelength-1]+dx;
	snakey[snakelength-1]=snakey[snakelength-1]+dy;
	
	for(i=0;i<snakelength-1;i++)
		map[snakey[i]][snakex[i]]=SNAKE_BODY;
	map[snakey[snakelength-1]][snakex[snakelength-1]]=SNAKE_HEAD;
	
}

void output(void)										//更新界面 
{
	int i,j;
	for(i=0;i<12;i++)
	{
		for(j=0;j<12;j++)
			putchar(map[i][j]);
		printf("\n");
	}	
}

void gameover(void)
{
	printf("Game Over!!!\n");
}


