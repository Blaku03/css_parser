#ifndef INC_1_CSS_DATASTRUCTURES2_HXX
#define INC_1_CSS_DATASTRUCTURES2_HXX
#include "DataStructures.h"

template<typename T>
Node<T>::~Node(){
    if(next != nullptr) delete next;
}

template<> size_t LinkedList<Pair>::find_value(const Mstring &user_value) {
    if(first == nullptr) return -1;

    Node<Pair>* current_node = first;

    size_t index = 0;
    while(current_node != nullptr){
        if(current_node->data.value == user_value) return index;
        current_node = current_node->next;
        index++;
    }

    return -1;
}

template<typename T>
T* LinkedList<T>::operator[](size_t index) {
    if(first == nullptr) return nullptr;

    Node<T>* current_node = first;
    for(int i = 0; i < index; i++){
        if(current_node == nullptr) return nullptr;
        current_node = current_node->next;
    }

    return &current_node->data;
}

template<typename T>
void LinkedList<T>::add_element_selector(const char *element) {
    Node<T>* new_node = new Node<T>;
    new_node->data = element;

    if(first == nullptr){
        first = new_node;
        last = new_node;
    } else{
        last->next = new_node;
        new_node->previous = last;
        last = new_node;
    }
}

template<typename T>
LinkedList<T>::~LinkedList<T>() {
    while(first != nullptr){
        Node<T> *temp = first;
        first = first->next;
        delete temp;
    }
}

#endif //INC_1_CSS_DATASTRUCTURES2_HXX
