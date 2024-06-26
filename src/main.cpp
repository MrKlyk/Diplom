#include <iostream>
#include "vector.h"

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