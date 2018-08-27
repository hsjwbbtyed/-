//
//  B- tree.h
//  B- Tree
//
//  Created by rmbp on 2018/8/27.
//  Copyright © 2018年 rmbp. All rights reserved.
//
#include "Vector.h"
#include <cstdio>
using namespace std;

#ifndef B__tree_h
#define B__tree_h

#define Posi(T) BTrNode<T>*

template <typename T> struct BTrNode{
    Posi(T) par;
    Vector<T> key;// the vector of values
    Vector< Posi(T) > child;  //the vector of children they are more than key by 1
    
    //constructor  2 kinds
    BTrNode(){ par=NULL; child.push_back(NULL);}
    
    BTrNode( T key, Posi(T) lc=NULL, Posi(T) rc=NULL ){
        par=NULL;
        key.insert(0,key);
        child.insert(0,lc);  child.insert(1,rc);
        if(lc) lc->par=this;  if(rc) rc->par=this;
    }
};


template <typename T>
class BTree {
protected:
    int _size,_order; Posi(T) _root;
    Posi(T) hot;// last position of non-null node be visited with search()
    
    //core section
    void solveOverFlow(Posi(T) );  //to deal with overflow by insert,we split it
    void solveUnderFlow(Posi(T) );//to deal with underflow by remove,we merge it

public:
    BTree(int assign=3): _order(assign),_size(0){ _root=new BTrNode<T>();}//默认起码3阶
    ~BTree(){ if(_root) release(_root);}
    
    Posi(T) search(const T & value);
    bool insert(const T & value);
    bool remove(const T & value);
    int const size() {return _size; }   //keep _size can not be changed in external
    int const order(){return _order; }  //ditto
    Posi(T)& root(){ return _root;}
    bool empty() {return !_root;}
    
};

#endif /* B__tree_h */
