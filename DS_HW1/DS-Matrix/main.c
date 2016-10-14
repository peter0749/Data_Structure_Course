#include <stdio.h>
#include <stdlib.h>
#define MAXN 5
int data[MAXN][MAXN];

void rotate(void)//For MAXN is odd
{
    int i, j, m, n, vi, vj;
    int temp;
    m = MAXN>>1;
    n = m - 1;
    //printf("%d %d\n",m,n);
    for(i=0; i<=n; i++)
	{
		for(j=0; j<=m; j++)
		{
			vi = i - m;
			vj = j - m;
			temp = data[i][j];
			data[i][j] = data[m+vj][m-vi];
			data[m+vj][m-vi] = data[m-vi][m-vj];
			data[m-vi][m-vj] = data[m-vj][m+vi];
			data[m-vj][m+vi] = temp;
		}
	}
}

void display(void)
{
    int i, j;
    for(i=0; i<MAXN; i++)
    {
        printf("%d",data[i][0]);
        for(j=1; j<MAXN; j++)
            printf(" %d",data[i][j]);
        printf("\n");
    }
}

int main(void)
{
    char opcode;
    int i, j;
    for(i=0; i<MAXN; i++)
        for(j=0;j<MAXN; j++)
            scanf("%d",&data[i][j]);
            //data[i][j] = i*MAXN + j;
    while((scanf("%c", &opcode))!=EOF)
    {
        switch(opcode)
        {
        case 'L':
            rotate();
            break;
        }
    }
    display();
    return 0;
}
