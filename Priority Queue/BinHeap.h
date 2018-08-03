#ifndef BinHeap_h
#define BinHeap_h
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;
PriorityQueue Init(int maxValue);
void Insert(int X,PriorityQueue H);
int Delete(PriorityQueue H);
void PercolateDown(int *a,int root,int size);
void Display(PriorityQueue H);
void BuildHeap(int N,PriorityQueue H);

#endif /* BinHeap_h */


struct HeapStruct {
    int capacity; //总空间
    int size;     //所有实际元素的大小
    int *Element;
};
