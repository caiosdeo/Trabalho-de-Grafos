#include "Graph.h"
#include "Node.h"
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

        Node* aux_node = next_node->getNextNode();
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

// Other methods
void Graph::insertNode(int id, int weight){

    Node* aux_node = this->first_node;
    Node* node = new Node(id, weight);

    while(aux_node->getNextNode() != nullptr)
        aux_node = aux_node->getNextNode();

    aux_node->setNextNode(node);

}

void Graph::removeNode(int id){

    Node* aux = this->first_node;
    Node* previous = nullptr;

    while(aux->id() != id){

        aux = aux->getNextNode();
        previous = aux;

    }



}

bool Graph::searchNode(int id){

    

}