#include "Css_parser.h"

void Css_parser::read_css() {
    if(input == "????"){
        commands = true;
        input.clear();
        std::cout<<"Commands: "<<std::endl;
    }

    if(input_char == '{'){
        attributes = true;
        input.remove_last_char();
        curr_section->selectors.push_back(input);
        input.clear();
    }

    if(input_char == '}'){
        attributes = false;
        input.clear();
        sections.add_section();
        curr_section = curr_section->next;
    }

    if(input_char == ','){
        if(!attributes){
            input.remove_last_char();
            curr_section->selectors.push_back(input);
            input.clear();
        }
    }

    if(input_char == ':'){
        input.remove_last_char();
        if(curr_section->find_attribute(input)){
            attribute_reoccurance = true;
        }
        else{
            curr_section->properties.push_back(input);
        }
        input.clear();
    }

    if(input_char == ';'){
       input.remove_last_char();
       if(attribute_reoccurance){
           curr_section->values[curr_section->find_attribute(input)] = input;
           attribute_reoccurance = false;
       }
       else
           curr_section->values.push_back(input);
       input.clear();
    }
}

void Css_parser::read_commands() {
    if(input == "****"){
        commands = false;
        input.clear();
        std::cout<<"Commands ended"<<std::endl;
    }

    if(input_char == '?' && command_part_counter < 2){
        std::cout<<sections.size() - 1;
        std::cout<<sections[0]->properties[0]<<std::endl;
        std::cout<<sections[0]->values[0];
        input.clear();
    }

    if(input_char == ',' || command_part_counter == 2){
        if(command_part_counter == 0){
           command_part_counter++;
           assign_type_command(input, command_part1_digit);
           command_part1 = input;
           if(command_part1.size() > 0) command_part1.remove_last_char();
           input.clear();
           return;
        }

        if(command_part_counter == 1){
           command_part_counter++;
           main_command = input[0];
           input.clear();
           return;
        }

        if(command_part_counter == 2){
           command_part_counter = 0;
           assign_type_command(input, command_part2_digit);
           command_part2 = input;
           input.clear();
           
        }

    }
}

void Css_parser::read_char() {
    if(command_part_counter == 2){
        std::cin>>input;
        return;
    }
    std::cin>>input_char;
    temp_input[0] = input_char;
    input += temp_input;
}

void Css_parser::start() {
    sections.add_section();
    curr_section = sections[0];

    //main loop
    while(true){
        read_char();

        if(!commands) {
            read_css();
            continue;
        }
        else {
            read_commands();
            continue;
        }
    }
}

void Css_parser::assign_type_command(Mstring &user_command, int& command_part_digit) {
    command_part_digit = 0;
    int pow_10 = 1;
    for(int i = user_command.size() - 1; i >= 0; i++){
        if(!isdigit(user_command[i])) return;
           command_part_digit += (user_command[i] - '0') * pow_10;
              pow_10 *= 10;
    }

    user_command.clear();
}