/**************************************************************************************************
 * Implementation of the TAD Node
**************************************************************************************************/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h" // Include of the Edge class

using namespace std;

// Definition of the Node class
class Node{

    // Attributes
    private:
        Edge* first_edge;  
        Edge* last_edge;
        int id;
        unsigned int in_degree;
        int out_degree;
        float weight;
        int degree;
        Node* next_node;
    
    public:
        // Constructor
        Node(int id);
        // Destructor
        ~Node();
        // Getters
        Edge* getFirstEdge();
        Edge* getLastEdge();
        int getId();
        int getInDegree();
        int getOutDegree();
        float getWeight();
        int getDegree();
        Node* getNextNode();
        // Setters
        void setNextNode(Node* node);
        void setWeight(float weight);
        // Other methods
        void insertEdge(Edge* edge);
        void removeEdge();

}  

#endif // NODE_H_INCLUDED