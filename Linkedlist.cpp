#include "Linkedlist.h"

Mstring::Mstring(const char* user_char) : Mvector<char>() {
    add_ms(user_char);
}

Mstring::Mstring(char user_char[]) : Mvector<char>() {
    add_ms(user_char);
}

Mstring::Mstring(const Mstring& user_mstring) : Mvector<char>() {
    main_buffer = copy_array(user_mstring.main_buffer, user_mstring.current_size, false);
    number_of_elements = user_mstring.number_of_elements;
    current_size = user_mstring.current_size;
}

Mstring::Mstring(Mstring&& user_mstring) noexcept : Mvector<char>() {
    main_buffer = user_mstring.main_buffer;
    user_mstring.main_buffer = nullptr;

    number_of_elements = user_mstring.number_of_elements;
    current_size = user_mstring.current_size;
}

Mstring& Mstring::add_ms(const char* user_char) {
    int element = 0;

    while (user_char[element] != '\0') {
        if (number_of_elements >= current_size) expand_twice_the_size();
        *(main_buffer + number_of_elements) = user_char[element];
        element++;
        number_of_elements++;
    }

    return *this;
}

Mstring& Mstring::operator=(const Mstring& user_mstring){
    delete[] main_buffer;

    main_buffer = copy_array(user_mstring.main_buffer, user_mstring.current_size, false);
    number_of_elements = user_mstring.number_of_elements;
    current_size = user_mstring.current_size;

    return *this;
}

Mstring& Mstring::operator=(const char* user_char){
    int element = 0;

    while (user_char[element] != '\0') {
        if (number_of_elements >= current_size) expand_twice_the_size();
        *(main_buffer + element) = user_char[element];
        element++;
        number_of_elements++;
    }

    *(main_buffer + element) = '\0';
    number_of_elements++;

    return *this;
}

Mstring& Mstring::operator=(Mstring&& user_mstring) noexcept{
    delete[] main_buffer;

    main_buffer = user_mstring.main_buffer;
    number_of_elements = user_mstring.number_of_elements;
    current_size = user_mstring.current_size;

    user_mstring.main_buffer = nullptr;
    user_mstring.number_of_elements = 0;
    user_mstring.current_size = 0;

    return *this;
}

bool Mstring::operator==(const Mstring& user_mstring){
    if (number_of_elements != user_mstring.number_of_elements) return false;

    for (int i = 0; i < number_of_elements; i++) {
        if (main_buffer[i] != user_mstring.main_buffer[i]) return false;
    }

    return true;
}

bool Mstring::operator==(const char *user_char) {
    int element = 0;

    while (user_char[element] != '\0') {
        if (main_buffer[element] != user_char[element]) return false;
        element++;
    }

    return true;
}

Mstring& Mstring::operator+(const char* user_char){
    add_ms(user_char);

    return *this;
}

Mstring& Mstring::operator+(const Mstring& user_mstring){
    Mstring *new_mstring = new Mstring();

    new_mstring->add_ms(main_buffer);
    new_mstring->add_ms(user_mstring.main_buffer);

    return *new_mstring;
}

Mstring& Mstring::operator+=(const char* user_char){
    add_ms(user_char);

    return *this;
}

Mstring& Mstring::operator+=(const Mstring& user_mstring){
    add_ms(user_mstring.main_buffer);

    return *this;
}


std::ostream& operator<<(std::ostream &os, const Mstring &mstring){

    for (int i = 0; i < mstring.size(); i++) {
        os << mstring.main_buffer[i];
    }

    return os;
}

std::istream& operator>>(std::istream &is, Mstring &mstring){
    char *user_input = new char[1024];
    std::cin >> user_input;

    mstring.add_ms(user_input);

    delete [] user_input;
    return is;
}

void Node::add_selector(const char* user_selector) {
    Mstring temp(user_selector);
    selectors.push_back(temp);
}

void Node::add_property(const char* user_property) {
    Mstring temp(user_property);
    properties.push_back(temp);
}

void Node::add_value(const char* user_value) {
    Mstring temp(user_value);
    values.push_back(temp);
}

LinkedList::LinkedList() {
    first = nullptr;
    last = nullptr;
}

LinkedList::~LinkedList() {
    Node* current_node = first;
    Node* next_node = nullptr;

    while (current_node != nullptr) {
        next_node = current_node->next;
        delete current_node;
        current_node = next_node;
    }
}

void LinkedList::add_section() {
    Node *new_node = new Node();

    if (first == nullptr) {
        first = new_node;
        last = new_node;
    } else {
        last->next = new_node;
        new_node->previous = last;
        last = new_node;
    }
}

void LinkedList::pop_back() {
    if (first == nullptr) return;

    Node* previous_node = last->previous;
    delete last;
    last = previous_node;
    last->next = nullptr;
}

void LinkedList::pop_front() {
    if (first == nullptr) return;

    Node* next_node = first->next;
    delete first;
    first = next_node;
    first->previous = nullptr;
}

void LinkedList::pop(size_t index) {
    if (first == nullptr) return;

    Node *current_node = first;

    for (int i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    current_node->previous->next = current_node->next;
    current_node->next->previous = current_node->previous;
    delete current_node;
    std::cout << "deleted";
}

Node& LinkedList::operator[](size_t index) {
    Node* index_node = first;

    for(int i = 0; i < index; i++) {
        if(index_node == nullptr){
            throw std::out_of_range("Index out of range");
        }

        index_node = index_node->next;
    }

    return *index_node;
}
