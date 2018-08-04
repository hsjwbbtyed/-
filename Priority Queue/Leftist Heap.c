//
//  Leftist heap.c
//  Heap
//
//  Created by rmbp on 2018/8/2.
//  Copyright © 2018年 rmbp. All rights reserved.
//

#include "LeftHeap.h"
#include <stdio.h>
#include <stdlib.h>

void swap(LefHeap h1,LefHeap h2){
    LefHeap temp=h1;
    h1=h2;
    h2=temp;
}
static LefHeap Merge1(LefHeap H1,LefHeap H2);
void SwapChildren(LefHeap H1){
    swap(H1->left, H1->right);
}

LefHeap Merge(LefHeap a,LefHeap b){
    //递归基
    if(!a)
        return b;
    if (!b)
        return a;
    /*执行到这一句之后就说明两个堆都不为空,此时我们要比较两个根节点在数值上的大小，如果有必要应将二者互换名称。从而保证在数值上a总是不小于b，以便在后续递归的过程中将b作为a的后代。
     */
    if (a->value < b->value)
        swap(a, b);  //一般情况下首先确保a更大,然后执行合并
    a->right=Merge(a->right, b);
    //之后我们要保证a的左倾性：
    if(!a->left || a->left->Npl < a->right->Npl)
        //如果有必要，我们就交换a的左右子堆，以确保右子堆的npl更小
        SwapChildren(a);
    
    //然后更新a的npl
    a->Npl=a->right->Npl+1;
    return a;//返回合并后的堆顶
}

void Insert(int x,LefHeap H){
    LefHeap fresh;
    fresh=malloc(sizeof(struct TreeNode));
    fresh->value=x;
    fresh->Npl=0;
    fresh->left=fresh->right=NULL;
    H=Merge(fresh, H);
}

int DeleteMin(LefHeap H){
    LefHeap l=H->left;
    LefHeap r=H->right;
    int t=H->value;//前三句都是铺垫，对相关的数据作备份而已。
    free(H);//根节点的物理摘除由这一句来完成。
    //此后只需将此时被隔离开的左子堆与右子堆重新地合并起来。
    H=Merge(l, r);
    return t;
}
int main(){
    
}
