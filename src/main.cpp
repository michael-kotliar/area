#include "polygon.h"


using namespace std;


int main(int argc, char* argv[]){
	string coordinate_file = argv[1];
    Polygon polygon = Polygon(coordinate_file);
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
