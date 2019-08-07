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
        line(image, edges[i].start, edges[i].end, Scalar(255,255,255));
    }
}

bool Polygon::shift(int &x, int &y){
    for (int i=x-1; i<=x+1; i++){
        for (int j=y-1; j<=y+1; j++){
            if (i==x && j==y){
                continue;
            }
            Vec3b &color_val = image.at<Vec3b>(Point(i,j));
            if (color_val[0] == 255 && color_val[1] == 255 && color_val[2] == 255){
                color_val = Vec3b(0,255,0);
                x = i;
                y = j;
                return true;
            }
        }
    }
    return false;
}

bool Polygon::is_closed(const int &x, const int &y){
    int count_green = 0;
    int count_white = 0;
    for (int i=x-1; i<=x+1; i++){
        for (int j=y-1; j<=y+1; j++){
            if (i==x && j==y){
                continue;
            }
            Vec3b &color_val = image.at<Vec3b>(Point(i,j));
            if (color_val[0] == 0 && color_val[1] == 255 && color_val[2] == 0){
                count_green++;
            };
            if (color_val[0] == 255 && color_val[1] == 255 && color_val[2] == 255){
                count_white++;
            }
        }
    }
    if (count_white==0 && count_green>=2){
        return true;
    }
    return false;
}

bool Polygon::validate(){
    int start_x = edges[0].start.x;
    int start_y = edges[0].start.y;
    cout << "start_x " << start_x << ", start_y " << start_y << endl;
    int cur_x = start_x;
    int cur_y = start_y;
    while (shift(cur_x, cur_y)){
        if (is_closed(cur_x, cur_y)){
            return true;
        }
    }
    return false;
}

void Polygon::show(){
    namedWindow("Area", WINDOW_AUTOSIZE);
    imshow("Polygon", image);
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