#include <cstdio>
#include <cstdlib>
struct Node;                //先声明一个节点，下面给出定义
typedef struct Node *PtrToNode;     /*声明节点指针，并且将其类型替换为PtrToNode（替换之前是struct Node*），这样做的目的是方便我们理解*/


typedef PtrToNode List; //将struct Node*再次替换为List（表），进一步直观化
typedef PtrToNode Position;//将struct Node*再次替换为Position(位置）

struct Node{
    int data;
    Position Next;
};


int IsEmpty(List L){
         return L->Next==NULL;//在最后一个单元里，后面是封口的，也就是指针域是NULL
}



//如果P是在表中的末尾位置，返回1
int IsLast(Position P) {
    return P->Next==NULL;
}



Position FindPrevious(int X,List L){
    Position P;                 //声明一个节点指针，并指向头节点（和表头一样）
    P=L;
   while (P!=NULL && P->Next->data!=X) { //P没有走到末尾，同时还没找到给定的X时
        P=P->Next;                  //P向后走
    }           //走到这一步时，说明要么没找到，P=NULL（结尾处），要么找到了，P=前驱的位置
    return P;
}




Position Find(int X,List L) {
    Position P;
    P=L->Next;      //和上面对比一下，区别在哪？
    while (P!=NULL && X!=P->data) {
        P=P->Next;
    }
    return P;
}



void Delete(int X,List L) {
    Position P,Temp;        //申请两个节点，一个用作拉住前驱，一个用作临时变量
    P=FindPrevious(X, L);   //用P拉住X的前驱
    if (!IsLast(P)) {       //确定P不是末尾，否则没法删除（末尾后面什么也没有）
        Temp=P->Next;       //用临时指针拉住当前位置，以便后面直接越过这个节点
        P->Next=Temp->Next; //当前节点的前驱直接指向后继，绕过了当前节点
        free(Temp);         //释放当前节点内存
        Temp->Next=NULL;    //将当前节点的指针“收回来”，脑补一下飞机起落架。
    }
}

void InsertBefore(int X,Position P){
    Position NewNode;            //用一个临时变量，用以“拴住”新单元
    NewNode=(List)malloc(sizeof(struct Node));  //申请内存，List相当于struct Node*
    NewNode->data=X;              //将数据填入新单元
    NewNode->Next=P->Next;        //与后方单元相连
    P->Next=NewNode;              //与前方单元相连，这两行顺序不能反，原因…你们试试就知道了
}





void PushBack(int X,Position P) {
    Position NewNode;       //声明一个新的节点指针
    NewNode=(Position)malloc(sizeof(struct Node));//分配内存
    NewNode->Next=NULL;     //新节点指针域封闭
    NewNode->data=X;        //数据装填
    while(!IsLast(P))       //通过循环走到整个链表的末尾
        P=P->Next;
    P->Next=NewNode;        //将新节点的地址交给原链表末尾，从尾部链接。
}


void Traverse(List L){
    while (L->Next!=NULL) {
        printf("%d ",L->Next->data);
        L=L->Next;
    }
    printf("\n");
}


int main(){
    int i;
    List L=(List)malloc(sizeof(struct Node));
    L->Next=NULL;
    printf("Input amount of lists\n");
    scanf("%d",&i);
    
    while (i--) {
        int n;
        scanf("%d",&n);
        PushBack(n, L);
    }
    Traverse(L);
    printf("Which item would you like to remove?\n");
    scanf("%d",&i);
    Delete(i, L);
    printf("\n");
    printf("The current linked lists are : ");
    Traverse(L);
}
