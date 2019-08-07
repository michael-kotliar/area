#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>
#include <iostream>


using namespace std;


inline vector<string> split_by_delim(const string &line, string delim = "\t"){
    stringstream buffer(line);
    string temp;
    vector<string> values;
    while(getline(buffer, temp, buffer.widen(*delim.c_str()))) {
        values.push_back(temp);
    }
    return values;
}


#endif