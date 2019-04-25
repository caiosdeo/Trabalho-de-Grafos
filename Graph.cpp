#include "Graph.h"
#include "Node.h"
#include "Edge.h"
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

        next_node->removeEdges();
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
void Graph::insertNode(int id, int target_id, float weight){

    if(this->searchNode(id) && this->searchNode(target_id, weight)){

        if(this->directed)
            this->getNode(id)->insertEdge(target_id, weight);

        else{

            this->getNode(id)->insertEdge(target_id, weight);
            this->getNode(target_id)->insertEdge(id, weight);

        }

    }
    else if(this->searchNode(id, weight) || this->searchNode(target_id, weight)){



    }
    else{

        Node* aux = this->first_node;
        Node* node = new Node(id);
        Node* target_node = new Node(target_id);
        node->setWeight(weight);

        while(aux->getNextNode() != nullptr)
            aux = aux->getNextNode();

        aux->setNextNode(node);

    }

}

/*

    Node* aux = this->first_node;
    Node* node = new Node(id);
    node->setWeight(weight);

    while(aux->getNextNode() != nullptr)
        aux = aux->getNextNode();

    aux->setNextNode(node);

*/

void Graph::removeNode(int id){

    if(this->searchNode(id)){

        if(this->first_node != nullptr){

            Node* aux = this->first_node;
            Node* previous = nullptr;

            while(aux->getId() != id){

                previous = aux;
                aux = aux->getNextNode();

            }

            previous->setNextNode(aux->getNextNode());
            aux->removeEdges();
            delete aux;

        }

        this->order--;

    }

}

bool Graph::searchNode(int id){

    Node* aux = this->first_node;

    while(aux->getNextNode() != nullptr)
        if(aux->getId() == id)
            return true;

    return false;

}

Node* Graph::getNode(int id){


    Node *aux = first_node;

    while(aux != NULL){

        if(aux->getId() == id){
            return aux;
        }

        aux = aux->getNextNode();
    }

    return aux;
}

void Graph::printGraph(){

    for(Node* p = this->first_node; p->getNextNode() != nullptr; p = p->getNextNode()){
        cout << p->getId();
        for(Edge* e = p->getFirstEdge(); e->getNextEdge() != nullptr; e = e->getNextEdge()){
            cout << " " << e->getTargetId();
        }
        cout << endl;
    }

}
