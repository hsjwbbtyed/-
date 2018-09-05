#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "RB Tree.h"

Position
FindMin( RedBlackTree T ) //返回值指向以T为根的树上最小元，同时也是T的直接后继
{
    T = T->right;
    while( T->left != NullNode )
        T = T->left;
    
    return T;
}

static void DoPrint(RedBlackTree T){
    if (T != NullNode) {
        DoPrint(T->left);
        printf("%d ",T->value);
        DoPrint(T->right);
    }
}

void Display(RedBlackTree T){
    DoPrint(T->right);
    printf("\n");
}

RedBlackTree Initialize()
{
    RedBlackTree T;
    if (NullNode == NULL) { //如果NullNode不存在，就让它成为一个空闲仓库，并且保证合乎红黑树规则
        NullNode=(Position)malloc(sizeof(struct RedBlackNode));
        NullNode->left=NullNode->right=NullNode;
        NullNode->col=black;
        NullNode->value=Infinity;
    }
    
    //Create the header node
    T=(Position)malloc(sizeof(struct RedBlackNode));
    T->value=NegINF;
    T->left=T->right=NullNode;
    T->col=black;
    
    return T;
}

//在X处执行旋转
static Position
Rotate(int Item,Position par)
{
    if (Item < par->value)
        return par->left = Item < par->left->value ?
        SingleRotateWithLeft(par->left) :
        SingleRotateWithRight(par->left);
    
    else
        return par->right = Item < par->right->value ?
        SingleRotateWithLeft(par->right) :
        SingleRotateWithRight(par->right);
}


//双红修复
static Position X,P,GP,GGP;

void
HandleReorient(int Item,RedBlackTree T)
{
    X->col=red;  //默认染红，下面孩子还是得遵守规则，保证是黑
    X->left->col=black;
    X->right->col=black;
    
    if (P->col == red) {  //引发双红缺陷
        GP->col=red;
        if ((Item < GP->value) != (Item < P->value)) //两者异或为真，意味着是之字形，要在父节点多做一次旋转，否则以曾祖父为轴做单旋转
            P = Rotate(Item, GP);
        X = Rotate(Item, GGP);
        X->col=black;
    }
    T->right->col=black; //让新根染黑
}

RedBlackTree
Insert(int Item,RedBlackTree T)
{
    X=P=GP=T;
    NullNode->value=Item;  //此时经过初始化，NullNode已经是一个空闲节点，存入指定的数值
    while (X->value != Item)    //自树根拾级而下，扫除一切uncle为红的情况

    {
        GGP=GP; GP=P; P=X;
        if(Item < X->value )
            X=X->left;
        else
            X=X->right;
        //节点的两个孩子都是红色，转换成B树意味着内部节点上溢，如图M，N，需要进行修复
        if( X->left->col == red && X->right->col == red )
            HandleReorient(Item, T);
    }
    //走到这一步时，X->value已经是期望的Item了
    if(X != NullNode)
        return NullNode; //重复
    
    //否则就创建新的节点接入
    X=(Position)malloc(sizeof(struct RedBlackNode));
    X->value=Item;
    X->left = X->right = NullNode;
    
    if(Item < P->value)
        P->left=X;
    else
        P->right=X;
    HandleReorient(Item, T);
    
    return T;
}

//删除部分
//------------------------------------------------------------------------------------------------------------------------------------------------

Position p=NULL;  //被查找元素的父亲



Position SearchIn(Position v,int e,Position& parent){
    if (!v || (e == v->value)) return v; //递归基，如果直接命中或不存在则返回
    parent=v; //一般情况则是先记下当前节点,然后深入一层。
    return SearchIn((e < v->value ? v->left : v->right), e, parent);
}//返回值指向命中节点，parent为其父。

Position Search(int target,RedBlackTree T){
    return SearchIn(T, target, p);
}

Position GetPar(int e){
    Search(e, fir);
    return p;
}

Position GetParentOf(Position T){
    Search(T->value, fir);
    return p;
}
//

Position removeAt(Position x){
    Position temp;
    if (x->left && x->right) {
        temp=FindMin(x->right);
        x->value=temp->value;
        x->right=removeAt(x->right);
    }
    else{
        temp=x;
        if(!x->left) x=x->right;
        else if (!x->right) x=x->left;
        free(temp);
    }
    return x;
}//返回被删除节点的位置

//------------------------------------------------------------------------------------------------------------------------------------------------




int main(){
    int cnt;
    printf("please input cnt of rbt\n");
    RedBlackTree t;
    t=Initialize();
    scanf("%d",&cnt);
    for (int i=0; i<cnt; i++) {
        t=Insert(i+5, t);
    }
    Display(t);
}
