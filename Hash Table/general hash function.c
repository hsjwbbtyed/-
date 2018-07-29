#define MinTableSize 5

#include "HashSep.h"
#include <iostream>
#include <cstdio>

typedef unsigned Index;

Index TrivialHash(const char* Key,int size){// a simple hash function
    
    unsigned int val=0;
    while (*Key !='\0') {
        val+=*Key++;
    }
    return val%size;

}

Index BadHashEx(const char* Key,int size){
    return (Key[0]+27*Key[1]+720*Key[2])%size;
    //easy to collision
}

Index greatHash(const char* Key,int size){
    unsigned int val=2;
    while (*Key!='\0')
        val=(val<<5)+ *Key++;
    
        return val%size;
}
