/**************************************************************************************************
 * Implementation of the TAD Graph
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
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        Node* getFirstNode();
        Node* getLastNode();
        void setOrder(int order);
        void setNumberEdges(int n);
        void setDirected(bool directed);
        void setWeightedEdge(bool weighted_edge);
        void setFirstNode(Node* first_node);
        void setLastNode(Node* last_node);

} 

#endif