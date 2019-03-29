/**************************************************************************************************
 * 
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
        int weight;
        int degree;
        Node* next_node;
    
    public:
        Node();
        ~Node();


} 

#endif