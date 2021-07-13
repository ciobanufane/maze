#ifndef PRIO_QUEUE_H
#define PRIO_QUEUE_H

#include "heap.h"
#include <vector>

template <typename T>
class PrioQueue
{
public:
    PrioQueue() { }
    PrioQueue(const std::vector<T>& vec): heap(vec)
    {
    }

    T pop()
    {
        return heap.pop();
    }
    int size()
    {
        return heap.size();
    }
    void add(const T& value)
    {
        heap.add(value);
    }
    bool contains(const T& value)
    {
        return heap.contains(value);
    }
    bool isEmpty() const
    {
        return heap.isEmpty();
    }
private:
    Heap<T> heap;
};

#endif
