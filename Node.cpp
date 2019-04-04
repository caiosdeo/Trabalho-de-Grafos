#include "Node.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Node's methods
**************************************************************************************************/

// Constructor
Node::Node(int id){

    this->id = id;
    this->in_degree = 0;
    this->out_degree = 0;
    this->degree = 0;
    this->adjacency_list = nullptr;
    this->next_node = nullptr;

};

// Destructor
Node::~Node(){

    Edge* next_edge = this->adjacency_list;

    while(next_edge != nullptr){

        Node* aux_edge = next_edge->getNext();
        delete next_edge;
        next_edge = aux_edge;
        
    }

};

// Getters
Edge* Node::getAdjacencyList(){

    return this->adjacency_list;

}

int Node::getId(){

    return this->id;

}

int Node::getInDegree(){

    return this->in_degree;

}

int Node::getOutDegree(){

    return this->out_degree;

}

float Node::getWeight(){

    return this->weight;

}

int Node::getDegree(){

    return this->degree;

}

Node* Node::getNextNode(){

    return this->next_node;

}

// Setters

void Node::setNextNode(Node* next_node){

    this->next_node = next_node;

}

void Node::setWeight(float weight){

    this->weight = weight;

}