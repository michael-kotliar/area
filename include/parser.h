#ifndef PARSER_H
#define PARSER_H

#include "cxxopts.hpp"

using namespace std;

class Parser {
public:
    Parser (int argc, char * argv[]);
    string coord;
};

#endif