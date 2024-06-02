#pragma once
#include <queue>
#ifndef __PDFOBJINDEXENTRYVECTOR_H__
#define __PDFOBJINDEXENTRYVECTOR_H__
template <typename T,size_t capacity>
class PdfObjIndexEntryVector {
private:
    std::queue<T> q;

public:
    void push(const T& value) {
        q.push(value);
        if (q.size() > capacity) {
            q.pop();
        }
    }

    T front() {
        return q.front();
    }

    T back() {
        return q.back();
    }

    size_t size() {
        return q.size();
    }

    bool empty() {
        return q.empty();
    }
};
#endif
