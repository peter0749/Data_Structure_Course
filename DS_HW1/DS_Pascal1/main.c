#include <stdio.h>
#include <stdlib.h>

typedef struct Linked_List
{
    unsigned long long int val;
    struct Linked_List *next;
}List;

int main(void)
{
    //freopen("testout.txt","w",stdout);
    List *Levels = NULL;
    List *Listptr = NULL;
    List *preList = NULL;
    List *crrList = NULL;
    int num, i, j;
    unsigned long long int maxval;
    while(scanf("%d",&num)!=EOF)
    {
        Levels = (List*)malloc(sizeof(List)*num);
        Levels[0].val = 1;
        Levels[0].next=NULL;
        for(i=1, maxval=1; i<num; i++)
        {
            Levels[i].val = 1;
            preList = &Levels[i-1];
            crrList = &Levels[i];
            while(preList->next != NULL)
            {
                Listptr = (List*)malloc(sizeof(List));//Allocate new node;
                Listptr->val = preList->val + preList->next->val;
                if(Listptr->val > maxval) maxval = Listptr->val;
                Listptr->next = NULL;
                crrList->next = Listptr;
                crrList = Listptr;
                preList = preList->next;
            }
            Listptr = (List*)malloc(sizeof(List));//Allocate new node;
            Listptr->val = 1; Listptr->next=NULL;
            crrList->next = Listptr;
        }
        for(i=0; i<num; i++)
        {
            crrList = &Levels[i];
            printf("%llu", crrList->val);
            crrList = crrList->next;
            while(crrList!=NULL)
            {
                printf(" %llu", crrList->val);
                crrList = crrList->next;
            }
            printf("\n");
        }
        printf("%llu\n", maxval);
        for(i=0; i<num; i++)
        {
            crrList = Levels[i].next;
            while(crrList!=NULL)
            {
                Listptr = crrList;
                crrList = crrList->next;
                free(Listptr);
            }
        }
        free(Levels);
    }
    return 0;
}
