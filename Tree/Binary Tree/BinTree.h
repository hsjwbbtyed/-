#ifndef BinTree_h
#define BinTree_h




struct BinNode;
typedef struct BinNode *SearchTree;
typedef struct BinNode *Position;
struct BinNode{
    int Value;
    SearchTree lc,rc;
    int height;
};

SearchTree root=NULL;


// Function signature
SearchTree Insert(SearchTree T,int X);
SearchTree Delete(int X,SearchTree T);
int Height(SearchTree T);
void PreOrder(SearchTree T);
void InOrder(SearchTree T);
void LevelOrder(SearchTree T);
void DisplayInfo(SearchTree t);
Position FindMax(SearchTree T);
Position FindMix(SearchTree T);


#endif /* BinTree_h */
