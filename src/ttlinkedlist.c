#include "ttmemory.h"
#include "ttconfig.h"
#include "ttlinkedlist.h"
#include <stdlib.h>

void linkedListNew(LinkedList *list, int elementSize, void *(*nodeDestructorCallback)(LinkedListNode *)) {
    list->_logicalLen = 0;
    list->_allocLen = 0;
    list->_firstElement = NULL;
    list->_elementSize = elementSize;
    list->nodeDestructorCallback = nodeDestructorCallback;
}

void linkedListInsert(LinkedList *list, void* element) {
    list->_logicalLen++;
    if (list->_firstElement == NULL) {
        list->_firstElement = _linkedListNodeNew(list, NULL, NULL, element);
    } else  {
        LinkedListNode* lastNode = _linkedListGetLastNode(list->_firstElement);
        lastNode->_next = _linkedListNodeNew(list, lastNode, NULL, element);
    }
    list->_allocLen++;
}

void linkedListErase(LinkedList *list) {
    list->_logicalLen--;
    LinkedListNode* lastNode = NULL;
    if (list->_firstElement == NULL) {
        // nothing to erase!
        return;
    } else {
        // finds the last
        LinkedListNode* node = _linkedListGetLastNode(list->_firstElement);
        _linkedListNodeDestroy(list, node);
        list->_allocLen--;
        return;
    }
}

void linkedListDispose(LinkedList *list) {
    list->_logicalLen = 0;
    list->_allocLen = 0;
    LinkedListNode* node = _linkedListGetLastNode(list->_firstElement);
    while (list->_firstElement) {
        _linkedListNodeDestroy(list, list->_firstElement);
    }
    list->_firstElement = NULL;
}

/// returns NULL if input node is null, otherwise finds the last valid node
LinkedListNode* _linkedListGetLastNode(LinkedListNode* node) {
    if (node->_next) {
        return _linkedListGetLastNode(node->_next);
    } else {
        return node;
    }
}

void _linkedListNodeDestroy(LinkedList *list, LinkedListNode *node) {
    if (node->_previous) {
        LinkedListNode* previous = node->_previous;
        // both next and previous exist
        if (node->_next) {
            LinkedListNode* next = node->_next;
            previous->_next = next;
            next->_previous = previous;
        }
        // only previous exists: last node
        else {
            previous->_next = NULL;
        }
    } else if (node->_next) {
        // only next exists. First element
        LinkedListNode* next = node->_next;
        next->_previous = NULL;
        list->_firstElement = next;
    } else {
        // this means we have either a next element or neither. It should never be in this state
    }
    // content deallocation
    if (list->nodeDestructorCallback) {
        list->nodeDestructorCallback(node);
    } else {
        ttfree(node->contents);
    }
    // node deallocation
    ttfree(node);
    node = NULL;
}

LinkedListNode* _linkedListNodeNew(LinkedList *list, LinkedListNode* previous, LinkedListNode* next, void* element) {
    // node allocation
    LinkedListNode* node = ttmalloc(sizeof(LinkedListNode));
    // content allocation
    node->contents = ttmalloc(list->_elementSize);
    node->_previous = previous;
    node->_next = next;
    ttmemcpy(node->contents, element, list->_elementSize);
    return node;
}