/**
 * Copyright (C) 2019, Douglas Rocha Ferraz
 * SPDX-License-Identifier: MIT
**/

#ifndef TT_LINKED_LIST_H
#define TT_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*** OBJECTS ***/

typedef struct {
    void* _next;
    void* _previous;
    void* contents;
} LinkedListNode;

typedef struct {
    int _logicalLen;
    int _allocLen;
    LinkedListNode* _firstElement;
    int _elementSize;
    void* (*nodeDestructorCallback)(LinkedListNode* node);
} LinkedList;

/*** METHODS ***/

void linkedListNew(LinkedList *list, int elementSize, void *(*nodeDestructorCallback)(LinkedListNode *));
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

LinkedListNode* _linkedListNodeNew(LinkedList *list, LinkedListNode* previous, LinkedListNode* next, void* element);
void _linkedListNodeDestroy(LinkedList *list, LinkedListNode *node);
LinkedListNode* _linkedListGetLastNode(LinkedListNode* node);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TT_LINKED_LIST_H */
