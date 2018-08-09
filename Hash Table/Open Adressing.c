
#include "HashQuad.h"
#define aPrime 307
#define MinTableSize 5
#include <stdio.h>
#include <stdlib.h>
typedef unsigned Index;

Index Hash(int key,int size) {
    return key%size;
}

//open addressing
HashTable Initial(int size){
    HashTable H;
    int i;
    if (size<MinTableSize) {
        printf("Table size too small\n");
        return NULL;
    }
    
    //Allocate table
    H=(HashTable)malloc(sizeof(struct HashTb1));
    H->TableSize=aPrime;
    
    //Allocate array of cells
    H->TheCells=(Cell*)malloc(sizeof(Cell)*H->TableSize);
    
    //    List header=(List)malloc(sizeof(struct ListNode));
    //Allocate list headers
    for (i=0; i<H->TableSize; i++)
        H->TheCells[i].Info=Empty;
    return H;
}


Position Find(int key,HashTable H){
    Position cur;
    int CollisionNum=0;
    cur=Hash(key,H->TableSize);
    while (H->TheCells[cur].Info != Empty &&
           H->TheCells[cur].value!= key)
    {
        cur+= (++CollisionNum-1)<<1;
        if (cur>=H->TableSize)
            cur-=H->TableSize;
    }
    return cur;
}


void Insert(int key, HashTable H){
    Position P=Find(key, H);
    if (H->TheCells[P].Info != Legitimate)
    {
        H->TheCells[P].Info=Legitimate;
        H->TheCells[P].value=key;
    }
}


HashTable Rehash(HashTable H) {
    int i,OldSize;
    Cell *OldCells;
    
    OldCells=H->TheCells;
    OldSize=H->TableSize;
    
    //Get a new empty table
    H=Init(OldSize<<1);
    
    //Scan through old table, reinserting into new one
    for (i=0; i<OldSize; i++) {
        if (OldCells[i].Info==Legitimate) {
            Insert(OldCells[i].value, H);
        }
    }
    
    free(OldCells);
    return H;
}


int main(){
    
}
