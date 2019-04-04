/**************************************************************************************************
 * Implementation of the TAD Matrix Graph
**************************************************************************************************/


#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

using namespace std;



class MatrixGraph
{
    private:
        int ** graph; // Ponteiro de ponteiro para armazenar o grafo.
        int order;
        int number_node;
        bool directed;
        bool weighted_edge;
        bool weighted_node;

    public:

        MatrixGraph(int number_node, bool directed, bool weighted_edge, bool weighted_node, int order);
        ~MatrixGraph();

        int getOrder();
        int getNumberNode();

        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();


        void insertNode(int node);
        void insertEdge(int node1, int node2, int weight);
};


#endif