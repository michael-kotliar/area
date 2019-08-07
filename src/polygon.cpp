#include <polygon.h>
#include <utils.h>


Edge::Edge (const Point &a, const Point &b){
    start = a;
    end = b;
}


void Edge::print(){
    cout << "[" << start.x << ", " << start.y << "]  -  [" << end.x << ", " << end.y << "]" <<  endl;
}


Polygon::Polygon(const string &path){
    resolution = 50;
    offset = 50;
    load_data(path);
    setup_canvas();
    draw();
}

void Polygon::setup_canvas(){
    int min_x = vertices[0].x;
    int max_x = vertices[0].x;
    int min_y = vertices[0].y;
    int max_y = vertices[0].y;
    for (int i=0; i < vertices.size(); i++){
        if (vertices[i].x < min_x){
            min_x = vertices[i].x;
        };
        if (vertices[i].y < min_y){
            min_y = vertices[i].y;
        };
        if (vertices[i].x > max_x){
            max_x = vertices[i].x;
        };
        if (vertices[i].y > max_y){
            max_y = vertices[i].y;
        };
    }
    width = (max_x - min_x) + 2 * offset;
    height = (max_y - min_y) + 2 * offset;
    for (int i=0; i<vertices.size(); i++){
        vertices[i].y = height - vertices[i].y - offset;
        vertices[i].x = vertices[i].x + offset;
    }
    for (int i=0; i<edges.size(); i++){
        edges[i].start.y = height - edges[i].start.y - offset;
        edges[i].start.x = edges[i].start.x + offset;
        edges[i].end.y = height - edges[i].end.y - offset;
        edges[i].end.x = edges[i].end.x + offset;
    }
    cout << "width " << width << ", height " << height << endl; 
}

void Polygon::draw(){
    image = Mat(height, width, CV_8UC3, Scalar(0, 0, 0));
    for (int i=0; i<edges.size(); i++){
        line(image, edges[i].start, edges[i].end, Scalar(200,200,200));
    }
}

void Polygon::show(){
    namedWindow("Area", WINDOW_AUTOSIZE );
    imshow("Polygon", image);
    waitKey(0);
}


void Polygon::print_edges(){
    cout << endl << "Printing " << edges.size() << " polygon's edges (resolution " << resolution << ")" << endl;
    for (int i=0; i<edges.size(); i++){
        edges[i].print();
    }
}

void Polygon::print_vertices(){
    cout << endl << "Printing " << vertices.size() << " polygon's vertices (resolution " << resolution << ")" << endl;
    for (int i=0; i<vertices.size(); i++){
        cout << "[" << vertices[i].x << ", " << vertices[i].y << "]" <<  endl;
    }
}


void Polygon::load_data(const string &path){
    cout << endl <<"Loading polygon model from " << path << endl;
    ifstream input_stream(path);
    string line;
    while (getline(input_stream, line)){
        vector<string> values = split_by_delim(line, ",");
        Point start = Point(atoi(values[0].c_str())*resolution, atoi(values[1].c_str())*resolution);
        Point end = Point(atoi(values[2].c_str())*resolution, atoi(values[3].c_str())*resolution);
        vertices.push_back(start);
        vertices.push_back(end);
        Edge edge = Edge(start, end);
        edges.push_back(edge);
    }
}