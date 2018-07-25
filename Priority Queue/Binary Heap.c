#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//以小根堆为例

#define MinData (-2)
typedef struct HeapStruct *PriorityQueue;

void swap(int *a,int *b) {
    int t=*a;
    *a=*b;
    *b=t;
}


struct HeapStruct {
    int capacity; //总空间
    int size;     //所有实际元素的大小
    int *Element;
};

PriorityQueue Init(int maxValue){
    PriorityQueue H;
    H=(PriorityQueue)malloc(sizeof(HeapStruct));
    
    H->Element=(int*)malloc((maxValue+1)*sizeof(int));//保持一定冗余
    H->capacity=maxValue;
    H->size=0;
    H->Element[0]=MinData;
    
    return H;
}


void Insert(int X,PriorityQueue H) {
    int i;
    
    //进行上滤
    for (i=++(H->size); H->Element[i/2]>X; i/=2) {
        //取CBT的下一个空闲位置，如果满足heap order则进行插入，否则和父节点交换数值
        H->Element[i]=H->Element[i/2];
    }
    H->Element[i]=X;
}


int Delete(PriorityQueue H){
    int i,child;
    int MinElement,last;
    
    MinElement=H->Element[1];//取出树根的值，根据heap order它是最小元素
    last=H->Element[H->size--];//取出末尾元素以便后续安置
    
    //执行下滤，搜索每个膝下有子的父节点
    //具体做法是：把last放在沿着从根开始包含最小儿子的一条路径的某个恰当位置，这是步进条件的由来
    for (i=1; i*2<=H->size; i=child) {
        //首先确定下滤的孩子索引（找到更小的那个）
        child=i<<1;//先取左孩子
        if (child!=H->size && H->Element[child+1] < H->Element[child])
            child++;
        
        //然后下滤一层
        if (last > H->Element[child])
            H->Element[i]=H->Element[child];
        else
            break;
    }
    H->Element[i]=last;//把最后一个元素放在合适的空穴里
    return MinElement;
}

void PercolateDown(int *a,int root,int size) {
    int l,r,min;
    l=root<<1;
    r=(root<<1)+1;
    //找到局部子树最小值的索引
    if (l<=size && a[l]>a[root] ) min=root;//先比较lChild & root
    else min=l;
    
    if (r<size && a[r]<a[min]) min=r;
    
    if(min!=root){ //相等时意味已经满足最小堆的性质
        swap(&a[root],&a[min]);//执行下滤
        PercolateDown(a,min,size);//继续处理下一棵树
    }
    
}

void Display(PriorityQueue H){
    for(int i=0;i<=H->size;i++)
        printf("%d ",H->Element[i]);
    printf("\n");
}

void BuildHeap(int N,PriorityQueue H) {
    for(int i=N/2;i>0;i--)
        PercolateDown(H->Element, i, H->size);
}

int main(){
    srand(time(nullptr));
    int n;
    scanf("%d",&n);
    PriorityQueue pq=Init(n);
    for(int i=0;i<n;i++) Insert(rand()%n+5, pq);
    BuildHeap(n, pq);
    Display(pq);
    printf("The min is %d\n",Delete(pq));
}
