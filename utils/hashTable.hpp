#ifndef UTILS_HASHTABLE_
#define UTILS_HASHTABLE_

#include "array.hpp"
#include "memory/allocation.hpp"
#include "memory/iterator.hpp"
#include "utils/linkedList.hpp"

template<class Key, class Value>
class HashTableNode {
    template<class, class>
    friend class Bucket;
public:
    HashTableNode(Key _key, Value _value, int _hashCode) 
    : key(_key), value(_value), hashCode(_hashCode) {}

    const Key key;
    Value value;
    const int hashCode;

private:
    HashTableNode<Key, Value>* next;
};

template<class Key, class Value>
struct HashTableClosure : public Closure {
    virtual bool do_node(HashTableNode<Key, Value>*) = 0;
};

template<class Key, class Value>
class Bucket {
    using Node = HashTableNode<Key, Value>;
public:
    Bucket()
    : head(NULL), _size(0) {}

    void push(Node* n) {
        ++_size;
        n->next = head;
        head = n;
    }

    Node* pop() {
        if(head) {
            --_size;
            auto tmp = head;
            head = head->next;
            return tmp;
        }

        return NULL;
    }

    size_t size() { return _size; }

    bool iterate(HashTableClosure<Key, Value>* cl) {
        for(auto iter = head; iter; iter = iter->next)
            if(!cl->do_node(iter))
                return false;

        return true;
    }

    bool empty() { return !head; }

private:
    Node* head;
    size_t _size;
};

template<
    class Key, class Value, int(*hash)(Key), 
    bool(*equals)(HashTableNode<Key, Value>&&, HashTableNode<Key, Value>&&)>
class HashTable : CHeapObj {
    using Node = HashTableNode<Key, Value>;
public:
    HashTable(size_t nBuckets = 128, float _rehashThreshold = 0.75)
    : old(NULL), rehashThreshold(_rehashThreshold) {
        cur = new Array<Bucket<Key, Value>>(nBuckets);
        assert(cur, "out of memory(c heap)");
    }

    int put(Key k, Value v);
    Value get(Key k);
    Bucket<Key, Value>* get(int);
    bool exist(Key);
    bool exist(int);

    size_t size() { return _size; }
    bool empty() { return !size(); }

    void iterate(HashTableClosure<Key, Value>* cl);

private:
    void put(int, Node*);

    float loadFactor() { return size() / cur->capacity(); }

    void rehash();

private:
    float rehashThreshold;
    Array<Bucket<Key, Value>>* old, *cur;
    size_t _size;
};

#endif