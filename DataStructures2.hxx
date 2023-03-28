#ifndef INC_1_CSS_DATASTRUCTURES2_HXX
#define INC_1_CSS_DATASTRUCTURES2_HXX

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

int Node::find_property(const Mstring& user_attribute) {
    for (int i = 0; i < properties.size(); i++) {
        if (properties[i] == user_attribute) return i;
    }

    return -1;
}

int Node::find_selector(const Mstring &user_selector) {
    for (int i = 0; i < selectors.size(); i++) {
        if (selectors[i] == user_selector) return i;
    }

    return -1;
}

bool Node::delete_property(const Mstring &user_property) {
    int index = 0;

    index = find_property(user_property);

    if(index < 0) return false;

    properties.pop_index(index);

    return true;
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

bool LinkedList::pop_back() {
    if (first == nullptr) return false;

    Node* previous_node = last->previous;
    delete last;
    last = previous_node;
    last->next = nullptr;

    return true;
}

bool LinkedList::pop_front() {
    if (first == nullptr) return false;

    Node* next_node = first->next;
    delete first;
    first = next_node;
    if(first == nullptr) return true;
    first->previous = nullptr;

    return true;
}

bool LinkedList::pop(size_t index) {
    if (first == nullptr) return false;
    if(index == 0) {
        return pop_front();
    }

    Node *current_node = first;

    for (int i = 0; i < index; i++) {
        if(current_node == nullptr){
            return false;
        }
        current_node = current_node->next;
    }

    if(current_node == last) {
        return pop_back();
    }

    if(current_node == nullptr) return false;

    current_node->previous->next = current_node->next;
    current_node->next->previous = current_node->previous;
    delete current_node;
    return true;
}

int LinkedList::size() {
    int size = 0;
    if(first == nullptr) return 0;

    Node* current_node = first;

    while (current_node != nullptr) {
        size++;
        current_node = current_node->next;
    }

    return size;
}

Node* LinkedList::operator[](size_t index) {
    Node* index_node = first;

    for(int i = 0; i < index; i++) {
        if(index_node == nullptr){
            return nullptr;
        }

        index_node = index_node->next;
    }

    return index_node;
}

#endif //INC_1_CSS_DATASTRUCTURES2_HXX
