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
        Node();
        ~Node();
        Edge* getAdjacencyList();
        int getId();
        int getInDegree();
        int getOutDegree();
        float getWeight();
        int getDegree();
        Node* getNextNode();
        void setAdjacencyList(Edge* adjacency_list);
        void setId(int id);
        void setInDegree(unsigned int in_degree);
        void setOutDegree(int out_degree);
        void setWeight(float weight);
        void setDegree(int degree);
        void setNextNode(Node* next_node);

} 

#endif