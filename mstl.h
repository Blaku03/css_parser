#pragma once
#include <iostream>
    template<typename T>
    class Mvector {
    protected:
        size_t current_size;
        size_t number_of_elements;

        void expand_twice_the_size();
        T *copy_array(T *pointer_to_array_that_should_be_copied, size_t size_of_array, bool double_size);

        //Check if buffer have enough space to take "x" elements
        bool enough_buffer_space(size_t space_to_add);

    public:
        T *main_buffer;

        Mvector();
        ~Mvector();

        //Returning references to allow chained calls
        Mvector &push_back(T user_value);
        Mvector &push_back(T* user_arr, size_t size_of_user_arr);
        Mvector &push_back(const Mvector &user_vector);
        Mvector &push_back(Mvector&& user_vector);

        T pop();
        T pop_front();
        T pop_index(size_t index_of_element);

        //Chaining methods below doesn't make much sense
        void shrink_to_fit();
        void clear();

        //Returns the value of i element of main buffer
        T& i_element(size_t index_of_element);
        T& operator[](size_t index_of_element);
        const T& i_element(size_t index_of_element) const;
        const T& operator[](size_t index_of_element) const;
        Mvector& operator=(const Mvector& user_vector);
        size_t size() const;

    };