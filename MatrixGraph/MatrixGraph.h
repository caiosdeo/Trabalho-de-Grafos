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

    public:

        MatrixGraph(int number_node, bool directed, bool weighted_edge, int order);
        ~MatrixGraph();

        int getOrder();
        int getNumberNode();
        int edgeWeight(int node1, int node2); //if directed node1 points to node2

        bool getDirected();
        bool getWeightedEdge();


        void insertNode(int node);
        void insertEdge(int node1, int node2, int weight);
        void removeEdge(int node1, int node2);;
        void removeNode(int node);
};

#endif
