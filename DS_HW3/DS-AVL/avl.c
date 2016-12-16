#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE{
    int key, h;
    struct NODE *l, *r;
}AVL;

int _MAX2(int X, int Y){
    return X > Y ? X:Y;
}

void update(AVL *n){
    n->h = 1 + _MAX2((n->l?n->l->h:0),(n->r?n->r->h:0));
}

int BFactor(AVL *n){
    return (n->r?n->r->h:0) - (n->l?n->l->h:0);
}

AVL *rR(AVL *x){
    AVL *y = x->l;
    x->l=y->r; y->r=x;
    update(x); update(y);
    return y;
}

AVL *rL(AVL *x){
    AVL *y = x->r;
    x->r = y->l; y->l=x;
    update(x); update(y);
    return y;
}

AVL *balance(AVL *x){
    update(x);
    if( BFactor(x) == 2){//rotateR
        if(BFactor(x->r) < 0) x->r = rR(x->r);
        return rL(x);
    }
    if( BFactor(x)  == -2){//rotateL
        if(BFactor(x->l) > 0) x->l = rL(x->l);
        return rR(x);
    }
    return x;
}

AVL *insert(AVL *x, int key){
    if(!x){
        x = (AVL*)malloc(sizeof(AVL));
        x->key = key;
        x->h = 1;
        x->l = x->r = NULL;
        return x;
    }
    if(key < x->key) x->l = insert(x->l, key);
    else x->r = insert(x->r, key);
    return balance(x);
}

int stk[100000], top=0;

void infix(AVL *node){
    if(node){
        infix(node->l);
        //printf("(node,height): %d %d\n",node->key, node->h);
        stk[top++] = node->key;
        infix(node->r);
    }
}

void postfix(AVL *node){
    if(node){
        postfix(node->l);
        postfix(node->r);
        stk[top++] = node->key;
        free(node);
    }
}

int main(void){
    int N, num, i;
    AVL *root=NULL;
    scanf("%d", &N);
    while(N--){
        while(scanf("%d",&num) && num!=-1) root = insert(root, num);
        top=0;
        infix(root);
        printf("%d",stk[0]);
        for(i=1; i<top; ++i) printf(",%d",stk[i]);
        printf("\n");
        top=0;
        postfix(root);
        printf("%d",stk[0]);
        for(i=1; i<top; ++i) printf(",%d",stk[i]);
        printf("\n");
        root = NULL;
    }
    return 0;
}
