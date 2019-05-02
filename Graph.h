/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>

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
        int* stronglyConnectedComponents();
        Graph* getTranspose();
        void breadthFirstSearch();

    private:
        //Auxiliar methods
        int indexForNodes(int id);
        bool auxDepthFirstSearch(int initialId,int targetId,bool visited[]);
        void exploreOrder(int initialId, int targetId, bool visited[], stack<int>* explored);
        void auxStronglyConnectedComponents(int initialId, int targetId, bool visited[], int sc[], int label);
        bool auxBreadthFirstSearchVerify(int *verify, int size, int targetId);

};

#endif // GRAPH_H_INCLUDED
