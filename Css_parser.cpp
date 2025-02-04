#include "Css_parser.h"

void Css_parser::read_css() {
    if(selectors) read_selector();

    if(question_counter == 3){
        commands = true;
        input.clear();
        question_counter = 0;
        mainList::remove_last_section(last_list,sections_list, all_active_arr_sections);
        return;
    }

    if(input_char == '{'){
        selectors = false;
        if(input_char == input[input.size() - 1]) input.remove_last_char();
        input.remove_white_space_end();

        int selector_reoccurrence  = curr_section->find_selector(input);


        if(selector_reoccurrence == -1 && input.size() > 0){
            curr_section->add_selector(input);
        }
        input.clear();
        return;
    }

    if(input_char == '}'){
        selectors = true;
        input.clear();
        curr_section = last_list->add_section(last_list, all_active_arr_sections);
        return;
    }

    if(input_char == ','){

        if(input_char == input[input.size() - 1]) input.remove_last_char();
        input.remove_white_space_end();

        int selector_reoccurrence = curr_section->find_selector(input);

        if(selector_reoccurrence == -1 && input.size() > 0){
            curr_section->add_selector(input);
        }
        input.clear();
        return;
    }

    if(input_char == ':'){
        if(selectors) return;

        if(input_char == input[input.size() - 1]) input.remove_last_char();
        input.remove_white_space_end();

        attribute_reoccurrence = curr_section->find_property(input);
        if(attribute_reoccurrence == -1 && input.size() > 0){
            curr_section->add_property(input);
        }

        input.clear();
        read_attribute();
    }

}

void Css_parser::read_command_data() {

    star_counter = 0;
    if(input_char == '*') star_counter++;
    while(input_char != ',' && input_char != '\n' && input_char != '?'){
        if(!std::cin.good()) return;
        input_char = (char)std::getchar();

        if(input_char == '*'){
            star_counter++;
            if(star_counter == 4) return;
            continue;
        }

        star_counter = 0;

        temp_input[0] = input_char;
        input += temp_input;
    }
}

void Css_parser::read_commands() {

    read_command_data();

    if(star_counter == 4){
        commands = false;
        star_counter = 0;
        input_char = '\0';

        if(sections_list == nullptr || sections_list->curr_section_arr_size == 0){
            sections_list = new mainList;
            last_list = sections_list;
            curr_section = &sections_list->sections[0];
            all_active_arr_sections = 1;
            input.clear();
            return;
        }

        curr_section = last_list->add_section(last_list, all_active_arr_sections);
        input.clear();
        return;
    }

    if(input_char == '?' && command_part_counter < 2){
        std::cout<<"? == ";
        std::cout<<sections_list->number_of_active_sections()<<"\n";
        input.clear();
        input_char = '\0';
        return;
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

void Css_parser::read_attribute() {

    input_char = (char)std::getchar();

    if(input_char != ' '){
        temp_input[0] = input_char;
        input += temp_input;
    }

    while(input_char != ';' && input_char != '\n' && input_char != '}'){
        input_char = (char)std::getchar();
        temp_input[0] = input_char;
        input += temp_input;
    }


    if(input_char == input[input.size() - 1]) input.remove_last_char();
    input.remove_white_space_end();
    if(input.size() == 0) return;

    if(attribute_reoccurrence != -1){
        curr_section->add_value_position(input, attribute_reoccurrence);
        attribute_reoccurrence = -1;
    }
    else
        curr_section->add_value(input);

    if(input_char == '}'){
        selectors = true;
        curr_section = last_list->add_section(last_list, all_active_arr_sections);
    }

    input.clear();
}

void Css_parser::read_selector() {
    question_counter = 0;

    while(input_char != '{' && input_char != ','){
        input_char = (char)std::getchar();

        if(input_char == '?') {
            question_counter++;
            if(question_counter == 3) return;
            continue;
        }
        question_counter = 0;

        if(input_char == '\n') {
            continue;
        }

        temp_input[0] = input_char;
        input += temp_input;
    }

}

void Css_parser::start() {
    sections_list = new mainList;
    last_list = sections_list;
    curr_section = &sections_list->sections[0];

    //main loop
    while(std::cin){
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
            Section* section = sections_list->i_index(--command_part1_digit);
            if(section != nullptr) {
                std::cout<<command_part1_digit + 1<<","<<main_command<<",? == ";
                std::cout<<section->selectors_counter<<"\n";
                return;
            }
        }

        if(command_part1_digit > 0 && command_part2_digit > 0){
            Section* section = sections_list->i_index(--command_part1_digit);
            if(section == nullptr) return;
            if(section->selectors_counter < command_part2_digit) return;
            Mstring selector = section->selector_index(--command_part2_digit);
            if(selector.size() == 0) return;
            std::cout<<command_part1_digit + 1<<","<<main_command<<","<<command_part2_digit + 1<<" == ";
            std::cout<<selector<<"\n";
            return;
        }

        if(command_part2 == "?" && command_part1.size() > 0){
            int count = 0;
            std::cout<<command_part1<<","<<main_command<<",? == ";
            mainList* curr_list = sections_list;

            for(int i = 0; i < all_active_arr_sections; i++){
                for(int j = 0; j < ARR_LIST_SIZE; j++){
                    if(!curr_list->is_used[j]) continue;
                    for(int k = 0; k < curr_list->sections[j].selectors_counter; k++){
                        if(curr_list->sections[j].selector_index(k) == command_part1){
                            count++;
                            break;
                        }
                    }
                }
                if(curr_list->next == nullptr) break;
                curr_list = curr_list->next;
            }
            std::cout<<count<<"\n";
            return;
        }
    }

    if(main_command == 'A'){
        if(command_part2 == "?" && command_part1_digit > 0){
            Section* section = sections_list->i_index(--command_part1_digit);
            if(section != nullptr) {
                std::cout<<command_part1_digit + 1<<","<<main_command<<",? == ";
                std::cout<<section->block_data_counter<<"\n";
            }
            return;
        }

        if(command_part1_digit > 0 && command_part2.size() > 0){
            Section* section = sections_list->i_index(--command_part1_digit);
            if(section == nullptr) return;
            int index = section->find_property(command_part2);
            if(index != -1){
                std::cout<<command_part1_digit + 1<<","<<main_command<<","<<command_part2<<" == ";
                std::cout<<section->value_index(index)<<"\n";
            }
            return;
        }

        if(command_part1.size() > 0 && command_part2 == "?"){
            int count = 0;
            mainList* curr_list = sections_list;

            for(int i = 0; i < all_active_arr_sections; i++){
                for(int j = 0; j < ARR_LIST_SIZE; j++){
                    if(!curr_list->is_used[j]) continue;
                    for(int k = 0; k < curr_list->sections[j].block_data_counter; k++){
                        if(curr_list->sections[j].property_index(k) == command_part1){
                            count++;
                            break;
                        }
                    }
                }
                if(curr_list->next == nullptr) break;
                curr_list = curr_list->next;
            }

            std::cout<<command_part1<<","<<main_command<<",? == ";
            std::cout<<count<<"\n";
        }
    }

    if(main_command == 'E'){
        mainList* curr_list = last_list;

        for(int i = 0; i < all_active_arr_sections; i++){
            for(int j = ARR_LIST_SIZE - 1; j >= 0; j--){
                if(!curr_list->is_used[j]) continue;
                for(int k = curr_list->sections[j].selectors_counter - 1; k >= 0; k--){
                    if(curr_list->sections[j].selector_index(k) == command_part1){
                        int index = curr_list->sections[j].find_property(command_part2);
                        if(index != -1){
                            std::cout<<command_part1<<","<<main_command<<","<<command_part2<<" == ";
                            std::cout<<curr_list->sections[j].value_index(index)<<"\n";
                            return;
                        }
                    }
                }
            }
            if(curr_list->previous == nullptr) break;
            curr_list = curr_list->previous;
        }
    }

    if(main_command == 'D'){
        if(command_part2 == "*"){
            if(sections_list == nullptr) return;
            if(sections_list->number_of_active_sections() == 0) return;
            if(command_part1_digit > 0){
                if(mainList::remove_section_index(--command_part1_digit, last_list, sections_list, all_active_arr_sections)){
                    std::cout<<command_part1_digit + 1<<","<<main_command<<","<<command_part2<<" == deleted\n";
                    return;
                }
            }
        }

        if(command_part2.size() > 0){
            if(sections_list == nullptr) return;
            Section* section = sections_list->i_index(--command_part1_digit);
            if(section == nullptr) return;
            if(section->delete_property(command_part2)){
                std::cout<<command_part1_digit + 1<<","<<main_command<<","<<command_part2<<" == deleted\n";
                if(section->block_data_counter == 0){
                    mainList::remove_section_index(command_part1_digit, last_list, sections_list, all_active_arr_sections);
                }
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