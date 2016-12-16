#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 100000

typedef struct{
    int x, y;
}Point;

double crossP(Point *o, Point *a, Point *b){
    return (a->x - o->x) * (b->y-o->y) -\
    (a->y - o->y) * (b->x-o->x);
}

int cmp( const void *c, const void *d){
    Point *a = (Point*)c;
    Point *b = (Point*)d;
    return (a->x < b->x) || (a->x==b->x && a->y<b->y);
}

Point P[MAXN];
Point C[MAXN];
int Pm, Cm;

void Andrew(void){
    int i, t;
    qsort(P, Pm, sizeof(Point), cmp);
    Cm = 0;
    for(i=0; i<Pm; ++i){
        while(Cm>=2 && crossP(&C[Cm-2],&C[Cm-1], &P[i]) <= 0) --Cm;
        C[Cm++] = P[i];
    }
    for(i=Pm-2, t=Cm+1; i>=0; --i){
        while(Cm>=t && crossP(&C[Cm-2],&C[Cm-1], &P[i]) <= 0) --Cm;
        C[Cm++] = P[i];
    }
    Cm--;
}

int main(void){
    char input[1000];
    int x, y, s;
    Pm = Cm = 0;
    while((fgets(input,sizeof(input),stdin))!=NULL){
        sscanf(input,"%d %d", &x, &y);
        P[Pm].x = x;
        P[Pm++].y = y;
    }
    Andrew();
    //printf("??? %d %d\n", P[Pm-1].x, P[Pm-1].y);
    for(s=0; s<Cm && !(C[s].x==P[Pm-1].x&&C[s].y==P[Pm-1].y); ++s);
    for(int i=0; i<Cm; ++i){
        printf("%d %d\n", C[(i+s)%Cm].x, C[(i+s)%Cm].y);
    }
    return 0;
}
