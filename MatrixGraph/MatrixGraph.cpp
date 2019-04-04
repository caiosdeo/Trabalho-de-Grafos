/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

#include "MatrixGraph.h"

using namespace std;

MatrixGraph::MatrixGraph(int number_node, bool directed, bool weighted_edge, bool weighted_node, int order){
    
    //setting the variables
    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->number_node = number_node;

    //creating matrix
    **graph = * new int[this->number_node]; //creating the column that will point to the lines
    for(int i = 0; i < this->number_node; i++)
    {
        graph[i] = new int[this->number_node]; //creating a line for the "i" in the first column
    }

    //setting the values in the graph to zero

    for(int i = 0;  i < this->number_node; i++)
    {
        for(int j = 0;  j < this->number_node; j++)
        {
            graph[i][j] = 0;
        }
    }
};

MatrixGraph::~MatrixGraph(){

    //deleting matrix
    for(int i = 0; i < this->number_node; i++)
    {
        delete [] graph[i]; // deleting the column pointed by "i"
    }
    delete [] graph; // deleting the line that pointed to the other vectors
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
    //inserting node in the matrix
    int i = 0;
    for(; graph[i][0] != 0; i++)
    {
        //finding a empty space for the new node
    }
    graph[i][0] = graph[0][i] = node; // add the id of the node to the empty space finded
};

void MatrixGraph::insertEdge(int node1, int node2, int weight){
    int i = 0;
    int j = 0;
    for( ; graph[i][0] != node1 && graph[i][0] != 0; i++){}//finding node1
    for( ; graph[0][j] != node2 && graph[0][j] != 0; i++){}//finding node 2
    if(graph[i][0] == 0) //if the node doesnt exist, add it to the graph
        insertNode(node1);
    if(graph[0][j] == 0) //if the node doesnt exist, add it to the graph
        insertNode(node2);
    if(getWeightedEdge() == true)
        {
        if(getDirected() == true)
            //if the graph is directed that means that the edges point from a node to other, so only one node gets the variable changed
            //in that form is possible to know which node is point to the other.
            graph[i][j] == weight; 
        else
        {
            //if the graph isn't directed that means that the edges doesn't point from node to other, needing to put in both spaces
            //the number that shows that the nodes are connected by an edge.
            graph[i][j] = graph[j][i] = weight;
        }
    }
    else 
    {
        if(getDirected() == true)
            //if the graph is directed that means that the edges point from a node to other, so only one node gets the variable changed
            //in that form is possible to know which node is point to the other.
            graph[i][j] == 1; 
        else
        {
            //if the graph isn't directed that means that the edges doesn't point from node to other, needing to put in both spaces
            //the number that shows that the nodes are connected by an edge.
            graph[i][j] = graph[j][i] = 1;
        }
    }
};

