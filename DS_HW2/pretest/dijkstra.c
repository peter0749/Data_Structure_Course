#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1001

int map[MAXN][MAXN];
int DP[MAXN][MAXN];

int main(void){
    int N, E, S, T, u, v, w;
    int i, j, k, t, maxnode;
    scanf("%d",&N);
    while(N--){
        scanf("%d",&E);
        scanf("%d%d",&S,&T);
        for(i=0; i<MAXN; ++i)for(j=0;j<MAXN;++j)map[i][j]=1e9;
        maxnode=0;
        for(i=0; i<E; ++i){
            scanf("%d%d%d",&u,&v,&w);
            map[u][v]=w;
            if(u>maxnode)maxnode=u;
            if(v>maxnode)maxnode=v;
        }
        scanf("%d",&u);
        for(i=0; i<=maxnode; ++i){
            for(j=0; j<=maxnode; ++j)
                DP[i][j]=map[i][j];
            DP[i][i]=0;
        }
        /*Floyd Warshall*/
        for(k=0; k<=maxnode; ++k){
            for(i=0; i<=maxnode; ++i){
                for(j=0; j<=maxnode; ++j){
                    t = DP[i][k] + DP[k][j];
                    if(t<DP[i][j]) DP[i][j] = t;
                }
            }
        }
        printf("%d\n",DP[S][T]);
    }
    return 0;
}
