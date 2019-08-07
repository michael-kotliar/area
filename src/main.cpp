#include "parser.h"
#include "polygon.h"


using namespace std;


int main(int argc, char* argv[]){
	Parser custom_parser = Parser(argc, argv);
    Polygon polygon = Polygon(custom_parser.coord);
    polygon.print_edges();
    polygon.print_vertices();
    return 0;
}
