#include <iostream>
#include <new> 

template <typename T>
class Vector {
private:
    T* data = nullptr;
    size_t count = 0;
    size_t requestedSize = 0;

public:
    Vector() {}

    Vector(size_t size) : requestedSize(size), data(new(std::nothrow) T[size]) {
        if (data == nullptr) {
            std::cout << "Memory allocation failed in constructor" << std::endl;
        }
    }

    Vector(const Vector& other) : requestedSize(other.requestedSize), count(other.count) {
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

    ~Vector() {
        delete[] data;
    }

    Vector& operator=(const Vector& other) {
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

    T& operator[](size_t index) {
        return data[index];
    }

    void push_back(const T& item) {
        if (count < requestedSize) {
            data[count++] = item;
        }
        else {
            std::cout << "No more space to add new items." << std::endl;
        }
    }

    Vector operator+(const Vector& other) {
        Vector result(this->count + other.count);
        for (size_t i = 0; i < this->count; ++i) {
            result.push_back(this->data[i]);
        }
        for (size_t i = 0; i < other.count; ++i) {
            result.push_back(other.data[i]);
        }
        return result;
    }

    void resize(size_t newSize, std::nothrow_t) {
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

    size_t size() const {
        return count;
    }
};

int main() {
    Vector<int> v(3);
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int> v2 = v;
    Vector<int> v3;
    v3 = v + v2;

    std::cout << "v3 elements after adding v and v2:" << std::endl;
    for (int i = 0; i < v3.size(); ++i) {
        std::cout << v3[i] << std::endl;
    }

    v.resize(10, std::nothrow);
    v.push_back(40);
    v.push_back(50);

    std::cout << "v elements after resizing and adding new items:" << std::endl;
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << std::endl;
    }

    return 0;
}