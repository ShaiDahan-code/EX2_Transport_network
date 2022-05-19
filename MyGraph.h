//
// Created by shai0 on 5/16/2022.
//

#ifndef EX2_MYGRAPH_H
#define EX2_MYGRAPH_H


#include <string>
#include <vector>
#include <iostream>
#include<array>
#include <map>
using namespace std;

class MyGraph {
// Implement a graph useing matrix
private:
    vector<string> vertices;
    vector<vector<string> > bus_matrix;
    vector<vector<string> > tram_matrix;
public:
     vector<vector<string>> &getBusMatrix() ;

     vector<vector<string>> &getTramMatrix() ;

     vector<vector<string>> &getSprinterMatrix() ;

     vector<vector<string>> &getRailMatrix() ;

     vector<vector<string>> &getAllWayMatrix() ;

private:
    vector<vector<string> > sprinter_matrix;
    vector<vector<string> > rail_matrix;
    vector<vector<string> > all_way_matrix;
    map<string, int> stop_car_time_map;

public:
    map<string, int> &getStopCarTimeMap();

    map<string, int> &getStopCityTimeMap();

private:
    map<string,int> stop_city_time_map;

public:
    MyGraph();


    //BFS Algorithm
    void call_BFS_for_outbound(string spot);
    vector<string> BFS_Algoritem(string start, vector<vector<std::string>> vec) const;





    //Graph functions
    int isItThere(string name,vector<vector<string> > &vec) const;
    void addEdge(const string from, const string to,const int time,vector<vector<string> > &vec);
    void addNewToVector(const string name,vector<vector<string> > &vec);
    void printType(vector<vector<string> > &vec) const;
    void addNewEdgeByType(string from,string to,int time,string name);

    vector<vector<string>> reverse_graph(vector<vector<string>> vec);

    string all_object_to_string(vector<vector<string>> &vec);

    void call_BFS_for_inbound(string spot);
};

#endif //EX2_MYGRAPH_H
