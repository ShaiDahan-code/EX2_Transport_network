//
// Created by shai0 on 5/16/2022.
//

#ifndef EX2_MYGRAPH_H
#define EX2_MYGRAPH_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class MyGraph {

private:
    struct Node {
        int vertex;
        string name;
        vector<Node*> neighbors;
    };
    int numOfVertices;
    int numOfEdges;

//Implement a graph class
public:
    //Default constructor
    MyGraph();

    //Constructor
    MyGraph(int n);

    //Destructor
    ~MyGraph();

    //Add an edge between the vertices u and v
    void addEdge(int u, int v);

    //Print the graph
    void printGraph();

    //Return the number of vertices
    int getNumOfVertices();

    //Return the number of edges
    int getNumOfEdges();

    //Return the adjacency list of vertex v
    int *getAdjList(int v);

    Node*

};



#endif //EX2_MYGRAPH_H
