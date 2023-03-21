#pragma once
#include <iostream>
#define VECTOR_INIT_SIZE 8
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

        //Chaining methods below doesn't make much sense
        void shrink_to_fit();
        void clear();

        //Returns the value of i element of main buffer
        T i_element(size_t index_of_element);
        T operator[](size_t index_of_element);
        T i_element(size_t index_of_element) const;
        T operator[](size_t index_of_element) const;
        Mvector& operator=(const Mvector& user_vector);
        size_t size() const;

    };

//    class Mstring : public Mvector<char> {
//    public:
//        using Mvector::Mvector;
//
//        Mstring(const char* user_mstring);
//        Mstring(char user_string[]);
//        Mstring(const Mstring& user_mstring);
//        Mstring(Mstring&& user_mstring) noexcept;
//
//        Mstring& add_ms(const char* user_char);
//
//        Mstring& operator=(const Mstring& user_mstring);
//        Mstring& operator=(const char* user_char);
//        Mstring& operator=(Mstring&& user_mstring) noexcept;
//        bool operator==(const Mstring& user_mstring);
//        bool operator==(const char* user_char);
//
//        Mstring& operator+(const char* user_char);
//        Mstring& operator+(const Mstring& user_mstring);
//        Mstring& operator+=(const Mstring& user_mstring);
//        Mstring& operator+=(const char* user_char);
//    };
//
//    class Node{
//    public:
//       Node* next = nullptr;
//       Node* previous = nullptr;
//       Mvector<Mstring> selectors;
//       Mvector<Mstring> values;
//       Mvector<Mstring> properties;
//
//       void add_selector(const char* user_selector);
//       void add_value(const char* user_value);
//       void add_property(const char* user_property);
//    };
//
//
//    class LinkedList {
//        Node* first;
//        Node* last;
//
//    public:
//        LinkedList();
//        ~LinkedList();
//
//        void add_section();
//
//        void pop_back();
//        void pop_front();
//        void pop(size_t index);
//
//        Node& operator[](size_t index);
//    };
//}
