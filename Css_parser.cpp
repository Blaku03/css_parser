#include "Css_parser.h"

void Css_parser::start() {
    while(true){
        std::cin>>input;
        if(!commands) {
            if(input == "????"){
                commands = true;
                input.clear();
                std::cout<<"Commands: "<<std::endl;
                continue;
            }
        }
        else {
            if(input == "****"){
                commands = false;
                input.clear();
                std::cout<<"Commands ended"<<std::endl;
                continue;
            }
        }
    }
}