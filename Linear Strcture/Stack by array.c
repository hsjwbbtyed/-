

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> a;
int n,m;
const int N=10000+10;
struct Stack{
    int a[N];
    int top;
    void Initial(){ top=0;}
    void push(int x){ a[++top]=x;}
    void pop(){ top--;}  //lazy remove
    int size(){ return top; }
    int query(){ return a[top]; }  //like top() in STL Stack
};
