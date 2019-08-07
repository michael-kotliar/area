#include <polygon.h>
#include <utils.h>


Vertex::Vertex(const int &a, const int & b) {
    x = a;
    y = b;
}


void Vertex::print(){
    cout << "[" << x << ", " << y << "]" << endl;
}


Edge::Edge (const Vertex &a, const Vertex &b){
    start = a;
    end = b;
}


void Edge::print(){
    cout << "[" << start.x << ", " << start.y << "]  -  [" << end.x << ", " << end.y << "]" <<  endl;
}


Polygon::Polygon(const string &path){
    load(path);
}


void Polygon::print_edges(){
    cout << endl << "Printing " << edges.size() << " polygon's edges" << endl;
    for (int i=0; i<edges.size(); i++){
        edges[i].print();
    }
}

void Polygon::print_vertices(){
    cout << endl << "Printing " << vertices.size() << " polygon's vertices" << endl;
    for (int i=0; i<vertices.size(); i++){
        vertices[i].print();
    }
}


void Polygon::load(const string &path){
    cout << endl <<"Loading polygon model from " << path << endl;
    ifstream input_stream(path);
    string line;
    while (getline(input_stream, line)){
        vector<string> values = split_by_delim(line, ",");
        Vertex start = Vertex(atoi(values[0].c_str()), atoi(values[1].c_str()));
        Vertex end = Vertex(atoi(values[2].c_str()), atoi(values[3].c_str()));
        vertices.push_back(start);
        vertices.push_back(end);
        Edge edge = Edge(start, end);
        edges.push_back(edge);
    }
}