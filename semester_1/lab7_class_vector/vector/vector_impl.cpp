#include "vector_impl.h"

size_t Vector::Size() const {
    return size;
}

size_t Vector::Capacity() const {
    return capacity;
}

int& Vector::operator[](size_t index) {
    return data[index];
}

const int& Vector::operator[](size_t index) const {
    return data[index];
}

int& Vector::At(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const int& Vector::At(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

Vector::Vector() {
    size = 0;
    capacity = 1;
    data = new int[capacity];
}

Vector::Vector(size_t n) {
    size = n;
    capacity = (n == 0 ? 1 : n);
    data = new int[capacity];

    for (size_t i = 0; i < size; ++i) {
        data[i] = 0;
    }
}

Vector::Vector(std::initializer_list<int> list) {
    size = list.size();
    capacity = size;
    data = new int[capacity];

    size_t i = 0;
    for (int value : list) {
        data[i++] = value;
    }
}

Vector::Vector(const Vector& other) {
    size = other.size;
    capacity = other.capacity;
    data = new int[capacity];

    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Vector::~Vector() {
    delete[] data;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    delete[] data;

    size = other.size;
    capacity = other.capacity;
    data = new int[capacity];

    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }

    return *this;
}

void Vector::Swap(Vector& other) {
    int* tempData = data;
    data = other.data;
    other.data = tempData;

    size_t tempSize = size;
    size = other.size;
    other.size = tempSize;

    size_t tempCapacity = capacity;
    capacity = other.capacity;
    other.capacity = tempCapacity;
}

void Vector::PushBack(int value) {
    if (size == capacity) {
        size_t newCapacity = capacity * 2;
        int* newData = new int[newCapacity];

        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    data[size] = value;
    ++size;
}

void Vector::PopBack() {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    --size;
}

void Vector::Clear() {
    size = 0;
}

void Vector::Reserve(size_t n) {
    if (n <= capacity) {
        return;
    }

    int* newData = new int[n];
    for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = n;
}

std::ostream& operator<<(std::ostream& out, const Vector& vec) {
    out << "[";
    for (size_t i = 0; i < vec.Size(); ++i) {
        out << vec[i];
        if (i + 1 < vec.Size()) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}
