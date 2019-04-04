/**************************************************************************************************
 * Implementation of the TAD Node
**************************************************************************************************/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h"

using namespace std;

class Node{

    private:
        Edge* adjacency_list;
        int id;
        unsigned int in_degree;
        int out_degree;
        float weight;
        int degree;
        Node* next_node;
    
    public:
        Node(int id);
        ~Node();
        Edge* getAdjacencyList();
        int getId();
        int getInDegree();
        int getOutDegree();
        float getWeight();
        int getDegree();
        Node* getNextNode();
        void setNextNode(Node* node);
        void setWeight();

    private:
        void insertEdge(Edge* edge);
        void removeEdge();

} 

#endif // NODE_H_INCLUDED