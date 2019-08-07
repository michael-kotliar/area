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


using namespace std;


struct Vertex {
    int x;
    int y;
    void print();
    Vertex (const int &a, const int & b);
    Vertex ():
        x(0),
        y(0){}
};


struct Edge {
    Vertex start;
    Vertex end;
    Edge (const Vertex &a, const Vertex &b);
    void print();
};


class Polygon {

public:
    Polygon(const string &path);
    void load(const string &path);
    void print_edges();
    void print_vertices();
private:
    vector<Vertex> vertices;
    vector<Edge> edges;

};


#endif