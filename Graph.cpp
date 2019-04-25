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

    Node* source_node;
    Node* target_node;
    bool source = this->searchNode(id);
    bool target = this->searchNode(target_id);

    if(source && target){

        source_node = this->getNode(id);
        target_node = this->getNode(target_id);
           
    }
    else if(source || target){

        if(source){

            source_node = this->getNode(id);
            target_node = new Node(target_id);
            this->last_node->setNextNode(target_node);
            this->last_node = target_node;

        }

        if(target){

            target_node = this->getNode(target_id);
            source_node = new Node(id);
            this->last_node->setNextNode(source_node);
            this->last_node = source_node;

        }

    }
    else{

        source_node = new Node(id);
        target_node = new Node(target_id);

        if(this->last_node != nullptr){

            this->last_node->setNextNode(source_node);
            source_node->setNextNode(target_node);
            this->last_node = target_node;

        } 
        else{

            this->last_node = source_node;
            source_node->setNextNode(target_node);
            this->last_node = target_node;

        }       

    }

    if(this->directed){

        source_node->insertEdge(target_id, weight);
        source_node->incrementOutDegree();
        target_node->incrementInDegree();

    }
    else{

        source_node->insertEdge(target_id, weight);
        target_node->insertEdge(id, weight);
        source_node->incrementInDegree();
        target_node->incrementInDegree();

    }

}

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