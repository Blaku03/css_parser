#include "DataStructures.h"

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

void Mstring::remove_last_char() {
    main_buffer[number_of_elements - 1] = '\0';
    number_of_elements--;
}

void Mstring::remove_white_space_end() {

    for(size_t i = number_of_elements - 1; i >= 0; i--){
        if(main_buffer[i] != ' '){
            return;
        }
        remove_last_char();
    }
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

    for (size_t i = 0; i < number_of_elements; i++) {
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

int Section::find_property(const Mstring &property_to_find) const {
    if(block_data == nullptr) return -1;
    if(block_data->first == nullptr) return -1;

    Node<Pair> *current_node = block_data->first;

    int index = 0;
    while(current_node->next != nullptr){
        if(current_node->data.property == property_to_find) return index;
        current_node = current_node->next;
        index++;
    }

    return -1;
}

void Section::add_selector(const char *selector_to_add) {
    //avoid adding empty selectors
    if (selector_to_add == nullptr) return;

}

void mainList::add_section() {
    if (curr_section_arr_size == ARR_LIST_SIZE - 1){
        // switch to the new list node with new array
        mainList* new_list = new mainList();
        if(first == nullptr){
            first = new_list;
            last = new_list;
        } else {
            last->next = new_list;
            new_list->previous = last;
            last = new_list;
        }
    }

    is_used[curr_section_arr_size] = true;
    curr_section_arr_size++;
    active_sections++;
}

mainList::mainList() {
    for(int i = 0; i < ARR_LIST_SIZE; i++){
        is_used[i] = false;
        sections[i] = Section();
    }
}

mainList::~mainList() {
    while(first != nullptr){
        mainList* temp = first;
        first = first->next;
        delete temp;
    }
}
