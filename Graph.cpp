#include "Graph.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node){

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;

}

// Destructor
Graph::~Graph(){

    Node* next_node = this->first_node;

    while(next_node != nullptr){

        Node* aux_node = next_node->getNext();
        delete next_node;
        next_node = aux_node;

    }

}

// Getters 
int Graph::getOrder(){

    return this->order;

}
int Graph::getNumberEdges(){

    return this->number_edges;

}

bool Graph::getDirected(){

    return this->directed;

}


bool Graph::getWeightedEdge(){

    return this->weighted_edge;

}

Node* Graph::getFirstNode(){

    return this->first_node;

}

Node* Graph::getLastNode(){

    return this->last_node;

}

// Setters
void Graph::setNumberEdges(int n){

    this->number_edges = n;

}

void Graph::setDirected(bool directed){

    this->directed = directed;

}

void Graph::setWeightedEdge(bool weighted_edge){

    this->weighted_edge = weighted_edge;

}

void Graph::setFirstNode(Node* first_node){

    this->first_node = first_node;

}

void Graph::getLastNode(Node* last_node){

    this->last_node = last_node;

}