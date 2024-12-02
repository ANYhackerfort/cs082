#include "SimpleList.h"
#include <iostream>
#include <type_traits>
#include "InvalidIndexException.h"
#include "EmptyListException.h"
#include "FullListException.h"

template<class T>
void deleteHelper(T* pointer) {
    delete pointer; 
}


template <class T>
SimpleList<T>::SimpleList() : numElements(0) {
    this->elements = new T[CAPACITY];
}

template <class T>
SimpleList<T>::~SimpleList() {
    for (int i = 0; i < numElements; i++) {
        if constexpr (std::is_pointer<T>::value) {
            deleteHelper(elements[i]); 
            elements[i] = nullptr;
        } 
    }
    delete[] elements;
}

template<class T>
T SimpleList<T>::at(int index) const {
    if (index >= numElements || index < 0) {
        throw InvalidIndexException();
    } else {
        return elements[index]; 
    }
}

template<class T>
bool SimpleList<T>::empty() const {
    if (numElements == 0) {
        return true; 
    } else {
        return false; 
    }
}

template<class T>
T SimpleList<T>::first() const {
    if (empty()) {
        throw EmptyListException();
    } else {
        return elements[0];
    }
}

template<class T>
T SimpleList<T>::last() const {
    if (empty()) {
        throw EmptyListException();
    } else {
        return elements[numElements - 1];
    }
}

template<class T>
int SimpleList<T>::getNumElements() const {
    return numElements;
}

template<class T>
void SimpleList<T>::insert(T item) {
    if (numElements >= CAPACITY) {
        throw FullListException();
    }
    elements[numElements] = item;
    numElements++; 
}

template<class T>
void SimpleList<T>::remove(int index) {
    if (empty()) {
        throw EmptyListException();
    }
    at(index);

    //delete
    if constexpr (std::is_pointer<T>::value) {
        deleteHelper(elements[index]); 
        elements[index] = nullptr;
    } 

    elements[index] = elements[index + 1];
    index++; 
    while ((index + 1) <= numElements) {
        elements[index] = elements[index + 1];
        index++;
    } 
    numElements--;
}



