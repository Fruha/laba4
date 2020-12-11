#pragma once
#include <initializer_list>

template <class T>
class  MyVector
{
public:

    typedef T* iterator;

    MyVector();
    MyVector(int size);
    MyVector(int size, const T& initial);
    MyVector(const MyVector<T>& v);
    MyVector(const std::initializer_list<T>& list);
    ~MyVector();

    int capacity() const;
    int size() const;
    iterator begin();
    iterator end();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();

    void reserve(int capacity);
    void resize(int size);

    T& operator[](int index);
    MyVector<T>& operator=(const MyVector<T>&);
    void clear();

private:
    int vecSize;
    int vecCapacity;
    T* buffer;
};

template<class T>
MyVector<T>::MyVector(const std::initializer_list<T>& list) : 
    vecSize(list.size()),
    vecCapacity(list.size())
{
    int count = 0;
    buffer = new T[vecSize];
    for (auto& element : list)
    {
        buffer[count] = element;
        ++count;
    }
}

template<class T>
MyVector<T>::MyVector()
{
    vecCapacity = 0;
    vecSize = 0;
    buffer = nullptr;
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& v)
{
    vecSize = v.vecSize;
    vecCapacity = v.vecCapacity;
    buffer = new T[vecSize];
    for (int i = 0; i < vecSize; i++)
        buffer[i] = v.buffer[i];
}

template<class T>
MyVector<T>::MyVector(int size)
{
    vecCapacity = size;
    vecSize = size;
    buffer = new T[size];
}

template<class T>
MyVector<T>::MyVector(int size, const T& initial)
{
    vecSize = size;
    vecCapacity = size;
    buffer = new T[size];
    for (int i = 0; i < size; i++)
        buffer[i] = initial;
    //T();
}

template<class T>
MyVector<T>& MyVector<T>::operator = (const MyVector<T>& v)
{
    delete[] buffer;
    vecSize = v.vecSize;
    vecCapacity = v.vecCapacity;
    buffer = new T[vecSize];
    for (int i = 0; i < vecSize; i++)
        buffer[i] = v.buffer[i];
    return *this;
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::begin()
{
    return buffer;
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::end()
{
    return buffer + size();
}

template<class T>
T& MyVector<T>::front()
{
    return buffer[0];
}

template<class T>
T& MyVector<T>::back()
{
    return buffer[vecSize - 1];
}

template<class T>
void MyVector<T>::push_back(const T& v)
{
    if (vecSize >= vecCapacity)
        reserve(vecCapacity + 5);
    buffer[vecSize++] = v;
}

template<class T>
void MyVector<T>::pop_back()
{
    vecSize--;
}

template<class T>
void MyVector<T>::reserve(int capacity)
{
    if (buffer == nullptr)
    {
        vecSize = 0;
        vecCapacity = 0;
    }
    T* Newbuffer = new T[capacity];
    int lSize = capacity < vecSize ? capacity : vecSize;

    for (int i = 0; i < lSize; i++)
        Newbuffer[i] = buffer[i];

    vecCapacity = capacity;
    delete[] buffer;
    buffer = Newbuffer;
}

template<class T>
int MyVector<T>::size()const
{
    return vecSize;
}

template<class T>
void MyVector<T>::resize(int size)
{
    reserve(size);
    vecSize = size;
}

template<class T>
T& MyVector<T>::operator[](int index)
{
    return buffer[index];
}

template<class T>
int MyVector<T>::capacity()const
{
    return vecCapacity;
}

template<class T>
MyVector<T>::~MyVector()
{
    delete[] buffer;
}
template <class T>
void MyVector<T>::clear()
{
    vecCapacity = 0;
    vecSize = 0;
    buffer = nullptr;
}