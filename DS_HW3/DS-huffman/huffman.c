#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 100000

typedef struct NODE{
    int freq;
    struct NODE *l, *r;
}BT;

typedef BT* HDATA_T;
typedef struct{
    int rear, full;
    HDATA_T *data;
    int (*comp)(const void *a, const void*b);
}HEAP_t;

void memswap(char *src, char *tar, size_t len){
    char *temp = (char*)malloc(len);
    memcpy(temp,src,len);
    memcpy(src,tar,len);
    memcpy(tar,temp,len);
}
int init_HEAP_t(HEAP_t *ptr, int size, int (*comp)(const void *a, const void*b)){
    ptr->data = (HDATA_T*)malloc(sizeof(HDATA_T)*size);
    if(!ptr->data){
        fprintf(stderr,"Out of memory...\n");
        exit(-1);
    }
    ptr->rear = 0;
    ptr->full = size;
    ptr->comp = comp;
    return size;
}

void des_HEAP_t(HEAP_t *h){
    free(h->data);
    h->data = NULL;
    h->rear = h->full = 0;
}

void pushHEAP(HDATA_T key, HEAP_t *h){
    int ch, pa;
    if(h->rear==h->full){
        fprintf(stderr,"HEAP Full!\n");
        exit(-1);
    }
    ch=h->rear; pa=(ch-1)>>1;
    h->data[h->rear++] = key;
    while( ch>0 && h->comp(&h->data[ch], &h->data[pa])){ //child < parent
        memswap(&h->data[ch], &h->data[pa], sizeof(HDATA_T));// swap it
        ch=pa;
        pa=(ch-1)>>1;
    }
}

HDATA_T topHEAP(HEAP_t *h){
    if(!h||!h->data||h->rear==0){
        fprintf(stderr,"HEAP is empty or not initialized.\n");
        exit(-1);
    }
    return h->data[0];
}
HDATA_T popHEAP(HEAP_t *h){
    if(!h||!h->data||h->rear==0){
        fprintf(stderr,"HEAP is empty or not initialized.\n");
        exit(-1);
    }
    HDATA_T output = h->data[0];
    h->data[0] = h->data[--h->rear];
    int pos=0, ch;
    while((ch = (pos<<1)+1) < h->rear){
        if( ch+1<h->rear && h->comp(&h->data[ch+1], &h->data[ch]) ) ++ch;
        if( h->comp(&h->data[ch], &h->data[pos])){
            memswap(&h->data[ch],&h->data[pos], sizeof(h->data[ch]));
            pos = ch;
        }else break;
    }
    return output;
}
char emptyHEAP(HEAP_t *h){
    return (!h||!h->data || h->rear==0)? 1:0;
}

int cmp(const void *a, const void *b){
    HDATA_T *c=(HDATA_T*)a, *d=(HDATA_T*)b;
    return (*c)->freq < (*d)->freq ?1:0;
}

void huffTravl(BT *root, int crrCode, int *maxdepth, int depth){
    if(root->l==NULL && root->r==NULL){
        root->freq = crrCode|(1<<depth);
        if(depth > *maxdepth) *maxdepth = depth;
        return;
    }
    if(root->l)huffTravl(root->l, crrCode<<1, maxdepth, depth+1);
    if(root->r)huffTravl(root->r, crrCode<<1|1, maxdepth, depth+1);
    free(root);
}

int huffmanTree(int *freqs, int *code, int N){
    int i, mxbit;
    HEAP_t heap;
    init_HEAP_t(&heap, N, cmp);
    BT *left, *right, *newR;
    BT *list=(BT*)malloc(sizeof(BT)*N);
    left = right = newR = NULL;
    for(i=0; i<N; ++i) {
        list[i].freq=freqs[i];
        list[i].l = list[i].r = NULL;
        pushHEAP(&list[i], &heap);
    }
    while(heap.rear>=2){
        right = popHEAP(&heap);
        left = popHEAP(&heap);
        newR = (BT*)malloc(sizeof(BT));
        newR->freq = left->freq+right->freq;
        newR->l = left; newR->r = right;
        pushHEAP(newR, &heap);
    }
    newR = popHEAP(&heap);
    des_HEAP_t(&heap);
    mxbit=0;
    if(newR->l)huffTravl(newR->l, 0, &mxbit, 1);
    if(newR->r)huffTravl(newR->r, 1, &mxbit, 1);
    for(i=0; i<N; ++i)  code[i] = list[i].freq;
    free(newR);
    free(list);
    return mxbit;
}

typedef struct{
    char op;
    int freq;
}inputDATA;

int cmpdata(const void *a, const void *b){
    return (int)((inputDATA*)a)->op - (int)((inputDATA*)b)->op;
}

void bin2str(char *str, int bin, int bitn){
    int i;
    for(i=bitn; i>=0 && (bin&(1<<i))==0 ; --i);
    //printf("#%d\n", i);
    str[i--] = '\0';
    for(; i>=0; --i){
        str[i] = (bin&1) + '0';
        bin>>=1;
    }
}

typedef struct{
    char OP;
    char codes[32];
}OUTPUT;

int cmpout(const void *a, const void *b){
    int lendiff = strlen(((OUTPUT*)b)->codes) - strlen(((OUTPUT*)a)->codes);
    return  lendiff?lendiff:\
    strcmp(((OUTPUT*)b)->codes, ((OUTPUT*)a)->codes);
}

int main(void){
    BT *huffRoot=NULL;
    inputDATA data[MAXN];
    OUTPUT out[MAXN];
    int code[MAXN];
    int freq[MAXN];
    int N, i, n, bitn;
    char *ptr, input[MAXN], tok[]=" \t";
    fgets(input,MAXN,stdin);
    N=atoi(input);
    while(N--){
        fgets(input,MAXN,stdin);
        i = 0;
        ptr = strtok(input, tok);
        while(ptr){
            data[i++].op = *ptr;
            ptr = strtok(NULL,tok);
        }
        fgets(input,MAXN,stdin);
        i = 0;
        ptr = strtok(input, tok);
        while(ptr){
            data[i++].freq = atoi(ptr);
            ptr = strtok(NULL,tok);
        }
        n=i;
        fgets(input,10,stdin);
        qsort(data, n, sizeof(inputDATA), cmpdata);
        for(i=0; i<n; ++i) freq[i] = data[i].freq;
        bitn = huffmanTree(freq, code, n);
        for(i=0; i<n; ++i){
            bin2str(out[i].codes, code[i], bitn);
            out[i].OP = data[i].op;
        }
        qsort(out,n,sizeof(OUTPUT),cmpout);
        for(i=0; i<n; ++i) printf("%c %s\n",out[i].OP, out[i].codes);
    }

    return 0;
}
