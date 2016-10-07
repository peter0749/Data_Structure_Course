#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define STKSIZE 65536
#define BR printf("\n")

typedef struct
{
    int front, rear;
    int stk[STKSIZE];
}QUEUE;
void _Init(QUEUE *que)
{
    que->front = 1;
    que->rear = 0;
}

void _PushBack(QUEUE *que, int n)
{
    if(que->rear >= STKSIZE) return;
    que->stk[que->rear++] = n;
}

int _Pop(QUEUE *que)
{
    if(que->front > que->rear) return INT_MIN;
    return que->stk[(que->front++)-1];
}

QUEUE queue;

int main(void)
{
    int input, data, i;
    _Init(&queue);
    while(scanf("%d", &input)!=EOF && input!=3)
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
        if(queue.front <= queue.rear)
        {
            printf("%d", queue.stk[queue.front-1]);
            for(i=queue.front; i<queue.rear; i++)
                printf(" %d", queue.stk[i]);
            BR;
        }
        printf("%d\n%d\n", queue.front, queue.rear);
    }
    return 0;
}
