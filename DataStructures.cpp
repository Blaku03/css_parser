#include "DataStructures.h"

Mstring::Mstring(const char *user_string) : Mvector<char>()
{
    add_ms(user_string);
}

Mstring::Mstring(char user_char[]) : Mvector<char>()
{
    add_ms(user_char);
}

Mstring::Mstring(const Mstring &user_mstring) : Mvector<char>(user_mstring)
{
    main_buffer = copy_array(user_mstring.main_buffer, user_mstring.current_size, false);
    number_of_elements = user_mstring.number_of_elements;
    current_size = user_mstring.current_size;
}

Mstring::Mstring(Mstring &&user_mstring) noexcept : Mvector<char>()
{
    main_buffer = user_mstring.main_buffer;
    user_mstring.main_buffer = nullptr;

    number_of_elements = user_mstring.number_of_elements;
    current_size = user_mstring.current_size;
}

Mstring &Mstring::add_ms(const char *user_char)
{
    int element = 0;

    while (user_char[element] != '\0')
    {
        if (number_of_elements >= current_size)
            expand_twice_the_size();
        *(main_buffer + number_of_elements) = user_char[element];
        element++;
        number_of_elements++;
    }

    return *this;
}

void Mstring::remove_last_char()
{
    main_buffer[number_of_elements - 1] = '\0';
    number_of_elements--;
}

void Mstring::remove_white_space_end()
{

    for (int i = (int)number_of_elements - 1; i >= 0; i--)
    {
        if (main_buffer[i] != ' ')
        {
            return;
        }
        remove_last_char();
    }
}

Mstring &Mstring::operator=(const Mstring &user_mstring)
{
    delete[] main_buffer;

    main_buffer = copy_array(user_mstring.main_buffer, user_mstring.current_size, false);
    number_of_elements = user_mstring.number_of_elements;
    current_size = user_mstring.current_size;

    return *this;
}

Mstring &Mstring::operator=(const char *user_char)
{
    int element = 0;

    while (user_char[element] != '\0')
    {
        if (number_of_elements >= current_size)
            expand_twice_the_size();
        *(main_buffer + element) = user_char[element];
        element++;
        number_of_elements++;
    }

    *(main_buffer + element) = '\0';
    number_of_elements++;

    return *this;
}

Mstring &Mstring::operator=(Mstring &&user_mstring) noexcept
{
    delete[] main_buffer;

    main_buffer = user_mstring.main_buffer;
    number_of_elements = user_mstring.number_of_elements;
    current_size = user_mstring.current_size;

    user_mstring.main_buffer = nullptr;
    user_mstring.number_of_elements = 0;
    user_mstring.current_size = 0;

    return *this;
}

bool Mstring::operator==(const Mstring &user_mstring)
{
    if (number_of_elements != user_mstring.number_of_elements)
        return false;

    for (size_t i = 0; i < number_of_elements; i++)
    {
        if (main_buffer[i] != user_mstring.main_buffer[i])
            return false;
    }

    return true;
}

bool Mstring::operator==(const char *user_char)
{
    int element = 0;

    while (user_char[element] != '\0')
    {
        if (main_buffer[element] != user_char[element])
            return false;
        element++;
    }

    return true;
}

Mstring &Mstring::operator+(const char *user_char)
{
    add_ms(user_char);

    return *this;
}

Mstring &Mstring::operator+(const Mstring &user_mstring)
{
    Mstring *new_mstring = new Mstring();

    new_mstring->add_ms(main_buffer);
    new_mstring->add_ms(user_mstring.main_buffer);

    return *new_mstring;
}

Mstring &Mstring::operator+=(const char *user_char)
{
    add_ms(user_char);

    return *this;
}

Mstring &Mstring::operator+=(const Mstring &user_mstring)
{
    add_ms(user_mstring.main_buffer);

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Mstring &mstring)
{

    for (unsigned int i = 0; i < mstring.size(); i++)
    {
        os << mstring.main_buffer[i];
    }

    return os;
}

std::istream &operator>>(std::istream &is, Mstring &mstring)
{
    char *user_input = new char[1024];
    std::cin >> user_input;

    mstring.add_ms(user_input);

    delete[] user_input;
    return is;
}

int Section::find_property(const Mstring &property_to_find) const
{
    if (block_data == nullptr)
        return -1;
    if (block_data->first == nullptr)
        return -1;

    Node<Pair> *current_node = block_data->first;

    int index = 0;
    while (current_node != nullptr)
    {
        if (current_node->data.property == property_to_find)
            return index;
        current_node = current_node->next;
        index++;
    }

    return -1;
}

int Section::find_selector(const Mstring &selector_to_find) const
{
    if (selectors == nullptr)
        return -1;
    if (selectors->first == nullptr)
        return -1;

    Node<Mstring> *current_node = selectors->first;

    int index = 0;
    while (current_node != nullptr)
    {
        if (current_node->data == selector_to_find)
            return index;
        current_node = current_node->next;
        index++;
    }

    return -1;
}

void Section::add_selector(const Mstring &selector_to_add)
{

    selectors_counter++;
    if (selectors == nullptr)
    {
        selectors = new LinkedList<Mstring>;
        Node<Mstring> *new_node = new Node<Mstring>;
        new_node->data = selector_to_add;
        selectors->first = new_node;
        selectors->last = new_node;
    }
    else
    {
        Node<Mstring> *new_node = new Node<Mstring>;
        new_node->data = selector_to_add;
        selectors->last->next = new_node;
        new_node->previous = selectors->last;
        selectors->last = new_node;
    }
}

void Section::add_value(const Mstring &value_to_add) const
{
    block_data->last->data.value = value_to_add;
}

void Section::add_value_position(const Mstring &value_to_add, int position) const
{

    Node<Pair> *current_node = block_data->first;

    for (int i = 0; i < position; i++)
    {
        current_node = current_node->next;
    }

    current_node->data.value = value_to_add;
}

void Section::add_property(const Mstring &property_to_add)
{

    block_data_counter++;
    if (block_data == nullptr || block_data->first == nullptr)
    {
        block_data = new LinkedList<Pair>;
        Node<Pair> *new_node = new Node<Pair>;
        new_node->data.property = property_to_add;
        block_data->first = new_node;
        block_data->last = new_node;
    }
    else
    {
        Node<Pair> *new_node = new Node<Pair>;
        new_node->data.property = property_to_add;
        block_data->last->next = new_node;
        new_node->previous = block_data->last;
        block_data->last = new_node;
    }
}

Mstring &Section::selector_index(int index) const
{

    Node<Mstring> *current_node = selectors->first;

    for (int i = 0; i < index; i++)
    {
        current_node = current_node->next;
    }

    return current_node->data;
}

Mstring &Section::value_index(int index) const
{
    Node<Pair> *current_node = block_data->first;

    for (int i = 0; i < index; i++)
    {
        current_node = current_node->next;
    }

    return current_node->data.value;
}

Mstring &Section::property_index(int index) const
{
    Node<Pair> *current_node = block_data->first;

    for (int i = 0; i < index; i++)
    {
        current_node = current_node->next;
    }

    return current_node->data.property;
}

bool Section::delete_property(const Mstring &property_to_delete)
{
    int index = find_property(property_to_delete);
    if (index == -1)
        return false;

    Node<Pair> *current_node = block_data->first;

    for (int i = 0; i < index; i++)
    {
        current_node = current_node->next;
    }

    // check if current node is only node
    if (current_node->previous == nullptr && current_node->next == nullptr)
    {
        block_data->first = nullptr;
        block_data->last = nullptr;
        delete current_node;
        block_data_counter--;
        return true;
    }
    if (current_node->previous == nullptr)
    {
        block_data->first = current_node->next;
        current_node->next->previous = nullptr;
    }
    else if (current_node->next == nullptr)
    {
        block_data->last = current_node->previous;
        current_node->previous->next = nullptr;
    }
    else
    {
        current_node->previous->next = current_node->next;
        current_node->next->previous = current_node->previous;
    }

    delete current_node;
    block_data_counter--;
    return true;
}

Section::~Section()
{
    if (selectors != nullptr)
    {
        while (selectors->first != nullptr)
        {
            Node<Mstring> *temp = selectors->first;
            selectors->first = selectors->first->next;
            delete temp;
        }
        delete selectors;
    }

    if (block_data != nullptr)
    {
        while (block_data->first != nullptr)
        {
            Node<Pair> *temp = block_data->first;
            block_data->first = block_data->first->next;
            delete temp;
        }
        delete block_data;
    }
}

Section *mainList::add_new_sections_tab(mainList *&address_of_last)
{
    mainList *new_list = new mainList();

    address_of_last->next = new_list;
    new_list->previous = address_of_last;
    address_of_last = new_list;

    return &new_list->sections[0];
}

Section *mainList::add_section(mainList *&address_of_last, int& all_sections_counter)
{
    if (curr_section_arr_size >= ARR_LIST_SIZE || is_used[7])
    {
        all_sections_counter++;
        // switch to the new list node with new array
        return add_new_sections_tab(address_of_last);
    }

    int additional_index = 0;
    while (is_used[curr_section_arr_size + additional_index])
    {
        additional_index++;
    }
    is_used[curr_section_arr_size + additional_index] = true;
    curr_section_arr_size++;
    return this->sections + curr_section_arr_size + additional_index - 1;
}

void mainList::remove_last_section(mainList *&address_of_last,mainList *&address_of_first, int& all_sections_counter)
{

    if (address_of_last == nullptr) return;
    mainList *node_delete = address_of_last;

    int index_to_delete = 0;

    for (int i = ARR_LIST_SIZE - 1; i >= 0; i--)
    {
        if (node_delete->is_used[i])
        {
            index_to_delete = i;
            break;
        }
    }

    handle_deleting_section(address_of_last, address_of_first, all_sections_counter, index_to_delete, node_delete);
}

bool mainList::remove_section_index(int index, mainList *&address_of_last, mainList *&address_of_first, int& all_sections_counter)
{

    mainList *node_delete = address_of_first;

    while (index >= node_delete->curr_section_arr_size)
    {
        index -= node_delete->curr_section_arr_size;
        node_delete = node_delete->next;
        if (node_delete == nullptr) return false;
    }

    for (int i = 0; i <= index; i++)
    {
        if (!node_delete->is_used[i])
            index++;
    }

    handle_deleting_section(address_of_last, address_of_first, all_sections_counter, index, node_delete);

    return true;
}

void mainList::handle_deleting_section(mainList *&address_of_last, mainList *&address_of_first, int &all_sections_counter, int index_to_delete, mainList* node_delete) {

    node_delete->is_used[index_to_delete] = false;
    delete node_delete->sections[index_to_delete].block_data;
    delete node_delete->sections[index_to_delete].selectors;
    node_delete->sections[index_to_delete].block_data = nullptr;
    node_delete->sections[index_to_delete].selectors = nullptr;
    node_delete->sections[index_to_delete].block_data_counter = 0;
    node_delete->sections[index_to_delete].selectors_counter = 0;
    node_delete->curr_section_arr_size--;

    if (node_delete->curr_section_arr_size <= 0)
    {
        if (node_delete->previous != nullptr)
        {
            node_delete->previous->next = node_delete->next;
        }
        if (node_delete->next != nullptr)
        {
            node_delete->next->previous = node_delete->previous;
        }
        // check if node_delete is first
        if (node_delete == address_of_first)
        {
            address_of_first = node_delete->next;
        }
        // same thing with last
        if (node_delete == address_of_last)
        {
            address_of_last = node_delete->previous;
        }
        delete node_delete->sections->block_data;
        delete node_delete->sections->selectors;
        all_sections_counter--;
    }
}

Section *mainList::i_index(int index)
{
    if (index >= curr_section_arr_size)
    {
        // switch to the next list node with new array
        if (next != nullptr)
        {
            return next->i_index(index - curr_section_arr_size);
        }
        else
            return nullptr;
    }

    for (int i = 0; i <= index; i++)
    {
        if (!is_used[i])
            index++;
    }

    return &sections[index];
}

int mainList::number_of_active_sections()
{
    int counter = 0;

    mainList *curr_list = this;
    while (curr_list != nullptr)
    {
        counter += (int)curr_list->curr_section_arr_size;
        curr_list = curr_list->next;
    }
    return counter;
}

mainList::mainList()
{
    for (int i = 0; i < ARR_LIST_SIZE; i++)
    {
        is_used[i] = false;
        sections[i] = Section();
    }
    curr_section_arr_size = 1;
    is_used[0] = true;
}

mainList::~mainList()
{
    while (next != nullptr)
    {
        mainList *temp = next;
        next = next->next;
        delete temp;
    }
}
