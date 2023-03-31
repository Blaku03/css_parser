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
    while(current_node != nullptr){
        if(current_node->data.property == property_to_find) return index;
        current_node = current_node->next;
        index++;
    }

    return -1;
}

int Section::find_selector(const Mstring &selector_to_find) const {
    if(selectors == nullptr) return -1;
    if(selectors->first == nullptr) return -1;

    Node<Mstring> *current_node = selectors->first;

    int index = 0;
    while(current_node != nullptr){
        if(current_node->data == selector_to_find) return index;
        current_node = current_node->next;
        index++;
    }

    return -1;
}

void Section::add_selector(const Mstring& selector_to_add) {

    selectors_counter++;
    if(selectors == nullptr){
        selectors = new LinkedList<Mstring>;
        Node<Mstring> *new_node = new Node<Mstring>;
        new_node->data = selector_to_add;
        selectors->first = new_node;
        selectors->last = new_node;
    }
    else{
        Node<Mstring> *new_node = new Node<Mstring>;
        new_node->data = selector_to_add;
        selectors->last->next = new_node;
        new_node->previous = selectors->last;
        selectors->last = new_node;
    }
}

void Section::add_value(const Mstring& value_to_add) {
    block_data->last->data.value = value_to_add;
}

void Section::add_value_position(const Mstring& value_to_add, size_t position) {

        Node<Pair> *current_node = block_data->first;

        for (size_t i = 0; i < position; i++) {
            current_node = current_node->next;
        }

        current_node->data.value = value_to_add;
}

void Section::add_property(const Mstring& property_to_add) {

    block_data_counter++;
    if(block_data == nullptr){
        block_data = new LinkedList<Pair>;
        Node<Pair> *new_node = new Node<Pair>;
        new_node->data.property = property_to_add;
        block_data->first = new_node;
        block_data->last = new_node;
    }
    else{
        Node<Pair> *new_node = new Node<Pair>;
        new_node->data.property = property_to_add;
        block_data->last->next = new_node;
        new_node->previous = block_data->last;
        block_data->last = new_node;
    }
}

Mstring& Section::selector_index(size_t index) const {
    Node<Mstring> *current_node = selectors->first;

    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node->data;
}

Mstring& Section::value_index(size_t index) const {
    Node<Pair> *current_node = block_data->first;

    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node->data.value;
}

Mstring& Section::property_index(size_t index) const {
    Node<Pair> *current_node = block_data->first;

    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    return current_node->data.property;
}

bool Section::delete_property(const Mstring &property_to_delete) {
    int index = find_property(property_to_delete);
    if(index == -1) return false;

    Node<Pair> *current_node = block_data->first;

    for (size_t i = 0; i < index; i++) {
        current_node = current_node->next;
    }

    //check if current node is only node
    if(current_node->previous == nullptr && current_node->next == nullptr){
        block_data->first = nullptr;
        block_data->last = nullptr;
        delete current_node;
        block_data_counter--;
        return true;
    }
    if(current_node->previous == nullptr){
        block_data->first = current_node->next;
        current_node->next->previous = nullptr;
    }
    else if(current_node->next == nullptr){
        block_data->last = current_node->previous;
        current_node->previous->next = nullptr;
    }
    else{
        current_node->previous->next = current_node->next;
        current_node->next->previous = current_node->previous;
    }

    delete current_node;
    block_data_counter--;
    return true;
}

Section::~Section() {
    if(selectors != nullptr){
        while(selectors->first != nullptr){
            Node<Mstring> *temp = selectors->first;
            selectors->first = selectors->first->next;
//            delete temp;
        }
//        delete selectors;
    }

    if(block_data != nullptr){
        while(block_data->first != nullptr){
            Node<Pair> *temp = block_data->first;
            block_data->first = block_data->first->next;
//            delete temp;
        }
//        delete block_data;
    }
}

Section* mainList::add_new_sections_tab() {
    mainList* new_list = new mainList();
    if(first == nullptr){
        first = new_list;
        last = new_list;
    } else {
        last->next = new_list;
        new_list->previous = last;
        last = new_list;
        new_list->first = first;
        new_list->last = last;
        first->last = last;
    }
    new_list->is_used[0] = true;
    new_list->curr_section_arr_size = 1;
    return &new_list->sections[0];
}

Section* mainList::add_section() {
    if (curr_section_arr_size == ARR_LIST_SIZE){
        // switch to the new list node with new array
        return add_new_sections_tab();
    }

    is_used[curr_section_arr_size] = true;
    curr_section_arr_size++;
    return this->sections + curr_section_arr_size - 1;
}

void mainList::remove_last_section() {

    mainList* node_delete = last;
    int index_to_delete = 0;

    for(int i = ARR_LIST_SIZE - 1; i >= 0; i--){
        if(node_delete->is_used[i]){
            index_to_delete = i;
            break;
        }
    }

    node_delete->is_used[index_to_delete] = false;
    node_delete->curr_section_arr_size--;

    if(node_delete->curr_section_arr_size <= 0){
        last = node_delete->previous;
        if(node_delete->previous != nullptr){
            node_delete->previous->next = node_delete->next;
        }
        if(node_delete->next != nullptr){
            node_delete->next->previous = node_delete->previous;
        }
        delete node_delete->sections->block_data;
        delete node_delete->sections->selectors;
    }
}

//TODO check if after deleting section the array is empty
bool mainList::remove_section_index(size_t index) {

    mainList* node_delete = first;
    while(index >= curr_section_arr_size){
        if(node_delete->next == nullptr) return false;
        node_delete = node_delete->next;
        index -= curr_section_arr_size;
    }

    while(!is_used[index]) ++index;

    node_delete->is_used[index] = false;
    node_delete->curr_section_arr_size--;

    if(node_delete->curr_section_arr_size <= 0){
        if(node_delete->previous != nullptr){
            node_delete->previous->next = node_delete->next;
        }
        if(node_delete->next != nullptr){
            node_delete->next->previous = node_delete->previous;
        }
        //check if node_delete is first
        if(node_delete->first == node_delete){
            node_delete->first = node_delete->next;
        }
        //same thing with last
        if(node_delete->last == node_delete){
            node_delete->last = node_delete->previous;
        }
        delete node_delete->sections->block_data;
        delete node_delete->sections->selectors;
    }
    return true;
}

Section* mainList::i_index(size_t index) {

    if (index >= curr_section_arr_size){
        // switch to the next list node with new array
        if (next != nullptr){
            return next->i_index(index - curr_section_arr_size);
        }
        else return nullptr;
    }

    for(int i = 0; i < index; i++){
        if(!is_used[i]) index++;
    }

    return &sections[index];
}

int mainList::number_of_active_sections() const {
    int counter = 0;
    mainList* curr_list = first;
    while(curr_list != nullptr){
       counter += (int)curr_list->curr_section_arr_size;
       curr_list = curr_list->next;
    }
    return counter;
}

void mainList::init_main_list() {
    first = this;
    last = this;
    curr_section_arr_size = 1;
    is_used[0] = true;
}

mainList::mainList() {
    for(int i = 0; i < ARR_LIST_SIZE; i++){
        is_used[i] = false;
        sections[i] = Section();
    }
}

mainList::~mainList() {
    while(first != nullptr){
        if(first == last) break;
        mainList* temp = first;
        first = first->next;
        delete temp;
    }
}
