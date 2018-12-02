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
void put_money(void);										//正确产生食物 
void output(void);											//更新界面 
void gameover(void);										//结束游戏 
int checkmany(void);										//检查是否撞墙或者吃自己 
int checkone(int x,int y);									//检查是否出现在蛇身上（用于检查是否正确产生食物，障碍物） 
void put_obstacles(void);									//正确产生障碍物 

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
int snakex[SNAKE_MAX_LENGTH]={1,2,3,4,5};					//蛇的位置
int snakey[SNAKE_MAX_LENGTH]={1,1,1,1,1};

int snakelength=5;
int money[2]={12,12}; 								//食物的位置

int obstaclex[3]={9,8,7};							//障碍物的位置
int obstacley[3]={9,8,7}; 
int flagmoney=0; 

int main(void)
{
	output();
	printf("press w,a,s,d for up,left,down,right "
	"and g for exit.\n");
	int ch,countobs=0,i,flagobs=0;
	while((ch=getchar())!='g')
	{
		if(!flagmoney)			//正确产生食物 
		{
			put_money();
			flagmoney=1;
		}	
		if(!countobs)			//正确产生障碍物 
		{	
			put_obstacles();
			countobs=3;	
		}				
		switch(ch)				//移动
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
		if(checkmany())							//是否撞上自身或墙壁 
			break;
		for(i=0;i<3;i++)																//是否撞上障碍物 
			if(obstaclex[i]==snakex[snakelength-1]&&obstacley[i]==snakey[snakelength-1])
			{
				flagobs=1;
				break;
			}
		if(flagobs)								//如果撞上障碍物，结束游戏 
			break; 
		output();							 	//更新界面
		countobs--;
		while((ch=getchar())!='\n')
			continue;
	}
	gameover();
	
}

void snakemove(int dy,int dx)
{
	int i;
	if(snakex[snakelength-1]+dx==money[0]&&snakey[snakelength-1]+dy==money[1])			//若吃到食物，则变长 
	{
		snakex[snakelength]=snakex[snakelength-1]+dx;
		snakey[snakelength]=snakey[snakelength-1]+dy;
		
		snakelength++;
		map[snakey[0]][snakex[0]]=SNAKE_BODY;
		flagmoney=0;
	}
	else												//没吃到，则只移动位置 
	{
		map[snakey[0]][snakex[0]]=BLANK_CELL;
		for(i=0;i<snakelength-1;i++)
		{
			snakex[i]=snakex[i+1];
			snakey[i]=snakey[i+1];
		}
		snakex[snakelength-1]=snakex[snakelength-1]+dx;
		snakey[snakelength-1]=snakey[snakelength-1]+dy;
	}
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

int checkmany(void)				//判断是否撞上墙或自身 
{
	int i;
	for(i=0;i<snakelength-1;i++)													//是否撞到自己 
	{
		if((snakex[snakelength-1]==snakex[i])&&(snakey[snakelength-1]==snakey[i]))
			return 1;
	}
	if(snakex[snakelength-1]<1||snakex[snakelength-1]>10||snakey[snakelength-1]<1||snakey[snakelength-1]>10)	//是否撞到墙 
		return 1;
	return 0;
}

void put_money(void)
{
	
	map[money[1]][money[0]]=BLANK_CELL;
	
	do											//如果食物出现在蛇身上，重置 
	{
		money[0]=(money[0]+(unsigned int)time(0)%11)%11;
		money[1]=(money[0]+(unsigned int)time(0)%11)%11;
		money[0]=(money[0]<1)?(money[0]+1):money[0];
		money[1]=(money[1]<1)?(money[1]+1):money[1];
	}while(checkone(money[0],money[1]));
	
	map[money[1]][money[0]]=SNAKE_FOOD;
}

int checkone(int x,int y)									//检查是否出现在蛇身上 
{
	int i;
	for(i=0;i<snakelength;i++)
	{
		if((x==snakex[i])&&(y==snakey[i]))
			return 1;
	}
	return 0;
}

void put_obstacles(void)
{
	int i;
	for(i=0;i<3;i++)								//把之前的障碍物去除 
		map[obstacley[i]][obstaclex[i]]=BLANK_CELL;
	
	for(i=0;i<3;i++)								//生成三个障碍物，若出现在蛇身上，则重置 
	{
		do														
		{
			obstaclex[i]=(obstaclex[i]+(unsigned int)time(0)%11)%11;
			obstacley[i]=(obstaclex[i]+(unsigned int)time(0)%11)%11;
			obstaclex[i]=(obstaclex[i]<1)?(obstaclex[i]+1):obstaclex[i];
			obstacley[i]=(obstacley[i]<1)?(obstacley[i]+1):obstacley[i];
		}while(checkone(obstaclex[i],obstacley[i])||(obstaclex[i]==money[0]&&obstacley[i]==money[1]));
		map[obstacley[i]][obstaclex[i]]=WALL_CELL;
	}
		
}
