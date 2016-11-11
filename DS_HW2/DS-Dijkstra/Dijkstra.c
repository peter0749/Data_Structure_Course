#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_NODE 10000
#define INF INT_MAX

typedef int _PAIR_TYPE;
typedef struct{
    _PAIR_TYPE first, second;
}_PAIR;

typedef _PAIR VEC_TYPE;
typedef struct{
    size_t usage, full;
    VEC_TYPE *arr;
}_VECTOR;

void _init_vec(_VECTOR *v){
    v->usage = 0;
    v->full = 5;
    v->arr = (VEC_TYPE*)malloc(v->full * sizeof(VEC_TYPE));
}
void _push_back(_VECTOR *v, VEC_TYPE val){
    VEC_TYPE *newptr=NULL;
    int i;
    if( v->usage==v->full ){
        v->full<<=1;
        newptr = (VEC_TYPE*)malloc(v->full*sizeof(VEC_TYPE));
        memcpy(newptr,v->arr,v->usage*sizeof(VEC_TYPE));
        free(v->arr);
        v->arr = newptr;
    }
    v->arr[v->usage++] = val;
}
void _des_vec(_VECTOR *v){
    free(v->arr);
    v->arr = NULL;
    v->usage = v->full = 0;
}

_VECTOR graph[MAX_NODE];
int dist[MAX_NODE];
bool visit[MAX_NODE];
int edges=0, path_len=0;
int max_node=-1;

void dijkstra(int src, int tar){
    int i, j, u, v, w, min_dist, t;
    memset(visit,0x00,sizeof(visit));
    for(i=0; i<MAX_NODE; ++i) dist[i] = INF;
    dist[src] = 0;
    for(j=0; j<max_node; ++j){
        /*I'm lazy to use a heap :P*/
        min_dist = INF;
        for(i=0; i<=max_node; ++i){
            if(!visit[i] && dist[i]<min_dist){
                min_dist = dist[i];
                u = i;
            }
        }
        visit[u] = true;/*Pop u from the pseudo heap.*/
        for(i=0; i<graph[u].usage; ++i){
            v = graph[u].arr[i].first;
            if(!visit[v]){
                w = graph[u].arr[i].second;
                t = dist[u]+w;
                dist[v] = (t<dist[v]?t:dist[v]);
            }
        }
    }
}

int main(void){
    int N, u, v, w, S, T, i, j;
    _PAIR p;
    char input[1000];
    fgets(input,sizeof(input),stdin);
    N = atoi(input);
    while(N--){
        max_node=0;
        for(i=0; i<MAX_NODE; ++i) _init_vec(&graph[i]);
        fgets(input,sizeof(input),stdin);
        edges = atoi(input);
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d %d", &S, &T);
        while(1){
            fgets(input,sizeof(input),stdin);
            if(atoi(input)==-1)break;
            sscanf(input,"%d %d %d", &u, &v, &w);
            max_node = (u>v? (u>max_node?u:max_node):(v>max_node?v:max_node) );
            p.first = v;p.second = w;
            _push_back(&graph[u], p);
        }
        /*
        for(i=0; i<MAX_NODE; ++i){
            for(j=0; j<graph[i].usage; ++j){
                printf("%d %d %d\n", i, graph[i].arr[j].first, graph[i].arr[j].second);
            }
        }*/
        dijkstra(S,T);
        printf("%d\n", dist[T]);
        for(i=0; i<MAX_NODE; ++i) _des_vec(&graph[i]);
    }
    return 0;
}
