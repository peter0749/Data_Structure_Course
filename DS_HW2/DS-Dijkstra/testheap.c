#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_NODE 1000000
#define INF 2000000000

typedef int VEC_TYPE;
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
        v->full<<=1;
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

void _PUSH_HEAP(_VECTOR *heap, VEC_TYPE val){
	int ch, pa;
	ch = heap->usage;
	_push_back(heap,val);
	while(ch>0){
		pa = (ch-1)>>1;
		if(heap->arr[ch] <= heap->arr[pa]){
			_SWAP(&heap->arr[ch], &heap->arr[pa] );
			ch = pa;
		}else break;
	}
}

VEC_TYPE _POP_HEAP(_VECTOR *heap){
	VEC_TYPE temp=-1;
	int ch=0, pa=0;
	if(heap->usage>0){
		temp = heap->arr[0];
		heap->arr[0] = heap->arr[--heap->usage];
		while( (ch=(pa<<1)+1)<heap->usage ){
			if( ch+1<heap->usage && heap->arr[ch] > heap->arr[ch+1] ) ++ch;
			if( heap->arr[pa]>heap->arr[ch]){
				_SWAP(&heap->arr[pa], &heap->arr[ch] );
				pa = ch;
			}else break;
		}
	}
	return temp;
}

_VECTOR heap;

int main(void){
	int i;
	VEC_TYPE fir,sec;
	srand(time(NULL));
	_init_vec(&heap);
	for(i=0; i<MAX_NODE; ++i) _PUSH_HEAP(&heap,rand());
	fir = _POP_HEAP(&heap);
	while(heap.usage){
		//printf("%d\n", fir);
		assert(fir<=(sec=_POP_HEAP(&heap)));
		fir=sec;
	}
	return 0;
}