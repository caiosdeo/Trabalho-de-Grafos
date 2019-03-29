#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node){

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;

}

Graph::~Graph(){

    Node* next_node = this->first_node;

    while(next_node != nullptr){

        Node* aux_node = next_node->getNext();
        delete next_node;
        next_node = aux_node;

    }

}