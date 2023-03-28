#ifndef INC_1_CSS_LINKEDLIST_H
#define INC_1_CSS_LINKEDLIST_H
#include "mstl.hxx"

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


class Node{
public:
    Node* next = nullptr;
    Node* previous = nullptr;
    Mvector<Mstring> selectors;
    Mvector<Mstring> values;
    Mvector<Mstring> properties;

    void add_selector(const char* user_selector);
    void add_value(const char* user_value);
    void add_property(const char* user_property);
    int find_property(const Mstring& user_attribute);
    int find_selector(const Mstring& user_selector);
    bool delete_property(const Mstring& user_property);
};

class LinkedList {
public:
    Node* first;
    Node* last;

    LinkedList();
    ~LinkedList();

    void add_section();

    bool pop_back();
    bool pop_front();
    bool pop(size_t index);
    int size();

    Node* operator[](size_t index);
};


#endif //INC_1_CSS_LINKEDLIST_H
