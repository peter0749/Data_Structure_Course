#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_NODE 100000
#define INF 1000000009

typedef int _PAIR_TYPE;
typedef struct{
    _PAIR_TYPE first, second;
}_PAIR;

typedef _PAIR VEC_TYPE;
typedef struct{
    size_t usage, full;
    VEC_TYPE *arr;
}_VECTOR;

void _SWAP(VEC_TYPE *a, VEC_TYPE *b){
	VEC_TYPE temp = *a;
	*a = *b;
	*b = temp;
}

void _init_vec(_VECTOR *v){
	if(!v) return;
    v->usage = 0;
    v->full = 5;
    v->arr = (VEC_TYPE*)malloc(v->full * sizeof(VEC_TYPE));
}
void _push_back(_VECTOR *v, VEC_TYPE val){
    VEC_TYPE *newptr=NULL;
    int i;
    if( v->usage==v->full ){
        v->full += v->full<<1;
        newptr = (VEC_TYPE*)malloc(v->full*sizeof(VEC_TYPE));
        memcpy(newptr,v->arr,v->usage*sizeof(VEC_TYPE));
        free(v->arr);
        v->arr = newptr;
    }
    v->arr[v->usage++] = val;
}
void _des_vec(_VECTOR *v){
	if(!v || !v->arr) return;
    free(v->arr);
    v->arr = NULL;
    v->usage = v->full = 0;
}

void _PUSH_HEAP(_VECTOR *heap, _PAIR val){
	int ch, pa;
	ch = heap->usage;
	_push_back(heap,val);
	while(ch>0){
		pa = (ch-1)>>1;
		if(heap->arr[ch].second <= heap->arr[pa].second){
			_SWAP(&heap->arr[ch], &heap->arr[pa] );
			ch = pa;
		}else break;
	}
}

_PAIR _POP_HEAP(_VECTOR *heap){
	_PAIR temp = {-1,-1};
	int ch=0, pa=0;
	if(heap->usage>0){
		temp = heap->arr[0];
		heap->arr[0] = heap->arr[--heap->usage];
		while( (ch=(pa<<1)+1)<heap->usage ){
			if( ch+1<heap->usage && heap->arr[ch].second > heap->arr[ch+1].second  ) ++ch;
			if( heap->arr[pa].second>heap->arr[ch].second ){
				_SWAP(&heap->arr[pa], &heap->arr[ch] );
				pa = ch;
			}else break;
		}
	}
	return temp;
}

_VECTOR graph[MAX_NODE];
_VECTOR heap;
int dist[MAX_NODE];
int edges=0, path_len=0;

void dijkstra(int src, int tar, _VECTOR *heap){
    int i, j, u, v, w, min_dist, t, uw;
	_PAIR temp;
    for(i=0; i<MAX_NODE; ++i) dist[i] = INF;
    dist[src] = 0;
	temp.first = src;
	temp.second = 0;
	heap->usage = 0;
	_PUSH_HEAP(heap,temp);
	while(heap->usage){
        temp = _POP_HEAP(heap);
        if(temp.first==tar) return;
		if(temp.second > dist[temp.first] ) continue;
		u = temp.first;
		uw = temp.second;
        for(i=0; i<graph[u].usage; ++i){
            v = graph[u].arr[i].first;
            w = graph[u].arr[i].second;
            t = uw+w;
			if(t < dist[v] ){
				dist[v] = t;
				temp.first = v;temp.second = dist[v];
				_PUSH_HEAP(heap,temp);
			}
        }
    }
}

int main(void){
	/*
	int i;
	_PAIR ars[4] = {
		{1,2},
		{3,4},
		{5,6},
		{7,8}
	}, temp;
	_init_vec(&heap);
	for(i=4; i>=0; --i) _PUSH_HEAP(&heap,ars[i]);
	for(i=0; i<4; ++i){
		temp = _POP_HEAP(&heap);
		printf("%d : %d\n",temp.first,temp.second);
	}
	_des_vec(&heap);
	*/
    int N, u, v, w, S, T, i, j;
	int max_node_num;
    _PAIR p;
    char input[1000];
    for(i=0; i<MAX_NODE; ++i) _init_vec(&graph[i]);
	_init_vec(&heap);
    fgets(input,sizeof(input),stdin);
    N = atoi(input);
    while(N--){
		max_node_num = 0;
        fgets(input,sizeof(input),stdin);
        edges = atoi(input);
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d %d", &S, &T);
        while(1){
            fgets(input,sizeof(input),stdin);
            if(atoi(input)==-1)break;
            sscanf(input,"%d %d %d", &u, &v, &w);
			if(u>max_node_num) max_node_num = u;
			if(v>max_node_num) max_node_num = v;
            p.first = v;p.second = w;
            _push_back(&graph[u], p);
        }

        dijkstra(S,T, &heap);
        printf("%d\n", dist[T]);
		for(i=0; i<=max_node_num; ++i) graph[i].usage=0;
    }
    for(i=0; i<MAX_NODE; ++i) _des_vec(&graph[i]);
	_des_vec(&heap);
    return 0;
}
