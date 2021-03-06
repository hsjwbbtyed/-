
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef Vector_h
#define Vector_h

typedef int Rank;
#define DEFAULT_CAPACITY  3



template <typename T> //最重要的就是这个模版参数，会给出一系列的类
class Vector {
private:
    Rank _size; int _capacity; T* _elem;
    //size为有效数据
protected:
    //inner function
    
    void Expand();
    
public:
    //interface
    Rank Insert(Rank r, const T & e);  //特定位置插入
    void Insert(Rank r);//顺次往后插入
    Rank search(const T & e);
    T& operator[] ( Rank r );
    int remove(Rank lo,Rank hi);
    Vector(int c= DEFAULT_CAPACITY){
        _elem=new T[_capacity=c];
        _size=0;
    }
    void shrink();
    Rank Find(T const & e,Rank lo,Rank hi);
    int uniquify();
    T remove(Rank r);
    int deduplicate();
    int H_uniquify();
    static Rank A_binSearch(T* A,T const& e,Rank lo,Rank hi);
    static Rank fibSearch(T* A,T const& e,Rank lo,Rank hi);//待续
    static Rank B_binSearch(T* A,T const& e,Rank lo,Rank hi);
    void sort(Rank lo,Rank hi);
    void bubblesort(Rank lo,Rank hi);
    void mergesort(Rank lo,Rank hi);
    bool bubble(Rank lo,Rank hi);
    void bubblesort_plus(Rank lo ,Rank hi);
    Rank bubble_p(int lo,int hi);//改进版
    void CopyFrom ( T* const A, Rank lo, Rank hi );
    void display();
    void mergeSort(Rank lo,Rank hi);
    void merge(Rank lo,Rank mi,Rank hi);
    
};

template <typename T>
Rank Vector<T>::Insert(Rank r,T const & e) {
    Expand();
    for (int i=_size; i>r; i--) {
        _elem[i]=_elem[i-1];//把所有元素往后移动一位
    }
    _elem[r]=r;     //数据装填
    _size++;
    return r;
}

template <typename T>
void Vector<T>::Insert(Rank r){
    Expand();
    _elem[_size++]=r;
    
}
template <typename T>
Rank Vector<T>::search(const T & e){
    int start=0,end=_size-1;
    while (start < end-- && _elem[end] != e) ;
    return end;
}

template <typename T> Rank Vector<T>::Find(T const & e,Rank lo,Rank hi){
    while (lo<hi-- && _elem[hi]!= e) ;
    return hi;
}


template <typename T> int Vector<T>::remove(Rank lo ,Rank hi) {
    if(lo==hi) return 0;
    while (hi<_size) {
        _elem[lo++]=_elem[hi++];
    }
    _size=lo;
    return hi-lo;
}


template <typename T> T Vector<T>::remove(Rank r){
    T e=_elem[r]; //备份被删除元素
    remove(r, r+1);
    return e;
}

template <typename T> int Vector<T>::deduplicate(){  //繁琐版+错误版
    int oldSize =_size;
    Rank i=1;
    while (i<_size) {  //自前向后考察各个元素
        (Find(_elem[i], 0, i)<0)?       //在前缀中寻找雷同
        i++
        :remove(i);
    }
    return oldSize-_size;
}

template <typename T>
T& Vector<T>::operator[] ( Rank r ) //重载下标操作符
{ return _elem[r]; } // assert: 0 <= r < _size

template <typename T>
void Vector<T>::CopyFrom(T* const A,Rank lo , Rank hi){
    _elem=new T[_capacity=2*(hi-lo)];//防止因频繁扩容而打断计算过程
    _size=0;//新空间的存量
    while(lo<hi)    //A[lo,hi)内的元素逐一复制到_elem[0,hi-lo)
        _elem[_size++]=A[lo++];
}

template <typename T> void Vector<T>::shrink() { //装填因子过小时压缩向量所占空间
    if ( _capacity < DEFAULT_CAPACITY << 1 ) return; //不致收缩到DEFAULT_CAPACITY以下
    if ( _size << 2 > _capacity ) return; //以25%为界
    T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //容量减半
    for ( int i = 0; i < _size; i++ ) _elem[i] = oldElem[i]; //复制原向量内容
    delete [] oldElem; //释放原空间
}

template <typename T> void Vector<T>::Expand(){
    if (_size<_capacity) {
        return;
    }
    _capacity=max(_capacity,DEFAULT_CAPACITY);
    T* oldelem=_elem;  _elem=new T[_capacity<<=1];
    for (int i=0; i<_size; i++) {
        _elem[i]=oldelem[i];
    }
    delete [] oldelem;
}

//得益于向量的封装，虽然扩容后数据的物理地址改变，但防止了指针
//
//1.是否可以将视频里向量扩容代码中的：
//
//for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
//
//替代为：
//
//memcpy(_elem, oldElem, _size * sizeof(T));
//
//答： 否，因为后者能否达到目的与元素类型T有关。
//分析：前一段函数调用拷贝函数；后一段当T不是基本数据类型且拥有自己的拷贝函数时，只能执行浅拷贝。浅拷贝是位拷贝，不会重新分配资源。深拷贝和浅拷贝的区别可以从以下例子中看出，A=B，如果B中有申请的内存，当释放掉B后，A中指向相同位置的指针变为野指针。在此时，就应该用深拷贝来处理。



//唯一化：有序向量。  一个区间保留一个元素即可
template <typename T>
int Vector<T>::uniquify(){      //低效版
    int oldSize =_size;  int i=0;   //从首元素开始
    while (i<_size-1) {         //从前向后，挨个比较每一对相邻元素
        (_elem[i]==_elem[i+1])?remove(i+1):i++;
    }
    return oldSize-_size;       //规模变化量，也就是删除的总数。
}//其中_size的减小，由remove隐式完成

template <typename T>
int Vector<T>::H_uniquify(){
    Rank i =0,j=0;//各对互异相邻元素的秩
    while (++j<_size) //   逐一扫描，直至末尾元素
        //跳过雷同者；发现不同元素时，向前移到紧邻于前者右侧
        if (_elem[i]!=_elem[j])  _elem[++i]=_elem[j];
    _size=++i;  //直接截除尾部多余元素(i是当前末尾下标，+1是统计规模)
    return j-i;//规模变化量
}   //注意：通过remove(lo,hi)批量删除，仍然不能达到高效率





template <typename T>//O(1.5lgn)，还可以改进
Rank Vector<T>::A_binSearch(T* A,T const& e,Rank lo,Rank hi){
    while (lo<hi) {
        Rank mid=(lo+hi)>>1;
        if (e<A[mid]) hi=mid;//尽量用小于号
        else if (A[mid]<e) lo=mid+1;
        else  return mid;
    }
    return -1;
}
//有改进余地在于：转向左右分支前的比较次数不等，而递归深度相等。它是试图通过各种情况的搜索在迭代次数上的平衡来回避掉最坏情况。

//因此改进思路：用递归深度的不平衡对转向成本的不均衡进行补偿，ASL能进一步减少。如果lengh=fib(k)-1, then mid=fib(k-1)-1,前后子向量长度就是：fib(k-1)-1,fib(k-2)-1


template <typename T>
Rank Vector<T>::fibSearch(T* A,T const& e,Rank lo,Rank hi){
    ;
}

template <typename T>
Rank Vector<T>::B_binSearch(T* A,T const& e,Rank lo,Rank hi){
    while (1<(hi-lo)) {  //有效区间宽度缩减至1，算法终止。
        Rank mid=(hi-lo)>>1;
        (e<A[mid])?hi=mid:lo=mid;
    }//出口时hi=lo+1,查找区间仅含一个元素A[lo]
    return (e==A[lo])?lo:-1;   //返回命中元素的秩or -1
}



//Sorting
template <typename T>
void Vector<T>::sort(Rank lo,Rank hi){
    switch (rand()%5) {
        case 1:
            bubblesort(lo,hi);
            break;
        case 2: mergesort(lo,hi); break;
    }
}

//冒泡排序改进
template <typename T> void Vector<T>::bubblesort(Rank lo ,Rank hi)
{    while (!bubble(lo,hi--));}//逐趟做扫描交换，直至全序



template <typename T> bool Vector<T>::bubble(Rank lo,Rank hi){
    bool sorted=true;
    while (++lo<hi) //自左向右逐一检查各对相邻元素
        if (_elem[lo-1]>_elem[lo]) {//如果仍然存在逆序
            sorted=false;
            swap(_elem[lo-1], _elem[lo]);
        }
    return sorted;
}//乱序限于[0,sqrt(n))时，仍需O(n^3/2)——按理O（n）就足够了，所以还有改进空间



//再改进:判断后面一段已经有序后，直接把hi移到未排序的末端。

template <typename T> void Vector<T>::bubblesort_plus(Rank lo ,Rank hi)
{    while ((hi=bubble_p(lo,hi)));}


template <typename T> void Vector<T>::display(){
    for (int i=0; i<_size; i++) {
        printf("%d ",_elem[i]);
    }
    printf("\n");
}

template <typename T> Rank Vector<T>::bubble_p(Rank lo,Rank hi){
    int last=lo; //最右侧的逆序对初始化为[lo-1,lo]
    while (++lo<hi) {
        if (_elem[lo-1]>_elem[lo]) {
            last=lo;//更新最右侧逆序对的位置记录，并交换
            swap(_elem[lo-1],_elem[lo]);
        }
    }
    return last;  //返回最右侧的逆序对位置，用来调整hi的位置。
}


//mergeSort
template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi-lo<2) return;//单元素区间必然有序
    int mid=(lo+hi)>>1;
    mergeSort(lo, mid);
    mergeSort(mid, hi);
    merge(lo, mid, hi);
}
//S[lo,hi)=S[lo,mid)+S[mid,hi)
//  A          B        C

template <typename T> void Vector<T>::merge(Rank lo,Rank mid,Rank hi){
    T* A=_elem+lo;//合并后的向量A[0,hi-lo)=_elem[lo.hi)
    int lb=mid-lo;
    T* B=new T [lb];//前子向量B[0,lb)=_elem[lo,mid)
    for(Rank i=0;i<lb;i++)B[i]=A[i];//复制前半段向量
    int lc=hi-mid; T* C=_elem+mid;//后子向量C[0,lc)=_elem[mid,hi)
    for (Rank i=0,j=0,k=0;(j<lb)||(k<lc); ) {   //B和C中较小的转至A的末尾
        
        if((j<lb)&&(lc<=k ||(B[j]<=C[k]))) A[i++]=B[j++];
        /*  &左边：j没有越界，B[j]还是一个实在的元素，而非不存在。
         &右边：k已经越界  or B当前元素更大
         可以想象C的右侧有一个哨兵节点，值为正无穷。越界，倒不如说C[k]的值已经到正无穷了，那么所有的B[j]都小于它，这样一来，就把“||”两端的逻辑统一起来了。
         */
        if((k<lc)&&(lb<=j ||(C[k]<B[j]))) A[i++]=C[k++];//同理
        //到此，两段子向量就被有序并入A了。
    }//逻辑紧凑，但效率不如拆分处理
    delete [] B;
}


#endif /* Vector_h */
