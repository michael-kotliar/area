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
    int min_x = edges[0].start.x;
    int max_x = edges[0].start.x;
    int min_y = edges[0].start.y;
    int max_y = edges[0].start.y;
    for (int i=0; i < edges.size(); i++){
        if (edges[i].start.x < min_x){
            min_x = edges[i].start.x;
        };
        if (edges[i].end.x < min_x){
            min_x = edges[i].end.x;
        };
        if (edges[i].start.y < min_y){
            min_y = edges[i].start.y;
        };
        if (edges[i].end.y < min_y){
            min_y = edges[i].end.y;
        };
        if (edges[i].start.x > max_x){
            max_x = edges[i].start.x;
        };
        if (edges[i].end.x > max_x){
            max_x = edges[i].end.x;
        };
        if (edges[i].start.y > max_y){
            max_y = edges[i].start.y;
        };
        if (edges[i].end.y > max_y){
            max_y = edges[i].end.y;
        };
    }
    width = (max_x - min_x) + 2 * offset;
    height = (max_y - min_y) + 2 * offset;
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


void Polygon::load_data(const string &path){
    cout << endl <<"Loading polygon model from " << path << endl;
    ifstream input_stream(path);
    string line;
    while (getline(input_stream, line)){
        vector<string> values = split_by_delim(line, ",");
        Point start = Point(atoi(values[0].c_str()) * resolution, atoi(values[1].c_str()) * resolution);
        Point end = Point(atoi(values[2].c_str()) * resolution, atoi(values[3].c_str()) * resolution);
        Edge edge = Edge(start, end);
        edges.push_back(edge);
    }
}