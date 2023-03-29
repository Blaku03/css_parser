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

    size_t find_value(const char* user_value);
    T* operator[](size_t index);
    void add_element_selector(const char* element);

    ~LinkedList();
};

#endif //INC_1_CSS_DATASTRUCTURES2_H
