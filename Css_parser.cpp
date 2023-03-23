#include "Css_parser.h"

void Css_parser::read_css() {
    if(input == "????"){
        commands = true;
        input.clear();
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
        else input+=" ";
    }

    if(input_char == ':'){
        input.remove_last_char();
        try {
            bool temp = curr_section->find_property(input);
            if(temp){
                attribute_reoccurance = true;
            }
        }
        catch(std::out_of_range& e){}

        curr_section->properties.push_back(input);
        input.clear();
    }

    if(input_char == ';'){
       input.remove_last_char();
       if(attribute_reoccurance){
           curr_section->values[curr_section->find_property(input)] = input;
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
    }

    if(input_char == '?' && command_part_counter < 2){
        std::cout<<"? == ";
        std::cout<<sections.size() - 1<<"\n";
        input.clear();
    }

    if(input_char == ',' || command_part_counter == 2){
        if(command_part_counter == 0){
           command_part_counter++;
           input.remove_last_char();
           assign_type_command(input, command_part1_digit);
           command_part1 = input;
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
           handle_rest_of_commands();
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

void Css_parser::handle_rest_of_commands() {
    if(main_command == 'S'){
        if(command_part2 == "?" && command_part1_digit > 0){
            try{
                std::cout<<command_part1_digit<<","<<main_command<<",? == ";
                std::cout<<sections[--command_part1_digit]->selectors.size()<<"\n";
                return;
            }
            catch(std::exception& e){
                return;
            }
        }

        if(command_part1_digit > 0 && command_part2_digit > 0){
            try{
                std::cout<<command_part1_digit<<","<<main_command<<","<<command_part2_digit<<" == ";
                std::cout<<sections[--command_part1_digit]->selectors[--command_part2_digit]<<"\n";
                return;
            }
            catch(std::exception& e){
                return;
            }
        }

        if(command_part2 == "?" && command_part1.size() > 0){
            try{
                int count = 0;
                std::cout<<command_part1<<","<<main_command<<",? == ";
                for(int i = 0; i < sections.size(); i++){
                    for(int j = 0; j < sections[i]->selectors.size(); j++){
                        if(sections[i]->selectors[j] == command_part1){
                            count++;
                        }
                    }
                }
                std::cout<<count<<"\n";
                return;
            }
            catch(std::exception& e){
                return;
            }
        }
    }

    if(main_command == 'A'){
        if(command_part2 == "?" && command_part1_digit > 0){
            try{
                std::cout<<command_part1_digit<<","<<main_command<<",? == ";
                std::cout<<sections[--command_part1_digit]->properties.size()<<"\n";
                return;
            }
            catch(std::out_of_range& e){
                return;
            }
        }

        if(command_part1_digit > 0 && command_part2.size() > 0){
            try{
                Mstring ans = sections[--command_part1_digit]->values[sections[command_part1_digit]->find_property(command_part2)];
                std::cout<<command_part1_digit + 1<<","<<main_command<<","<<command_part2<<" == ";
                std::cout<<ans<<"\n";
                return;
            }
            catch(std::out_of_range& e){
                return;
            }
        }

        if(command_part1.size() > 0 && command_part2 == "?"){
            int count = 0;
            try{
                for(int i = 0; i < sections.size(); i++){
                    for(int j = 0; j < sections[i]->properties.size(); j++){
                        if(sections[i]->properties[j] == command_part1){
                            count++;
                        }
                    }
                }
                std::cout<<command_part1<<","<<main_command<<",? == ";
                std::cout<<count<<"\n";
            }
            catch(std::out_of_range& e){
                return;
            }
        }
    }

    if(main_command == 'E'){
        try {
           for(int i = sections.size() - 1; i >= 0; i--){
               for(int j = 0; j < sections[i]->selectors.size(); j++){
                   if(sections[i]->selectors[j] == command_part1){
                       std::cout<<command_part1<<","<<main_command<<","<<command_part2<<" == ";
                       std::cout<<sections[i]->values[sections[i]->find_property(command_part2)]<<"\n";
                       return;
                   }
               }
           }
        }
        catch (std::out_of_range& e){
            return;
        }
    }

    if(main_command == 'D'){
        if(command_part2 == "*"){
            try{
                sections.pop(command_part1_digit - 1);
                std::cout<<command_part1_digit<<","<<main_command<<","<<command_part2<<" == deleted\n";
                return;
            }
            catch (std::out_of_range& e){
                return;
            }
        }

        if(command_part2.size() > 0){
            try{
                if(sections[--command_part1_digit]->delete_property(command_part2)){
                    std::cout<<command_part1_digit + 1<<","<<main_command<<","<<command_part2<<" == deleted\n";
                    if(sections[command_part1_digit]->properties.size() == 0) sections.pop(command_part1_digit);
                }
            }
            catch (std::out_of_range& e){
                return;
            }
        }
    }
}

void Css_parser::assign_type_command(Mstring &user_command, int& command_part_digit) {
    command_part_digit = 0;
    int pow_10 = 1;
    for(int i = user_command.size() - 1; i >= 0; i--){
        if(!isdigit(user_command[i])){
            command_part_digit = 0;
            return;
        }
        command_part_digit += (user_command[i] - '0') * pow_10;
        pow_10 *= 10;
    }

    user_command.clear();
}