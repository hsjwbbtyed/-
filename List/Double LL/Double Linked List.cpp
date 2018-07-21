
typedef int Rank;

#define Posi(T) ListNode<T>*

template <typename T> struct ListNode{
    //member
    T data;
    Posi(T) pred,succ;
    //constructor
    ListNode(){}//for head and trail
    ListNode(T e,Posi(T) p=nullptr,Posi(T) s=nullptr)
    :data(e),pred(p),succ(s){}
    // operating interface
    Posi(T) insertAsPred(T const e);
    Posi(T) insertAsSucc(T const e);
    
};




template <typename T> class List {
private: int _size;//规模
    Posi(T) header,trailer;//头尾哨兵
    /*哨兵节点对外不可见，仅为概念，之间的部分才是真正的实质节点
    等效而言，头首末尾节点的秩可以分别理解为 -1,0,n-1,n
*/
     
protected:  /*内部函数*/
    void init();
    int clear();
    void copyNodes(Posi(T),int);//基于复制的构造
    
    
    
public: /*....构造，析构函数，只读，可写，遍历接口*/
    //构造函数
    List(){init();}
    
    //析构函数
    ~List();
    Posi(T) find(T const& e,int n,Posi(T) p) const;
    Posi(T) insertBefore(Posi(T) p,T const& e);
    Posi(T) insertAsLast(Posi(T) p,T const& e);
    Posi(T) insertAfter(Posi(T) p,T const& e);
    T remove(Posi(T) p);
    int deduplicate();
    Posi(T) first();
    int uniquify();//有序列表的唯一化
    Posi(T) search(T const& e, int n,Posi(T) p) const;//有序列表里找到<e的最后一个位置
    void selectionSort(Posi(T) p,int n);//从p开始，长度为n的区间里排序
    Posi(T) selectMax(Posi(T) p,int n);//从p开始，长度为n的区间里取最大值。
    void InsertionSort(Posi(T) p,int n);
    void swapPtr(Posi(T) a,Posi(T)b);
    
};



//--------------------------------------------------------------------------------------------





template <typename T> Posi(T) List<T>::selectMax(Posi(T) p,int n){
    Rank max=0;
    Posi(T) end=p;
    for(int i=0;i<n;i++) end=end->succ;
    while (p!=end){
        if (p->data>max)
            max=p->data;
        p=p->succ;
    }
    return p;
}

//对列表中起始于位置p的连续n个元素做选择排序,valid(p) && rank(p)+n<=size
template <typename T> void List<T>::selectionSort(Posi(T) p,int n){
    
/*    防止越界，我们设置两个界桩，head and tail一前一后,一开始tail就在区间里第n个元素后面，随着迭代tail不断前移。
 示意如下：
 [head,p~~~~~~~~~~~~~~~~~~~tail-----p+n]
 从[tail,p+n)这段区间已经排序了。[p,tail)这部分尚未排序
 */
    Posi(T) head=p->pred, tail=p;//待排序区间(head,tail)
    for(int i=0;i<n;i++)tail=tail->succ;//把tail放在第n个元素后面
    while (n>1) {
        //反复从待排序区间里找出最大值，并且移到有序区间的前面。
        insertBefore(tail, remove(selectMax(head->succ, n)));
        
        /*但这里面涉及了new,delete,太耗费资源，所以可以简化
        1.只局部修改max和tail的引用
         2.直接交换max和tail的数据.
         */
        
        tail=tail->pred; n--;//同步更新待排序区间和已排序区间的长度。
        
    }
}


template <typename T>
Posi(T) List<T>::search(T const& e, int n,Posi(T) p) const{
    while (n-->=0)
        if((p=p->pred)->data <= e) break;
        return p;
}



template <typename T> int List<T>::uniquify(){ //批量删除重复元素

    if(_size<2)  return 0;  //平凡情况肯定不重复
    int oldSize=_size; //记录原规模
    Posi(T) p=first(); Posi(T) q;//p为各个区段起点,q为p的直接后继
    while (trailer != (q=p->succ)) {
        if (p->data!= q->data)  p=q;//如果不相等，说明遇到新的区段，那么把q的位置放在新区段的头部。
        else remove(q);//雷同则删除后者
    }
    return oldSize-_size;
}//遍历一遍即可，O(n)

template <typename T> void List<T>::InsertionSort(Posi(T) p, int n){
    for (int r=0; r>n; r++) {
        insertAfter(search(p->data, r, p), p->data);//search + insert
        p=p->succ; remove(p->pred);//转向下一节点
        
        /*这里我有一个更好的办法，以上的方法new,delete开销很大，直接交换指针更快，还不占空间。
         
         
         
         
         */
    }//n次迭代，每次O(r+1)
}//仅使用O（1）空间，属于就地算法









template <typename T> Posi(T)  List<T>::first() { return header->succ; }



template <typename T> List<T>::~List() {
    //先将所有实质节点删除，再删除头尾哨兵
    clear();
    delete header;  delete trailer;
}
template <typename T>  int List<T>::clear(){
    int oldSize=_size;
    while (_size) {
        remove(header->succ);//反复删除首节点，直到列表为空，过程中呈现向前缩减的样子。
        return oldSize;
    }
}
template <typename T>//删除合法位置p的节点，返回其值
T List<T>::remove(Posi(T) p){   //O(1)
    T temp=p->data;//备份待删除数据
    p->pred->succ=p->succ;
    p->succ->pred=p->pred;//恢复原有的拓扑结构
    delete p;  _size--;
    return temp;
}

template <typename T> int List<T>::deduplicate(){
/*在这个算法里我们将列表视为三部分：前缀（已经不包含重复节点，是当前算法的循环不变量），当前节点p，（可能非空）后缀
   设p->data=e，在前缀中查找，无论成功与否，问题规模都会降低。
 */
    if(_size<2)  return 0;  //平凡情况肯定不重复
    int oldSize=_size; //记录原规模
    Posi(T) p=first(); Rank r=1;//p从首节点起
    while (trailer!= (p=p->succ)) {  //直到末尾
        Posi(T) q=find(p->data, r, p); //在p的r个（前缀长度=r）前驱中查找是否有相同元素
        q?remove(q):r++;//存在就删除，不存在就把当前节点归入前缀，长度+1继续下一轮迭代。
    }//assert:循环中的任一时刻，p的所有前驱互不相同，也就保证了前缀的纯洁性。
    //遍历完整个列表
    return oldSize-_size;//返回删除量。
}

template <typename T>
Posi(T) List<T>::insertAsLast(Posi(T) p,T const& e) {
    /*在前面的定义中，所谓的末节点后面还有一个哨兵，trailer，因此末节点的位置是trailer->pred
    末节点插入就相当于在trailer前面插入，这是它的不变性。
     */
    insertBefore(trailer, e);
}

template <typename T>
Posi(T) List<T>::insertBefore(Posi(T) p,T const& e){
    _size++;  return p->insertAsPred(e);
}

template <typename T>
Posi(T) ListNode<T>::insertAsPred(T const e ){//O(1)
    /*对于特殊情况也能处理：假如当前节点是首节点，pred不存在。也不会出问题
     因为此前设立过哨兵，即便当前这个节点是首节点，他的前驱在内部依然存在——header
     前面至少有个东西挡着，不至于内存泄漏。因此这种情况下依然是安全的
     */
    Posi(T) x=new ListNode(e,pred ,this);
    pred->succ=x; pred=x;
    return x;//调整链接
}

template <typename T>
void List<T>::copyNodes(Posi(T) p,int n) {
    init();
    while (n--) {
        insertBefore(p, n);
    }
}

template <typename T>//外部调用时，0<= n <= rank(p) < _size
Posi(T) List<T>::find(T const& e,int n,Posi(T) p) const{
    //参数列表如此设置是有讲究的233，n在p前面意味着从p的n个前驱中找。
    while (n-- >0)
        if(e ==(p=p->pred)->data ) return p;//从后向前，直到命中 or 越界
        return nullptr;//左侧越界，说明失败
    //如果要查找的元素多于一个，将返回最靠后的节点位置
    
}//header的存在使处理更为简洁

template <typename T>
void List<T>::init(){
    header=new ListNode<T>;
    trailer=new ListNode<T>;
    header->succ=trailer;   header->pred=nullptr;
    trailer->pred=header;   trailer->succ=nullptr;//双向互联
    _size=0;//记录规模
}


int main(){
    
}



