#ifndef POLYGON_H
#define POLYGON_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


struct Edge {
    Point start;
    Point end;
    Edge (const Point &a, const Point &b);
};


class Polygon {

public:
    Polygon(const string &path);
    void load_data(const string &path);
    void show();
    double calculate_area();
    bool validate();
private:
    int resolution;
    int width;
    int height;
    int offset;
    Mat image;
    vector<Edge> edges;
    vector <pair <int, int> > lookup_direction;
    void setup_canvas();
    void build();
    bool make_step(int &x, int &y, vector <Point> &available_steps);
    bool is_single();
};


#endif