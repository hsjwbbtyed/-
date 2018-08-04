
#include "avltree.h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


struct AvlNode
{
    int value;
    AvlTree  lc;
    AvlTree  rc;
    int      Height;
};


AvlTree
MakeEmpty( AvlTree T )
{
    if( T != NULL )
    {
        MakeEmpty( T->lc );
        MakeEmpty( T->rc );
        free( T );
    }
    return NULL;
}

static int
Height( Position P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}


void Preorder(Position root);

int main() {
    srand(time(NULL));
    AvlTree a=nullptr;
    int n,v;
    printf("Please input how many nodes in the avl tree: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++) a=Insert(rand()%(n<<1), a);
    Preorder(a);
    printf("\n\nThe height of avlt with %d nodes is : %d\n",n,Height(a));
}

Position
Find( int X, AvlTree T )
{
    if( !T )
        return NULL;
    if( X < T->value ){
        return Find( X, T->lc );
    }
    else
        if( X > T->value )
            return Find( X, T->rc );
        else
            return T;
}

Position
FindMin( AvlTree T )
{
    if( !T )
        return NULL;
    else
        if( T->lc == NULL )
            return T;
        else
            return FindMin( T->lc );
}

Position
FindMax( AvlTree T )
{
    if( T != NULL )
        while( T->rc != NULL )
            T = T->rc;
    
    return T;
}


int max(int a,int b){ return a>b?a:b;}

// This function can be called only if g has a left child
// Perform a rotate between a node (g) and its left child
// Update heights, then return new root

static Position
SingleRotateWithLeft( Position p )   //左-左的情况
{
    Position temp;
    
    temp = p->lc;
    p->lc = temp->rc;
    temp->rc = p;
    
    p->Height = max( Height( p->lc ), Height( p->rc ) ) + 1;
    temp->Height = max( Height( temp->lc ), p->Height ) + 1;
    
    return temp;  /* New root */
}


// This function can be called only if g has a right child
// Perform a rotate between a node (g) and its right child
// Update heights, then return new root

static Position
SingleRotateWithRight( Position g )   //右-右的情况
{
    
    Position temp;
    
    temp = g->rc;
    g->rc = temp->lc;
    temp->lc = g;
    
    g->Height = max( Height( g->lc ), Height( g->rc ) ) + 1;
    temp->Height = max( Height( temp->rc ), g->Height ) + 1;
    
    return temp;  /* New root */
}


// This function can be called only if K3 has a left
// child and K3's left child has a right child
// Do the left-right double rotation
// Update heights, then return new root

static Position
DoubleRotateWithLeft( Position K3 )   //左-右的情况
{
    /* Rotate between K1 and K2 */
    K3->lc = SingleRotateWithRight( K3->lc );
    
    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}

// This function can be called only if g has a right 
// child and g's right child has a left child 
// Do the right-left double rotation 
// Update heights, then return new root 

static Position
DoubleRotateWithRight( Position g )   //右-左的情况
{
    // Rotate between p and v, p means g->rc
    g->rc = SingleRotateWithLeft( g->rc );
    
    // Rotate between g and p
    return SingleRotateWithRight( g );
}


AvlTree
Insert( int X, AvlTree T )
{
    if( !T ){//这里是实质的插入部分，无中生有
        //创建并返回一个单节点树
        T = (Position)malloc( sizeof( struct AvlNode ) );
        if( !T ) printf("Fatal Error: Out Of Space!\n");//错误检测
        else{
            T->value = X;
            T->Height = 0;
            T->lc = T->rc = nullptr;
        }
    }
    
    //还未走到应插入的地点时
    else
        if( X < T->value ) //遵循BST的规则，new value < root value，往左走
        {
            T->lc = Insert( X, T->lc );//此时插入完成后，t指向被插入节点的父亲
            if( Height(T->lc)-Height(T->rc) == 2 )
                 //如果新插入节点后lc比rc深2层，那么就是情形1，2
                if( X < T->lc->value )//如果是这样，根据BST规则，是左-左
                    T = SingleRotateWithLeft( T );
                else //否则是左-右
                    T = DoubleRotateWithLeft( T );
         /*
          我们需要根据情况去采取不同的旋转策略，使其恢复平衡
          单旋转调整了情形1:发生在外侧，对a的lc->lc插入
          双旋转调整了情形2:发生在内侧，对a的lc->rc插入
          */

        }
        else
            if( X > T->value )
            {
                T->rc = Insert( X, T->rc );
                //遵循BST的规则，new value > root value，往右走
                
                if( Height(T->rc)-Height(T->lc) == 2 )
                    //如果新插入节点后右子树更高，那么就是情形3，4
                    if( X > T->rc->value )  //如果是这样，根据BST规则，是右-右
                        T = SingleRotateWithRight( T );
                    else //否则是右-左
                        T = DoubleRotateWithRight( T );
                /*
                 这个分支里
                 单旋转调整了情形3:发生在外侧，对a的rc->rc插入
                 双旋转调整了情形4:发生在内侧，对a的rc->lc插入
                */
            }
    
    /* Else X is in the tree already; we'll do nothing */
    
    T->Height = max( Height( T->lc ), Height( T->rc ) ) + 1;
    return T;
}


int
Retrieve( Position P )
{
    return P->value;
}




void Preorder(Position root){
    if (root) {
        printf("%d ",root->value);
        Preorder(root->lc);
        Preorder(root->rc);
    }
    
}


