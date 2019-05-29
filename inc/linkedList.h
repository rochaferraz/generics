#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// CONFIGURATIONS

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// OBJECTS

typedef struct {
    void* _next;
    void* _previous;
    void* contents;
} LinkedListNode;

typedef struct {
    int _logicalLen;
    int _allocLen;
    LinkedListNode _elements;
    int _elementSize;
} LinkedList;

// METHODS

void llistNew(Stack *s, int elementSize);
void llistDispose(Stack *s);
void llistClear();
void llistInsert();
void llistErase();
void llistPushBack(Stack *s, void* elementAddress);
void llistPopBack(Stack *s, void* elementAddress);
void llistMapApply();
void llistAt();
void llistSwap();
void llistFront(Stack *s, void* elementAddress);
void llistSwap(Stack *s, void* elementAddress);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LINKED_LIST_H */
