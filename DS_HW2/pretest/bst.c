#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 110

char infix[MAXN],prefix[MAXN];
int label[MAXN];
int tree[1000000];
int stk[MAXN], top;

void _push(int lev, int val){
    if(tree[lev]==-1){
        tree[lev]=val;
        return;
    }
    else if(val<tree[lev]) _push((lev<<1)+1,val);
    else _push((lev<<1)+2,val);
}

void _postfix(int lev){
    if(tree[lev]==-1) return;
    _postfix((lev<<1)+1);
    _postfix((lev<<1)+2);
    stk[top++] = tree[lev];
}

int main(void){
    int i, N;
    scanf("%d",&N);
    while(N--){
        scanf("%s %s",prefix,infix);
        for(i=0; infix[i]!='\0'; ++i) label[infix[i]] = i;
        //puts("here");
        memset(tree,-1,sizeof(tree));
        for(i=0; prefix[i]!='\0'; ++i) _push(0,label[prefix[i]]);
        //puts("here");
        top=0;
        _postfix(0);
        for(i=0; i<top; ++i) printf("%c", infix[stk[i]]);
        printf("\n");
    }
    return 0;
}
