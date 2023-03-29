#include "DataStructures.h"

int main() {
    mainList* main_list = new mainList;
    main_list->init_main_list();
    main_list->sections[0].add_selector("body");
    main_list->sections[0].add_selector("div");
    main_list->sections[0].add_property("color");
    main_list->sections[0].add_value("red");
    main_list->sections[0].add_property("padding");
    main_list->sections[0].add_value("none");
//    std::cout<<main_list->sections[0].find_selector("div")<<"\n";
//    std::cout<<main_list->sections[0].find_property("padding")<<"\n";

    main_list->add_section();
    main_list->sections[1].add_selector("body");
    main_list->sections[1].add_selector("div");
    main_list->sections[1].add_property("color");
    main_list->sections[1].add_value("red");
    main_list->i_index(1)->add_property("padding");
    std::cout<<main_list->sections[1].find_property("padding")<<"\n";

    main_list->add_new_sections_tab();
    main_list->i_index(9)->add_selector("body");
    std::cout<<main_list->i_index(9)->find_selector("body");
    return 0;
}
