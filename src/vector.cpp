#include "vector.h"

template <typename T>
Vector<T>::Vector() {}

template <typename T>
Vector<T>::Vector(size_t size) : requestedSize(size), data(new(std::nothrow) T[size]) {
    if (data == nullptr) {
        std::cout << "Memory allocation failed in constructor" << std::endl;
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other) : requestedSize(other.requestedSize), count(other.count) {
    data = new(std::nothrow) T[requestedSize];
    if (data != nullptr) {
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }
    else {
        std::cout << "Memory allocation failed in copy constructor" << std::endl;
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        requestedSize = other.requestedSize;
        count = other.count;
        data = new(std::nothrow) T[requestedSize];
        if (data != nullptr) {
            for (size_t i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
        }
        else {
            std::cout << "Memory allocation failed in assignment operator" << std::endl;
        }
    }
    return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
void Vector<T>::push_back(const T& item) {
    if (count < requestedSize) {
        data[count++] = item;
    }
    else {
        std::cout << "No more space to add new items." << std::endl;
    }
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector& other) {
    Vector result(this->count + other.count);
    for (size_t i = 0; i < this->count; ++i) {
        result.push_back(this->data[i]);
    }
    for (size_t i = 0; i < other.count; ++i) {
        result.push_back(other.data[i]);
    }
    return result;
}

template <typename T>
void Vector<T>::resize(size_t newSize, std::nothrow_t) {
    T* newData = new(std::nothrow) T[newSize];
    if (newData != nullptr) {
        size_t elementsToCopy = (newSize < count) ? newSize : count;
        for (size_t i = 0; i < elementsToCopy; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        requestedSize = newSize;
        count = elementsToCopy;
    }
    else {
        std::cout << "Memory allocation failed in resize" << std::endl;
    }
}

template <typename T>
size_t Vector<T>::size() const {
    return count;
}