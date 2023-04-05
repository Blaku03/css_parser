#ifndef INC_1_CSS_DATASTRUCTURES_H
#define INC_1_CSS_DATASTRUCTURES_H
#include "mstl.hxx"
#include "DataStructures2.hxx"
#define ARR_LIST_SIZE 8

class Mstring : public Mvector<char> {
public:
    using Mvector::Mvector;

    explicit Mstring(const char* user_string);
    explicit Mstring(char user_char[]);
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


class Section{
public:
    LinkedList<Mstring>* selectors = nullptr;
    LinkedList<Pair>* block_data = nullptr;

    int selectors_counter = 0;
    int block_data_counter = 0;

    int find_property(const Mstring& property_to_find) const;
    int find_selector(const Mstring& selector_to_find) const;
    void add_selector(const Mstring&  selector_to_add);
    void add_value(const Mstring& value_to_add) const;
    void add_value_position(const Mstring& value_to_add, int position) const;
    void add_property(const Mstring& property_to_add);
    Mstring& selector_index(int index) const;
    Mstring& value_index(int index) const;
    Mstring& property_index(int index) const;
    bool delete_property(const Mstring& property_to_delete);

    ~Section();
};

class mainList{
public:
    Section sections[ARR_LIST_SIZE];
    bool is_used[ARR_LIST_SIZE]{};
    mainList* next = nullptr;
    mainList* previous = nullptr;
    int curr_section_arr_size = 0;

    static Section* add_new_sections_tab(mainList*& address_of_last);
    Section* add_section(mainList*& address_of_last, int& all_sections_counter);
    static void remove_last_section(mainList*& address_of_last, mainList *&address_of_first, int& all_sections_counter);
    static bool remove_section_index(int index, mainList*& address_of_last, mainList*& address_of_first, int& all_sections_counter);
    static void handle_deleting_section(mainList*& address_of_last, mainList*& address_of_first, int& all_sections_counter, int index_to_delete, mainList* node_delete);
    Section* i_index(int index);
    int number_of_active_sections();
    mainList();
    ~mainList();

};

#endif //INC_1_CSS_DATASTRUCTURES_H
