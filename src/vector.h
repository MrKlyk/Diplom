#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <new>

template <typename T>
class Vector {
private:
    T* data = nullptr;
    size_t count = 0;
    size_t requestedSize = 0;

public:
    Vector();
    Vector(size_t size);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    T& operator[](size_t index);
    void push_back(const T& item);
    Vector operator+(const Vector& other);
    void resize(size_t newSize, std::nothrow_t);
    size_t size() const;
};

#include "vector.cpp"

#endif 