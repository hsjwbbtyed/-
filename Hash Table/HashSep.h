#ifndef HashSep_h
#define HashSep_h
struct ListNode;
typedef struct ListNode *Position;
struct HashTb1;
typedef struct HashTb1 *HashTable;

#endif /* HashSep_h */

struct ListNode {
    int value;
    Position next;
};

typedef Position List;


struct HashTb1 {
    int size;
    List *TheLists;
};
