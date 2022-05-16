//
// Created by shai0 on 5/16/2022.
//

#include "GraphNode.h"


GraphNode::GraphNode(string value) {
    this->_value = value;
    this->_visited = false;
}

string GraphNode::getValue() {
    return this->_value;
}

