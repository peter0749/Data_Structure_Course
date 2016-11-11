#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 110

int graph[MAXN][MAXN];
char visit[MAXN];
int pa[MAXN];

char dfs(int u, int dim){
    int i, j, t;
    for(i=0; i<dim; ++i){
        if(graph[u][i]){
            //printf("%d -> %d\n",u+1,i+1);
            if(visit[i]){
                for(j=pa[u], t=i; j!=t; j=pa[t=j]){
                    //printf("%d ",j+1);
                    if(j==i) return 1;
                }
            }
            else{
                visit[i] = 1;
                pa[i] = u;
                if(dfs(i,dim)) return 1;
            }
        }
    }
    return 0;
}

int main(void){
    int N, dim, i, j;
    scanf("%d", &N);
    while(N--){
        scanf("%d", &dim);
        for(i=0; i<dim; ++i){
            for(j=0; j<dim; ++j) scanf("%d", &graph[i][j]);
        }
        scanf("%d", &i);
        for(i=0; i<dim; ++i){
            //printf("Start: %d\n",i+1);
            memset(visit,0x00,sizeof(visit));
            visit[i] = 1;
            for(j=0; j<dim; ++j) pa[j]=j;
            if(dfs(i,dim))break;
        }
        printf(i==dim?"No\n":"Yes\n");
    }
    return 0;
}
