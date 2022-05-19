//
// Created by shai0 on 5/16/2022.
//

#include <sstream>
#include "MyGraph.h"
#include <queue>



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
    bool first_time = from_index || to_index;

    if(!from_index) {
        addNewToVector(from,vec);
    }

    if(!to_index) {
        addNewToVector(to,vec);
    }
    if(from.length() > 32 || to.length() > 32) {
        throw "Name is too long";
    }
    //TODO:REVIEW Later
//    if(first_time){
//        int exist_time;
//        stringstream ss(vec[from_index][to_index]);
//        ss >> exist_time;
//        if(exist_time > time){
//
//        }
//    }

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

vector<string> MyGraph::BFS_Algoritem(string start, vector<vector<string> > &vec) const{
    vector<string> reachable;
    map<string,int> distance_from_start;
    queue<string> next;
    next.push(start);
    int index_of_start;
    bool is_there = false;
    //init all Vertices to -1 , and only the start to 0

    for(int i=1;i<vec.size();i++){
        if(vec[0][i] == start){
            distance_from_start.insert(pair<string,int>(vec[0][i],0));
            index_of_start = i;
            is_there = true;
        }
        else{
            distance_from_start.insert(pair<string,int>(vec[0][i],-1));
        }
    }
    if(is_there) {
        while (!next.empty()) {
            index_of_start = isItThere(next.front(), vec);
            for (int i = 1; i < vec.size(); i++) {
                if (vec[index_of_start][i] != "0" && index_of_start != i) {
                    if (distance_from_start[vec[0][i]] == -1) {
                        distance_from_start[vec[0][i]] = distance_from_start[vec[0][index_of_start]] + 1;
                        reachable.push_back(vec[0][i]);
                        next.push(vec[0][i]);
                    } else {
                        if (distance_from_start[vec[0][i]] > distance_from_start[vec[0][index_of_start]] + 1) {
                            distance_from_start[vec[0][i]] = distance_from_start[vec[0][index_of_start]] + 1;
                        }
                    }
                }
            }
            next.pop();
        }
    }


    //print reachable
    if(reachable.size() == 0)
        cout << "no outbound travel" << endl;
    else {
        for (int i = 0; i < reachable.size(); i++) {
            cout << reachable[i] << "\t";
        }
        cout << "..." << endl;
    }
    return reachable;
}

void MyGraph::call_BFS_By_Type(string spot) {
    cout << "[output]\tbus: ";
    BFS_Algoritem(spot,this->bus_matrix);
    cout << "[output]\ttram: ";
    BFS_Algoritem(spot,this->tram_matrix);
    cout << "[output]\tsprinter: ";
    BFS_Algoritem(spot,this->sprinter_matrix);
    cout << "[output]\trail: ";
    BFS_Algoritem(spot,this->rail_matrix);

}



