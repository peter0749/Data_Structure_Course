#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define DIM 1001
#define INF INT_MAX
bool map[DIM][DIM];
int power[DIM];
int fails=0, success=0, total=0;

bool dfs(int u, int dim, int tar){
    if(total>=tar) return true;
    int i;
    for(i=0; i<dim; ++i){
        if(map[u][i]){
            if(total > power[i]){
                //printf("# %d %d\n", u, i);
                total += power[i];
                ++success;
                if(dfs(i, dim, tar)) return true;
            }
            else{
                ++fails;
                power[i]=INF;
            }
        }
    }
    return false;
}

int main(void){
    int N, J, K, L, i, j, u, v;
    while( scanf("%d%d%d%d", &N, &J, &K, &L)==4 ){
        memset(map,0x00,sizeof(map));
        for(i=0; i<N; ++i){
            scanf("%d", &power[i]);
        }
        for(i=0; i<J; ++i){
            scanf("%d%d", &u, &v);
            map[u][v] = true;
        }
        fails=0, success=0, total=K;
        if(total<L){
            if(total > power[0]){
                success++;
                dfs(0, N, L);
            }
            else fails++;
        }
        printf("%d %d %d\n", fails, success, total);
    }
    return 0;
}
