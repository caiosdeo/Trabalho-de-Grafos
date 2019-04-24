#include "Node.h"
#include "Edge.h"
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
    this->weight = 0;
    this->first_edge = nullptr;
    this->last_edge = nullptr;
    this->next_node = nullptr;

};

// Destructor
Node::~Node(){

    Edge* next_edge = this->first_edge;

    while(next_edge != nullptr){

        Edge* aux_edge = next_edge->getNextEdge();
        delete next_edge;
        next_edge = aux_edge;

    }

};

// Getters
Edge* Node::getFirstEdge(){

    return this->first_edge;

}

Edge* Node::getLastEdge(){

    return this->last_edge;

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

// Other methods
void Node::insertEdge(int target_id, float weight){

    if(this->first_edge != nullptr){

        Edge* aux = this->first_edge;
        Edge* edge = new Edge(target_id);
        edge->setWeight(weight);

        while(aux->getNextEdge() != nullptr)
            aux = aux->getNextEdge();

        aux->setNextEdge(edge);

    }
    else{

        this->first_edge = new Edge(target_id);
        this->first_edge->setWeight(weight);

    }

    this->degree++;

}

void Node::removeEdges(){

    if(this->first_edge != nullptr){

        Edge* previous = nullptr;
        Edge* aux = this->first_edge;

        while(aux != nullptr){

            Node* target_node = getNode(aux->getTargetId());
            target_node->removeEdge(this->getId());
            previous = aux;
            aux = aux->getNextEdge();
            delete previous;

        }

    }

}

void Node::removeEdge(int id){

    if(this->searchEdge(id)){

        Edge* aux = this->first_edge;
        Edge* previous = nullptr;

        while(aux->getTargetId() != id){

            previous = aux;
            aux = aux->getNextEdge();

        }

        previous->setNextEdge(aux->getNextEdge());
        delete aux;

        this->in_degree--;

    }

}

bool Node::searchEdge(int target_id){

    Edge* aux = this->first_edge;

    while(aux->getNextEdge() != nullptr)
        if(aux->getTargetId() == target_id)
            return true;

    return false;

}

void Node::incrementInDegree(){

    this->in_degree++;

}

void Node::incrementOutDegree(){

    this->out_degree--;

}

void Node::decrementInDegree(){

    this->in_degree--;

}

void Node::decrementOutDegree(){

    this->out_degree++;

}