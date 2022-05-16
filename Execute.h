//
// Created by shai0 on 5/16/2022.
//

#ifndef EX2_EXECUTE_H
#define EX2_EXECUTE_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
class Execute {
public:
    Execute() {}
    ~Execute() {}
    void execute(int argc, char* argv[]);
    void getFromFile_i(string tail);
    void getFromFile_c(string fname);
    void getFromFile_o(string fname);
private:

};


#endif //EX2_EXECUTE_H
