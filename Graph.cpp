#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>

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

bool Graph::getWeightedNode(){

    return this->weighted_node;

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

        if(this->first_node == nullptr){

            this->first_node = source_node;
            this->last_node = target_node;
            this->first_node->setNextNode(target_node);

        }
        else{

            this->last_node->setNextNode(source_node);
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

    this->number_edges++;

}

void Graph::removeNode(int id){

    if(this->first_node != nullptr){

        if(this->searchNode(id)){

            Node* aux_node = this->first_node;
            Node* previous_node = nullptr;
            Node* target_node = nullptr;

            while(aux_node->getId() != id){

                previous_node = aux_node;
                aux_node = aux_node->getNextNode();

            }

            previous_node->setNextNode(aux_node->getNextNode());
            Edge* aux_edge = aux_node->getFirstEdge();
            int remove_id = aux_node->getId();

            while(aux_edge != nullptr){

                target_node = this->getNode(aux_edge->getTargetId());
                target_node->removeEdge(remove_id, this->directed, target_node);
                aux_edge = aux_edge->getNextEdge();

            }

            aux_node->removeEdges();

            if(this->last_node = aux_node)
                this->last_node = previous_node;

            previous_node->setNextNode(aux_node->getNextNode());

            delete aux_node;

            if(this->directed){

                aux_node = this->first_node;

                while(aux_node != nullptr){

                    aux_node->removeEdge(remove_id, this->directed, aux_node);
                    aux_node = aux_node->getNextNode();

                }

            }

        }

        this->order--;

    }

}

bool Graph::searchNode(int id){

    if(this->first_node != nullptr){

        for(Node* aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
            if(aux->getId() == id)
                return true;

    }

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

void Graph::printGraph(ofstream& output_file){

    if(!this->weighted_edge && !this->weighted_node){

        output_file << "Nodes | Edges " << endl;
        for(Node* p = this->first_node; p != nullptr; p = p->getNextNode()){
            output_file << p->getId() << "     | ";
            for(Edge* e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
                output_file << " " << e->getTargetId();
            }
            output_file << endl;
        }

    }else if(this->weighted_edge && !this->weighted_node){

        output_file << "Nodes | Edges[Weight] " << endl;
        for(Node* p = this->first_node; p != nullptr; p = p->getNextNode()){
            output_file << p->getId() << "     | ";
            for(Edge* e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
                output_file << " " << e->getTargetId() << "[" << e->getWeight() << "]";
            }
            output_file << endl;
        }

    }else if(this->weighted_node && !this->weighted_edge){

        output_file << "Nodes[Weight] | Edges " << endl;
        for(Node* p = this->first_node; p != nullptr; p = p->getNextNode()){
            output_file << p->getId() << "[" << p->getWeight() << "]" << " | ";
            for(Edge* e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
                output_file << " " << e->getTargetId();
            }
            output_file << endl;
        }

    }else if(this->weighted_node && this->weighted_edge){

        output_file << "Nodes[Weight] | Edges[Weight] " << endl;
        for(Node* p = this->first_node; p != nullptr; p = p->getNextNode()){
            output_file << p->getId() << "[" << p->getWeight() << "]" << " | ";
            for(Edge* e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
                output_file << " " << e->getTargetId() << "[" << e->getWeight() << "]";
            }
            output_file << endl;
        }

    }

}

bool Graph::depthFirstSearch(int initialId,int targetId)
{
    bool *visited = new bool[order];
    if(getNode(initialId)==nullptr||getNode(targetId)==nullptr)
    {
        return false;
    }
    for(int i = 0;i < order;i++)
    {
        visited[i] = false;
    }
    return auxDepthFirstSearch(initialId,targetId,visited);

}

int Graph::connectedComponent(int initialId)
{
    int *cc = new int[order];
    Node* aux = getFirstNode();
    int i = 0;
    cc[i] = initialId;
    for(; aux->getNextNode() == nullptr ; aux = aux->getNextNode())
    {
        if(depthFirstSearch(initialId, aux->getId()))
        {
            i++;
            cc[i] = aux->getId();
        }
    }
    return *cc;
}

//Auxiliar methods

int Graph::indexForNodes(int id)
{
    int i = 0;
    Node *aux = first_node;
    while(aux!=nullptr)
    {
        if(aux->getId()==id)
        {
            return i;
        }
        aux = aux->getNextNode();
        i++;
    }
    
}

bool Graph::auxDepthFirstSearch(int initialId,int targetId,bool visited[])
{
    visited[indexForNodes(initialId)] = true;
    if(getNode(initialId)->searchEdge(targetId))
    {
        visited[indexForNodes(targetId)] = true;
        return true;
    }
    else
    {
        Edge *aux = getNode(initialId)->getFirstEdge();
        while(aux!=nullptr)
        {
            if(visited[indexForNodes(aux->getTargetId())] == false)
            {
                if(auxDepthFirstSearch(aux->getTargetId(),targetId,visited))
                {
                    return true;
                }
            }
            aux = aux->getNextEdge();
        }
        return false;
    }
}
