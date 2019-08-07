#include <polygon.h>
#include <utils.h>


Edge::Edge (const Point &a, const Point &b){
    start = a;
    end = b;
}


Polygon::Polygon(const string &path){
    resolution = 300;
    offset = 5;
    lookup_direction.push_back(pair <int, int > (-1, -1) );
    lookup_direction.push_back(pair <int, int > (0, -1) );
    lookup_direction.push_back(pair <int, int > (1, -1) );
    lookup_direction.push_back(pair <int, int > (1, 0) );
    lookup_direction.push_back(pair <int, int > (1, 1) );
    lookup_direction.push_back(pair <int, int > (0, 1) );
    lookup_direction.push_back(pair <int, int > (-1, 1) );
    lookup_direction.push_back(pair <int, int > (-1, 0) );
    load_data(path);
    setup_canvas();
    build();
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
}

void Polygon::build(){
    image = Mat(height, width, CV_8UC3, Scalar(0, 0, 0));
    for (int i=0; i<edges.size(); i++){
        line(image, edges[i].start, edges[i].end, Scalar(255,255,255));
    }
}

bool Polygon::make_step(int &x, int &y, vector <Point> &available_steps){
    for (int k = 0; k < lookup_direction.size(); k++){
        Point cur_point = Point(x + lookup_direction[k].first, y + lookup_direction[k].second);
        Vec3b &color = image.at<Vec3b>(cur_point);
        if (color[0] == 255 && color[1] == 255 && color[2] == 255){
            available_steps.push_back(cur_point);        // check if it already added
        };
    }
    if (available_steps.size() > 0){
        Point next_step = available_steps.back();
        available_steps.pop_back();
        Vec3b &color = image.at<Vec3b>(next_step);
        color = Vec3b(0,255,0);
        x = next_step.x;
        y = next_step.y;
        return true;
    }
    return false;
}

bool Polygon::is_single(){
    for (int i = 0; i < edges.size(); i++){
        Point start_point (edges[i].start.x, edges[i].start.y);
        Vec3b &color = image.at<Vec3b>(start_point);
        if (color[0] != 0 || color[1] != 255 || color[2] != 0){
            return false;
        };
    }
    return true;
}

bool Polygon::validate(){
    int start_x = edges[0].start.x;
    int start_y = edges[0].start.y;
    int cur_x = start_x;
    int cur_y = start_y;
    vector <Point> available_steps;
    bool closed = false;
    while (make_step(cur_x, cur_y, available_steps)){
        if (cur_x == start_x && cur_y == start_y){
            closed = true;
        }
    }
    return closed && is_single();
}

void Polygon::show(){
    namedWindow("Area", WINDOW_AUTOSIZE);
    imshow("Polygon", image);
}


double Polygon::calculate_area(){
    int count = 0;
    for(int j = 0; j < image.rows; j++){
        Point previous_point = Point(0, j);
        int start_x = 0;
        int end_x = 0;
        bool enter_green = false;
        for(int i = 0; i < image.cols; i++){
            Point cur_point (i, j);
            Vec3b &previous_color = image.at<Vec3b>(previous_point);
            Vec3b &cur_color = image.at<Vec3b>(cur_point);
            if (previous_color[0] == 0 && previous_color[1] == 0 && previous_color[2] == 0 && cur_color[0] == 0 && cur_color[1] == 255 && cur_color[2] == 0){
                enter_green = true;
                if (start_x != 0){
                    end_x = cur_point.x; 
                }
            };
            if (enter_green && previous_color[0] == 0 && previous_color[1] == 255 && previous_color[2] == 0 && cur_color[0] == 0 && cur_color[1] == 0 && cur_color[2] == 0){
                if (start_x == 0){
                    start_x = cur_point.x; 
                }
                enter_green = false;
            };
            previous_point = cur_point;
        };
        for (int i = start_x; i < end_x; i++){
            count++;
            Point cur_point (i, j);
            Vec3b &cur_color = image.at<Vec3b>(cur_point);
            cur_color = Vec3b(0,255,0);
        }
    }
    return count/pow(resolution, 2);
}


void Polygon::load_data(const string &path){
    ifstream input_stream(path);
    string line;
    while (getline(input_stream, line)){
        vector<string> values = split_by_delim(line, ",");
        Point start = Point( round(atof(values[0].c_str())*resolution), round(atof(values[1].c_str())*resolution) );
        Point end = Point( round(atof(values[2].c_str())*resolution), round(atof(values[3].c_str())*resolution) );
        Edge edge = Edge(start, end);
        edges.push_back(edge);
    }
}