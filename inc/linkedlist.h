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
} Node;

typedef struct {
    int _logicalLen;
    int _allocLen;
    Node* _firstElement;
    int _elementSize;
    void* (*nodeDestructorCallback)(Node* node);
} LinkedList;

// METHODS

void linkListNew(LinkedList *list, int elementSize, void* (*nodeDestructorCallback)(Node*));
void linkedListDispose(LinkedList *s);
void linkedListClear();
void linkedListInsert(LinkedList *list, void* element);
void linkedListErase(LinkedList *list);
void linkedListPushBack(LinkedList *s, void* elementAddress);
void linkedListPopBack(LinkedList *s, void* elementAddress);
void linkedListMapApply();
void linkedListAt(LinkedList *list, void* element);
void linkedListFront(LinkedList *s, void* elementAddress);
void linkedListSwap(LinkedList *s, void* elementAddress);

Node* _linkedListNodeNew(LinkedList *list, Node* previous, Node* next, void* element);
void _linkedListNodeDestroy(LinkedList *list, Node *node);
Node* _linkedListGetLastNode(Node* node);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LINKED_LIST_H */
