
//Circular queue
#include <vector>
using namespace std;
vector<int> a;
const int rdd=10;//means redundancy
const int N=10000+rdd;
struct Queue{
    int q[N];
    int l,r;// l means front ,r means rear
    void Initial(){l=0;r=0;}
    void enqueue(int x) {
        if(r==N-rdd) r=1;else r++;
        q[r]=x;
    }
    void dequeue(){ if(l==N-rdd) l=1; else l++;}  //lazy remove
    int front(){return q[l];}
    int size(){
        if(l<=r) return r-1;
        else return l-r+1;
    }
    bool empty() {return l==r;}
    bool full(){ return (r+1)%N==l;}
};
