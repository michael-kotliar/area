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
    void print();
};


class Polygon {

public:
    Polygon(const string &path);
    void load_data(const string &path);
    void print_edges();
    void show();
    bool validate();
private:
    int resolution;  // dots per unit
    int width;
    int height;
    int offset;
    Mat image;
    vector<Edge> edges;
    void setup_canvas();
    void draw();
    bool shift(int &x, int &y);
    bool is_closed(const int &x, const int &y);
};


#endif