#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 110

int graph[MAXN][MAXN];
char visit[MAXN][MAXN];
int pa[MAXN];

char dfs(int u, int dim){
    int i;
    for(i=0; i<dim; ++i){
        if(graph[u][i]){
            //printf("%d -> %d\n",u+1,i+1);
            if(visit[u][i]){
                if(pa[i]==u ) return 1;
                pa[i] = u;
            }
            else{
                visit[u][i] = 1;
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
            for(j=0; j<dim; ++j) pa[j]=j;
            if(dfs(i,dim))break;
        }
        printf(i==dim?"No\n":"Yes\n");
    }
    return 0;
}
