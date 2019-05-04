/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>

using namespace std;

class Graph{

    //Atributes
    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        Node* first_node;
        Node* last_node;
        //Auxiliar methods
        int indexForNodes(int id);
        bool auxDepthFirstSearch(int initialId,int targetId,bool visited[]);

    public:
        //Constructor
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();
        Node* getFirstNode();
        Node* getLastNode();
        //Other methods
        void insertNode(int id, int target_id, float weight);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);
        void printGraph(ofstream& output_file);
        bool depthFirstSearch(int initialId,int targetId);
        int connectedComponent(int initialId);

};

#endif // GRAPH_H_INCLUDED
