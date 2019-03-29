#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(int id){

    this->id = id;
    this->adjacency_list = nullptr;
    this->next_node = nullptr;

};

Node::~Node(){

    Edge* next_edge = this->adjacency_list;

    while(next_edge != nullptr){

        Node* aux_edge = next_edge->getNext();
        delete next_edge;
        next_edge = aux_edge;
        
    }

};