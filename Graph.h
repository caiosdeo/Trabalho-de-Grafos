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
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        ~Graph();
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        Node* getFirstNode();
        Node* getLastNode();

    private:
        void insertNode(Node* node);
        void removeNode(Node* node);

} #endif GRAPH_H_INCLUDED
