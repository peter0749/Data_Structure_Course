#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define STKSIZE 11
#define BR printf("\n")

typedef struct
{
    int front, rear;
    int stk[STKSIZE];
}QUEUE;
void _Init(QUEUE *que)
{
    que->front = 0;
    que->rear = 0;
}

void _PushBack(QUEUE *que, int n)
{
    if((que->rear+STKSIZE+1)%STKSIZE == (que->front+STKSIZE)%STKSIZE ) return;
	que->rear = (que->rear+1)%STKSIZE;
    que->stk[que->rear] = n;
}

int _Pop(QUEUE *que)
{
    if(que->front == que->rear) return INT_MIN;
	que->front = (que->front+1)%STKSIZE;
    return que->stk[que->front];
}

QUEUE queue;

int main(void)
{
    int input, data, i, t, N;
    _Init(&queue);
	scanf("%d", &N);
	while(N--)
	{
		scanf("%d", &data);
		_PushBack(&queue,data);
	}
    while(scanf("%d", &input)!=EOF)
    {
        switch(input)
        {
            case 1:
                scanf("%d",&data);
                _PushBack(&queue, data);
                break;
            case 2:
                _Pop(&queue);
                //printf("%d\n", _Pop(&queue));
                break;
        }
		//printf("%d %d\n", queue.front , queue.rear);
    }
    if(queue.front != queue.rear)
    {
		printf("%d", _Pop(&queue));
		while( ( t = _Pop(&queue)) != INT_MIN )
		{
			printf(" %d", t);
		}
		BR;
    }
    return 0;
}
