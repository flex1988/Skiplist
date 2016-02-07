#ifndef __SKIP_LIST_H__
#define __SKIP_LIST_H__

#define LIST_MAX_LEVEL 32
#define P 0.25
#include <stdbool.h>

typedef struct listNode {
    int key;
    int value;
    struct listNode* forwards[];
}listNode;

typedef struct skiplist{
    int level;
    struct listNode* header;
}skiplist;


skiplist* createList(void);
listNode* createNode(int level,int key,int value);
int randomLevel();
listNode* search(skiplist* l,int key);
bool insert(skiplist* l,int key,int value);
bool delete(skiplist* l,int key);
void freeList(skiplist* l);
#endif
