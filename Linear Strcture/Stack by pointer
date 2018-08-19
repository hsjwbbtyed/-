#include <stdio.h>
#include <stdlib.h>
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
struct Node{
    int Element;
    PtrToNode Next;
};
//函数签名
int IsEmpty(Stack i);
void Push(int X,Stack S);
int Top(Stack S);
void Pop(Stack S);
void MakeEmpty(Stack S);
Stack Creat();
void Traverse(Stack S);

//入口
int main(){
    Stack S;
    S=Creat();
    int n;
    printf("Please input all elements to complete a stack,finished by 0\n");
    while (scanf("%d",&n)&&n)
        Push(n, S);
    Traverse(S);
    printf("Input imperative(1:top\t2:remove\t3:add),0 to quit\n");
    while (scanf("%d",&n)&&n) {
        if (n==1)
            printf("Top element:%d\n",Top(S));
        else if(n==2){
            Pop(S);
            Traverse(S);
        }
        else if(n==3){
            printf("number:");
            scanf("%d",&n);
            Push(n, S);
            Traverse(S);
        }
        else
            printf("Input again,it is invalid");
    }
}

//接口内部一览
int IsEmpty(Stack i){
    return i->Next==NULL;
}
void Push(int X,Stack S){
    Stack TemCell;
    TemCell=(Stack)malloc(sizeof(S));
    if(S==NULL) printf("Out of space!!!");
    else{
        TemCell->Element=X;
        TemCell->Next=S->Next;
        S->Next=TemCell;
    }
}

int Top(Stack S){
    if(!IsEmpty(S))
        return S->Next->Element;
    printf("Empty stack");
    return 0;
}

void Pop(Stack S) {
    PtrToNode FirstNode;
    if(IsEmpty(S))
        printf("Empty stack");
    else{
        FirstNode=S->Next;
        S->Next=S->Next->Next;
        free(FirstNode);
    }
}
void MakeEmpty(Stack S){
    if(S==NULL)
        printf("Must creat a stack first");
    else
        while(!IsEmpty(S))
            Pop(S);
}
Stack Creat(){
    Stack S;
    S=(Stack)malloc(sizeof(struct Node));
    if(S==NULL)
        printf("out of space!!!");
    else
        S->Next=NULL;
    MakeEmpty(S);
    return S;
}
void Traverse(Stack S){
    for (; S->Next; S=S->Next) {
        printf("%d->",S->Next->Element);
    }
    printf("NULL\n");
}
