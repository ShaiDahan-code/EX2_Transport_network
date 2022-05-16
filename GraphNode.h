*//
// Created by shai0 on 5/16/2022.
//

#ifndef EX2_GRAPHNODE_H
#define EX2_GRAPHNODE_H
#include <string>
#include <vector>
#include <map>

using namespace std;

class GraphNode {

private:
    string _value;
    bool _visited;
    map<GraphNode*,int> _neighbors;
public:
    GraphNode(string value);
    string getValue();
    void setValue(string value);
    bool getVisited();
    void setVisited(bool visited);
    vector<GraphNode*> getNeighbors();
    void addNeighbor(GraphNode* neighbor);

};


#endif //EX2_GRAPHNODE_H
