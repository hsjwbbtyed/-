#include "Vector.h"
#include "B- tree.h"
#include <cstdio>
using namespace std;


template <typename T>
Posi(T) BTree<T>::search(const T & e) {
    Posi(T) cur = _root;  hot = NULL;  //start with root
    while ( cur ) {
        Rank r = cur -> key.search(e);  //顺序查找
        if(r >= 0 &&  e == cur -> key[r]) return cur; //如果成功则返回当前引用
        hot = cur; cur = cur -> child[r+1];//更新hot,转到下一层子树，把根载入内存
    }//走到这里时 !cur为真，说明抵达外部节点
    return NULL;
}

template <typename T>
bool BTree<T>::insert(const T & e){
    Posi(T)  t = search(e);//search in B- Tree
    if(t) return false;  //If target is in the tree,we do nothing.
    
    Rank r = hot->key.search(e);//在hot中确定插入位置,hot指向的是一个叶节点。search in vector
    hot->key.insert(r+1,e);//把目标关键码放在向量对应位置
    hot->child.insert(r+2,NULL);//创建一个空子树指针,视作右侧分支
    _size++;
    solveOverFlow(hot);//如果发生overflow要进行一次分裂
    return true;
}

template <typename T>
void BTree<T>::solveOverFlow(Posi(T) current){
    if(_order >= current->child.size()) return ;  //判断当前节点是否上溢，无则返回
    Rank mid=_order/2; //pivot, we have _order=key.size()=child.size()-1 now
    Posi(T) right=new BTrNode<T>(); // r will have had a null child
    
    for (int i=0; i<_order-mid-1; i++) {//当前右侧的_order-s-1个孩子和关键码分裂为右侧节点right(以下简称r)
        right->child.insert(i, current->child.remove(mid+1));
        right->key.insert(i,current->key.remove(mid+1));
    }
    right->child[_order-mid-1] =current->child.remove(mid+1);//移动当前最靠右的孩子
    
    if(right->child[0])//如果right的孩子非空
        for(int i=0;i< _order-mid;i++)
            right->child[i]->parent=right;  //令他们的父节点统一指向自己,因为下面的都是外部节点了
    Posi(T) p=current->par;
    if(!p) {  //这时候cur已经是根了，就执行对根分裂的步骤
        _root=p=new BTrNode<T>();
        p->child[0]=current;
        current->par=p;
    }
    Rank r=1+p->key.search(current->key[0]);//r获取到p中 指向u的指针的序号
    p->key.insert(r,current->key.remove(mid));//pivot关键码上升
    p->child.insert(r+1,right);
    right->par=p;        //新节点r与父节点p互联
    solveOverFlow(p);//视角上升一层，有必要就继续分裂，最多递归O（logn）层，判断放在递归基里
    
}

template <typename T>
bool BTree<T>::remove(const T & e){
    Posi(T) target = search(e);
    if(!target) return false;// confirm the e is in the tree
    Rank rk_e = target -> key.search(e); //gain the rank of e  in target node
    if( target -> child[0] ) { //if target is not a leaf
        Posi(T) right = target -> child[rk_e+1];//在右子树中一直向左即可
        while ( right -> child[0] )
            right = right -> child[0];//we find successor of e, it must belong a leaf
        target -> key[rk_e] = right -> key[0];
        target = right;
        rk_e = 0;// swap position of  target and e's successor
    }//In this time, v must in the bottom of B- Tree,and the r th key is it which we demand to delete
    target -> key.remove(rk_e);
    target -> child.remove(rk_e+1);
    _size--;
    solveUnderFlow(target);//如果有必要就旋转 or 合并
    return true;
}

template <typename T>
void BTree<T>::solveUnderFlow(Posi(T) v){
    if( (_order + 1 )>>1  <= v->child.size()) return;   //当前节点没有发生下溢
    Posi(T) p = v -> par;
    if (!p) {  //到达根节点
        if (!v->key.size() && v -> child[0]) { //如果v已经不含有关键码，但有唯一的非空child时
            _root = v -> child[0]; _root -> par = NULL;//这个节点被跳过
            v -> child[0] = NULL; delete v;  //然后销毁
        }//树高-1
        return;
    }
    Rank r=0;
    while (p->child[r] !=v) r++; //确定v是p的第几个孩子，记作r
    
    //COND 1 向左借元素
    if ( r > 0) {  //保证v不是p的第一个孩子
        Posi(T) ls = p -> child[r-1] ;//那左边一定有元素，是为左兄弟（left sibling），简称ls
        if( (_order + 1)>>1  < ls->child.size() ){//如果这个兄弟家有余粮的话
            v -> key.insert( 0 , p -> key[r-1] ); //v的父亲借出一个关键码作为v的min
            p -> key[r-1] = ls->key.remove( ls->key.size()-1 ); //ls的最大值补充给p
            v -> child.insert( 0, ls->child.remove(ls->child.size() - 1 ) );
            if( v->child[0] ) v->child[0]->par =v;//最后两步调整对应的指针
            return ; //右旋完成
        }
    } //至此左兄弟或者为空，或者不能再借了
    
    
    // COND 2 向右借元素
    if (p -> child.size() -1 > r ) {  //如果v并非p的最后一个孩子
        Posi(T) rs = p->child[r+1]; //右边一定有元素
        if ((_order + 1)>>1  < rs->child.size()) {
            v -> key.insert( v->key.size() , p -> key[r] );
            p -> key[r] = rs->key.remove(0);
            v -> child.insert( v->child.size() , rs->child.remove(0) );
            if( v->child[v->child.size()-1] ) //v->child.size()-1是末尾下标
                v->child[v->child.size()-1]->par =v;//最后两步调整对应的指针
            return; //左旋完成
        }
    }//至此右兄弟或者为空，或者不能再借了
    
    
    // COND 3 需要合并
    if (0 < r) {  //与左兄弟合并
        Posi(T) ls = p -> child[r-1];
        ls->key.insert( ls -> key.size(), p -> key.remove(r-1) );
        // p的第r-1个关键码转入ls
        ls->child.insert( ls -> child.size(),v -> child.remove(0));
        if( ls->child[ ls->child.size() - 1]) //把v最左边的孩子（min）给ls做最右侧孩子(max)
            ls->child[ ls->child.size() - 1] -> par = ls;
        while (!v -> key.empty() ){ //若v中元素仍非空，就把剩余的依次转入ls
            ls -> key.insert( ls -> key.size(), v->key.remove(0));
            ls -> child.insert( ls -> child.size(), v->child.remove(0));
            if( ls->child[ ls->child.size() - 1] )
                ls->child[ ls->child.size() - 1] -> par =ls;
        }
        delete v;
    }
    else{//与右兄弟合并
        Posi(T) rs = p -> child[r+1];
        rs->key.insert( 0 , p -> key.remove(r) );
        p->child.remove(r); //以上两步将p的第r个关键码转入rs
        rs->child.insert( 0,v -> child.remove(v -> child.size() -1 ) );
        if(rs -> child[0] )
            rs -> child[0] -> par = rs;
        while (!v -> key.empty()) {    //若v中元素仍非空，就把剩余的依次转入rs
            rs -> key.insert( 0, v->key.remove(v -> key.size()-1 ) );
            rs -> child.insert( 0, v->child.remove( v -> child.size() -1 ) );
            if( rs ->child[0] )
               rs->child[0] -> par =rs;
        }
        delete v;
    }
    solveUnderFlow( p ); //继续检查上一层
    return;
}



int main(){

}
