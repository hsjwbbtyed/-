//实际上大部分都是C代码，只是用到了C++的特性，层序遍历需要用队列
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <queue>
#include "BinTree.h"
using namespace std;
//Entrance
int main(){
    int n;
    srand(time(NULL));
    printf("Could you tell me each number in the tree?(0 to complete)\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        root=Insert(root, rand()%9990);
    printf("\n\n");
    DisplayInfo(root);
    printf("\n\nThe heighth of a bst have %d nodes is : %d\n\n",n,Height(root));
    printf("Which guys will be pushed?\n"); scanf("%d",&n);
    root=Insert(root, n); DisplayInfo(root);
    printf("Which value do you desire to remove?\n");  scanf("%d",&n);
    root=Delete(n, root);
    DisplayInfo(root);  printf("\n");
}


//接口内部一览
SearchTree MakeEmpty(SearchTree T){
    if (T){
        MakeEmpty(T->lc);
        MakeEmpty(T->rc);
        free(T);
    }
    return NULL;
}


Position Find(int X,SearchTree T){
    if(T == NULL) return NULL;      //如果走到叶子还没找到，返回空
    if (X < T->Value)  return Find(X, T->lc); //如果给定值比根小，往左边找
    else if(X > T->Value) return Find(X , T->rc);//比根大就往右找
    else return T;  //这种情况就是某时X==T->Value，正好命中的情况
}

Position FindMin(SearchTree T){
    if(T == NULL) return NULL;         //同上
    else if (T->lc==NULL) return  T;   //左子树空，意味着没有比它更小的值了，直接返回地址
    else return FindMin(T->lc); //如果上面两个情况都不符合，接着往左找
}

void DisplayInfo(SearchTree t){
    printf("\nCurrently\nPre-order is :");
    PreOrder(t);   printf("\n");
    printf("In-order is :");
    InOrder(t);    printf("\n");
    printf("Level-order is :");
    LevelOrder(t); printf("\n");
    printf("Height is %d\n",Height(root));
    printf("The min is: %d\n",FindMin(root)->Value);
    printf("The max is: %d\n",FindMax(root)->Value);
}

int Height(SearchTree T){
    //这两句都是根据定义得出的
    if(!T) return -1;
    else return 1+max(Height(T->lc), Height(T->rc));
}
SearchTree FindMinByLoop(SearchTree T) {
    if(T)
        while (T->lc)
            T=T->lc;
    return  T;
}

Position FindMax(SearchTree T) {
    if (T!=NULL)         //没有走到叶结点时寻找
        while (T->rc!=NULL)    //右边还有子树时一直往右走
            T=T->rc;
    return T;             //这个return包含了两种情形，如果传入的是叶子，自动返回NULL，如果找到最右边了，返回对应地址
}

SearchTree Insert(SearchTree T,int X) {
    if(!T){             //这是应对初始情况,空树
        T=(SearchTree)malloc(sizeof(struct BinNode));
        T->Value=X;
        T->lc=T->rc=NULL;  //底部封口
    }
    //在一棵现成的树里插入，二分查找
    else if (X < T->Value) T->lc=Insert(T->lc, X);
    else if (X > T->Value) T->rc=Insert(T->rc, X);
    //X==T->Value的情况什么也不用做
    return T;
}
SearchTree Delete(int X,SearchTree T) {
    Position TempCell;
    if (T==NULL)
        printf("Element not found\n");
    //search for Value
    
    else if(X<T->Value) T->lc=Delete(X, T->lc);
    else if(X>T->Value) T->rc=Delete(X, T->rc);
    //找到给定的X了，开始分类讨论
    else if(T->lc && T->rc){   //有两个儿子的情况
        TempCell=FindMin(T->rc);     //找到右子树下最小的数据
        T->Value=TempCell->Value;   //Replace
        T->rc=Delete(T->Value, T->rc);  //递归删除
    }
    else{       //1个儿子or叶子的情况,可以统一起来，操作逻辑是一致的
        TempCell=T;
        if (T->lc==NULL)       //只有右孩子，就把父节点直接连到右边
            T=T->rc;
        else if (T->rc==NULL){   //只有左孩子，就把父节点直接连到左边
            T=T->lc;
        }
        free(TempCell);
    }
    return T;
}


void PreOrder(SearchTree T) {
    if(T){                  //如果这颗子树非空，就打印，否则把控制权还给上级
        printf("%d ",T->Value);
        PreOrder(T->lc);
        PreOrder(T->rc);
    }
}

void InOrder(SearchTree T){
    if(T){
        InOrder(T->lc);
        printf("%d ",T->Value);
        InOrder(T->rc);
    }
}

void LevelOrder(SearchTree r) {
    SearchTree current=r;     //为了不修改根节点，新建一个指针作为光标
    queue<SearchTree> q;
    q.push(current);        //把当前（根）节点入队
    //以下是广搜的核心
    while (!q.empty()) {        //队列非空时进行遍历
        current=q.front();
        printf("%d ",current->Value);
        q.pop();            //打印完则出队
        if (current->lc)            //依次查看当前节点是否有后继，有的话重复上述入队过程，left,right or both
            q.push(current->lc);
        if (current->rc)
            q.push(current->rc);
    }
}
