/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

#include "MatrixGraph.h"
#include <iostream>

using namespace std;

MatrixGraph::MatrixGraph(int number_node, bool directed, bool weighted_edge, int order){
    
    //setting the variables
    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->number_node = number_node;

    //creating matrix
    **graph = * new int[this->number_node]; //creating the column that will point to the lines
    for(int i = 0; i < this->number_node; i++)
    {
        graph[i] = new int[this->number_node]; //creating a line for the "i" in the first column
    }

    //setting the values in the graph to zero
    //zero was defined to represent null in the case of Matrix graphs, since its not possible to apply null to a variable int
    //in this case, IDs can be negative or positive but not zero.

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


int MatrixGraph::edgeWeight(int node1, int node2){
    int i = 0;
    int j = 0;
    for( ; graph[i][0] != node1 && graph[i][0] != 0; i++){}//finding node1
    for( ; graph[0][j] != node2 && graph[0][j] != 0; i++){}//finding node 2
    if(getWeightedEdge() == true)
    {
        if(graph[i][j] == 0)
            cout << "The edge doesn't exists";
        return graph[i][j];
    }
    else 
    {
        cout << "The graph isn't weighted in edges so the edges doesn't have a weight different than one or zero";
        return graph[i][j];
    }
}

bool MatrixGraph::insertNode(int node){ // this actually bool so it become easier to manipulate insertEdge.
    //inserting node in the matrix
    int i = 1;
    for(; graph[i][0] != 0 && i < this->number_node; i++)
    {
        //finding a empty space for the new node
    }
    if(i == this->number_node)
    {
        cout << "Graph is full";
        return false;
    }
    graph[i][0] = graph[0][i] = node; // add the id of the node to the empty space finded
    return true;
};

void MatrixGraph::insertEdge(int node1, int node2, int weight){
    int i = 0;
    int j = 0;
    for( ; graph[i][0] != node1 && graph[i][0] != 0; i++){}//finding node1
    for( ; graph[0][j] != node2 && graph[0][j] != 0; j++){}//finding node 2
    if(graph[i][0] == 0) //if the node doesnt exist, add it to the graph
    {
        if(insertNode(node1) == false)
        {
            cout << "Wasn't possible to add the node1";
            return;
        }
    }    
    if(graph[0][j] == 0) //if the node doesnt exist, add it to the graph
    { 
        if(insertNode(node2) == false)
        {
            cout << "Wasn't possible to add the node2";
            return;
        }
    }
    if(getWeightedEdge() == true)
        {
        if(getDirected() == true)
        {
            //if the graph is directed that means that the edges point from a node to other, so only one node gets the variable changed
            //in that form is possible to know which node is point to the other.
            graph[i][j] == weight; 
        }
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
        {
            //if the graph is directed that means that the edges point from a node to other, so only one node gets the variable changed
            //in that form is possible to know which node is point to the other.
            graph[i][j] == 1; 
        }
        else
        {
            //if the graph isn't directed that means that the edges doesn't point from node to other, needing to put in both spaces
            //the number that shows that the nodes are connected by an edge.
            graph[i][j] = graph[j][i] = 1;
        }
    }
};

void MatrixGraph::removeEdge(int node1, int node2){
    int i = 0;
    int j = 0;
    for( ; graph[i][0] != node1 && graph[i][0] != 0 && i < this->number_node; i++){}//finding node1
    for( ; graph[0][j] != node2 && graph[0][j] != 0 && i < this->number_node; i++){}//finding node 2
    if(i == this->number_node || node1 == 0)
    {
        cout << "Node1 wasn't found";
        return;
    }
    if(j == this->number_node || node2 == 0)
    {
        cout << "Node2 wasn't found";
        return;
    }
    if(getDirected() == true)
    {  // since column and line are different, only the one pointing the oder must become zero.
        this->graph[i][j] = 0;
    }
    else
    {  // since both column and line is the same value, it's needed for both to become zero.
        this->graph[i][j] = 0;
        this->graph[j][i] = 0;
    }
};

void MatrixGraph::removeNode(int node){
    int i = 0;
    for(; graph[i][0] != node && i < this->number_node; i++){} //finding node in the graph
    if(i == this->number_node) //test if the node doesn't exist
    {
        cout << "Node doesn't exist in the Graph";
        return;
    }
    for(int j = 0; j < this->number_node; j++) // setting every value in the line/column to zero since zero is the neutral value that represents null in this graph. 
    {
        graph[i][j] = graph[j][i] = 0;
    }
};
