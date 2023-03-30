#include "DataStructures.h"

int main() {
    mainList* main_list = new mainList;
    main_list->init_main_list();

    Section* curr_section = &main_list->sections[0];

    //create 5 css sections and in each one add 1 selector and 1 property and 1 value

    //section 1
    curr_section->add_selector("body");
    curr_section->add_property("background-color");
    curr_section->add_value("red");

    //section 2
    curr_section = main_list->last->add_section();
    curr_section->add_selector("p");
    curr_section->add_property("font-size");
    curr_section->add_value("12px");

    //section 3
    curr_section = main_list->last->add_section();
    curr_section->add_selector("h1");
    curr_section->add_property("font-size");
    curr_section->add_value("24px");

    //section 4
    curr_section = main_list->last->add_section();
    curr_section->add_selector("h2");
    curr_section->add_property("font-size");
    curr_section->add_value("18px");

    //section 5
    curr_section = main_list->last->add_section();
    curr_section->add_selector("h3");
    curr_section->add_property("font-size");
    curr_section->add_value("14px");

    main_list->remove_last_section();
    main_list->remove_last_section();
//    main_list->remove_section_index(2);

    return 0;
}
