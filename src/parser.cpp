#include <parser.h>

Parser::Parser (int argc, char * argv[]){
    cxxopts::Options opt_parser("Area", "Polygon Area Calculator");
    opt_parser.add_options()("coord", "Polygon coordinates file", cxxopts::value<string>());
    opt_parser.parse(argc, argv);
    coord = opt_parser["coord"].as<string>();
}