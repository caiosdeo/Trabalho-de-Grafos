/**************************************************************************************************
 * 
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"

using namespace std;

class Graph{

    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        Node* first_node;
        Node* last_node;

    public:
        Graph();
        ~Graph();
        

} 

#endif