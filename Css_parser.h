#ifndef INC_1_CSS_CSS_PARSER_H
#define INC_1_CSS_CSS_PARSER_H
#include "DataStructures.h"

class Css_parser {

    Section sectionsx;
//    LinkedList sections;
//    Node* curr_section = nullptr;
    Mstring input;
    Mstring global_attribute;
    Mstring global_value;

    bool commands = false;
    bool selectors = true;
    bool global_attributes_section = false;
    int attribute_reoccurance = -1;
    int question_counter = 0;
    int star_counter = 0;

    char main_command;
    Mstring command_part1;
    int command_part1_digit = 0;
    Mstring command_part2;
    int command_part2_digit = 0;
    int command_part_counter = 0;

    char input_char;
    char temp_input[2] = { 0 };

public:
    void read_css();
    void read_commands();
    void read_command_data();
    void global_attribute_data();
    void read_char();
    void read_attribute();
    void handle_global_attribute();
    void read_selector();
    void start();
    void handle_rest_of_commands();
    void assign_type_command(Mstring& user_command, int& command_part_digit);
};


#endif //INC_1_CSS_CSS_PARSER_H
