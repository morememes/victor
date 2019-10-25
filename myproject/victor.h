//
// Created by morememes on 25.10.2019.
//

#ifndef MYPROJECT_VICTOR_H
#define MYPROJECT_VICTOR_H

template <class T>
class victor{
public:
    victor();
    victor(T *arr, size_t len);
    victor(const victor<T> &obj);
    victor(victor<T> &&obj);
    ~victor();
    victor& operator= (const victor<T> &obj);
    victor& operator= (victor<T> &&obj);
    T* begin();
    T* end();
    size_t size();
    void increaseLen();
    void push_back(const T& el);
    void push_back(T&& el);
    void pop_back();
    void erase(const T* inx);
    void erase(const T* b, const T* e);
    void swap(victor<T> &obj);
private:
    size_t len;
    T *arr;
    size_t capacity = 16;
};

#include "victor.cpp"

#endif //MYPROJECT_VICTOR_H
