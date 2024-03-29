#include <polygon.h>


Polygon::Polygon(const string &path){
    resolution = 300;
    offset = 5;
    lookup_direction.push_back(pair<int, int> (-1, -1) );
    lookup_direction.push_back(pair<int, int> (0, -1) );
    lookup_direction.push_back(pair<int, int> (1, -1) );
    lookup_direction.push_back(pair<int, int> (1, 0) );
    lookup_direction.push_back(pair<int, int> (1, 1) );
    lookup_direction.push_back(pair<int, int> (0, 1) );
    lookup_direction.push_back(pair<int, int> (-1, 1) );
    lookup_direction.push_back(pair<int, int> (-1, 0) );
    load_data(path);
    setup_canvas();
    build();
}


void Polygon::setup_canvas(){
    // define canvas parameters, shift coordinates
    int min_x = edges[0].start.x;
    int max_x = min_x;
    int min_y = edges[0].start.y;
    int max_y = min_y;
    for (int i = 0; i < edges.size(); i++){
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
    for (int i = 0; i < edges.size(); i++){
        edges[i].start.x = edges[i].start.x + offset;
        edges[i].start.y = height - edges[i].start.y - offset;
        edges[i].end.x = edges[i].end.x + offset;
        edges[i].end.y = height - edges[i].end.y - offset;
    }
}


void Polygon::build(){
    image = Mat(height, width, CV_8UC3, BLACK);
    for (int i = 0; i < edges.size(); i++){
        line(image, edges[i].start, edges[i].end, WHITE);
    }
}


void Polygon::show(){
    namedWindow("Area");
    imshow("Polygon", image);
}


bool Polygon::make_step(int &x, int &y, vector<Point> &available_steps){
    // add all possible steps aroubd the [x,y]
    for (int k = 0; k < lookup_direction.size(); k++){
        Point cur_point = Point(x+lookup_direction[k].first, y+lookup_direction[k].second);
        if (image.at<Vec3b>(cur_point) == WHITE){
            available_steps.push_back(cur_point);
        };
    }
    // make a step, mark it GREEN
    if (available_steps.size() > 0){
        Point next_step = available_steps.back();
        available_steps.pop_back();
        image.at<Vec3b>(next_step) = GREEN;
        x = next_step.x;
        y = next_step.y;
        return true;
    }
    return false;
}


bool Polygon::is_single(){
    // start points from all edges should be GREEN
    for (int i = 0; i < edges.size(); i++){
        Point start_point (edges[i].start.x, edges[i].start.y);
        if (image.at<Vec3b>(start_point) != GREEN){
            return false;
        };
    }
    return true;
}


bool Polygon::validate(){
    // Check if polygon is single and closed
    int start_x = edges[0].start.x;
    int start_y = edges[0].start.y;
    int cur_x = start_x;
    int cur_y = start_y;
    int previous_x = start_x;
    int previous_y = start_y;
    vector <Point> available_steps;
    bool closed = false;
    while (make_step(cur_x, cur_y, available_steps)){
        double dist = sqrt( pow((cur_x-previous_x),2) + pow((cur_y-previous_y),2) );
        if (cur_x == start_x && cur_y == start_y && dist < 1.5){   // need to check if we didn't jump to this point from far away
            closed = true;
        }
        previous_x = cur_x;
        previous_y = cur_y;
    }
    return closed && is_single();
}


double Polygon::calculate_area(){
    // Make polygon GREEN, return area
    int count = 0;
    for(int j = 0; j < image.rows; j++){
        Point previous_point = Point(0, j); // always BLACK because of offset
        int start_x = 0;
        int end_x = 0;
        bool inside = false;
        bool entering = false;
        for(int i = 0; i < image.cols; i++){
            Point cur_point (i, j);
            Vec3b &previous_color = image.at<Vec3b>(previous_point);
            Vec3b &cur_color = image.at<Vec3b>(cur_point);
            if (cur_color == GREEN){      // crossing the edge
                if (inside){              // leaving
                    end_x = cur_point.x;
                    entering = false;
                    inside = false;
                } else {                  // entering
                    entering = true;
                }
            };
            if (previous_color == GREEN && cur_color == BLACK){   // inside polygon
                if (entering){
                    inside = true;
                    start_x = cur_point.x;
                }
            };
            if (start_x != 0 && end_x != 0){            // make the line GREEN
                for (int i = start_x; i < end_x; i++){
                    count++;
                    image.at<Vec3b>(Point(i,j)) = GREEN;
                };
                start_x = 0;
                end_x = 0;
            }
            previous_point = cur_point;
        };
    }
    return count/pow(resolution, 2);
}


void Polygon::load_data(const string &path){
    // Load data from text file
    ifstream input_stream(path);
    string line;
    while (getline(input_stream, line)){
        if (line.empty()){
            continue;
        }
        vector<string> values = split_by_delim(line, ",");
        Point start = Point(
            round(atof(values[0].c_str())*resolution),
            round(atof(values[1].c_str())*resolution));
        Point end = Point(
            round(atof(values[2].c_str())*resolution),
            round(atof(values[3].c_str())*resolution));
        Edge edge = Edge(start, end);
        edges.push_back(edge);
    }
}