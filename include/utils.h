#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

// split line by delimiter
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