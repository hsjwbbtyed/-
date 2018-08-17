#ifndef Splay_h
#define Splay_h
struct SplayNode;
typedef struct SplayNode *SplayTree;
typedef struct SplayNode *Position;
SplayTree FindIn(int x,SplayTree T);
SplayTree Splaying(int Item,Position X);
SplayTree Insert(int Item,SplayTree T);
SplayTree Remove(int Item,SplayTree T);
SplayTree FindMin(SplayTree T);
Position FindMax(SplayTree T);
int Retrieve(SplayTree T);
#endif /* Splay_h */


struct SplayNode{
    int value;
    SplayTree left;
    SplayTree right;
};

static Position SingleRotateWithLeft(Position p){//zig
    Position temp=p->left;
    p->left=temp->right;
    temp->right=p;
    return temp;
    
}//zig


static Position SingleRotateWithRight(Position g){
    Position temp=g->right;
    g->right=temp->left;
    temp->left=g;
    return temp;
}//zag
