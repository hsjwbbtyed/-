#include<cstdio>
#include <algorithm>
using namespace std;
const int N=100000+10;

int par[N],n,m,size[N];

inline int find(int x){return x==par[x]?x:par[x]=find(par[x]);}  //一行路径压缩

inline void merge(int x,int y){  //按秩合并
    int xx=find(x),yy=find(y);
    if(xx==yy)return;
    if(size[xx]>size[yy]) swap(xx,yy);
    par[xx]=yy;size[yy]+=size[xx];
}

bool same(int i,int j){
    return find(i)==find(j)?true:false;
}


//同时使用路径压缩和按秩合并后的时间复杂度是O(α(n))，只用一种优化的话，复杂度是O(logn)
