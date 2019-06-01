#include "ttmemory.h"
#include <linkedlist.h>
#include <memory.h>
#include <stdlib.h>

void linkListNew(LinkedList *list, int elementSize, void* (*nodeDestructorCallback)(Node*)) {
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
        Node* lastNode = _linkedListGetLastNode(list->_firstElement);
        lastNode->_next = _linkedListNodeNew(list, NULL, NULL, element);
    }
    list->_allocLen++;
}

void linkedListErase(LinkedList *list) {
    list->_logicalLen--;
    Node* lastNode = NULL;
    if (list->_firstElement == NULL) {
        // nothing to erase!
        return;
    } else {
        // finds the last
        Node* node = _linkedListGetLastNode(list->_firstElement);
        Node* previous = node->_previous;
        if (previous) {
            previous->_next = NULL;
        }
        _linkedListNodeDestroy(list, node);
        list->_allocLen--;
        return;
    }
}

void linkedListDispose(LinkedList *list) {
    list->_logicalLen = 0;
    list->_allocLen = 0;
    Node* node = _linkedListGetLastNode(list->_firstElement);
    while (list->_firstElement) {
        _linkedListNodeDestroy(list, list->_firstElement);
    }
    list->_firstElement = NULL;
}

/// returns NULL if input node is null, otherwise finds the last valid node
Node* _linkedListGetLastNode(Node* node) {
    if (node->_next) {
        return _linkedListGetLastNode(node->_next);
    } else {
        return node;
    }
}

void _linkedListNodeDestroy(LinkedList *list, Node *node) {
    if (node->_previous) {
        Node* previous = node->_previous;
        // both next and previous exist
        if (node->_next) {
            Node* next = node->_next;
            previous->_next = next;
            next->_previous = previous;
        }
        // only previous exists: last node
        else {
            previous->_next = NULL;
        }
    } else if (node->_next) {
        // only next exists. First element
        Node* next = node->_next;
        next->_previous = NULL;
        list->_firstElement = next;
    } else {
        // this means we have either a next element or neither. It should never be in this state
    }
    // content deallocation
    if (list->nodeDestructorCallback) {
        list->nodeDestructorCallback(node);
    } else {
        free(node->contents);
    }
    // node deallocation
    free(node);
    node = NULL;
}

Node* _linkedListNodeNew(LinkedList *list, Node* previous, Node* next, void* element) {
    // node allocation
    Node* node = malloc(sizeof(Node));
    // content allocation
    node->contents = malloc(list->_elementSize);
    node->_previous = previous;
    node->_next = next;
    _memcpy(node->contents, element, list->_elementSize);
    return node;
}