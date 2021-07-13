#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
class Heap
{
public:
    Heap() {}
    Heap(const std::vector<T>& vec)
        : heapVec(vec)
    {
        heapify();
    }
    void add(const T& value)
    {
        heapVec.push_back(value);
        heapify();
    }
    T pop()
    {
        if(!size())
            return T();

        T value = heapVec[0];
        std::swap(heapVec[0], heapVec[size()-1]);
        heapVec.pop_back();
        heapify();
        return value;
    }
    int size() const
    {
        return heapVec.size();
    }
    bool isEmpty() const
    {
        return !size();
    }
    bool contains(const T& value) const
    {
        auto result = std::find(heapVec.begin(), heapVec.end(), value);
        return result != heapVec.end() ? true : false;
    }

    void setHeapVector(const std::vector<T>& vec)
    {
        heapVec = vec;
    }
    std::vector<T> heapVector() const
    {
        return heapVec;
    }

    void heapify()
    {
        for (int index = (size()-2)/2; index >= 0; --index) {
            doSwapHeapify(index);
        }
    }
    bool heapified()
    {
        for (int i = (size()-2)/2; i >= 0; --i) {
            int left = 2*i+1;
            int right = 2*i+2;

            if (left < size() && heapVec[i] > heapVec[left])
                return false;
            if (right < size() && heapVec[i] > heapVec[right])
                return false;
        }
        return true;
    }

private:
    void doSwapHeapify(int index)
    {
        int leftChildIndex = 2*index+1;
        int rightChildIndex = 2*index+2;
        int parentIndex = index;

        if (leftChildIndex < size() && heapVec[parentIndex] > heapVec[leftChildIndex])
            parentIndex = leftChildIndex;
        if (rightChildIndex < size() && heapVec[parentIndex] > heapVec[rightChildIndex])
            parentIndex = rightChildIndex;
        if (parentIndex != index) {
            std::swap(heapVec[index], heapVec[parentIndex]);
            doSwapHeapify(parentIndex);
        }
    }

    std::vector<T> heapVec;
};

#endif
