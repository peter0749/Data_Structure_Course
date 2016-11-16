#include <stdio.h>
#include <stdlib.h>
#define MAXN 100
#define INF 1000000009

int map[MAXN][MAXN];
int floyd[MAXN][MAXN];

int main(void){
    int N,E,u,v,w,i,j,k,S,T,temp;
    int maxnode;
    scanf("%d",&N);
    while(N--){
        maxnode = -1;
        scanf("%d",&E);
        scanf("%d%d", &S, &T);
        for(i=0; i<MAXN; ++i)for(j=0; j<MAXN; ++j)map[i][j]=INF;
        for(i=0; i<E; ++i){
            scanf("%d%d%d",&u,&v,&w);
            maxnode = u>v?(u>maxnode?u:maxnode):(v>maxnode?v:maxnode);
            map[u][v]=w;
        }
        scanf("%d",&i);
        /*
        for(i=0;i<=maxnode;++i){
            for(j=0; j<=maxnode; ++j){
                printf(map[i][j]==INF?"INF":("%3d"),map[i][j]);
            }
            printf("\n");
        }
        */
        for(i=0;i<=maxnode;++i){
            for(j=0;j<=maxnode;++j)floyd[i][j]=map[i][j];
            floyd[i][i]=0;
        }
        for(k=0; k<=maxnode; ++k){
            for(i=0; i<=maxnode; ++i){
                for(j=0; j<=maxnode; ++j){
                    temp = floyd[i][k]+floyd[k][j];
                    if(temp < floyd[i][j]) floyd[i][j] = temp;
                }
            }
        }
        printf("%d\n",floyd[S][T]);
    }
    return 0;
}
