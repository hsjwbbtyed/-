//Quad means Quadratic (Probing )
#ifndef HashQuad_h
#define HashQuad_h
typedef unsigned int Index;
typedef Index Position;
struct HashTb1;
typedef struct HashTb1 *HashTable;

HashTable Init(int size);
void DestroyTable(HashTable H);
void Insert(int key, HashTable H);
Position Find(int key,HashTable H);
int Retrieve(Position P);
HashTable ReTable(HashTable H);
#endif /* HashQuad_h */

enum KindOfEntry{
    Legitimate,
    Empty,
    Deleted
};

struct HashEntry {
    int value;
    enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

/*Cell *TheCells will be an array of 
 HashEntry cells,allocated later
 */
struct Cell {
    int TableSize;
    Cell *TheCells;
};
