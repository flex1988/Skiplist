#include <stdio.h>
#include "skiplist.h"

void printNode(listNode* n)
{
    if (n != NULL)
        printf("node key: %d, value: %d\n", n->key, n->value);
    else
        printf("node is null\n");
}

int main()
{
    skiplist* l = createList();
    if (l == NULL) {
        fprintf(stderr, "create skiplist error\n");
        return -1;
    }

    listNode* n = NULL;
    fprintf(stdout, "create skiplist \n");
    for (int i = 0; i < 20; i++) {
        bool r = insert(l, i, i * 2);
        if (!r) {
            printf("insert node failed\n");
        }
    }

    for (int i = 0; i < 20; i++) {
        listNode* t = search(l, i);
        printNode(t);
    }

    printNode(search(l, 10));
    printNode(search(l, 100));
    printNode(search(l, -1));
    printNode(search(l, -100));

    freeList(l);

    return 0;
}
