#ifndef UTIL_HASHTABLE_
#define UTIL_HASHTABLE_

#include "array.hpp"
#include "memory/allocation.hpp"
#include "memory/iterator.hpp"
#include "util/linkedList.hpp"

template<class Key, class Value>
class HashTableNode {
    template<class, class>
    friend class Bucket;
public:
    HashTableNode(Key key, Value _value, int hashCode) 
    : _key(key), value(_value), _hashCode(hashCode) {}

    Key key() { return _key; }
    Value value;
    int hashCode() { return _hashCode; }

private:
    Key _key;
    int _hashCode;
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
        n->next = head;
        head = n;
    }

    Node* pop() {
        if(head) {
            auto tmp = head;
            head = head->next;
            return tmp;
        }

        return NULL;
    }

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
    HashTable(size_t nBuckets = 128, float _loadFactor = 0.75)
    : old(NULL), loadFactor(_loadFactor) {
        cur = new Bucket<Key, Value>[nBuckets];
        assert(cur, "out of memory(c heap)");
    }

    int put(Key k, Value v);
    Value get(Key k);
    Bucket<Key, Value>* get(int);
    bool exist(Key);
    bool exist(int);

    void iterate(HashTableClosure<Key, Value>* cl);

private:
    void put(int, Node*);

private:
    float loadFactor;
    Bucket<Key, Value>* old, *cur;
};

#endif