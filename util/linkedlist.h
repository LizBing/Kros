#ifndef UTIL_LINKEDLIST_
#define UTIL_LINKEDLIST_

#include "closure.h"
#include "util/int.h"

typedef struct LinkedListNode LinkedListNode;
struct LinkedListNode {
    LinkedListNode* prev, *next;
};

typedef struct {
    LinkedListNode node;
    size_t size;
} LinkedList;

static inline void LinkedListNode_insert(LinkedListNode* pos, LinkedListNode* n) {
    n->prev = pos;
    n->next = pos->next;

    pos->next->prev = n;
    pos->next = n;
}

static inline void LinkedListNode_erase(LinkedListNode* pos) {
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
}

static inline void LinkedList_ctor(LinkedList* this) {
    this->size = 0;
    this->node.prev = this->node.next = &this->node;
}

static inline void LinkedList_pushFront(LinkedList* this, LinkedListNode* n) { 
    LinkedListNode_insert(&this->node, n);
    ++this->size;
}

static inline void LinkedList_pushBask(LinkedList* this, LinkedListNode* n) {
    LinkedListNode_insert(this->node.prev, n);
    ++this->size;
}

static inline LinkedListNode* LinkedList_popFront(LinkedList* this) {
    LinkedListNode* ret_val = this->node.next;
    if(this->size) {
        LinkedListNode_erase(this->node.next);
        --this->size;

        return ret_val;
    }
    return NULL;
}

static inline LinkedListNode* LinkedList_popBack(LinkedList* this) {
    LinkedListNode* ret_val = this->node.prev;
    if(this->size) {
        LinkedListNode_erase(this->node.prev);
        --this->size;

        return ret_val;
    }

    return NULL;
}

static inline LinkedListNode* LinkedList_head(LinkedList* this) { return this->node.next; }
static inline LinkedListNode* LinkedList_tail(LinkedList* this) { return this->node.prev; }

static inline bool LinkedList_iterate(LinkedList* this, Closure cl) {
    for(LinkedListNode* iter = this->node.next; iter != &this->node; iter = iter->next) {
        if(!Closure_do(cl, iter))
            return false;
    }

    return true;
}

#endif
