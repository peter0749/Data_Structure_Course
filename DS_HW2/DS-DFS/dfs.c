#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAXN 1200

char map[MAXN][MAXN];
int power[MAXN];
char avil[MAXN];

int succ, fail, total;

char solve(int u, int dim, int lim){
    if(total>=lim) return 1;
    int i;
    for(i=0; i<dim; ++i){
        if(map[u][i] && avil[i]){
            if(total > power[i]){
                total+=power[i];
                //power[i]=0;
                succ++;
                if(solve(i,dim,lim)) return 1;
            }else{
                fail++;
                avil[i] = 0;
            }
        }
    }
    return 0;
}

int main(void){
    int N, J, K, L, i, u, v, w;
    while((scanf("%d%d%d%d", &N, &J, &K, &L))==4){
        for(i=0; i<N; ++i) scanf("%d", &power[i]);
        memset(map,0x00,sizeof(map));
        for(i=0; i<J; ++i){
            scanf("%d%d", &u, &v);
            //while(1){}
            //assert(u!=0);
            map[u][v] = 1;
        }
        for(i=0; i<N; ++i) avil[i]=1;
        total = K;
        succ = fail = 0;
        if(total > power[0]){
            ++succ;
            total+=power[0];
            //power[0] = 0;
            solve(0,N,L);
        }else fail++;
        printf("%d %d %d\n",fail,succ,total);
    }
    return 0;
}
