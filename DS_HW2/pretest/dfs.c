#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1001

char map[MAXN][MAXN];
char vis[MAXN];
int power[MAXN];
int N,K,J,L;
int fail, succ, total;

void dfs(int node){
    int i;
    //printf("%d\n",node);
    vis[node]=1;
    if(total >= L) return;
    if(total > power[node]){
        ++succ;
        total+=power[node];
    }else{
        ++fail;
        return;
    }
    for(i=0; i<N; ++i){
        if(map[node][i] && !vis[i]) dfs(i);
    }
}

int main(void){
    int i,u,v;
    while(scanf("%d%d%d%d",&N,&J,&K,&L)==4){
        for(i=0; i<N; ++i) scanf("%d",power+i);
        memset(map,0x00,sizeof(map));
        for(i=0; i<J; ++i){
            scanf("%d%d",&u,&v);
            map[u][v] = 1;
        }
        memset(vis,0x00,sizeof(vis));
        fail=succ=0;
        total = K;
        dfs(0);
        printf("%d %d %d\n",fail,succ,total);
    }
    return 0;
}
