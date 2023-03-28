#ifndef INC_1_CSS_DATASTRUCTURES_H
#define INC_1_CSS_DATASTRUCTURES_H
#include "mstl.hxx"
#define ARR_LIST_SIZE 8

class Mstring : public Mvector<char> {
public:
    using Mvector::Mvector;

    Mstring(const char* user_mstring);
    Mstring(char user_string[]);
    Mstring(const Mstring& user_mstring);
    Mstring(Mstring&& user_mstring) noexcept;

    Mstring& add_ms(const char* user_char);
    void remove_last_char();
    void remove_white_space_end();

    Mstring& operator=(const Mstring& user_mstring);
    Mstring& operator=(const char* user_char);
    Mstring& operator=(Mstring&& user_mstring) noexcept;
    bool operator==(const Mstring& user_mstring);
    bool operator==(const char* user_char);

    Mstring& operator+(const char* user_char);
    Mstring& operator+(const Mstring& user_mstring);
    Mstring& operator+=(const Mstring& user_mstring);
    Mstring& operator+=(const char* user_char);

    friend std::istream& operator>>(std::istream &is, Mstring &mstring);
    friend std::ostream& operator<<(std::ostream &os, const Mstring &mstring);
};

class Pair{
public:
    Mstring property;
    Mstring value;
};

template<typename T>
class Node{
public:
    Node* next = nullptr;
    Node* previous = nullptr;
    T data;

    T& postion_i(int index);
    T& operator[](int index);
    size_t find_value(const Mstring& user_value);
};

template<typename T>
class LinkedList {
public:
    Node<T>* first;
    Node<T>* last;

    LinkedList();
    ~LinkedList();
};

class Section{
public:
    LinkedList<Mstring>* selectors;
    LinkedList<Pair>* block_data;
};

class mainList{
public:
    Section sections[ARR_LIST_SIZE];
    bool is_used[ARR_LIST_SIZE];
    mainList* next = nullptr;
    mainList* previous = nullptr;
    size_t curr_section_arr_size = 0;

    void add_new_sections_tab();
    void add_section();
};

#endif //INC_1_CSS_DATASTRUCTURES_H
