//
//  Splay Tree.c
//  Splay Tree
//
//  
//  Copyright © 2018年 rmbp. All rights reserved.
//

#include "Splay.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static Position Origin=NULL;


SplayTree Init(){
    if (!Origin) {   //When the tree we talked about is non-exsitent.
        Origin=(SplayTree)malloc(sizeof(struct SplayNode));
        Origin->left=Origin->right=NULL;
    }
    return Origin;
}

SplayTree FindMin(SplayTree T) {
    if(T){
        while (T->left)
            T=T->left;
    }
    return  T;
}

int Retrieve(SplayTree T){
    return T->value;
}

Position Find(int x,SplayTree T){
    Position p=FindIn(x, T);
    T=Splaying(x, p);
    return T;
}


Position FindIn(int x,SplayTree T){
    if(T == NULL) return NULL;      //如果走到叶子还没找到，返回空
    if (x < T->value)  return FindIn(x, T->left); //如果给定值比根小，往左边找
    else if(x > T->value) return FindIn(x , T->right);//比根大就往右找
    else return T;  //这种情况就是某时X==T->Value，正好命中的情况
}


Position FindMax(SplayTree T) {
    if (T){
        while (T->right)
            T=T->right;
    }
    return T;
}


//Top-down splay procedure,not requiring Item to be in the tree
SplayTree Splaying(int Item,Position X) {
    static struct SplayNode Header;
    Position LeftMax,RightMin;
    
    Header.left=Header.right=Origin;
    LeftMax=RightMin=&Header;
    Origin->value=Item;
    
    while (Item != X->value) {
        if (Item < X->value) {
            if (Item < X->left->value) {
                X=SingleRotateWithLeft(X);
            }
            if(X->left==Origin)
                break;
            //Link right
            RightMin->left=X;
            RightMin=X;
            X=X->left;
        }
        else{
            if(Item > X->right->value)
                X=SingleRotateWithRight(X);
            if(X->right==Origin)
                break;
            //Link left
            LeftMax->right=X;
            LeftMax=X;
            X=X->right;
        }
    }//while Item != X->value
    
    //Reassemble
    LeftMax->right=X->left;
    RightMin->left=X->right;
    X->left=Header.right;
    X->right=Header.left;
    
    return X;
}

SplayTree Insert(int Item,SplayTree T) {
    //T means original root
    static Position NewNode=NULL;
    if (!NewNode)
    {
        NewNode=malloc(sizeof(struct SplayNode));
    }
    NewNode->value=Item;
    
    if (T==Origin)
    {
        NewNode->left=NewNode->right=NULL;
        T=NewNode;
    }
    else
    {
        T=Splaying(Item, T);
        if (T->value > Item)
        {
            //look at left subtree
            NewNode->left=T->left;
            NewNode->right=T;
            T->left=Origin;
            T=NewNode;  //make inserted element as root of tree
        }
        else if(T->value < Item)
        {
            //look at right subtree
            NewNode->right=T->right;
            NewNode->left=T;
            T->right=Origin;
            T=NewNode;   //make inserted element as root of tree
        }
        else return T; //Already in the tree,we do nothing.
        
    }
    
    NewNode=NULL;
//  it given convince for the next insert,then next insert will call malloc straightly
    
    return T;  //always make the parameter T act as the root be returned

}

SplayTree Remove(int Item,SplayTree T){
    Position NewTree;  //
    if (T) {
        T=Splaying(Item, T);
        if (Item==T->value) {
            //primarily we find it
            if(!T->left)
                NewTree=T->right;
            else{
                NewTree=T->left;
                NewTree=Splaying(Item, NewTree);
                NewTree->right=T->right;
            }
            free(T);
            T=NewTree;
        }
    }
    
    return T;
}



int main(int argc, const char * argv[]) {
    
    
}
