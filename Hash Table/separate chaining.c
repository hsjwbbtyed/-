

#define aPrime 307
#define MinTableSize 5
#include "HashSep.h"
#include <cstdio>
#include <cstdlib>
typedef unsigned Index;


Index Hash(int key,int size){
    return key%size;
}


//separare chaining
HashTable Init(int size){
    HashTable H;
    int i;
    if (size<MinTableSize) {
        printf("Table size too small\n");
        return nullptr;
    }
    
    //Allocate table
    H=(HashTable)malloc(sizeof(struct HashTb1));
    H->TableSize=aPrime;
    
    //Allocate lists
    H->TheLists=(List*)malloc(sizeof(List) * H->TableSize);
//    List header=(List)malloc(H->TableSize * sizeof(struct ListNode));
    
    //Allocate list headers
    for (i=0; i<H->TableSize; i++) {
        H->TheLists[i]=(List)malloc(sizeof(struct ListNode));
//        H->TheLists[i]=&header[i];
        H->TheLists[i]->next=nullptr;
    }
    return H;
}

Position FindPre(int key,HashTable H) {
    List L=H->TheLists[Hash(key, H->TableSize)]; //指向要放的那个桶
    Position P=L->next;
    
    while (P && P->next->value!=key)
        P=P->next;
    return P;

}

Position Find(int key,HashTable H) {
    List L=H->TheLists[Hash(key, H->TableSize)]; //指向要放的那个桶
    Position P=L->next;
    
    while (P && P->value!=key)
        P=P->next;
    return P;
}

void Insert(int key, HashTable H) {
    Position p,newCell;
    List L;
    
    p=Find(key, H);//如果已经存在，就什么都不做
    if (!p) {   //key尚未存在
        newCell=(List)malloc(sizeof(struct ListNode));
        L=H->TheLists[Hash(key, H->TableSize)];//找到对应的桶，这时（可能）发生冲突了，就往前塞进去一个槽
        newCell->next=L->next;   //这老三步了，装填数据，插入前端
        newCell->value=key;
        L->next=newCell;
    }
}
int Retrieve(Position P){
    return P->value;
}

int Delete(int key,HashTable H) {
    Position cur,pre;
    cur=Find(key, H);
    pre=FindPre(key, H);
    if (cur) {
        pre->next=cur->next;
        cur->next=nullptr;//防止野指针
        free(cur);
    }
    else printf("%d has not been found!\n",key);
    return key;
}



int main() {
   
}
