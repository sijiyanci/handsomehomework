#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

void snakemove(int dy,int dx);								//�ƶ� 
void put_money(void);										//��ȷ����ʳ�� 
void output(void);											//���½��� 
void gameover(void);										//������Ϸ 
int checkmany(void);										//����Ƿ�ײǽ���߳��Լ� 
int checkone(int x,int y);									//����Ƿ�����������ϣ����ڼ���Ƿ���ȷ����ʳ��ϰ�� 
void put_obstacles(void);									//��ȷ�����ϰ��� 

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
int money[2]={12,12}; 
int obstaclex[3]={9,8,7};
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
		if(!flagmoney)			//��ȷ����ʳ�� 
		{
			put_money();
			flagmoney=1;
		}	
		if(!countobs)			//��ȷ�����ϰ��� 
		{	
			put_obstacles();
			countobs=3;	
		}				
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
		if(checkmany())							//�Ƿ�ײ�������ǽ�� 
			break;
		for(i=0;i<3;i++)																//�Ƿ�ײ���ϰ��� 
			if(obstaclex[i]==snakex[snakelength-1]&&obstacley[i]==snakey[snakelength-1])
			{
				flagobs=1;
				break;
			}
		if(flagobs)								//���ײ���ϰ��������Ϸ 
			break; 
		output();							 	//���½���
		countobs--;
		while((ch=getchar())!='\n')
			continue;
	}
	gameover();
	
}

void snakemove(int dy,int dx)
{
	int i;
	if(snakex[snakelength-1]+dx==money[0]&&snakey[snakelength-1]+dy==money[1])			//���Ե�ʳ���䳤 
	{
		snakex[snakelength]=snakex[snakelength-1]+dx;
		snakey[snakelength]=snakey[snakelength-1]+dy;
		
		snakelength++;
		map[snakey[0]][snakex[0]]=SNAKE_BODY;
		flagmoney=0;
	}
	else														//û�Ե�����ֻ�ƶ�λ�� 
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

void output(void)										//���½��� 
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

int checkmany(void)				//�ж��Ƿ�ײ��ǽ������ 
{
	int i;
	for(i=0;i<snakelength-1;i++)													//�Ƿ�ײ���Լ� 
	{
		if((snakex[snakelength-1]==snakex[i])&&(snakey[snakelength-1]==snakey[i]))
			return 1;
	}
	if(snakex[snakelength-1]<1||snakex[snakelength-1]>10||snakey[snakelength-1]<1||snakey[snakelength-1]>10)	//�Ƿ�ײ��ǽ 
		return 1;
	return 0;
}

void put_money(void)
{
	
	map[money[1]][money[0]]=BLANK_CELL;
	
	do														//���ʳ������������ϣ����� 
	{
		money[0]=(money[0]+(unsigned int)time(0)%11)%11;
		money[1]=(money[0]+(unsigned int)time(0)%11)%11;
		money[0]=(money[0]<1)?(money[0]+1):money[0];
		money[1]=(money[1]<1)?(money[1]+1):money[1];
	}while(checkone(money[0],money[1]));
	
	map[money[1]][money[0]]=SNAKE_FOOD;
}

int checkone(int x,int y)									//����Ƿ������������ 
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
	for(i=0;i<3;i++)										//��֮ǰ���ϰ���ȥ�� 
		map[obstacley[i]][obstaclex[i]]=BLANK_CELL;
	
	for(i=0;i<3;i++)										//���������ϰ���������������ϣ������� 
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
