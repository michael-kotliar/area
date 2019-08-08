#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utils.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


static const Vec3b GREEN = Vec3b(0,255,0);
static const Vec3b WHITE = Vec3b(255,255,255);
static const Vec3b BLACK = Vec3b(0,0,0);


struct Edge {
    Point start;
    Point end;
    Edge (Point a, Point b):
        start(a),
        end(b){}
};


class Polygon {
public:
    Polygon(const string &path);
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
    vector<pair <int, int> > lookup_direction;
    void load_data(const string &path);
    void setup_canvas();
    void build();
    bool make_step(int &x, int &y, vector<Point> &available_steps);
    bool is_single();
};


#endif