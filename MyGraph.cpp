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

map<string,int> MyGraph::BFS_Algoritem(string start, vector<vector<std::string>> vec) const{
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
    return distance_from_start;
}

void MyGraph::call_BFS_for_outbound(string spot) {
    cout << "[output]\tbus: ";
    BFS_Algoritem(spot,this->bus_matrix);
    cout << " [output]\ttram: ";
    BFS_Algoritem(spot,this->tram_matrix);
    cout << " [output]\tsprinter: ";
    BFS_Algoritem(spot,this->sprinter_matrix);
    cout << " [output]\trail: ";
    BFS_Algoritem(spot,this->rail_matrix);
}


void MyGraph::call_BFS_for_inbound(string spot) {
    cout << "[output]\tbus: ";
    BFS_Algoritem(spot,reverse_graph(this->bus_matrix));
    cout << " [output]\ttram: ";
    BFS_Algoritem(spot,reverse_graph(this->tram_matrix));
    cout << " [output]\tsprinter: ";
    BFS_Algoritem(spot,reverse_graph(this->sprinter_matrix));
    cout << " [output]\trail: ";
    BFS_Algoritem(spot,reverse_graph(this->rail_matrix));
}

vector<vector<string>> MyGraph::reverse_graph(vector<vector<string>> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j <vec.size() ; ++j) {
            string tmp = vec[i][j];
            vec[i][j] = vec[j][i];
            vec[j][i] = tmp;
        }
    }
    return vec;
}

map<string, int> MyGraph::Dijkstra_Algoritem(string spot, string to, vector<vector<string> > &vec,int extra_time) {
    map<string, int> distance_from_start;
    map<string, int> how_many_stops;
    vector<string> reachable;
    vector<string> next;
    vector<string> visited,unvisited;
    queue<string> to_check;

    //init all Vertices to -1 , and only the spot to 0
    for(int i=1;i < vec.size();i++){
        unvisited.push_back(vec[0][i]);
        if(vec[0][i] == spot){
            distance_from_start.insert(pair<string,int>(vec[0][i],0));

            to_check.push(vec[0][i]);

        }
        else {
            distance_from_start.insert(pair<string, int>(vec[0][i], -1));
        }
        how_many_stops.insert(pair<string,int>(vec[0][i],0));
    }

    vector<int> incoming;
    string spot_to_check;
    int count_spots = 0;
    while(!to_check.empty()){
        spot_to_check = to_check.front();
        int index_of_spot_to_check = isItThere(spot_to_check,vec);
        incoming = get_All_Incoming_Ranks(spot_to_check,vec);

        // make a for loop for each in incoming
        for(int i=0;i<incoming.size();i++){
            if(distance_from_start[vec[0][incoming[i]]] != 0){
                string s = vec[index_of_spot_to_check][incoming[i]].c_str();
                int value = atoi(s.c_str());
                if(distance_from_start[vec[0][incoming[i]]] == -1) { // in case it's infinite
                    distance_from_start[vec[0][incoming[i]]] = distance_from_start[spot_to_check] + value;
                    how_many_stops[vec[0][incoming[i]]] = 1;
                    if(distance_from_start[spot_to_check] > 0){
                        how_many_stops[vec[0][incoming[i]]] += 1;
                    }
                    to_check.push(vec[0][incoming[i]]);
                }

                else if(distance_from_start[vec[0][incoming[i]]] > (distance_from_start[vec[0][index_of_spot_to_check]] + value)) { // in case it's alerter init check the if it's smaller then the exist
                    distance_from_start[vec[0][incoming[i]]] = (distance_from_start[vec[0][index_of_spot_to_check]]  + value);
                    how_many_stops[vec[0][incoming[i]]]++;
                }

            }
        }
        to_check.pop();
        visited.push_back(spot_to_check);
    }


    //print the result for each
    for(int i=1;i< vec.size();i++){
        if(distance_from_start[vec[0][i]] != -1 && how_many_stops[vec[0][i]] > 1){
            distance_from_start[vec[0][i]] += (how_many_stops[vec[0][i]]-1)*extra_time;
        }
    }
    bool is_there2 = false;
    for (int i = 1; i < vec.size(); i++) {
        if(vec[0][i] == to){
            if(distance_from_start[vec[0][i]] != 0) {
                cout << distance_from_start[vec[0][i]] << endl;
                is_there2 = true;
            }
            else
                cout << "route unavailable" << endl;
        }
    }
    if(is_there2 == false)
        cout << "route unavailable" << endl;

    return distance_from_start;
}

vector<int> MyGraph::get_All_Incoming_Ranks(string spot,vector<vector<string> > &vec) {
    vector<int> incoming;
    int index_of_start = isItThere(spot, vec);
    for (int i = 1; i < vec.size(); i++) {
        if (vec[index_of_start][i] != "0" && index_of_start != i) {
            incoming.push_back(i);
        }
    }


    return incoming;
}

void MyGraph::call_Dijkstra(string from, string to) {
    cout << "[output]\tbus: ";
    Dijkstra_Algoritem(from,to,this->bus_matrix,stop_car_time_map["bus"]);
    cout << " [output]\ttram: ";
    Dijkstra_Algoritem(from,to,this->tram_matrix,stop_car_time_map["tram"]);
    cout << " [output]\tsprinter: ";
    Dijkstra_Algoritem(from,to,this->sprinter_matrix,stop_car_time_map["sprinter"]);
    cout << " [output]\trail: ";
    Dijkstra_Algoritem(from,to,this->rail_matrix,stop_car_time_map["rail"]);

}



