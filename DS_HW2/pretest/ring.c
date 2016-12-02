#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 110

int map[MAXN][MAXN], n;
int vis[MAXN],s[MAXN];
char flag=0;

void dfs(int u, int step) {
    int i;
    if(flag) return;
    vis[u]=1;
    s[u]=step;
    for(i=0; i<n&&!flag; ++i) {
        if(map[u][i]) {
            if(vis[i]) {
                if(s[i]<step) {
                    flag=1;
                    return;
                }
            } else dfs(i,step+1);
        }
    }
}

int main(void) {
    int N, i, j;
    scanf("%d",&N);
    while(N--) {
        scanf("%d",&n);
        for(i=0; i<n; ++i)for(j=0; j<n; ++j)scanf("%d",&map[i][j]);
        scanf("%d",&i);
        for(i=0, flag=0; i<n&&!flag; ++i) {
            memset(vis,0x00,sizeof(vis));
            dfs(i,0);
        }
        printf(flag?"Yes\n":"No\n");
    }
    return 0;
}
