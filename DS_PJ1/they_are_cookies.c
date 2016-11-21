#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define VIS
#ifdef VIS
#ifdef __WIN32
#include <windows.h>
#endif
#endif
#define MAXN 101
#define STKL 131072
#define STRL 2000
#define _MIN(X,Y) (X) < (Y) ? (X) : (Y)
#ifdef __WIN32
#define CLS system("cls")
#else
#define CLS system("clear")
#endif

const int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
//const int dirs[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
int maze[MAXN+2][MAXN+2];
char mark[MAXN+2][MAXN+2];
int stk[STKL][3];//y,x,dir
int fullpath[STKL][2];//y,x
int top, f, N;
int start[2], end[2];
int coins = 0;

#ifdef VIS
#ifdef __WIN32
   void gotoxy(int xpos, int ypos)
   {
   COORD scrn;
   HANDLE hOuput = GetStdHandle(STD_ERROR_HANDLE);
   scrn.X = xpos;
   scrn.Y = ypos;
   SetConsoleCursorPosition(hOuput,scrn);
   }
#else
void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1B,y+1,x+1);
	fflush(stdout);
}
#endif

void prtout(void)
{
	int i, j;
	CLS;
	for(i=1; i<=N; i++)
	{
		for(j=1; j<=N; j++)
		{
			fprintf(stdout,maze[i][j] ? (maze[i][j]==2?" o":" #"):"  ");
		}
		fprintf(stdout,"\n");
	}
}

void prtchar(int crr_row, int crr_col, int crr_dir)
{
	static int pr_col=1, pr_row=1, pr_coin=0;

	gotoxy((pr_col-1)*2, pr_row-1);
	fprintf(stdout,maze[pr_row][pr_col]==1 ? " #":"  ");
	fflush(stdout);
	gotoxy((crr_col-1)*2, crr_row-1);
	switch(crr_dir)
	{
		case 0:
			fprintf(stdout," v");
			break;
		case 1:
			fprintf(stdout," <");
			break;
		case 2:
			fprintf(stdout," ^");
			break;
		case 3:
			fprintf(stdout," >");
			break;
		case -1:
			fprintf(stdout," O");
			break;
		case -2:
			fprintf(stdout," W");
			break;
		case -3:
			fprintf(stdout," M");
			break;
		default:
			fprintf(stdout," D");
			break;
	}
	fflush(stdout);
	if(pr_coin!=coins){
		gotoxy(0,N+1);
		fprintf(stdout,"There are %d cookies. Yummy!\t\t\t\t\t\t\t\t",coins);
		fflush(stdout);
		pr_coin=coins;
	}
	pr_col = crr_col;
	pr_row = crr_row;
	usleep(190000);
}
#endif
char go_mice(const int startpos[2], const int endpos[2], const int dirs[][2], int *top, int stk[][3], int *fp, int fstk[][2])
{
	int crr_pos[3];
	int y,x,ny,nx,dir,i;
	char found=0;
	memset(mark,0x00,sizeof(mark));
	mark[startpos[0]][startpos[1]] = 1;
	++(*top);
	stk[*top][0] = startpos[0];
	stk[*top][1] = startpos[1];
	stk[*top][2] = 0;
	//for(i=0, ++(*fp); i<3; i++) fstk[*fp][i] = stk[*top][i];
#ifdef VIS
	CLS;
	prtout();
#endif
	while(*top>=0 && !found)
	{
		i=3;
		while(i--)
		{
			crr_pos[i] = stk[*top][i];
		}
		--(*top);//pop
		y = crr_pos[0];
		x = crr_pos[1];
		dir = crr_pos[2];
#ifdef VIS
		prtchar(y,x,dir);
#endif
		for(i=0, ++(*fp); i<2; i++) fstk[*fp][i] = crr_pos[i];//Mouse back track
		if(maze[y][x]==2){
			maze[y][x] = 0;
			++coins;
		}
		while(dir<4&&!found)
		{
			ny = y + dirs[dir][0];
			nx = x + dirs[dir][1];
			//printf("%d,%d,%d\n", ny,nx,dir);
			if( ny==endpos[0] && nx==endpos[1] )
				found = 1;
			else if( maze[ny][nx]!=1 && !mark[ny][nx])
			{
#ifdef VIS
				prtchar(ny,nx,dir);
#endif
				if(maze[ny][nx]==2){
					maze[ny][nx]=0;
					++coins;
				}
				++(*fp);//Mouse explore new area
				fstk[*fp][0] = ny;
				fstk[*fp][1] = nx;
				mark[ny][nx] = 1;
				(*top)++;
				stk[*top][0] = y;
				stk[*top][1] = x;
				stk[*top][2] = ++dir;
				x = nx;
				y = ny;
				dir=0;
			}
			else
			{
				++dir;
			}
		}
		//found ? prtchar(ny,nx,-found):prtchar(y,x,dir);//Found or 'X'
	}
	if(found)
	{
		(*top)++;
		stk[*top][0] = y;
		stk[*top][1] = x;
		//for(i=0, ++(*fp); i<3; i++) fstk[*fp][i] = stk[*top][i];
		(*top)++;
		stk[*top][0] = ny;
		stk[*top][1] = nx;
		for(i=0, ++(*fp); i<3; i++) fstk[*fp][i] = stk[*top][i];//Mouse at endpoint
		if(maze[ny][nx]==2){
			maze[ny][nx]=0;
			++coins;
		}
#ifdef VIS
		CLS;
#endif
	}
	return found;
}

int main(int argc, char *argv[])
{
	int i,j,step;
	char found = 0, flag;
	FILE *FP, *FOUT;
	FP = fopen(argv[1], "r");
	FOUT = fopen("result.txt","w");
	if(!FP || !FOUT) exit(-1);
	for(i=0; i<MAXN; ++i)for(j=0;j<MAXN;++j){
		maze[i][j]=1;
		mark[i][j]=0;
	}
	coins = 0;
	
	fscanf(FP,"%d",&N);
	fscanf(FP,"%d%d%d%d",&start[1],&start[0],&end[1],&end[0]);
	++start[0];++start[1];++end[0];++end[1];
	for(i=1; i<=N; i++)
	{
		for(j=1; j<=N; j++)
		{
			fscanf(FP,"%d",&maze[i][j]);
		}
	}
	//prtout();
	//while(1);
	
	f = top = -1;
#ifdef VIS
	CLS;
#endif
	flag = go_mice(start,end,dirs,&top,stk,&f,fullpath);
#ifdef VIS
	CLS;
#endif
	
	printf("Full Path:\n");
	step = f;
	for(i=0; i<=step ; i++)
	{
		printf("Step:%5d\tPacman(%2d,%2d)\n",i,fullpath[i][1]-1,fullpath[i][0]-1);
		fprintf(FOUT,"Step:%5d\tPacman(%2d,%2d)\n",i,fullpath[i][1]-1,fullpath[i][0]-1);
	}
	
	printf("I've eaten %d cookies. They're Tasty!\n",coins);
	
	fclose(FOUT); fclose(FP);
	return 0;
}