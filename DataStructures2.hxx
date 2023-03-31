#ifndef INC_1_CSS_DATASTRUCTURES2_HXX
#define INC_1_CSS_DATASTRUCTURES2_HXX
#include "DataStructures2.h"

template<typename T>
Node<T>::~Node(){
//    delete next;
    next = nullptr;
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
LinkedList<T>::~LinkedList<T>() {
    while(first != nullptr){
        Node<T> *temp = first;
        if(first == last){
            break;
        }
        first = first->next;
        delete temp;
    }
}

#endif //INC_1_CSS_DATASTRUCTURES2_HXX
