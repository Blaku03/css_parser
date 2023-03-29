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

    Node();
    ~Node();
};

template<typename T>
class LinkedList {
public:
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;

    size_t find_value(const Mstring& user_value);
    T* operator[](size_t index);
    void add_element_selector(const char* element);

//    LinkedList();
//    ~LinkedList();
};

class Section{
public:
    LinkedList<Mstring>* selectors = nullptr;
    LinkedList<Pair>* block_data = nullptr;

    int find_property(const Mstring& property_to_find) const;
    void add_selector(const char*  selector_to_add);
    void add_value(const char* value_to_add);
    void add_property(const char* property_to_add);

//    Section();
//    ~Section();
};

class mainList{
public:
    Section sections[ARR_LIST_SIZE];
    bool is_used[ARR_LIST_SIZE]{};
    mainList* next = nullptr;
    mainList* previous = nullptr;
    mainList* first = nullptr;
    mainList* last = nullptr;
    size_t curr_section_arr_size = 0;
    size_t active_sections = 0;
    Section* curr_section = nullptr;

    void add_new_sections_tab();
    void add_section();
    void remove_last_section();
    void remove_section_index(size_t index);
    Section& operator[](size_t index);
    mainList();
    ~mainList();

};

#endif //INC_1_CSS_DATASTRUCTURES_H
