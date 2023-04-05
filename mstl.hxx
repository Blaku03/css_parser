#pragma once
#include "mstl.h"

template<typename T>
void Mvector<T>::expand_twice_the_size() {
    T *helper_buffer = copy_array(main_buffer, current_size, false);
    delete[] main_buffer;

    //Doubling the size of main buffer
    main_buffer = copy_array(helper_buffer, current_size, true);
    current_size *= 2;

    delete[] helper_buffer;
}

template<typename T>
T* Mvector<T>::copy_array(T *pointer_to_array_that_should_be_copied, size_t size_of_array, bool double_size) {
    T *copied_array = new T[double_size ? size_of_array * 2 : size_of_array];

    for (unsigned int i = 0; i < size_of_array; i++) {
        *(copied_array + i) = *(pointer_to_array_that_should_be_copied + i);
    }

    return copied_array;
}

template<typename T>
bool Mvector<T>::enough_buffer_space(size_t space_to_add) const {
    return space_to_add + number_of_elements < current_size;
}

template<typename T>
Mvector<T>::Mvector() {
    current_size = 11;
    main_buffer = new T[current_size];
    number_of_elements = 0;
}

template<typename T>
Mvector<T>::~Mvector(){
    if(main_buffer != nullptr){
        delete [] main_buffer;
    }
}

template<typename T>
Mvector<T>& Mvector<T>::push_back(T user_value) {
    //Check if array isn't too small
    if (current_size <= number_of_elements) expand_twice_the_size();

    //Add user's value to array
    *(main_buffer + number_of_elements) = user_value;
    number_of_elements++;
    return *this;
}

template<typename T>
Mvector<T>& Mvector<T>::push_back(T *user_arr, size_t size_of_user_arr) {
    while (!enough_buffer_space(size_of_user_arr)) expand_twice_the_size();

    for (int i = 0; i < size_of_user_arr; i++) {
        *(main_buffer + number_of_elements) = *(user_arr + i);
        number_of_elements++;
    }

    return *this;
}

template<typename T>
Mvector<T>& Mvector<T>::push_back(const Mvector<T> &user_vector) {
    //Add it to variable to not call method all the time
    size_t user_vector_size = user_vector.size();

    while (!enough_buffer_space(user_vector_size)) expand_twice_the_size();

    for (int i = 0; i < user_vector_size; i++) {
        *(main_buffer + number_of_elements) = user_vector.i_element(i);
        number_of_elements++;
    }

    return *this;
}

template<typename T>
Mvector<T>& Mvector<T>::push_back(Mvector<T>&& user_vector) {
    //Add it to variable to not call method all the time
    size_t user_vector_size = user_vector.size();

    while (!enough_buffer_space(user_vector_size)) expand_twice_the_size();

    for (int i = 0; i < user_vector_size; i++) {
        *(main_buffer + number_of_elements) = user_vector.i_element(i);
        number_of_elements++;
    }

    return *this;
}

template<typename T>
T Mvector<T>::pop() {
    if (number_of_elements > 0) number_of_elements--;
    return main_buffer[number_of_elements];
}

template<typename T>
T Mvector<T>::pop_index(size_t index_of_element){

    if (index_of_element < number_of_elements) {
        T *helper_buffer = new T[current_size];
        T popped_element = main_buffer[index_of_element];

        for (size_t i = 0; i < index_of_element; i++) {
            *(helper_buffer + i) = *(main_buffer + i);
        }

        for (size_t i = index_of_element + 1; i < number_of_elements; i++) {
            *(helper_buffer + i - 1) = *(main_buffer + i);
        }

        number_of_elements--;
        delete[] main_buffer;
        main_buffer = helper_buffer;
        return popped_element;
    }
    std::cout << "ERROR: INDEX GIVEN IS NOT WITHIN THE VECTOR\n";
    exit(99);
}

template<typename T>
T Mvector<T>::pop_front() {
    if(number_of_elements == 0) return 0;

    T *helper_buffer = new T[current_size];
    T popped_element = main_buffer[0];

    for (int i = 1; i < number_of_elements; i++) {
        *(helper_buffer + i - 1) = *(main_buffer + i);
    }

    number_of_elements--;
    delete[] main_buffer;
    main_buffer = helper_buffer;
    return popped_element;
}

template<typename T>
void Mvector<T>::shrink_to_fit() {
    T *helper_buffer = copy_array(main_buffer, number_of_elements, false);
    delete[] main_buffer;

    main_buffer = helper_buffer;
    current_size = number_of_elements;
}

template<typename T>
void Mvector<T>::clear() {
    delete[] main_buffer;
    current_size = 11;
    main_buffer = new T[current_size];
    number_of_elements = 0;
}

template<typename T>
T& Mvector<T>::i_element(size_t index) {
    if (index < number_of_elements) return main_buffer[index];
    std::cout << "ERROR: INDEX GIVEN IS NOT WITHIN THE VECTOR\n";
    exit(99);
}

template<typename T>
T& Mvector<T>::operator[](size_t index) {
    return i_element(index);
}

template<typename T>
const T& Mvector<T>::i_element(size_t index) const {
    if (index < number_of_elements) return main_buffer[index];
    std::cout << "ERROR: INDEX GIVEN IS NOT WITHIN THE VECTOR\n";
    exit(99);
}

template<typename T>
const T& Mvector<T>::operator[](size_t index) const {
   return i_element(index);
}

template<typename T>
Mvector<T>& Mvector<T>::operator=(const Mvector& user_vector) {
    //handle self-assigment
    if (this == &user_vector) return *this;

    delete[] main_buffer;

    main_buffer = copy_array(user_vector.main_buffer, user_vector.current_size, false);
    number_of_elements = user_vector.number_of_elements;
    current_size = user_vector.current_size;

    return *this;
}

template<typename T>
size_t Mvector<T>::size() const {
    return number_of_elements;
}
