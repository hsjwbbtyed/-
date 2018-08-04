//
//  LeftHeap.h
//  Heap
//
//  Created by rmbp on 2018/8/2.
//  Copyright © 2018年 rmbp. All rights reserved.
//

#ifndef LeftHeap_h
#define LeftHeap_h
struct TreeNode;
typedef struct TreeNode *LefHeap;
LefHeap Init();
int FindMin(LefHeap H);
LefHeap Merge(LefHeap H1,LefHeap H2);

//#define Insert(X,H) (H=Insert1((X),H))
void Insert(int x,LefHeap H);
int DeleteMin(LefHeap H);
LefHeap Insert1(int x,LefHeap H);
LefHeap DeleteMin1(LefHeap H);



#endif /* LeftHeap_h */
struct TreeNode{
    int value;
    LefHeap left;
    LefHeap right;
    int Npl;
};
