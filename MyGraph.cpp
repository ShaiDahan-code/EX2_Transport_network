//
// Created by shai0 on 5/16/2022.
//

#include "MyGraph.h"



MyGraph::MyGraph() {
    bus_matrix = {{""}};
    tram_matrix = {{""}};
    sprinter_matrix = {{""}};
    rail_matrix = {{""}};
    all_way_matrix = {{""}};
    //for map
    stop_car_time_map = {{"bus", 1}, {"tram", 2}, {"sprinter",3}, {"rail", 5} };
    stop_city_time_map = {{"intercity", 15}, {"centraal", 10}, {"stad",5}};
}







int MyGraph::isItThere(string name, vector<vector<string>> &vec) const{
    for(int i=0;i<vec.size();i++){
        if(vec[0][i]==name){
            return i;
        }
    }
    return 0;
}

void MyGraph::addEdge(const string from, const string to, const int time, vector<vector<string>> &vec) {
    int from_index = this->isItThere(from,vec);
    int to_index = this->isItThere(to,vec);


    if(!from_index) {
        addNewToVector(from,vec);
    }
    if(!to_index) {
        addNewToVector(to,vec);
    }
    if(from.length() > 32 || to.length() > 32) {
        throw "Name is too long";
    }

    from_index = this->isItThere(from,vec);
    to_index = this->isItThere(to,vec);
    string s = vec[from_index][to_index].c_str();
    int a = atoi(s.c_str());

    if(a == 0 || a > time) {
        vec[from_index][to_index] = to_string(time);
    }
}

void MyGraph::addNewToVector(const string name, vector<vector<string>> &vec) {
    for(int i=1;i<vec.size();i++){
        vec[i].push_back("0");
    }
    vec[0].push_back(name);
    vector<string> temp;
    temp.push_back(name);
    for(int i=0;i<vec.size();i++){
        temp.push_back("0");
    }
    vec.push_back(temp);
}

void MyGraph::printType(vector<vector<string>> &vec) const{
    for(int i=0;i<vec.size();i++){
        for(int j=0;j<vec.size();j++){
            cout<<vec[i][j]<<"\t\t";
        }
        cout<<endl;
    }
}

void MyGraph::addNewEdgeByType(string from,string to,int time,string name) {
    if(name=="bus"){
        addEdge(from,to,time,this->bus_matrix);
    }
    else if(name=="tram"){
        addEdge(from,to,time,this->tram_matrix);
    }
    else if(name=="sprinter"){
        addEdge(from,to,time,this->sprinter_matrix);
    }
    else if(name=="rail"){
        addEdge(from,to,time,this->rail_matrix);
    }

}

map<string, int> &MyGraph::getStopCarTimeMap() {
    return stop_car_time_map;
}

map<string, int> &MyGraph::getStopCityTimeMap() {
    return stop_city_time_map;
}

string MyGraph::all_object_to_string(vector<vector<string>> &vec) {
    string s = "";
    for(int i=0;i<vec.size();i++) {
        for (int j = 0; j < vec.size(); j++) {
            s += vec[i][j] + "\t\t";
        }
        s+="\n";
    }
        return s;
}

vector<vector<string>> &MyGraph::getBusMatrix()  {
    return bus_matrix;
}

vector<vector<string>> &MyGraph::getTramMatrix()  {
    return tram_matrix;
}

vector<vector<string>> &MyGraph::getSprinterMatrix()  {
    return sprinter_matrix;
}

vector<vector<string>> &MyGraph::getRailMatrix()  {
    return rail_matrix;
}

vector<vector<string>> &MyGraph::getAllWayMatrix() {
    return all_way_matrix;
}



