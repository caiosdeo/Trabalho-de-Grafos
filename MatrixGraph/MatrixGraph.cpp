/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

#include "MatrixGraph.h"

using namespace std;

MatrixGraph::MatrixGraph(int number_node, bool directed, bool weighted_edge, bool weighted_node, int order){
    
    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->number_node = number_node;
    *graph = new int[this->number_node];
    **graph = * new int[this->number_node];
};

MatrixGraph::~MatrixGraph(){

};

int MatrixGraph::getOrder(){
    return this->order;
};

int MatrixGraph::getNumberNode(){
    return this->number_node;
};

bool MatrixGraph::getDirected(){
    return this->directed;
};

bool MatrixGraph::getWeightedEdge(){
    return this->weighted_edge;
};

bool MatrixGraph::getWeightedNode(){
    return this->weighted_node;
};

void MatrixGraph::insertNode(int node){

};

void MatrixGraph::insertEdge(int node1, int node2){

};

void MatrixGraph::sortAscendingGraph(){

};
