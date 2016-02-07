#include <stdlib.h>
#include <stdio.h>
#include "skiplist.h"

skiplist* createList()
{
    skiplist* l = (skiplist*)malloc(sizeof(l));
    if (l == NULL)
        return NULL;
    l->level = 0;
    l->header = createNode(LIST_MAX_LEVEL, -1, -1);

    if (l->header == NULL) {
        free(l);
        return NULL;
    }

    for (int i = 0; i < LIST_MAX_LEVEL; i++) {
        l->header->forwards[i] = NULL;
    }
    return l;
}

listNode* createNode(int level, int key, int value)
{
    listNode* n = (listNode*)malloc(sizeof(n) + level * sizeof(n));
    if (n == NULL)
        return NULL;
    n->key = key;
    n->value = value;

    return n;
}

int randomLevel()
{
    int level = 1;
    while ((random() & 0xFFFF) < (P * 0xFFFF))
        level++;
    return (level > LIST_MAX_LEVEL ? LIST_MAX_LEVEL : level);
}

bool insert(skiplist* l, int key, int value)
{
    struct listNode *q, *p = l->header;
    struct listNode* update[LIST_MAX_LEVEL];

    int level = l->level;

    do {
        while ((q = p->forwards[level]) && q->key < key)
            p = q;
        update[level] = p;
    } while (--level >= 0);

    if (p->key == key) {
        p->value = value;
        return true;
    }

    int rlevel = randomLevel() - 1;
    if (rlevel > l->level) {
        rlevel = ++l->level;
        update[rlevel] = l->header;
    }

    listNode* n = createNode(rlevel + 1, key, value);
    if (n == NULL)
        return false;

    do {
        p = update[rlevel];
        n->forwards[rlevel] = p->forwards[rlevel];
        p->forwards[rlevel] = n;
    } while (--rlevel >= 0);

    return true;
}

listNode* search(skiplist* l, int key)
{
    if (key <= -1 || l == NULL || l->header == NULL)
        return NULL;
    else {
        struct listNode *p = l->header, *q;
        int level = l->level;
        do {
            while ((q = p->forwards[level]) && q->key < key)
                p = q;
        } while (--level >= 0);

        if (q && q->key == key)
            return q;

        return NULL;
    }
}

bool delete (skiplist* l, int key)
{
    listNode* update[LIST_MAX_LEVEL];
    listNode *p = l->header, *q;

    int level = l->level - 1;

    do {
        while ((q = p->forwards[level]) && q->key < key)
            p = q;
        update[level] = p;
    } while (--level >= 0);

    if (q == NULL || q->key != key)
        return false;

    for (int i = l->level - 1; i >= 0; i--) {
        if (update[i]->forwards[i] == q) {
            update[i]->forwards[i] = q->forwards[i];
            if (l->header->forwards[i] == NULL)
                l->level--;
        }
    }
    free(q);

    return true;
}

void freeList(skiplist* l)
{
    if (l == NULL)
        return;
    listNode *p = l->header, *q;

    while (p) {
        q = p->forwards[0];
        free(p);
        p = q;
    }
    free(l);
}
