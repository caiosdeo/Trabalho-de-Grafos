/**************************************************************************************************
 * Implementation of the TAD Matrix Graph
**************************************************************************************************/


#ifndef MATRIXGRAPH_H_INCLUDED
#define MATRIXGRAPH_H_INCLUDED

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
        int getWeight(int node1, int node2);

        bool getDirected();
        bool getWeightedEdge();

        void insertNode(int node);
        void insertEdge(int node1, int node2, int weight);
        void removeEdge(int node1, int node2);;
        void removeNode(int node);
};


#endif
