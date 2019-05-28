#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>

using namespace std;

/**************************************************************************************************
 * Defining some Graph's specific methods
**************************************************************************************************/

//function that finds the connected component of a node
int* Graph::connectedComponents(){

    bool *visited = new bool[this->order];
    //Vector with the connectedComponents
    int *cc = new int[this->order];
    //Int to label the CCs
    int label = 0;

    //Begin the DFS with every node as unvisited
    for (int i = 0; i < order; i++){
        visited[i] = false;
    }

    //Label all nodes from the beginning
    for (Node* aux = this->getFirstNode(); aux != nullptr; aux = aux->getNextNode()){

        if(visited[indexForNodes(aux->getId())] == false){

            this->auxComponents(aux->getId(), this->getLastNode()->getId(), visited, cc, label);
            label++;

        }

    }
    return cc;
}

//Used Kosaraju Algorithm
int* Graph::stronglyConnectedComponents(){

    if(!this->connectedGraph()){
        return nullptr;

    }else{

        //Stack for visited nodes
        stack<int> explored;
        bool *visited = new bool[order];
        //Vector with the stronglyConnectedComponents
        int *sc = new int[this->order];
        //Int to label the SCCs
        int label = 0;

        if (this->first_node == nullptr || this->last_node == nullptr){
            return 0;
        }

        //Begin the DFS with every node as unvisited
        for (int i = 0; i < order; i++){
            visited[i] = false;
        }

        //Function to fill the stack with DFS visited nodes in post order
        exploreOrder(this->first_node->getId(), this->first_node->getId(), visited, &explored);

        //Confirms that all the nodes were included in the stack
        for (Node *n = this->first_node; n != nullptr; n = n->getNextNode())
            if (visited[indexForNodes(n->getId())] == false)
                exploreOrder(n->getId(), n->getId(), visited, &explored);

        //Create a reverse graph
        Graph *gT = this->getTranspose();

        //Define every node as unvisited for the second DFS
        for (int i = 0; i < order; i++)
        {
            visited[i] = false;
        }

        //DFS on the reverse graph by the stack order as its is running we find the SCCs of the graph
        while (explored.empty() == false)
        {

            int v = explored.top();
            explored.pop();

            //DFS on the reverse graph that will find the SCCs
            if (visited[gT->indexForNodes(v)] == false){

                gT->auxComponents(v, v, visited, sc, label);
                label++;

            }

        }

        return sc;

    }

}

// Kahn's algorithm adapted
int *Graph::topologicalSort()
{

    // Verifies if the graph has a circuit or not
    if (this->hasCircuit())
        return nullptr;

    else
    {

        int i = 0;
        Edge *aux_edge;
        Node *aux_node;
        int *vec = new int(this->order); // Allocating the vector that will contains the topological sort
        queue<Node *> topological_queue; // Declaring the auxiliar queue for the source nodes
        // Searching for nodes with indegree equal to zero
        for (aux_node = this->first_node; aux_node != nullptr; aux_node = aux_node->getNextNode())
        {
            // Verifies whether the indegree is equal to zero
            if (aux_node->getInDegree() == 0)
                topological_queue.push(aux_node); // Pushing the correct nodes in the queue
        }
        // Verifies if the queue is empty
        while (!topological_queue.empty())
        {

            vec[i] = topological_queue.front()->getId();          // Pushing the id of the node to be popped of the queue
            aux_edge = topological_queue.front()->getFirstEdge(); // Getting the first edge of the node to be popped
            topological_queue.pop();                              // Popping the node
            // Verifies whether an edge exists
            while (aux_edge != nullptr)
            {

                aux_node = this->getNode(aux_edge->getTargetId()); // Picking up the neighboring node
                aux_node->decrementInDegree();                     // Decrementing indegree
                // Verifies whether the indegree is equal to zero
                if (aux_node->getInDegree() == 0)
                    topological_queue.push(aux_node);

                aux_edge = aux_edge->getNextEdge();
            }

            i++;
        }

        return vec; // Returning the indexes correlated to the topological sort in a vector
    }
}

//This function is just to decide which way the greey will act if is a graph is directed or not
list<Node*> Graph::greedyMinimumConnectedDominantSet(Node** nodesSortedByOutDegree, float alpha){

    if(!this->connectedGraph()){
        list<Node*> empty;
        return empty;

    }else{
        if(this->directed){
            Graph* gS = this->getSubjacent();
            list<Node*> MCDS = gS->auxGreedyMinimumConnectedDominantSet(nodesSortedByOutDegree, alpha);
            return MCDS;

        }else{
            list<Node*> MCDS = this->auxGreedyMinimumConnectedDominantSet(nodesSortedByOutDegree, alpha);
            return MCDS;

        }

    }

}

// This function returns the Minimum Connected Dominant Set
list<Node*> Graph::auxGreedyMinimumConnectedDominantSet(Node** nodesSortedByOutDegree, float alpha){

    //List for the Minimum Connected Dominant Set
    list<Node*> minimun_connected_dominant_set;
    //Queue for visiting nodes
    queue<Node*> toVisit;
    //Vector to know if a node was visited and marking all as unvisited
    bool *visited = new bool[this->order];
    for(int i = 0; i < this->order; i++)
        visited[i] = false;

    Node* auxNode;

    // Get the alpha node which is already selected via rand and a given alpha
    Node* alphaNode = this->getAlphaNode(nodesSortedByOutDegree, alpha); 

    //The highestDegreeNode is already visited and is our root for the BFS
    visited[this->indexForNodes(alphaNode->getId())] = true;
    toVisit.push(alphaNode);

    while(!toVisit.empty()){

        //Auxilar to the node in the queue front
        auxNode = toVisit.front();
        // Adding the node id in the solution list
        minimun_connected_dominant_set.push_front(auxNode);
        //Then its is removed from the queue
        toVisit.pop();

        //Recur all of his adjacents
        for(Edge* auxEdge = auxNode->getFirstEdge(); auxEdge != nullptr; auxEdge = auxEdge->getNextEdge()){

            int targetId = auxEdge->getTargetId();
            int respectiveId = this->indexForNodes(targetId);
            //If a adjacent was not visited it is marked as visited and added to the queue
            if(!visited[respectiveId]){

                visited[respectiveId] = true;
                auxNode = this->getNode(targetId);
                if(!this->isLeafNode(auxNode, visited))
                    toVisit.push(auxNode);

            }

        }

    }

    return minimun_connected_dominant_set;

}

list<Node*> Graph::randomizedGreedy(int iterations, float alpha){

    Node** nodesSortedByOutDegree = this->sortNodesByOutDegree();
    list<Node*> starList = this->greedyMinimumConnectedDominantSet(nodesSortedByOutDegree, 0); 
    list<Node*> auxList;

    for(int i =0; i < iterations; i++){

        auxList = this->greedyMinimumConnectedDominantSet(nodesSortedByOutDegree, alpha);

        if(auxList.size() < starList.size())
            starList = auxList;

    } 

    return starList;

}

pair<list<Node*>, float> Graph::reactiveRandomizedGreedy(float maxAlpha, float alphaStep){

    /*
        alphasInfo matrix description

        0 - alpha values
        1 - alpha occurrences
        2 - alpha solutions sizes sum
        3 - alpha average of the sum solutions sizes in occurrences
        4 - alpha q - relation between star solution size and 3
        5 - alpha probability
    
    */

    Node** sortNodesByOutDegree = this->sortNodesByOutDegree();
    int vectorsSize = ceil(maxAlpha / alphaStep);
    float alphasInfo[6][vectorsSize];
    // Starting the starList with the randomized greedy solution
    list<Node*> starList = this->randomizedGreedy(1, 0.0);

    // Loop to initialize the elements of the alphasInfo matrix
    for(int i = 0; i < vectorsSize; i++, alphaStep += alphaStep){

        alphasInfo[0][i] = alphaStep;
        alphasInfo[1][i] = 1;
        alphasInfo[2][i] = 0;
        alphasInfo[3][i] = 0;
        alphasInfo[4][i] = 0;
        alphasInfo[5][i] = 1 / vectorsSize;

    }

}