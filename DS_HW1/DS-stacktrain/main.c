#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 110
int A[MAX], B[MAX], C[MAX];
int tA, tB, tC;

int main(void)
{
	int i, j;
	char temp[4096];
	char *ptr=NULL;
	const char tok[]=" \t";
	char flagA, flagC;
	while((gets(temp))!=NULL)
	{
		tA = tB = tC = 0;
		ptr = temp;
		ptr = strtok(ptr,tok);
		while(ptr!=NULL)
		{
			A[tA++] = atoi(ptr);
			ptr = strtok(NULL,tok);
		}
		gets(temp);
		ptr = temp;
		ptr = strtok(ptr,tok);
		while(ptr!=NULL)
		{
			B[tB++] = atoi(ptr);
			ptr = strtok(NULL,tok);
		}

		j = 0;//Front of A;
		for(i=0; i<tB && tC<=5; i++)
		{
			flagA = flagC = 0;
			if(tC!=0 && C[tC-1]==B[i])
			{
				flagC=1;
				tC--;
			}
			else
			{
				while(j<tA && tC<=5)
				{
					if(A[j]==B[i])
					{
						flagA=1;
						j++;
						break;
					}
					C[tC++] = A[j++];
				}
			}
			if(!(flagA|flagC)) break;
		}
		if(i==tB)puts("Yes");
		else puts("No");
	}

	return 0;
}

