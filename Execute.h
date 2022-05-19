//
// Created by shai0 on 5/16/2022.
//

#ifndef EX2_EXECUTE_H
#define EX2_EXECUTE_H
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>
#include "MyGraph.h"
#include <memory>

using namespace std;
class Execute {
public:
    Execute() : _output_file("output.dat") {}
    ~Execute() {}
    void execute(int argc, char* argv[]);

    //check in map in T is exist
    template<class T,class S>
    bool isExist(map<T, S>& map, T key) {
        return map.find(key) != map.end();
    }

    //Get input of -i flag =>
    void getFromFile_i(const string& tail);
    void readFile(const string& fname, const string& type);
    void getConfigFromFile(const string& fname);
    //TODO: implement this function
    void readTramFile(string fname);
    void readSprinterFile(string fname);
    void readRailFile(string fname);




    void getFromFile_c(string fname);
    void getFromFile_o(string fname);

private:
    //vector of string and the GraphNode to know if is there a station or not.
    MyGraph mg;
    string _output_file;
    void writeToFile(basic_string<char> basicString);
};


#endif //EX2_EXECUTE_H
