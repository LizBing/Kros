#ifndef UTILS_LINKEDLIST_
#define UTILS_LINKEDLIST_

#include "memory/iterator.hpp"

struct LinkedListNode {
    friend class LinkedList;

    void insert(LinkedListNode* n) {
        n->prev = this;
        n->next = next;

        next->prev = n;
        next = n;
    }

    void erase() {
        prev->next = next;
        next->prev = prev;
    }

    LinkedListNode* prev, *next;
};

struct LinkedListClosure : Closure {
    virtual bool func(LinkedListNode*) = 0;
};

struct LinkedList : LinkedListNode {
    LinkedList() { prev = next = this; }

    void pushBack(LinkedListNode* n) { prev->insert(n); }

    void pushFront(LinkedListNode* n) { insert(n); }

    void popFront() { next->erase(); }

    void popBack() { prev->erase(); }

    bool empty() { return prev == this /* && next == this && prev == next */; }

    LinkedListNode* head() { return next; }

    LinkedListNode* tail() { return prev; } 

    bool iterate(LinkedListClosure* cl) {
        using iterator =  LinkedListNode*;

        for(iterator iter = next; iter != this; iter = iter->next)
            if(!cl->func(iter))
                return false;

        return true;
    }
};

#endif
