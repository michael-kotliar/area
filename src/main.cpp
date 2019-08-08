#include "parser.h"
#include "polygon.h"


using namespace std;


int main(int argc, char* argv[]){
	Parser custom_parser = Parser(argc, argv);
    Polygon polygon = Polygon(custom_parser.coord);
    if (polygon.validate()){
        double area = polygon.calculate_area();
        cout << "Area = " << area << endl;
        polygon.show();
        waitKey(0);
    } else {
        cout << "Cannot build polygon: isn't single OR isn't closed OR includes holes" << endl;
    }
    return 0;
}
