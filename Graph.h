/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>

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
        void insertNode(int id);
        void makeGraph(int id, int target_id, float weight);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);
        void printGraph(ofstream& output_file);
        bool depthFirstSearch(int initialId,int targetId);
        int* stronglyConnectedComponents();
        Graph* getTranspose();
        void breadthFirstSearch(ofstream& output_file);
        Graph* getComplement();
        Graph* getSubjacent();
        int* degreeSequence();
        bool hasCircuit();
        int* topologicalSort();
        int* connectedComponents();
        bool connectedGraph();
        Node* getHighestDegreeNode();
        list<int> greedyMinimumConnectedDominantSet();
        Node** sortNodesByOutDegree();
        Node* getAlphaNode(float alpha);

    private:
        //Auxiliar methods
        int indexForNodes(int id);
        bool auxDepthFirstSearch(int initialId,int targetId,bool visited[]);
        void exploreOrder(int initialId, int targetId, bool visited[], stack<int>* explored);
        void auxComponents(int initialId, int targetId, bool visited[], int c[], int label);
        bool auxBreadthFirstSearchVerify(int *verify, int size, int targetId);
        bool isLeafNode(Node* node, bool *visited);
        list<int> auxGreedyMinimumConnectedDominantSet();
        void quickSort(Node** arr, int low, int high);
        int partition(Node** arr, int low, int high);
        void swap(Node** arr, int i, int j);

};

#endif // GRAPH_H_INCLUDED
