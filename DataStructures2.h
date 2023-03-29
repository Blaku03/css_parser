#ifndef INC_1_CSS_DATASTRUCTURES2_H
#define INC_1_CSS_DATASTRUCTURES2_H
#include <iostream>

template<typename T>
class Node{
public:
    Node* next = nullptr;
    Node* previous = nullptr;
    T data;

    ~Node();
};

template<typename T>
class LinkedList {
public:
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;

    T* operator[](size_t index);

    ~LinkedList();
};

#endif //INC_1_CSS_DATASTRUCTURES2_H
