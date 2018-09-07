#include <cstdio>

typedef int PtrToNode;       //因为现在不需要把数据和指针绑定，所以不再是结构体,而是数组下标

typedef PtrToNode List;

typedef PtrToNode Position

#define SpaceSize 100

struct Node{
    
    int value;
    
    Position Next;
    
};


struct Node CursorSpace[SpaceSize]; //cursor LL 的基地


//操作接口
void Initial();
int IsLast(Position P) ;
static Position CursorAlloc();
void CursorFree(Position P);
Position Insert(int X,Position P);
Position Find(int X,List L);
Position FindPrevious(int X,List L);
void Delete(int X , List L);
void Traverse(List L);




int main(){
    int i;
    Initial();
    List L=CursorAlloc();
    List t=L;
    printf("Input amount of lists\n");
    scanf("%d",&i);
    
    while (i--) {
        int n;
        scanf("%d",&n);
        t=Insert(n, t);
    }
    Traverse(L);
    printf("Which item would you like to remove?\n");
    scanf("%d",&i);
    Delete(i, L);
    printf("\n");
    printf("The current linked lists are : ");
    Traverse(L);
}



//具体实现

void Initial(){
    
    int i;
    for (i=0; i<SpaceSize-1; i++)   //遍历每一个单元
        
        CursorSpace[i].Next=i+1;    //依次对next升序编号
    
    CursorSpace[0].value=0;       //初始元素置空
    
    CursorSpace[SpaceSize-1].Next=0;//把最后一个单元的next设为0，就类似指针链表的尾指针是NULL
    
}

int IsLast(Position P) {
    
    return CursorSpace[P].Next==0;
    
}

static Position CursorAlloc(){
    
    Position P;
    
    P=CursorSpace[0].Next;     //先从next的第0个单元获取一个数，这个数是第P个单元的地址
    
    CursorSpace[0].Next=CursorSpace[P].Next;
    //cursor 0后面本来接的是cursor P，但现在第P个单元被申请走了，所以顺接到P后面的位置。
    
    return P;
    
}

Position Insert(int X,Position P){//P是插入前的末尾节点
    
    Position TempCell;
    
    TempCell=CursorAlloc(); //申请一块新内存
    
    if(!TempCell)
        printf("Out of space!");
    
    CursorSpace[TempCell].value=X;
    
   CursorSpace[TempCell].Next=0;
    
    CursorSpace[P].Next=TempCell;
    
    return TempCell;
}



void CursorFree(Position P){
         CursorSpace[P].Next=CursorSpace[0].Next;//cursor P后面接上原本是cursor 0所指的下一个
         CursorSpace[0].Next=P; //cursor 0后面接上被删除的P，相当于返还给操作系统。
}

int IsEmpty(List L) {
    
    return CursorSpace[L].Next==0;
    
}




Position Find(int X,List L) {
    
    Position P;
    
    P=CursorSpace[L].Next;
    
    while(P && CursorSpace[L].value!=X)   //当后续的表还存在，并且还未找到给定的X时
        
        P=CursorSpace[P].Next;     //向后迭代，并逐个比对元素
    
    return P;       //返回X在L中的位置，当没有找到时，返回0
    
}



Position FindPrevious(int X,List L){
    
    Position P;
    
    P=L;
    
    while (P && CursorSpace[CursorSpace[P].Next].value!=X) { //P没有走到末尾，同时还没找到给定的X时
        
        P=CursorSpace[P].Next; //P向后走
        
    }//走到这一步时，说明要么没找到，P=NULL（结尾处），要么找到了，P=前驱的位置
    
    return P;
    
}

void Delete(int X , List L){
    
    Position P,TempCell;
    
    P=FindPrevious(X, L);
    
    if (!IsLast(P)) {
        
        TempCell=CursorSpace[P].Next;
        
        CursorSpace[P].Next=CursorSpace[TempCell].Next;//相当于P->Next=P->Next->Next
        
        CursorFree(TempCell);
        
    }
    
}




void Traverse(List L){
    Position truth=CursorSpace[L].Next;//从表头后的“第一个实际元素”开始打印
    while (!IsLast(truth)){
        printf("%d ",CursorSpace[truth].value);
        truth=CursorSpace[truth].Next;
    }
    printf("%d ",CursorSpace[truth].value);
    printf("\n");
}
