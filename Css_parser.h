#ifndef INC_1_CSS_CSS_PARSER_H
#define INC_1_CSS_CSS_PARSER_H
#include "Linkedlist.h"

class Css_parser {

    LinkedList sections;
    bool commands = false;
    Mstring input;

public:
    void start();
};


#endif //INC_1_CSS_CSS_PARSER_H
